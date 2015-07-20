/*++

Module Name:

DeviceList.h

Abstract:

This file contains the device listings definitions.

Environment:

Kernel-mode Driver Framework

--*/
#define MAX_ID_LENGTH 255

typedef struct _MY_CHILD_IDENTIFICATION_DESCRIPTION
{
	WDF_CHILD_IDENTIFICATION_DESCRIPTION_HEADER Header;
	ULONG Id;

} MY_CHILD_IDENTIFICATION_DESCRIPTION, *PMY_CHILD_IDENTIFICATION_DESCRIPTION;

EVT_WDF_CHILD_LIST_CREATE_DEVICE EvtChildListCreateDevice;