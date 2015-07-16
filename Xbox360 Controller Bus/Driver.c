/*++

Module Name:

    driver.c

Abstract:

    This file contains the driver entry points and callbacks.

Environment:

    Kernel-mode Driver Framework

--*/

#include "Driver.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (INIT, DriverEntry)
#pragma alloc_text (PAGE, Xbox360ControllerBusEvtDeviceAdd)
#endif


NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT  DriverObject,
    _In_ PUNICODE_STRING RegistryPath
    )
{
    WDF_DRIVER_CONFIG Config;
    NTSTATUS Status;

	WDF_DRIVER_CONFIG_INIT(&Config,
                           Xbox360ControllerBusEvtDeviceAdd
                           );

	Status = WdfDriverCreate(DriverObject,
                             RegistryPath,
                             WDF_NO_OBJECT_ATTRIBUTES,
							 &Config,
                             WDF_NO_HANDLE
                             );

	if (!NT_SUCCESS(Status)) {
		Trace("WdfDriverCreate failed %X", Status);
		return Status;
    }

	return Status;
}

NTSTATUS
Xbox360ControllerBusEvtDeviceAdd(
    _In_    WDFDRIVER       Driver,
    _Inout_ PWDFDEVICE_INIT DeviceInit
    )
{
    NTSTATUS Status;

    UNREFERENCED_PARAMETER(Driver);

    PAGED_CODE();

	Status = Xbox360ControllerBusCreateDevice(DeviceInit);

	return Status;
}