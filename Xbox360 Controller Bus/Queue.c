/*++

Module Name:

    queue.c

Abstract:

    This file contains the queue entry points and callbacks.

Environment:

    Kernel-mode Driver Framework

--*/

#include "Driver.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (PAGE, Xbox360ControllerBusQueueInitialize)
#endif

NTSTATUS
Xbox360ControllerBusQueueInitialize(
    _In_ WDFDEVICE Device
    )
{
    WDFQUEUE Queue;
    NTSTATUS Status;
    WDF_IO_QUEUE_CONFIG QueueConfig;

    PAGED_CODE();
    
    WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(
		&QueueConfig,
        WdfIoQueueDispatchParallel
        );

	QueueConfig.EvtIoDeviceControl = Xbox360ControllerBusEvtIoDeviceControl;
	QueueConfig.EvtIoInternalDeviceControl = Xbox360ControllerBusEvtIoInternalDeviceControl;
	QueueConfig.EvtIoDefault = Xbox360ControllerBusEvtIoDefault;

    Status = WdfIoQueueCreate(
                 Device,
				 &QueueConfig,
                 WDF_NO_OBJECT_ATTRIBUTES,
                 &Queue
                 );

    if( !NT_SUCCESS(Status) ) 
	{
        Trace("WdfIoQueueCreate failed %X", Status);
        return Status;
    }

    return Status;
}

VOID
Xbox360ControllerBusEvtIoDeviceControl(
    _In_ WDFQUEUE Queue,
    _In_ WDFREQUEST Request,
    _In_ size_t OutputBufferLength,
    _In_ size_t InputBufferLength,
    _In_ ULONG IoControlCode
    )
{
    Trace("Device Control: Queue 0x%p, Request 0x%p OutputBufferLength %d InputBufferLength %d IoControlCode %d", 
                Queue, Request, (int) OutputBufferLength, (int) InputBufferLength, IoControlCode);

    WdfRequestComplete(Request, STATUS_SUCCESS);

    return;
}

VOID
Xbox360ControllerBusEvtIoInternalDeviceControl(
_In_ WDFQUEUE Queue,
_In_ WDFREQUEST Request,
_In_ size_t OutputBufferLength,
_In_ size_t InputBufferLength,
_In_ ULONG IoControlCode
)
{
	Trace("Internal Device Control: Queue 0x%p, Request 0x%p OutputBufferLength %d InputBufferLength %d IoControlCode %d",
		Queue, Request, (int)OutputBufferLength, (int)InputBufferLength, IoControlCode);

	WdfRequestComplete(Request, STATUS_SUCCESS);

	return;
}

VOID 
Xbox360ControllerBusEvtIoDefault(
_In_ WDFQUEUE   Queue,
_In_ WDFREQUEST Request
)
{
	Trace("Default Handler: Queue 0x%p, Request 0x%p",
		Queue, Request);

	WdfRequestComplete(Request, STATUS_SUCCESS);

	return;

}