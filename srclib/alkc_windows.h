#include <windows.h>

#ifndef ALKC_COREINITD
#include "../core/alkclib.h"
#endif

// Structure pour gérer la fenêtre
typedef struct STDWD {
    HWND hwnd; // Handle de la fenêtre
    MSG msg;
    UINT uMsg;
    WPARAM wParam;
    LPARAM lParam;
} STDWD;

// Prototype de la fonction de traitement des messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

STDWD INITWD(int dx, int dy) {
    printf("init!\n");
    STDWD wd;
    const char CLASS_NAME[] = "Sample Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc; 
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    if (!RegisterClass(&wc)) {
        wd.hwnd = NULL; 
        printf("Class registration failed!\n");
        return wd;
    }

    wd.hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Hello, Windows!",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        dx, dy,
        NULL,
        NULL,
        wc.hInstance,
        NULL
    );

    if (wd.hwnd == NULL) {
        printf("Window creation failed!\n"); 
        wd.hwnd = NULL;
    }

    return wd;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        printf("kcé!\n");
        PostQuitMessage(0); 
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void OPENWD(STDWD wd) {
    if (wd.hwnd != NULL) {
        printf("aaaaaaa!\n");
        ShowWindow(wd.hwnd, SW_SHOW); 
        UpdateWindow(wd.hwnd);        
    }
}

void EXTRACTEVENTS(STDWD wd) {
    if (wd.hwnd != NULL) {
        WindowProc(wd.hwnd, wd.uMsg, wd.wParam, wd.lParam);
    }else{
        printf("samerlapute!\n");
    }
}

// Macro pour définir les paquets d'applications
ALKCDEFINE_WDPACKAGE(STDWD, INITWD, OPENWD, EXTRACTEVENTS);
ALKCDEFINE_EVENTMAPPING(MSG, WPARAM, 60);
