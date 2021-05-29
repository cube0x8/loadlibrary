#include <sys/types.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <search.h>
#include <assert.h>
#include <unistd.h>

#include "winnt_types.h"
#include "pe_linker.h"
#include "ntoskernel.h"
#include "log.h"
#include "winexports.h"
#include "util.h"
#include "winstrings.h"

static PVOID WINAPI CreateThreadpoolTimer(PVOID pfnti, PVOID pv, PVOID pcbe)
{
    NOP_FILL();
    // DebugLog("%p, %p, %p", pfnti, pv, pcbe);
    return (PVOID) 'POOL';
}

static VOID WINAPI InitializeSRWLock(PVOID SRWLock)
{
    NOP_FILL();
    DebugLog("%p", SRWLock);
}

static VOID WINAPI SetThreadpoolTimer(PVOID pti, PVOID pftDueTime, DWORD msPeriod, DWORD msWindowLength)
{
    NOP_FILL();
    DebugLog("%p, %p, %u, %u", pti, pftDueTime, msPeriod, msWindowLength);
}

static VOID WINAPI WaitForThreadpoolTimerCallbacks(PVOID pti, BOOL fCancelPendingCallbacks)
{
    NOP_FILL();
    DebugLog("%p, %u", pti, fCancelPendingCallbacks);
}

static VOID WINAPI CloseThreadpoolTimer(PVOID pti)
{
    NOP_FILL();
    DebugLog("%p", pti);
}

static LONG InterlockedDecrement(PULONG Addend)
{
    NOP_FILL();
    DebugLog("%p", Addend);
    return --*Addend;
}

static LONG InterlockedIncrement(PULONG Addend)
{
    NOP_FILL();
    DebugLog("%p", Addend);
    return ++*Addend;
}

static LONG InterlockedCompareExchange(PULONG Destination, LONG Exchange, LONG Comparand)
{
    NOP_FILL();
    DebugLog("%p", Destination);
    if (*Destination == Comparand) {
        *Destination = Exchange;
    }
    return *Destination;
}

static HANDLE WINAPI CreateSemaphoreW(PVOID lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, PWCHAR lpName)
{
    NOP_FILL();
    char *name;
#ifndef NDEBUG
    name = CreateAnsiFromWide(lpName);
#else
    name = NULL;
#endif
    DebugLog("%p, %u, %u, %p [%s]", lpSemaphoreAttributes, lInitialCount, lMaximumCount, lpName, name);
    free(name);
    return (HANDLE) 'SEMA';
}

static HANDLE WINAPI GetCurrentProcess(VOID)
{
    NOP_FILL();
    return (HANDLE) -1;
}

static HANDLE WINAPI GetCurrentThread(VOID)
{
    NOP_FILL();
    return (HANDLE) -1;
}

static DWORD WINAPI GetCurrentThreadId(VOID)
{
    NOP_FILL();
    return getpid();
}

static DWORD WINAPI GetCurrentProcessId(VOID)
{
    NOP_FILL();
    return getpid();
}

static BOOL WINAPI RegisterWaitForSingleObject(PHANDLE phNewWaitObject, HANDLE hObject, PVOID Callback, PVOID Context, ULONG dwMilliseconds, ULONG dwFlags)
{
    NOP_FILL();
    DebugLog("");
    return TRUE;
}

static VOID WINAPI AcquireSRWLockExclusive(PVOID SRWLock)
{
    NOP_FILL();
    DebugLog("%p", SRWLock);
}

static VOID WINAPI AcquireSRWLockShared(PVOID SRWLock)
{
    NOP_FILL();
    DebugLog("%p", SRWLock);
}

static VOID WINAPI ReleaseSRWLockExclusive(PVOID SRWLock)
{
    NOP_FILL();
    DebugLog("%p", SRWLock);
}

static VOID WINAPI ReleaseSRWLockShared(PVOID SRWLock)
{
    NOP_FILL();
    DebugLog("%p", SRWLock);
}

