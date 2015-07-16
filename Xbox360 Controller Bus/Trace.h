/*++

Module Name:

    Trace.h

Abstract:

    Header file for the debug tracing related function defintions and macros.

Environment:

    Kernel mode

--*/
#ifndef _TRACE_H_
#define _TRACE_H_

#include <ntddk.h>

#define NTSTRSAFE_LIB
#include <ntstrsafe.h>

VOID
Trace(
_In_ PCCHAR  DebugMessage,
...
);

#endif