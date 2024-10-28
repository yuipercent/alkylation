#include "srclib/alkc_x11.h"
#include "alkylfw.h"
#include <immintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>

int main() {
	ALKC_STDWD* wd = ALKC_INITWD(250,400,RGB32);
	//naphtFORMAT(wd->Buffer,RGB,8);
	ALKC_OPENWD(wd);
	naphtRect rect;
	naphtRect clearance;
	clearance.PX = 0;
	clearance.PY = 0;
	clearance.DX = 150;
	clearance.DY = 150;
	rect.PX = 10;
	rect.PY = 20;
	//naphTools_FILLRECT(wd->Buffer,rect,1194876);
	while (ALKC_LOOPWD(wd)) {
		rect.DX = 40;
		rect.DY = 40;
		//naphTools_FILLRECT(&wd->attr,clearance,948410);
		naphTools_FILLRECT(&wd->attr,rect,640);
	};
	return 0;
};
