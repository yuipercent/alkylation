#include <X11/Xlib.h>
#include <X11/Xutil.h>

#ifndef ALKC_COREINITD

#include "../core/alkclib.h"
#endif

typedef struct WDHOLDER{
	Display *display;
	Window WD;
	XEvent event;
	int screen;
	XWindowAttributes InfoHolder;
}WDHOLDER;

extern inline WDHOLDER* INITWD(int dx, int dy) {
	WDHOLDER* wd = (WDHOLDER*)malloc(sizeof(WDHOLDER));
        wd->display = XOpenDisplay(NULL);
        wd->screen = DefaultScreen(wd->display);
        wd->WD = XCreateSimpleWindow(wd->display,RootWindow(
                                wd->display,wd->screen), 10, 10,
                                dx, dy, 1,
                                BlackPixel(wd->display,wd->screen),
                                WhitePixel(wd->display,wd->screen));
        return wd;
};

extern inline void OPENWD(WDHOLDER* wd) {
        XMapWindow(wd->display,wd->WD);
        XSelectInput(wd->display, wd->WD, ExposureMask | KeyPressMask);
        return;
};

extern inline void EXTRACTEVENTS(WDHOLDER* wd) {
	XNextEvent(wd->display, &wd->event);
	XGetWindowAttributes(wd->display,wd->WD,&wd->InfoHolder);
};

extern inline int GETX11DX(WDHOLDER* wd) {
	return wd->InfoHolder.width;
};

extern inline int GETX11DY(WDHOLDER* wd) {
	return wd->InfoHolder.height;
};

extern inline void RENDERBUFFER(WDHOLDER* wd, VT_naphtha* Buffer, int wdDX, int wdDY) {
	int sz = (Buffer->FORMAT.Size - Buffer->FORMAT.padding);
	int bytes_per_line = wdDX * sz;  // Ensure correct alignment
	int depth = DefaultDepth(wd->display, wd->screen);

	XImage *Intermediary = XCreateImage(
        	wd->display,
        	DefaultVisual(wd->display, wd->screen),
        	depth,
        	ZPixmap,         // Use ZPixmap for pixel data format
        	0,               // No offset
        	(char*) Buffer->naphtArray,  // The pixel data
        	wdDX, wdDY,      // Width and height
        	32,              // Bitmap pad, often 32 for TrueColor
        	0  // Bytes per line to align each scanline
	);

	if (!Intermediary) {
		fprintf(stderr, "Failed to create XImage.\n");
		return;
	}

	GC gc = XCreateGC(wd->display, wd->WD, 0, NULL);
	if (!gc) {
		fprintf(stderr, "Failed to create graphics context.\n");
		Intermediary->data = NULL;
		XDestroyImage(Intermediary);
		return;
	}
	XPutImage(wd->display, wd->WD, gc, Intermediary,
        0, 0, 0, 0, Buffer->DX, Buffer->DY);

	// Clean up
	Intermediary->data = NULL;
	XDestroyImage(Intermediary);
	XFreeGC(wd->display, gc);
}

ALKCDEFINE_WDPACKAGE(WDHOLDER,
		INITWD,
		OPENWD,
		EXTRACTEVENTS,
		GETX11DX,
		GETX11DY,
		RENDERBUFFER);

ALKCDEFINE_EVENTMAPPING(XEvent,int,60);
