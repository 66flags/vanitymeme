#ifndef LMAOBOX_LDR_IMPORT_LIST_HPP
#define LMAOBOX_LDR_IMPORT_LIST_HPP

inline std::vector< std::tuple< uintptr_t, const char *, const char * > > g_imports_list =
{
        { 0x19ea6000, "ADVAPI32.dll", "CryptEncrypt" },
        { 0x19ea6004, "ADVAPI32.dll", "CryptImportKey" },
        { 0x19ea6008, "ADVAPI32.dll", "CryptDestroyKey" },
        { 0x19ea600c, "ADVAPI32.dll", "CryptDestroyHash" },
        { 0x19ea6010, "ADVAPI32.dll", "CryptHashData" },
        { 0x19ea6014, "ADVAPI32.dll", "CryptCreateHash" },
        { 0x19ea6018, "ADVAPI32.dll", "CryptGenRandom" },
        { 0x19ea601c, "ADVAPI32.dll", "CryptGetHashParam" },
        { 0x19ea6020, "ADVAPI32.dll", "CryptReleaseContext" },
        { 0x19ea6024, "ADVAPI32.dll", "CryptAcquireContextA" },
        { 0x19ea602c, "CRYPT32.dll", "CertFindExtension" },
        { 0x19ea6030, "CRYPT32.dll", "CertAddCertificateContextToStore" },
        { 0x19ea6034, "CRYPT32.dll", "CryptDecodeObjectEx" },
        { 0x19ea6038, "CRYPT32.dll", "PFXImportCertStore" },
        { 0x19ea603c, "CRYPT32.dll", "CryptStringToBinaryA" },
        { 0x19ea6040, "CRYPT32.dll", "CertFreeCRLContext" },
        { 0x19ea6044, "CRYPT32.dll", "CertFindCertificateInStore" },
        { 0x19ea6048, "CRYPT32.dll", "CertGetNameStringA" },
        { 0x19ea604c, "CRYPT32.dll", "CertCloseStore" },
        { 0x19ea6050, "CRYPT32.dll", "CertOpenStore" },
        { 0x19ea6054, "CRYPT32.dll", "CertFreeCertificateChain" },
        { 0x19ea6058, "CRYPT32.dll", "CertGetCertificateChain" },
        { 0x19ea605c, "CRYPT32.dll", "CertEnumCertificatesInStore" },
        { 0x19ea6060, "CRYPT32.dll", "CertFreeCertificateChainEngine" },
        { 0x19ea6064, "CRYPT32.dll", "CertCreateCertificateChainEngine" },
        { 0x19ea6068, "CRYPT32.dll", "CryptQueryObject" },
        { 0x19ea6070, "GDI32.dll", "CreateRectRgn" },
        { 0x19ea6074, "GDI32.dll", "GetDeviceCaps" },
        { 0x19ea6078, "GDI32.dll", "DeleteObject" },
        { 0x19ea6080, "IMM32.DLL", "ImmReleaseContext" },
        { 0x19ea6084, "IMM32.DLL", "ImmSetCompositionWindow" },
        { 0x19ea6088, "IMM32.DLL", "ImmGetContext" },
        { 0x19ea6090, "KERNEL32.DLL", "HeapFree" },
        { 0x19ea6094, "ntdll.dll", "RtlSizeHeap" },
        { 0x19ea6098, "KERNEL32.DLL", "GetProcessHeap" },
        { 0x19ea609c, "KERNEL32.DLL", "InitializeCriticalSectionEx" },
        { 0x19ea60a0, "ntdll.dll", "RtlDeleteCriticalSection" },
        { 0x19ea60a4, "KERNEL32.DLL", "GetCurrentProcess" },
        { 0x19ea60a8, "KERNEL32.DLL", "CreateThread" },
        { 0x19ea60ac, "KERNEL32.DLL", "GetCurrentThread" },
        { 0x19ea60b0, "KERNEL32.DLL", "GetThreadContext" },
        { 0x19ea60b4, "KERNEL32.DLL", "DisableThreadLibraryCalls" },
        { 0x19ea60b8, "KERNEL32.DLL", "LocalFree" },
        { 0x19ea60bc, "KERNEL32.DLL", "FormatMessageW" },
        { 0x19ea60c0, "ntdll.dll", "RtlReAllocateHeap" },
        { 0x19ea60c4, "ntdll.dll", "RtlAllocateHeap" },
        { 0x19ea60c8, "KERNEL32.DLL", "GetLastError" },
        { 0x19ea60cc, "KERNEL32.DLL", "RaiseException" },
        { 0x19ea60d0, "KERNEL32.DLL", "CloseHandle" },
        { 0x19ea60d4, "ntdll.dll", "RtlDecodePointer" },
        { 0x19ea60d8, "KERNEL32.DLL", "CheckRemoteDebuggerPresent" },
        { 0x19ea60dc, "KERNEL32.DLL", "IsDebuggerPresent" },
        { 0x19ea60e0, "KERNEL32.DLL", "CreateDirectoryA" },
        { 0x19ea60e4, "KERNEL32.DLL", "WriteConsoleW" },
        { 0x19ea60e8, "KERNEL32.DLL", "CreatePipe" },
        { 0x19ea60ec, "KERNEL32.DLL", "GetExitCodeProcess" },
        { 0x19ea60f0, "KERNEL32.DLL", "WaitForSingleObject" },
        { 0x19ea60f4, "KERNEL32.DLL", "SetEnvironmentVariableW" },
        { 0x19ea60f8, "KERNEL32.DLL", "FreeEnvironmentStringsW" },
        { 0x19ea60fc, "KERNEL32.DLL", "GetEnvironmentStringsW" },
        { 0x19ea6100, "KERNEL32.DLL", "GetCommandLineW" },
        { 0x19ea6104, "KERNEL32.DLL", "GetCommandLineA" },
        { 0x19ea6108, "KERNEL32.DLL", "GetOEMCP" },
        { 0x19ea610c, "KERNEL32.DLL", "GetACP" },
        { 0x19ea6110, "KERNEL32.DLL", "IsValidCodePage" },
        { 0x19ea6114, "KERNEL32.DLL", "DeleteFileW" },
        { 0x19ea6118, "KERNEL32.DLL", "LoadLibraryA" },
        { 0x19ea611c, "KERNEL32.DLL", "FlushFileBuffers" },
        { 0x19ea6120, "KERNEL32.DLL", "GetTimeZoneInformation" },
        { 0x19ea6124, "KERNEL32.DLL", "EnumSystemLocalesW" },
        { 0x19ea6128, "KERNEL32.DLL", "QueryPerformanceFrequency" },
        { 0x19ea612c, "KERNEL32.DLL", "QueryPerformanceCounter" },
        { 0x19ea6130, "ntdll.dll", "VerSetConditionMask" },
        { 0x19ea6134, "KERNEL32.DLL", "WideCharToMultiByte" },
        { 0x19ea6138, "KERNEL32.DLL", "GetUserDefaultLCID" },
        { 0x19ea613c, "KERNEL32.DLL", "IsValidLocale" },
        { 0x19ea6140, "KERNEL32.DLL", "GetLocaleInfoW" },
        { 0x19ea6144, "KERNEL32.DLL", "LCMapStringW" },
        { 0x19ea6148, "KERNEL32.DLL", "CompareStringW" },
        { 0x19ea614c, "KERNEL32.DLL", "GetTimeFormatW" },
        { 0x19ea6150, "KERNEL32.DLL", "GetDateFormatW" },
        { 0x19ea6154, "KERNEL32.DLL", "CreateProcessW" },
        { 0x19ea6158, "KERNEL32.DLL", "DuplicateHandle" },
        { 0x19ea615c, "KERNEL32.DLL", "GetConsoleOutputCP" },
        { 0x19ea6160, "KERNEL32.DLL", "WriteFile" },
        { 0x19ea6164, "KERNEL32.DLL", "ReadConsoleW" },
        { 0x19ea6168, "KERNEL32.DLL", "GetConsoleMode" },
        { 0x19ea616c, "KERNEL32.DLL", "GetModuleFileNameW" },
        { 0x19ea6170, "KERNEL32.DLL", "SetFilePointerEx" },
        { 0x19ea6174, "KERNEL32.DLL", "FileTimeToSystemTime" },
        { 0x19ea6178, "KERNEL32.DLL", "SystemTimeToTzSpecificLocalTime" },
        { 0x19ea617c, "KERNEL32.DLL", "GetDriveTypeW" },
        { 0x19ea6180, "KERNEL32.DLL", "GetModuleHandleExW" },
        { 0x19ea6184, "KERNEL32.DLL", "FreeLibraryAndExitThread" },
        { 0x19ea6188, "ntdll.dll", "RtlExitUserThread" },
        { 0x19ea618c, "KERNEL32.DLL", "LoadLibraryExW" },
        { 0x19ea6190, "KERNEL32.DLL", "TlsFree" },
        { 0x19ea6194, "KERNEL32.DLL", "TlsSetValue" },
        { 0x19ea6198, "KERNEL32.DLL", "TlsGetValue" },
        { 0x19ea619c, "KERNEL32.DLL", "TlsAlloc" },
        { 0x19ea61a0, "ntdll.dll", "RtlInterlockedFlushSList" },
        { 0x19ea61a4, "ntdll.dll", "RtlInterlockedPushEntrySList" },
        { 0x19ea61a8, "KERNEL32.DLL", "RtlUnwind" },
        { 0x19ea61ac, "KERNEL32.DLL", "OutputDebugStringW" },
        { 0x19ea61b0, "KERNEL32.DLL", "LoadLibraryExA" },
        { 0x19ea61b4, "KERNEL32.DLL", "GetModuleFileNameA" },
        { 0x19ea61b8, "KERNEL32.DLL", "FlushInstructionCache" },
        { 0x19ea61bc, "KERNEL32.DLL", "GetStartupInfoW" },
        { 0x19ea61c0, "ntdll.dll", "RtlInitializeSListHead" },
        { 0x19ea61c4, "KERNEL32.DLL", "CreateEventW" },
        { 0x19ea61c8, "KERNEL32.DLL", "ResetEvent" },
        { 0x19ea61cc, "KERNEL32.DLL", "SetEvent" },
        { 0x19ea61d0, "KERNEL32.DLL", "InitializeCriticalSectionAndSpinCount" },
        { 0x19ea61d4, "KERNEL32.DLL", "MultiByteToWideChar" },
        { 0x19ea61d8, "KERNEL32.DLL", "GlobalFree" },
        { 0x19ea61dc, "KERNEL32.DLL", "GlobalLock" },
        { 0x19ea61e0, "KERNEL32.DLL", "GlobalUnlock" },
        { 0x19ea61e4, "KERNEL32.DLL", "GlobalAlloc" },
        { 0x19ea61e8, "KERNEL32.DLL", "VirtualProtect" },
        { 0x19ea61ec, "KERNEL32.DLL", "ExitProcess" },
        { 0x19ea61f0, "KERNEL32.DLL", "Beep" },
        { 0x19ea61f4, "KERNEL32.DLL", "WriteConsoleA" },
        { 0x19ea61f8, "KERNEL32.DLL", "SetConsoleMode" },
        { 0x19ea61fc, "KERNEL32.DLL", "AttachConsole" },
        { 0x19ea6200, "KERNEL32.DLL", "FreeConsole" },
        { 0x19ea6204, "KERNEL32.DLL", "AllocConsole" },
        { 0x19ea6208, "KERNEL32.DLL", "GetCurrentProcessId" },
        { 0x19ea620c, "KERNEL32.DLL", "SetStdHandle" },
        { 0x19ea6210, "KERNEL32.DLL", "GetStdHandle" },
        { 0x19ea6214, "KERNEL32.DLL", "GetModuleHandleW" },
        { 0x19ea6218, "KERNEL32.DLL", "IsProcessorFeaturePresent" },
        { 0x19ea621c, "KERNEL32.DLL", "TerminateProcess" },
        { 0x19ea6220, "KERNEL32.DLL", "GetTickCount64" },
        { 0x19ea6224, "KERNEL32.DLL", "Sleep" },
        { 0x19ea6228, "KERNEL32.DLL", "GetProcAddress" },
        { 0x19ea622c, "KERNEL32.DLL", "SetEndOfFile" },
        { 0x19ea6230, "KERNEL32.DLL", "SetUnhandledExceptionFilter" },
        { 0x19ea6234, "KERNEL32.DLL", "UnhandledExceptionFilter" },
        { 0x19ea6238, "KERNEL32.DLL", "GetCPInfo" },
        { 0x19ea623c, "KERNEL32.DLL", "CompareStringEx" },
        { 0x19ea6240, "KERNEL32.DLL", "GetStringTypeW" },
        { 0x19ea6244, "KERNEL32.DLL", "LCMapStringEx" },
        { 0x19ea6248, "KERNEL32.DLL", "CreateFileA" },
        { 0x19ea624c, "KERNEL32.DLL", "GetFileSizeEx" },
        { 0x19ea6250, "KERNEL32.DLL", "ReadFile" },
        { 0x19ea6254, "KERNEL32.DLL", "MapViewOfFile" },
        { 0x19ea6258, "KERNEL32.DLL", "UnmapViewOfFile" },
        { 0x19ea625c, "KERNEL32.DLL", "CreateFileMappingA" },
        { 0x19ea6260, "KERNEL32.DLL", "GetTickCount" },
        { 0x19ea6264, "ntdll.dll", "RtlEnterCriticalSection" },
        { 0x19ea6268, "ntdll.dll", "RtlLeaveCriticalSection" },
        { 0x19ea626c, "KERNEL32.DLL", "SleepEx" },
        { 0x19ea6270, "KERNEL32.DLL", "GetSystemDirectoryA" },
        { 0x19ea6274, "KERNEL32.DLL", "FreeLibrary" },
        { 0x19ea6278, "KERNEL32.DLL", "GetEnvironmentVariableA" },
        { 0x19ea627c, "KERNEL32.DLL", "SetLastError" },
        { 0x19ea6280, "KERNEL32.DLL", "MoveFileExA" },
        { 0x19ea6284, "KERNEL32.DLL", "GetFileType" },
        { 0x19ea6288, "KERNEL32.DLL", "PeekNamedPipe" },
        { 0x19ea628c, "KERNEL32.DLL", "WaitForMultipleObjects" },
        { 0x19ea6290, "KERNEL32.DLL", "WaitForSingleObjectEx" },
        { 0x19ea6294, "KERNEL32.DLL", "VerifyVersionInfoW" },
        { 0x19ea6298, "KERNEL32.DLL", "GetCurrentThreadId" },
        { 0x19ea629c, "ntdll.dll", "RtlInitializeConditionVariable" },
        { 0x19ea62a0, "ntdll.dll", "RtlReleaseSRWLockExclusive" },
        { 0x19ea62a4, "ntdll.dll", "RtlAcquireSRWLockExclusive" },
        { 0x19ea62a8, "ntdll.dll", "RtlTryAcquireSRWLockExclusive" },
        { 0x19ea62ac, "KERNEL32.DLL", "FormatMessageA" },
        { 0x19ea62b0, "KERNEL32.DLL", "GetLocaleInfoEx" },
        { 0x19ea62b4, "KERNEL32.DLL", "GetCurrentDirectoryW" },
        { 0x19ea62b8, "KERNEL32.DLL", "CreateDirectoryW" },
        { 0x19ea62bc, "KERNEL32.DLL", "CreateFileW" },
        { 0x19ea62c0, "KERNEL32.DLL", "FindClose" },
        { 0x19ea62c4, "KERNEL32.DLL", "FindFirstFileW" },
        { 0x19ea62c8, "KERNEL32.DLL", "FindFirstFileExW" },
        { 0x19ea62cc, "KERNEL32.DLL", "FindNextFileW" },
        { 0x19ea62d0, "KERNEL32.DLL", "GetFileAttributesExW" },
        { 0x19ea62d4, "KERNEL32.DLL", "GetFileInformationByHandle" },
        { 0x19ea62d8, "KERNEL32.DLL", "GetFullPathNameW" },
        { 0x19ea62dc, "KERNEL32.DLL", "GetTempPathW" },
        { 0x19ea62e0, "KERNEL32.DLL", "AreFileApisANSI" },
        { 0x19ea62e4, "KERNEL32.DLL", "MoveFileExW" },
        { 0x19ea62e8, "KERNEL32.DLL", "GetFileInformationByHandleEx" },
        { 0x19ea62ec, "KERNEL32.DLL", "GetSystemTimeAsFileTime" },
        { 0x19ea62f0, "ntdll.dll", "RtlEncodePointer" },
        { 0x19ea62f4, "KERNEL32.DLL", "GetModuleHandleA" },
        { 0x19ea62fc, "SHELL32.dll", "ShellExecuteA" },
        { 0x19ea6304, "SHLWAPI.dll", "StrStrIA" },
        { 0x19ea630c, "USER32.dll", "CallWindowProcW" },
        { 0x19ea6310, "USER32.dll", "GetKeyState" },
        { 0x19ea6314, "USER32.dll", "GetAsyncKeyState" },
        { 0x19ea6318, "USER32.dll", "SetClipboardData" },
        { 0x19ea631c, "USER32.dll", "GetClipboardData" },
        { 0x19ea6320, "USER32.dll", "EmptyClipboard" },
        { 0x19ea6324, "USER32.dll", "TrackMouseEvent" },
        { 0x19ea6328, "USER32.dll", "IsChild" },
        { 0x19ea632c, "USER32.dll", "GetCapture" },
        { 0x19ea6330, "USER32.dll", "SetCapture" },
        { 0x19ea6334, "USER32.dll", "ReleaseCapture" },
        { 0x19ea6338, "USER32.dll", "GetForegroundWindow" },
        { 0x19ea633c, "USER32.dll", "GetDC" },
        { 0x19ea6340, "USER32.dll", "ReleaseDC" },
        { 0x19ea6344, "USER32.dll", "GetClientRect" },
        { 0x19ea6348, "USER32.dll", "SetCursorPos" },
        { 0x19ea634c, "USER32.dll", "SetCursor" },
        { 0x19ea6350, "USER32.dll", "GetCursorPos" },
        { 0x19ea6354, "USER32.dll", "ClientToScreen" },
        { 0x19ea6358, "USER32.dll", "ScreenToClient" },
        { 0x19ea635c, "USER32.dll", "LoadCursorW" },
        { 0x19ea6360, "USER32.dll", "MonitorFromWindow" },
        { 0x19ea6364, "USER32.dll", "SetProcessDPIAware" },
        { 0x19ea6368, "USER32.dll", "OpenClipboard" },
        { 0x19ea636c, "USER32.dll", "SetWindowLongW" },
        { 0x19ea6370, "USER32.dll", "CloseClipboard" },
        { 0x19ea6378, "WS2_32.dll", "WSACleanup" },
        { 0x19ea637c, "WS2_32.dll", "WSAStartup" },
        { 0x19ea6380, "WS2_32.dll", "socket" },
        { 0x19ea6384, "WS2_32.dll", "setsockopt" },
        { 0x19ea6388, "WS2_32.dll", "send" },
        { 0x19ea638c, "WS2_32.dll", "WSACloseEvent" },
        { 0x19ea6390, "WS2_32.dll", "listen" },
        { 0x19ea6394, "WS2_32.dll", "inet_addr" },
        { 0x19ea6398, "WS2_32.dll", "recv" },
        { 0x19ea639c, "WS2_32.dll", "htonl" },
        { 0x19ea63a0, "WS2_32.dll", "connect" },
        { 0x19ea63a4, "WS2_32.dll", "closesocket" },
        { 0x19ea63a8, "WS2_32.dll", "bind" },
        { 0x19ea63ac, "WS2_32.dll", "WSACreateEvent" },
        { 0x19ea63b0, "WS2_32.dll", "WSAEnumNetworkEvents" },
        { 0x19ea63b4, "WS2_32.dll", "accept" },
        { 0x19ea63b8, "WS2_32.dll", "WSAEventSelect" },
        { 0x19ea63bc, "WS2_32.dll", "WSAResetEvent" },
        { 0x19ea63c0, "WS2_32.dll", "WSAWaitForMultipleEvents" },
        { 0x19ea63c4, "WS2_32.dll", "WSAGetLastError" },
        { 0x19ea63c8, "WS2_32.dll", "__WSAFDIsSet" },
        { 0x19ea63cc, "WS2_32.dll", "select" },
        { 0x19ea63d0, "WS2_32.dll", "WSASetLastError" },
        { 0x19ea63d4, "WS2_32.dll", "getpeername" },
        { 0x19ea63d8, "WS2_32.dll", "getsockname" },
        { 0x19ea63dc, "WS2_32.dll", "getsockopt" },
        { 0x19ea63e0, "WS2_32.dll", "htons" },
        { 0x19ea63e4, "WS2_32.dll", "WSAIoctl" },
        { 0x19ea63e8, "WS2_32.dll", "inet_pton" },
        { 0x19ea63ec, "WS2_32.dll", "htonl" },
        { 0x19ea63f0, "WS2_32.dll", "recvfrom" },
        { 0x19ea63f4, "WS2_32.dll", "sendto" },
        { 0x19ea63f8, "WS2_32.dll", "getaddrinfo" },
        { 0x19ea63fc, "WS2_32.dll", "FreeAddrInfoW" },
        { 0x19ea6400, "WS2_32.dll", "ioctlsocket" },
        { 0x19ea6404, "WS2_32.dll", "gethostname" },
        { 0x19ea6408, "WS2_32.dll", "htons" },
        { 0x19ea6410, "d3dx9_43.dll", "D3DXCreateTextureFromFileInMemory" },
        { 0x19ea6418, "dwmapi.dll", "DwmEnableBlurBehindWindow" },
        { 0x19ea641c, "dwmapi.dll", "DwmGetColorizationColor" },
        { 0x19ea6420, "dwmapi.dll", "DwmIsCompositionEnabled" },
};

#endif//LMAOBOX_LDR_IMPORT_LIST_HPP
