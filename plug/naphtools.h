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

