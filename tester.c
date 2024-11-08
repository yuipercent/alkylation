#include "srclib/alkc_x11.h"
#include "alkylfw.h"

int main() {
	ALKC_STDWD* wd = ALKC_INITWD(250,400,RGB32);
	//naphtFORMAT(wd->Buffer,RGB,8);
	ALKC_OPENWD(wd);
	naphtRect rect;
	naphtEllipse clearance;
	clearance.px = 100;
	clearance.py = 100;
	clearance.eccentricity = 50;
	clearance.coefX = 1;
	clearance.coefY = 2;
	rect.px = 10;
	rect.py = 20;
	//naphTools_FILLRECT(wd->Buffer,rect,1194876);
	while (ALKC_LOOPWD(wd)) {
		rect.dx = 40;
		rect.dy = 40;
		//naphTools_FILLRECT(&wd->attr,clearance,948410);
		//naphTools_FILLRECT(wd->attr.buffer,rect,640);
		naphTools_FILLELLIPSE(wd->attr.buffer,clearance,640);
	};
	return 0;
};
