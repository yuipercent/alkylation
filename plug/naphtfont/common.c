#include "../naphtfont.h"

#define _NTFONTCONST_COMMONDEFD

// ----< Random utils >-------------------
//
extern inline uint64_t _NTFONT_SWAPEND64(uint64_t value) {
    return ((value & 0x00000000000000FFULL) << 56) |
           ((value & 0x000000000000FF00ULL) << 40) |
           ((value & 0x0000000000FF0000ULL) << 24) |
           ((value & 0x00000000FF000000ULL) << 8)  |
           ((value & 0x000000FF00000000ULL) >> 8)  |
           ((value & 0x0000FF0000000000ULL) >> 24) |
           ((value & 0x00FF000000000000ULL) >> 40) |
           ((value & 0xFF00000000000000ULL) >> 56);
};
// ChatGPT function damn its so useful its a war crime
extern inline uint32_t _NTFONT_SWAPEND32(uint32_t value) {
    return ((value >> 24) & 0xff) |
           ((value << 8) & 0xff0000) |
           ((value >> 8) & 0xff00) |
           ((value << 24) & 0xff000000);
}

// this too btw but who cares
extern inline uint16_t _NTFONT_SWAPEND16(uint16_t value) {
    return (value >> 8) | (value << 8);
}

extern void
_NTFONT_FREAD_WSWAP16(FILE* cfile, uint16_t* cpyMem,int size) {

	uint16_t buffer = 0x0000;
	for (int itx = 0; itx < size; ++itx) {

		fread(&buffer,2,1,cfile);
		cpyMem[itx] = _NTFONT_SWAPEND16(buffer);
	};
};

#define _NTFONT_FREAD_LIEND16(cFile,object,offset,size) \
	_NTFONT_FREAD_WSWAP16(cFile,((uint16_t*)object)+offset,size/2)

extern void
_NTFONT_FREAD_WSWAP32(FILE* cfile, uint32_t* cpyMem,int size) {
	
	uint32_t buffer = 0x00000000;
	for (int itx = 0; itx < size; ++itx) {
		fread(&buffer,4,1,cfile);
		cpyMem[itx] = _NTFONT_SWAPEND32(buffer);
	};
};

#define _NTFONT_FREAD_LIEND32(cFile,object,offset,size) \
	_NTFONT_FREAD_WSWAP32(cFile,((uint32_t*)object)+offset,size/4)

extern void
_NTFONT_FREAD_WSWAP64(FILE* cfile, uint64_t* cpyMem,int size) {

	uint64_t buffer = 0x0000000000000000ULL;
	for (int itx = 0; itx < size; ++itx) {

		fread(&buffer,8,1,cfile);
		cpyMem[itx] = _NTFONT_SWAPEND64(buffer);
	};
};

#define _NTFONT_FREAD_LIEND64(cFile,object,offset,size) \
	_NTFONT_FREAD_WSWAP64(cFile,((uint64_t*)object)+offset,size/8)
// - - - - - - - - - - - - - - - - - - - - - - - -
// < _NTFONT_ Bezcurv calculation functions > ----
//
static inline uint32_t _INTR_BINOMCOF(int n,int k) {
	if (k > n) 		return 0;
	if (k == 0 || k == n) 	return 1;
    
	uint32_t res = 1;
	if (k > n - k) k = n - k;

	for (int i = 0; i < k; ++i) {
		res *= (n - i);
		res /= (i + 1);
	}
	return res;
};

// Gets for all points the coefficients assigned to them
static inline void
_INTR_GET_BEZCURV_COEFS(double* ptcoef, double t, int n) {

	for (int itk = 0; itk < n; ++itk) {
		ptcoef[itk] = _INTR_BINOMCOF(n,itk) * 
		pow(t,(double)itk) * pow(1.0-t,(double)n);
	};
};

// CAlculates pos of current point based on the variable t
extern inline _NTFONT_POINT _INTR_GET_CPT_POS
(_NTFONT_POINT* ctlpoints, double* bezcc, int len) {
	
	double nptpx = 0.0;
	double nptpy = 0.0;
	_NTFONT_POINT npt;

	for (int itk = 0; itk < len; ++itk) {
		nptpx += bezcc[itk] * ctlpoints[itk].px;
		nptpy += bezcc[itk] * ctlpoints[itk].py;
	};

	npt.px = (int)nptpx;
	npt.py = (int)nptpy;
	return npt;

};

extern _NTFONT_POINT _NTFONT_GENPOINT
(_NTFONT_BEZCURV* curve,double t) {
	_INTR_GET_BEZCURV_COEFS(curve->coefs,t,curve->order);
	return _INTR_GET_CPT_POS(curve->points,curve->coefs,curve->order);
};

// --< object managers >----------------------------------	//
//								//
// Object cleaner						//
extern inline void 						//
_NTFONT_FREE_BEZCURVE(_NTFONT_BEZCURV* acurv) {			//
	free(acurv->points);					//
	free(acurv->coefs);					//
	free(acurv);						//
};								//
// Object initializer						//
_NTFONT_BEZCURV* _NTFONT_INIT_BEZCURVE(unsigned char order) {	//
								//
	_NTFONT_BEZCURV* ncurv = (_NTFONT_BEZCURV*)		//
	malloc(sizeof(_NTFONT_BEZCURV));			//
								//
	ncurv->order = order;					//
	ncurv->points = (_NTFONT_POINT*)			//
	malloc(sizeof(_NTFONT_POINT)*order);			//
	ncurv->coefs = (double*)malloc(sizeof(double)*order);	//
	return ncurv;						//
};								//

