#include <stdint.h>
#include <stdio.h>

#ifndef ALKC_COREINITD

#include "../core/alkore.h"
#endif

typedef struct NaphToolsARG_Rectangle{
	int PX;
	int PY;
	unsigned int DX;
	unsigned int DY;
}naphtRect;

static inline _ALKRS_REGTYPEI _NAPHTOOLS_REPEATPAT(long Color,int Size);

static inline void _NAPHTOOLSFILL_REGULAR(WDinfo* wd, naphtRect Args, uint64_t color);

static inline void _NAPHTOOLSFILL_SIMDREGULAR(WDinfo* wd, naphtRect Args, uint64_t color);

extern void naphTools_FILLRECT(WDinfo* wd,naphtRect Args, uint64_t color);
