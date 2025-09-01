#include "../include/anti_debug.h"
#include "../include/common.h"

BOOL CheckAntiDebug() {
    printf("[ANTI-DEBUG] Checking for debugger...\n");
    
    // Check 1: IsDebuggerPresent
    if (IsDebuggerPresent()) {
        printf("[ANTI-DEBUG] Debugger detected via IsDebuggerPresent\n");
        g_debug_detected = TRUE;
        return FALSE;
    }
    
    // Check 2: Timing check
    DWORD start = GetTickCount();
    Sleep(1000);
    DWORD end = GetTickCount();
    
    if ((end - start) < 900) {  // Si moins de 900ms, probablement débugué
        printf("[ANTI-DEBUG] Timing anomaly detected\n");
        g_debug_detected = TRUE;
        return FALSE;
    }
    
    printf("[ANTI-DEBUG] No debugger detected\n");
    return TRUE;
}
