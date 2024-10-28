#include "naphtools.h"

static inline _ALKRS_REGTYPEI _NAPHTOOLS_REPEATPAT(long Color,int Size) {
	uint8_t* intr = (uint8_t*)malloc(_ALKRS_REGSZ);
	for (int fill = 0; fill < _ALKRS_REGSZ; ++fill) {
		intr[fill] = (Color >> ((fill % Size) * 8)) % 256;
	};
	return _ALKRS_LOADVALUE((_ALKRS_REGTYPEI*)intr);
};

static inline void _NAPHTOOLSFILL_REGULAR
(WDinfo* wd, naphtRect Args, uint64_t color) {
	VT_naphtha* CNaphtA = wd->buffer;
	
	int pzDX = (Args.PX - Args.DX);
	int pzDY = (Args.PY - Args.DY);
	int BPP = CNaphtA->FORMAT.Size;
	char* arrPtr = (char*)CNaphtA->naphtArray +
	((Args.PY * CNaphtA->DX * BPP) + Args.PX * BPP);
	int repeatN = pzDX * pzDY;
	int ndx = CNaphtA->DX;

	for (int ci = 0; ci < repeatN; ++ci) {
	};
};

static inline void _NAPHTOOLSFILL_SIMDREGULAR
(WDinfo* wd, naphtRect Args, uint64_t color) {
	VT_naphtha* CNaphtA = wd->buffer;

	VT_naphTestLock(CNaphtA);VT_naphtLock(CNaphtA);

	int pixSize = CNaphtA->FORMAT.Size;
	_ALKRS_REGTYPEI PasteSchem = _NAPHTOOLS_REPEATPAT(
			color, pixSize);

	int BPP  = wd->format.Size;		// Bytes per pixel
	int PPR  = _ALKRS_REGSZ/BPP;		// Pixel per Register	
	int nDX  = (Args.DX / PPR);		// New DimX
	int lost = Args.DX - nDX * PPR;
	int repeatN = nDX * Args.DY;
	printf("Blit onto window of supposed size %d;%d\n",wd->dx,wd->dy);
	
	char* arrPtr = ((char*)CNaphtA->naphtArray 
	+ (Args.PY * wd->dx * BPP) + Args.PX * BPP);
	printf("Pointer = %p / %d :: %d\n",arrPtr,Args.PY,wd->dx);
	char* cPtr = NULL;

	for (int ci = 0; ci < repeatN; ++ci) {
		// Get current arrPtr
		cPtr = arrPtr + (ci % nDX) * _ALKRS_REGSZ +
		(ci / nDX) * wd->dx * BPP;

		_ALKRS_STOREVALUE((_ALKRS_REGTYPEI*)cPtr,PasteSchem);
	};
	VT_naphtLock(CNaphtA);
};
/** This function assumes that the pixel's size in the
 * naphtha is a power of 2 paddding included, bad usage
 * of this function will result in memory corruption. */
extern void naphTools_FILLRECT
(WDinfo* wd,naphtRect Args, uint64_t color) {
	if (( wd->format.GCID >> 6 ) == 2) {
		_NAPHTOOLSFILL_SIMDREGULAR(wd,Args,color);
	};
	return;
};


