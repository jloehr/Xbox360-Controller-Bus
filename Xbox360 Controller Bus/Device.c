/*++

Module Name:

    device.c - Device handling events for example driver.

Abstract:

   This file contains the device entry points and callbacks.
    
Environment:

    Kernel-mode Driver Framework

--*/

#include "Driver.h"

NTSTATUS EnumerateDevices(_In_ PDEVICE_CONTEXT DeviceContext);

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, Xbox360ControllerBusCreateDevice)
#pragma alloc_text (PAGE, EnumerateDevices)
#endif


NTSTATUS
Xbox360ControllerBusCreateDevice(
    _Inout_ PWDFDEVICE_INIT DeviceInit
    )
{
    WDF_OBJECT_ATTRIBUTES DeviceAttributes;
	WDF_CHILD_LIST_CONFIG ChildListConfig;
	PNP_BUS_INFORMATION BusInfo;
    PDEVICE_CONTEXT DeviceContext;
    WDFDEVICE Device;
    NTSTATUS Status;

    PAGED_CODE();

	WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&DeviceAttributes, DEVICE_CONTEXT);

	//Settings for Bus Drivers
	WdfDeviceInitSetDeviceType(DeviceInit, FILE_DEVICE_BUS_EXTENDER);
	WdfDeviceInitSetExclusive(DeviceInit, TRUE);

	//Child List Config
	WDF_CHILD_LIST_CONFIG_INIT(&ChildListConfig, sizeof(MY_CHILD_IDENTIFICATION_DESCRIPTION), EvtChildListCreateDevice);

	WdfFdoInitSetDefaultChildListConfig(DeviceInit, &ChildListConfig, WDF_NO_OBJECT_ATTRIBUTES);

	Status = WdfDeviceCreate(&DeviceInit, &DeviceAttributes, &Device);
	if (!NT_SUCCESS(Status))
	{
		return Status;
	}
       
    DeviceContext = DeviceGetContext(Device);

	//Init Context
	DeviceContext->Device = Device;

	//Init Queue
    Status = Xbox360ControllerBusQueueInitialize(Device);

	//Set Legacy Bus Info
	UNREFERENCED_PARAMETER(BusInfo);
	/*
	BusInfo.BusTypeGuid = GUID_DEVCLASS_TOASTER;
	BusInfo.LegacyBusType = PNPBus;
	BusInfo.BusNumber = 0;

	WdfDeviceSetBusInformationForChildren(Device, &BusInfo);
	*/

	Status = EnumerateDevices(DeviceContext);
	if (!NT_SUCCESS(Status))
	{
		return Status;
	}

    return Status;
}


NTSTATUS
EnumerateDevices(
_In_ PDEVICE_CONTEXT DeviceContext
)
{
	NTSTATUS Status;
	WDFCHILDLIST  DefaultList;
	MY_CHILD_IDENTIFICATION_DESCRIPTION ChildIdentificationDescription;

	PAGED_CODE();

	DefaultList = WdfFdoGetDefaultChildList(DeviceContext->Device);

	WDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER_INIT(&ChildIdentificationDescription.Header, sizeof(ChildIdentificationDescription));

	ChildIdentificationDescription.Id = 1;

	Status = WdfChildListAddOrUpdateChildDescriptionAsPresent(DefaultList, &ChildIdentificationDescription.Header, NULL);
	if (Status == STATUS_OBJECT_NAME_EXISTS) 
	{
		Status = STATUS_INVALID_PARAMETER;
	}

	if (!NT_SUCCESS(Status))
	{
		return Status;
	}

	return STATUS_SUCCESS;
}