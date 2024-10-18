#include <windows.h>
#include <malloc.h>
#include "../core/alkclib.h"

typedef struct WDHOLDER {
    HWND hwnd;      // Handle de la fenêtre
    HDC hdc;       // Contexte de périphérique pour la fenêtre
    MSG msg;       // Structure pour les messages Windows (événements)
    RECT InfoHolder; // Stocke les dimensions de la fenêtre
    int width, height; // Dimensions de la fenêtre
} WDHOLDER;

// Fonction de gestionnaire de fenêtre
extern inline LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY: // Si la fenêtre est fermée
            PostQuitMessage(0); // Arrêter la boucle d'événements
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

// Fonction pour initialiser la fenêtre
extern inline WDHOLDER* INITWD(int dx, int dy) {
    WDHOLDER* wd = (WDHOLDER*)malloc(sizeof(WDHOLDER));

    HINSTANCE hInstance = GetModuleHandle(NULL);

    // Définir la classe de la fenêtre
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;  // Fonction de traitement des messages
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("WindowClass");

    RegisterClass(&wc);

    // Créer la fenêtre
    wd->hwnd = CreateWindowEx(
        0,
        TEXT("WindowClass"),
        TEXT("Sample Window"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, dx, dy,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    wd->width = dx;
    wd->height = dy;

    return wd;
}

// Fonction pour afficher la fenêtre
extern inline void OPENWD(WDHOLDER* wd) {
    ShowWindow(wd->hwnd, SW_SHOW);  // Afficher la fenêtre
    UpdateWindow(wd->hwnd);         // Mettre à jour son contenu
}

// Fonction pour rendre un buffer à l'écran
extern inline void RENDERBUFFER(WDHOLDER* wd, VT_naphtha* Buffer) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(wd->hwnd, &ps); // Commencer à dessiner dans la fenêtre

    // Créer un bitmap compatible à partir du buffer
    HBITMAP bitmap = CreateBitmap(
        Buffer->DX, Buffer->DY, 
        1, 32, Buffer->naphtArray
    );

    // Créer un DC compatible en mémoire pour y dessiner
    HDC hdcMem = CreateCompatibleDC(hdc);
    SelectObject(hdcMem, bitmap);  // Sélectionner le bitmap dans le DC

    // Copier le bitmap dans la fenêtre
    BitBlt(hdc, 0, 0, Buffer->DX, Buffer->DY, hdcMem, 0, 0, SRCCOPY);

    // Nettoyage
    DeleteDC(hdcMem);   // Supprimer le DC en mémoire
    DeleteObject(bitmap); // Supprimer le bitmap
    EndPaint(wd->hwnd, &ps); // Fin du dessin
}

// Fonction pour extraire les événements de la file d'attente
extern inline void EXTRACTEVENTS(WDHOLDER* wd) {
    GetClientRect(wd->hwnd, &wd->InfoHolder); // Obtenir la taille de la fenêtre
    // Traiter les événements
    while (PeekMessage(&wd->msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&wd->msg);
        DispatchMessage(&wd->msg);
    }
}

// Obtenir la largeur de la fenêtre
extern inline int GETWINDX(WDHOLDER* wd) {
    return wd->InfoHolder.right - wd->InfoHolder.left;
}

// Obtenir la hauteur de la fenêtre
extern inline int GETWINDY(WDHOLDER* wd) {
    return wd->InfoHolder.bottom - wd->InfoHolder.top;
}

// Définitions des fonctions pour ALKC
ALKCDEFINE_WDPACKAGE(WDHOLDER,
    INITWD,
    OPENWD,
    EXTRACTEVENTS,
    GETWINDX,
    GETWINDY,
    RENDERBUFFER
);

ALKCDEFINE_EVENTMAPPING(MSG, int, 60);
