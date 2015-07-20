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
_In_ PWDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER IdentificationDescriptionHeader,
_In_ PWDFDEVICE_INIT ChildInit
)
{
	NTSTATUS Status = STATUS_SUCCESS;
	WDFDEVICE Child;
	PMY_CHILD_IDENTIFICATION_DESCRIPTION IdentificationDescription;

	DECLARE_CONST_UNICODE_STRING(HardwareID, L"X360CB\\VirtualController\0");
	//DECLARE_CONST_UNICODE_STRING(DeviceID, L"XUSBBusTest\\Child\0");
	DECLARE_CONST_UNICODE_STRING(CompatibleID, L"USB\\MS_COMP_XUSB10\0"); 
	DECLARE_UNICODE_STRING_SIZE(InstanceID, MAX_ID_LENGTH);
	DECLARE_CONST_UNICODE_STRING(DeviceLocationDescription, L"Software Emulated XBox360 Controller\0");
	DECLARE_CONST_UNICODE_STRING(DeviceLocation, L"VirutalXBox360ControllerBus\0");

	UNREFERENCED_PARAMETER(ChildList);

	IdentificationDescription = CONTAINING_RECORD(IdentificationDescriptionHeader, MY_CHILD_IDENTIFICATION_DESCRIPTION, Header);

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
	
	Status = RtlUnicodeStringPrintf(&InstanceID, L"%02d", IdentificationDescription->Id);
	if (!NT_SUCCESS(Status)) 
	{
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