static HANDLE WINAPI CreateMutexW(PVOID lpMutexAttributes, BOOL bInitialOwner, PWCHAR lpName)
{
    NOP_FILL();
    DebugLog("%p, %u, %p");
    return INVALID_HANDLE_VALUE;
}

static DWORD WINAPI WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds)
{
    NOP_FILL();
    DebugLog("%p, %u", hHandle, dwMilliseconds);
    return -1;
}

static ULONG WINAPI LsaNtStatusToWinError(NTSTATUS Status)
{
    NOP_FILL();
    DebugLog("%#x", Status);
    return Status;
}

static BOOL WINAPI CreateTimerQueueTimer(PHANDLE phNewTimer,
                                         HANDLE TimerQueue,
                                         PVOID Callback,
                                         PVOID Parameter,
                                         DWORD DueTime,
                                         DWORD Period,
                                         ULONG Flags)
{
    NOP_FILL();
    DebugLog("");
    return TRUE;
}

static BOOL WINAPI GetThreadTimes(HANDLE hThread,
                                  PFILETIME lpCreationTime,
                                  PFILETIME lpExitTime,
                                  PFILETIME lpKernelTime,
                                  PFILETIME lpUserTime)
{
    NOP_FILL();
    DebugLog("");
    return TRUE;
}

static ULONG WINAPI RtlNtStatusToDosError(NTSTATUS Status)
{
    NOP_FILL();
    DebugLog("%#x", Status);
    return 5;
}

static BOOL WINAPI SetThreadToken(PHANDLE Thread, HANDLE Token)
{
    NOP_FILL();
    DebugLog("");
    return FALSE;
}

static BOOL WINAPI ProcessIdToSessionId(DWORD dwProcessId, DWORD *pSessionId)
{
    NOP_FILL();
    DebugLog("");
    return FALSE;
}

DECLARE_CRT_EXPORT("RtlNtStatusToDosError", RtlNtStatusToDosError);
DECLARE_CRT_EXPORT("GetThreadTimes", GetThreadTimes);
DECLARE_CRT_EXPORT("GetCurrentThread", GetCurrentThread);
DECLARE_CRT_EXPORT("CreateTimerQueueTimer", CreateTimerQueueTimer);
DECLARE_CRT_EXPORT("RegisterWaitForSingleObject", RegisterWaitForSingleObject);
DECLARE_CRT_EXPORT("WaitForSingleObject", WaitForSingleObject);
DECLARE_CRT_EXPORT("GetCurrentProcess", GetCurrentProcess);
DECLARE_CRT_EXPORT("LsaNtStatusToWinError", LsaNtStatusToWinError);
DECLARE_CRT_EXPORT("SetThreadToken", SetThreadToken);
DECLARE_CRT_EXPORT("InterlockedDecrement", InterlockedDecrement);
DECLARE_CRT_EXPORT("InterlockedIncrement", InterlockedIncrement);
DECLARE_CRT_EXPORT("InterlockedCompareExchange", InterlockedCompareExchange);
DECLARE_CRT_EXPORT("CreateSemaphoreW", CreateSemaphoreW);
DECLARE_CRT_EXPORT("AcquireSRWLockExclusive", AcquireSRWLockExclusive);
DECLARE_CRT_EXPORT("AcquireSRWLockShared", AcquireSRWLockShared);
DECLARE_CRT_EXPORT("InitializeSRWLock", InitializeSRWLock);
DECLARE_CRT_EXPORT("ReleaseSRWLockExclusive", ReleaseSRWLockExclusive);
DECLARE_CRT_EXPORT("ReleaseSRWLockShared", ReleaseSRWLockShared);
DECLARE_CRT_EXPORT("SetThreadpoolTimer", SetThreadpoolTimer);
DECLARE_CRT_EXPORT("WaitForThreadpoolTimerCallbacks", WaitForThreadpoolTimerCallbacks);
DECLARE_CRT_EXPORT("GetCurrentThreadId", GetCurrentThreadId);
DECLARE_CRT_EXPORT("GetCurrentProcessId", GetCurrentProcessId);
DECLARE_CRT_EXPORT("ProcessIdToSessionId", ProcessIdToSessionId);
