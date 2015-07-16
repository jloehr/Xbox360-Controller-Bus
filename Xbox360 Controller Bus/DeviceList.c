/*++

Module Name:

DeviceList.c

Abstract:

Handles the functions for the child PDOs

Environment:

Kernel-mode Driver Framework

--*/

#include "Driver.h"


NTSTATUS
EvtChildListCreateDevice(
_In_ WDFCHILDLIST ChildList,
_In_ PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER IdentificationDescription,
_In_ PWDFDEVICE_INIT ChildInit
)
{
	NTSTATUS Status = STATUS_SUCCESS;
	WDFDEVICE Child;

	DECLARE_CONST_UNICODE_STRING(HardwareID, L"XUSBBusTest\\Child\0");
	//DECLARE_CONST_UNICODE_STRING(DeviceID, L"XUSBBusTest\\Child\0");
	DECLARE_CONST_UNICODE_STRING(CompatibleID, L"XUSBBusTest\\Child\\Compatible\0");
	DECLARE_CONST_UNICODE_STRING(InstanceID, L"01\0");
	DECLARE_CONST_UNICODE_STRING(DeviceLocationDescription, L"XUSBTest\0");
	DECLARE_CONST_UNICODE_STRING(DeviceLocation, L"XUSBTestBus\0");

	UNREFERENCED_PARAMETER(ChildList);
	UNREFERENCED_PARAMETER(IdentificationDescription);

	WdfDeviceInitSetDeviceType(ChildInit, FILE_DEVICE_BUS_EXTENDER);

	Status = WdfPdoInitAssignDeviceID(ChildInit, &HardwareID);
	if (!NT_SUCCESS(Status))
	{
		return Status;
	}

	Status = WdfPdoInitAddHardwareID(ChildInit, &HardwareID);
	if (!NT_SUCCESS(Status))
	{
		return Status;
	}

	Status = WdfPdoInitAddCompatibleID(ChildInit, &CompatibleID);
	if (!NT_SUCCESS(Status))
	{
		return Status;
	}

	Status = WdfPdoInitAssignInstanceID(ChildInit, &InstanceID);
	if (!NT_SUCCESS(Status))
	{
		return Status;
	}

	// Device Text
	Status = WdfPdoInitAddDeviceText(ChildInit, &DeviceLocationDescription, &DeviceLocation, 0x409);
	if (!NT_SUCCESS(Status))
	{
		return Status;
	}

	WdfPdoInitSetDefaultLocale(ChildInit, 0x409);

	// Create Device
	Status = WdfDeviceCreate(&ChildInit, NULL, &Child);
	if (!NT_SUCCESS(Status))
	{
		return Status;
	}


	return Status;
}
