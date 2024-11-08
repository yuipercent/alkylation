#include <math.h>
#ifndef _NAPHTOOLSUTILS_COREDEFD
#include "../naphtools.h"
#endif

#define _NAPHTOOLSUTILS_COMMONDEFD

// - - - - Utilitary functions - - - - - - - -
//
extern inline _ALKRS_REGTYPEI _NAPHTOOLSUTILS_REPEATPAT(long Color,int Size) {
	uint8_t* intr = (uint8_t*)malloc(_ALKRS_REGSZ);
	for (int fill = 0; fill < _ALKRS_REGSZ; ++fill) {
		intr[fill] = (Color >> ((fill % Size) * 8)) % 256;
	};
	return _ALKRS_LOADVALUE((_ALKRS_REGTYPEI*)intr);
};

extern inline char* _NAPHTOOLSUTILS_GETBLITADDRESS
(VT_naphtha* CNaphtA,int addrX,int addrY) {
	return (char*)CNaphtA->naphtArray + 
	(addrY * CNaphtA->dx + addrX) * CNaphtA->format.Size;
};
