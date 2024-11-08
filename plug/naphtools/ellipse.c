#ifndef _NAPHTOOLSUTILS_COMMONDEFD
#include "common.c"
#endif

//=========================================================
// ----< Ellipse functions >----------------------------- //

extern void _NAPHTOOLSFILLELLIPSE_REGULAR
(VT_naphtha* CNaphtA,naphtEllipse ellipse, uint64_t color) {
	ellipse.px -= 1;
	float _a = ellipse.coefY / ellipse.coefX;
	float _b = ellipse.coefX / ellipse.coefY;
	int sizeX = ellipse.eccentricity;
	int sizeY = ellipse.eccentricity;

	if (_a < _b) {sizeX *= sqrt(_a) + 1; sizeY *= sqrt(_b);}
	else 	     {sizeX *= sqrt(_b) + 1; sizeY *= sqrt(_a);};

	int osizeX = sizeX;
	int osizeY = sizeY;
	char* colorPtr = (char*)&color;

	int originx = ellipse.px - sizeX;
	int originy = ellipse.py - sizeY;

	int pixSize = CNaphtA->format.Size;
	_ALKRS_REGTYPEI PasteSchem = _NAPHTOOLSUTILS_REPEATPAT(
			color, pixSize);

	float inv_pixel_per_iteration = (float)CNaphtA->format.Size / _ALKRS_REGSZ;
	int   pixel_per_iteration     = _ALKRS_REGSZ / CNaphtA->format.Size;
	int ndx = (sizeX*2) / pixel_per_iteration;

	// Prepare the blit address
	char* arrPtr = _NAPHTOOLSUTILS_GETBLITADDRESS(CNaphtA,originx,originy);
	//printf("Pointer = %p / %d :: %d\n",arrPtr,Args.PY,wd->dx);
	//
	int nsz = sizeY * 2 * ndx;

	char* cPtr = NULL;	// Ptr slider
	int cpy = -1;		// current position y
	int cpx = 0;
	int ledge = 0;

	// - - - - - - - - - - -
	// y² * cY + cX * x² < ecc
	//
	// cX * x² < ecc - y² * cY
	// x² < (ecc - y² * cY) / cX
	// x < sqrt((ecc - y² * cY) / cX)
	
	// Prepares the calculation variable
	int interm = 0;
	float x1  = 0;
	float x2  = 0;
	float x1alt = 0;
	float x2alt = 0;
	int adjusted_cpx = 0;
	int eccentricity = ellipse.eccentricity * ellipse.eccentricity;

	// - SIMD blitter - - - - - - - - - - - - -
	for (int ci = 0; ci < (nsz); ++ci) {
		cpx = ci % ndx;
		ledge = cpx + pixel_per_iteration;
		if (cpx == 0) { 

			++cpy;
			interm = cpy - osizeY;

			x1alt = sqrt((eccentricity - interm * interm * ellipse.coefY) / ellipse.coefX);
			x2alt = (float)osizeX + x1alt;
			x1alt = (float)osizeX - x1alt;
			x1 = round( x1alt * inv_pixel_per_iteration);
			x2 = round( x2alt * inv_pixel_per_iteration);
		};
		//printf("CUrrentvars : cpx : %d | x1 : %f | x2 : %f\n",cpx,x1,x2);

		// Get current arrPtr
		if ((cpx > x1) || (ledge <= x2)) {
		//printf("Delta : %f | x1 : %f | x2 : %f \n",x1alt,x1,x2);

		cPtr = arrPtr + cpx * _ALKRS_REGSZ +
		cpy * CNaphtA->dx * CNaphtA->format.Size;

		// -< Case where area is fully colored
		if ((cpx > x1) && (ledge <= x2)) {

			_ALKRS_STOREVALUE((_ALKRS_REGTYPEI*)cPtr,PasteSchem);

		// -> Case where partially colored
		} else {
			adjusted_cpx = cpx * pixel_per_iteration;
			for (int lcpx = 0; lcpx < _ALKRS_REGSZ; ++lcpx) {
				cpx = adjusted_cpx + lcpx / pixel_per_iteration;
				if ((cpx > x1alt) && (cpx <= x2alt)) {
				cPtr[lcpx] = colorPtr[lcpx % CNaphtA->format.Size];};
				};
			};
				
		};
	
	};
}; 

