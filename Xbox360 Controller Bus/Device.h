/*++

Module Name:

    device.h

Abstract:

    This file contains the device definitions.

Environment:

    Kernel-mode Driver Framework

--*/

#include "Public.h"

typedef struct _DEVICE_CONTEXT
{
	WDFDEVICE Device;

} DEVICE_CONTEXT, *PDEVICE_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, DeviceGetContext)

NTSTATUS
Xbox360ControllerBusCreateDevice(
    _Inout_ PWDFDEVICE_INIT DeviceInit
    );

