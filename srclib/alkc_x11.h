#include <X11/Xlib.h>

#ifndef ALKC_COREINITD

#include "../core/alkclib.h"
#endif

typedef struct WDHOLDER{
	Display *display;
	Window WD;
	XEvent event;
	int screen;
}WDHOLDER;

extern inline WDHOLDER INITWD(int dx, int dy) {
        WDHOLDER wd;
        wd.display = XOpenDisplay(NULL);
        wd.screen = DefaultScreen(wd.display);
        wd.WD = XCreateSimpleWindow(wd.display,RootWindow(
                                wd.display,wd.screen), 10, 10,
                                dx, dy, 1,
                                BlackPixel(wd.display,wd.screen),
                                WhitePixel(wd.display,wd.screen));
        return wd;
};

extern inline void OPENWD(WDHOLDER wd) {
        XMapWindow(wd.display,wd.WD);
        XSelectInput(wd.display, wd.WD, ExposureMask | KeyPressMask);
        return;
};

extern inline void EXTRACTEVENTS(WDHOLDER wd) {
	XNextEvent(wd.display, &wd.event);
};

ALKCDEFINE_WDPACKAGE(WDHOLDER,INITWD,OPENWD,EXTRACTEVENTS);
ALKCDEFINE_EVENTMAPPING(XEvent,int,60);
