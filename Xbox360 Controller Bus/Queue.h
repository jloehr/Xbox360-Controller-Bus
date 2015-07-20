/*++

Module Name:

    queue.h

Abstract:

    This file contains the queue definitions.

Environment:

    Kernel-mode Driver Framework

--*/

NTSTATUS
Xbox360ControllerBusQueueInitialize(
    _In_ WDFDEVICE hDevice
    );

EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL Xbox360ControllerBusEvtIoDeviceControl;
EVT_WDF_IO_QUEUE_IO_INTERNAL_DEVICE_CONTROL Xbox360ControllerBusEvtIoInternalDeviceControl;
EVT_WDF_IO_QUEUE_IO_DEFAULT Xbox360ControllerBusEvtIoDefault;
