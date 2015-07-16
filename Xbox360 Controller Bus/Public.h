/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that app can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_Xbox360ControllerBus,
    0x7c25595d,0x7acd,0x4038,0x90,0xb7,0xa3,0x7c,0x83,0x3e,0xce,0x8b);
// {7c25595d-7acd-4038-90b7-a37c833ece8b}
