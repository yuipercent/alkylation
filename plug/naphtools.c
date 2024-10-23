#include "naphtools.h"

extern inline _ALKRS_REGTYPEI _NAPHTOOLS_REPEATPAT(long Color,int Size) {
	uint8_t* intr = (uint8_t*)malloc(_ALKRS_REGSZ);
	for (int fill = 0; fill < _ALKRS_REGSZ; ++fill) {
		intr[fill] = (Color >> ((fill % Size) * 8)) % 256;
	};
	return _ALKRS_LOADVALUE((_ALKRS_REGTYPEI*)intr);
};

static void naphToolsFILL_REGULAR
(VT_naphtha* CNaphtA, naphtRect Args, uint64_t color) {
	
	int pzDX = (Args.PX - Args.DX);
	int pzDY = (Args.PY - Args.DY);
	int BPP = CNaphtA->bytes_per_pixel;
	char* arrPtr = (char*)CNaphtA->naphtArray +
	((Args.PY * CNaphtA->DX * BPP) + Args.PX * BPP);
	int repeatN = pzDX * pzDY;
	int ndx = CNaphtA->DX;

	for (int ci = 0; ci < repeatN; ++ci) {
	};
};

static void naphToolsFILL_SIMDREGULAR
(VT_naphtha* CNaphtA, naphtRect Args, uint64_t color) {

	int pixSize = CNaphtA->bytes_per_pixel;
	_ALKRS_REGTYPEI PasteSchem = _NAPHTOOLS_REPEATPAT(
			color, pixSize);

	int BPP  = CNaphtA->bytes_per_pixel;
	int PPR  = _ALKRS_REGSZ/BPP;		// Pixel per Register	
	int pzDX = (Args.PX - Args.DX) * BPP;	// Processing zone dx
	int pzDY = (Args.PY - Args.DY) * BPP;	// Processing zone dx
	
	
	_ALKRS_REGTYPEI* arrPtr = (_ALKRS_REGTYPEI*)((char*)CNaphtA->naphtArray 
	+ (Args.PY * CNaphtA->DX * BPP) + Args.PX * BPP);
	
	for (int px = 0; px < 0; ++px) {
		
	};
};
/** This function assumes that the pixel's size in the
 * naphtha is a power of 2 paddding included, bad usage
 * of this function will result in memory corruption. */