extern void _NAPHTOOLSFILLELLIPSE_REGUSAFE
(VT_naphtha* CNaphtA,naphtEllipse ellipse, uint64_t color) {
	ellipse.px -= 1;
	float _a = ellipse.coefY / ellipse.coefX;
	float _b = ellipse.coefX / ellipse.coefY;
	int sizeX = ellipse.eccentricity;
	int sizeY = ellipse.eccentricity;

	if (_a < _b) {sizeX *= sqrt(_a) + 1; sizeY *= sqrt(_b);}
	else 	     {sizeX *= sqrt(_b) + 1; sizeY *= sqrt(_a);};

	int osizeX = sizeX;
	int osizeY = sizeY;
	char* colorPtr = (char*)&color;

	int originx = ellipse.px - sizeX;
	int originy = ellipse.py - sizeY;

	if (originx < 0) 			{originx = 0;};
	if (originy < 0) 			{originy = 0;};
	if (ellipse.px + sizeX >= CNaphtA->dx) 	{sizeX = CNaphtA->dx - ellipse.px;};
	if (ellipse.py + sizeY >= CNaphtA->dy) 	{sizeY = CNaphtA->dy - ellipse.py;};

	int pixSize = CNaphtA->format.Size;
	_ALKRS_REGTYPEI PasteSchem = _NAPHTOOLSUTILS_REPEATPAT(
			color, pixSize);

	float inv_pixel_per_iteration = (float)CNaphtA->format.Size / _ALKRS_REGSZ;
	int   pixel_per_iteration     = _ALKRS_REGSZ / CNaphtA->format.Size;
	int ndx = (sizeX*2) / pixel_per_iteration;

	// Prepare the blit address
	char* arrPtr = _NAPHTOOLSUTILS_GETBLITADDRESS(CNaphtA,originx,originy);
	//printf("Pointer = %p / %d :: %d\n",arrPtr,Args.PY,wd->dx);
	//
	int lost_l = originx - ellipse.px + sizeX;
	int lost_u = originy - ellipse.py + sizeY;
	int nsz = sizeY * 2 * ndx - lost_u * ndx;

	char* cPtr = NULL;	// Ptr slider
	int cpy = -1;		// current position y
	int cpx = 0;
	int ledge = 0;

	// - - - - - - - - - - -
	// y² * cY + cX * x² < ecc
	//
	// cX * x² < ecc - y² * cY
	// x² < (ecc - y² * cY) / cX
	// x < sqrt((ecc - y² * cY) / cX)
	
	// Prepares the calculation variable
	printf("LOST = %d\n",lost_u);
	int interm = 0;
	float x1  = 0;
	float x2  = 0;
	float x1alt = 0;
	float x2alt = 0;
	int adjusted_cpx = 0;
	int eccentricity = ellipse.eccentricity * ellipse.eccentricity;

	// - SIMD blitter - - - - - - - - - - - - -
	for (int ci = 0; ci < (nsz); ++ci) {
		cpx = ci % ndx;
		ledge = cpx + pixel_per_iteration;
		if (cpx == 0) { 

			++cpy;
			interm = cpy - osizeY + lost_u;

			x1alt = sqrt((eccentricity - interm * interm * ellipse.coefY) / ellipse.coefX);
			x2alt = (float)osizeX + x1alt - lost_l;
			x1alt = (float)osizeX - x1alt - lost_l;
			x1 = round( x1alt * inv_pixel_per_iteration);
			x2 = round( x2alt * inv_pixel_per_iteration);
		};
		//printf("CUrrentvars : cpx : %d | x1 : %f | x2 : %f\n",cpx,x1,x2);

		// Get current arrPtr
		if ((cpx > x1) || (ledge <= x2)) {
		//printf("Delta : %f | x1 : %f | x2 : %f \n",x1alt,x1,x2);

		cPtr = arrPtr + cpx * _ALKRS_REGSZ +
		cpy * CNaphtA->dx * CNaphtA->format.Size;

		// -< Case where area is fully colored
		if ((cpx > x1) && (ledge <= x2)) {

			_ALKRS_STOREVALUE((_ALKRS_REGTYPEI*)cPtr,PasteSchem);

		// -> Case where partially colored
		} else {
			adjusted_cpx = cpx * pixel_per_iteration;
			for (int lcpx = 0; lcpx < _ALKRS_REGSZ; ++lcpx) {
				cpx = adjusted_cpx + lcpx / pixel_per_iteration;
				if ((cpx > x1alt) && (cpx <= x2alt)) {
				cPtr[lcpx] = colorPtr[lcpx % CNaphtA->format.Size];};
				};
			};
				
		};
	
	};
}; 
