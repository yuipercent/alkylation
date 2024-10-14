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

extern inline void RENDERBUFFER(WDHOLDER* wd,VT_naphtha* Buffer) {
	// This looks so messy help me please
	XImage *Intermediary = XCreateImage(
		wd->display,
		// Specifies the connection to the X server. 
		DefaultVisual(wd->display,wd->screen),
		// Specifies the Visual structure. 
		Buffer->FORMAT.Size,
		// Specifies the depth of the image. 
		ZPixmap,
		// Specifies the format for the image. 
		0,
		// Specifies the number of pixels to ignore
		// at the beginning of the scanline. 
		(char*) Buffer->naphtArray,
		// Specifies the image data. 
		Buffer->DX,
		// Specifies the X dimension
		Buffer->DY,
		// Specifies the Y dimension
		32,
		// Specifies the quantum of a scanline
		0);
		// Specifies the number of bytes in the client
		// image between the start of one scanline
		// and the start of the next. 

	GC gc = XCreateGC(wd->display,wd->WD,0,NULL);
	XPutImage(wd->display,wd->WD,gc,Intermediary,
	0, 0, 0, 0,Buffer->DX,Buffer->DY);

	// Clear intermediary objects memory
	XDestroyImage(Intermediary);
	XFreeGC(wd->display,gc);
};

extern inline void EXTRACTEVENTS(WDHOLDER* wd) {
	XNextEvent(wd->display, &wd->event);
};

ALKCDEFINE_WDPACKAGE(WDHOLDER,INITWD,OPENWD,EXTRACTEVENTS,RENDERBUFFER);
ALKCDEFINE_EVENTMAPPING(XEvent,int,60);
