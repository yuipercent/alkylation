#include <stdint.h>
#include <stdio.h>

#ifndef ALKC_COREINITD

#include "../core/alkore.h"
#endif

#define _NAPHTOOLSUTILS_COREDEFD

typedef struct NaphToolsARG_Rectangle{
	int px;
	int py;
	unsigned int dx;
	unsigned int dy;
}naphtRect;

typedef struct NaphToolsARG_Ellipse{
	int px;
	int py;
	float coefX;
	float coefY;
	unsigned int eccentricity;
}naphtEllipse;

extern void naphTools_FILLRECT(VT_naphtha* CNaphtA,naphtRect Args, uint64_t color);

extern void naphTools_FILLELLIPSE(VT_naphtha* CNaphtA,naphtEllipse Args, uint64_t color);
