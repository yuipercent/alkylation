#include "srclib/alkc_x11.h"
#include "alkylfw.h"
#include <immintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>

int main() {
	ALKC_STDWD* wd = ALKC_INITWD(250,480,RGB32);
	VT_naphTestLock(wd->Buffer);
	//naphtFORMAT(wd->Buffer,RGB,8);
	ALKC_OPENWD(wd);
	naphtRect rect;
	rect.PX = 0;
	rect.PY = 0;
	rect.DX = 20;
	rect.DY = 20;
	//naphTools_FILLRECT(wd->Buffer,rect,1194876);
	VT_naphTestLock(wd->Buffer);
	while (ALKC_LOOPWD(wd)) {
	};
	return 0;
};
