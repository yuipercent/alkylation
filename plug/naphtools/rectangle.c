#ifndef _NAPHTOOLSUTILS_COMMONDEFD
#include "common.c"
#endif

//============================================================
// ----< Rectangle functions >----------------------------- //
//
extern void _NAPHTOOLSFILL_REGULAR
(VT_naphtha* CNaphtA, naphtRect Args, uint64_t color) {

	int pixSize = CNaphtA->format.Size;
	_ALKRS_REGTYPEI PasteSchem = _NAPHTOOLSUTILS_REPEATPAT(
			color, pixSize);

	int BPP  = CNaphtA->format.Size;	// Bytes per pixel
	int PPR  = _ALKRS_REGSZ/BPP;		// Pixel per Register	
	int nDX  = (Args.dx / PPR);		// New DimX
	int repeatN = nDX * Args.dy;
	//printf("Blit onto window of supposed size %d;%d\n",wd->dx,wd->dy);
	
	// Prepare the blit address
	char* arrPtr = _NAPHTOOLSUTILS_GETBLITADDRESS(CNaphtA,Args.px,Args.py);
	//printf("Pointer = %p / %d :: %d\n",arrPtr,Args.PY,wd->dx);
	char* cPtr = NULL;	// Ptr slider

	// - SIMD blitter - - - - - - - - - - - - -
	for (int ci = 0; ci < repeatN; ++ci) {
		// Get current arrPtr
		cPtr = arrPtr + (ci % nDX) * _ALKRS_REGSZ +
		(ci / nDX) * CNaphtA->dx * BPP;

		_ALKRS_STOREVALUE((_ALKRS_REGTYPEI*)cPtr,PasteSchem);
	};

	// Proccesses the bit that couldn't be calculated using SIMD because
	// of memory alignment issues
	int lost = Args.dx - nDX * PPR;

	if (lost != 0) {

		uint8_t* npasteSchem = (uint8_t*)&PasteSchem;
		int restoreb = lost * BPP;
		arrPtr = arrPtr + nDX * _ALKRS_REGSZ;
		
		// - Remainder blitter - - - - - - - - - - 
		for (int ci = 0; ci < (Args.dy); ++ci) {
			for (int nci = 0; nci < restoreb; ++nci) {
				cPtr = arrPtr + (ci * CNaphtA->dx * BPP);
				cPtr[nci] = npasteSchem[nci];
			};
		};
	};
};
/** This function assumes that the pixel's size in the
 * naphtha is a power of 2 paddding included, bad usage
 * of this function will result in memory corruption. */

