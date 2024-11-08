#include "naphtools.h"
#include "naphtools/common.c"
#include "naphtools/ellipse.c"
#include "naphtools/rectangle.c"

extern void naphTools_FILLRECT
(VT_naphtha* CNaphtA,naphtRect Args, uint64_t color) {

	VT_naphTestLock(CNaphtA);VT_naphtLock(CNaphtA);
	int statint = CNaphtA->format.GCID >> 4;
	if ( statint == 8) {
		_NAPHTOOLSFILL_REGULAR(CNaphtA,Args,color);
	};
	VT_naphtLock(CNaphtA);
	return;
};

extern void naphTools_FILLELLIPSE
(VT_naphtha* CNaphtA, naphtEllipse Args, uint64_t color) {

	VT_naphTestLock(CNaphtA);VT_naphtLock(CNaphtA);
	int statint = CNaphtA->format.GCID >> 4;
	if ( statint == 8) {
		_NAPHTOOLSFILLELLIPSE_REGULAR(CNaphtA,Args,color);
	};
	VT_naphtLock(CNaphtA);
	return;
};
