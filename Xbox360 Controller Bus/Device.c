/*++

Module Name:

    device.c - Device handling events for example driver.

Abstract:

   This file contains the device entry points and callbacks.
    
Environment:

    Kernel-mode Driver Framework

--*/

#include "Driver.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, Xbox360ControllerBusCreateDevice)
#endif


NTSTATUS
Xbox360ControllerBusCreateDevice(
    _Inout_ PWDFDEVICE_INIT DeviceInit
    )
{
    WDF_OBJECT_ATTRIBUTES DeviceAttributes;
    PDEVICE_CONTEXT DeviceContext;
    WDFDEVICE Device;
    NTSTATUS Status;

    PAGED_CODE();

	WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&DeviceAttributes, DEVICE_CONTEXT);

	Status = WdfDeviceCreate(&DeviceInit, &DeviceAttributes, &Device);
	if (!NT_SUCCESS(Status))
	{
		return Status;
	}
       
    DeviceContext = DeviceGetContext(Device);

	//Init Context
    DeviceContext->Foo = 0;

	//Init Queue
    Status = Xbox360ControllerBusQueueInitialize(Device);

    return Status;
}


