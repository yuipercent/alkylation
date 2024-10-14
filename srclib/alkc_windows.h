#include <windows.h>

#ifndef ALKC_COREINITD
#include "../core/alkclib.h"
#endif

typedef struct WDHOLDER {
    HINSTANCE hInstance;  // Handle to the application instance
    HWND hWnd;            // Handle to the window
    MSG msg;              // Message/event structure
    int screen;           // Placeholder, can be removed or repurposed
} WDHOLDER;

// Window Procedure to handle events (similar to XEvent)
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

extern inline WDHOLDER* INITWD(int dx, int dy) {
    WDHOLDER* wd = (WDHOLDER*)malloc(sizeof(WDHOLDER));

    wd->hInstance = GetModuleHandle(NULL);

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;          // Callback function for window events
    wc.hInstance = wd->hInstance;
    wc.lpszClassName = "SampleWindowClass";

    RegisterClass(&wc);

    wd->hWnd = CreateWindowEx(
        0,                              // Optional window styles
        "SampleWindowClass",            // Window class name
        "My Windows Application",       // Window title
        WS_OVERLAPPEDWINDOW,            // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, dx, dy,  // Position and size
        NULL,                           // Parent window (if any)
        NULL,                           // Menu (if any)
        wd->hInstance,                  // Handle to application instance
        NULL                            // Additional application data
    );

    if (wd->hWnd == NULL) {
        free(wd);
        return NULL;
    }

    return wd;
}

extern inline void OPENWD(WDHOLDER* wd) {
    ShowWindow(wd->hWnd, SW_SHOW);
    UpdateWindow(wd->hWnd);  // Forces a repaint event
    return;
}

extern inline void EXTRACTEVENTS(WDHOLDER* wd) {
    // Check if there is a message and dispatch it
    if (GetMessage(&wd->msg, NULL, 0, 0)) {
        TranslateMessage(&wd->msg);
        DispatchMessage(&wd->msg);
    }
}

// Here are your macro/definitions (assuming they're similar on Windows)
ALKCDEFINE_WDPACKAGE(WDHOLDER, INITWD, OPENWD, EXTRACTEVENTS);
ALKCDEFINE_EVENTMAPPING(MSG, int, 60);
