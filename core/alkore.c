#include "alkore.h"

//--------------------------- AFFILIATED FUNCTIONS -----------------------------//
										//
static inline struct compositeFORMAT VTINIT_compositeSCHEM(const int cFORMAT) {	//
	struct compositeFORMAT CFormat;						//
	CFormat.GCID = VTEXTRACT_compositeFORMATARGUMENTS(cFORMAT,0);		//
	CFormat.BPCA = VTEXTRACT_compositeFORMATARGUMENTS(cFORMAT,16);		//
	CFormat.BFAA = VTEXTRACT_compositeFORMATARGUMENTS(cFORMAT,24);		//
	CFormat.Size = VTEXTRACT_compositeFORMATARGUMENTS(cFORMAT,8);		//
	return CFormat;								//
};										//
static void VTINIT_naphtArrayFORMAT(						//
VT_naphtha* CNaphtA,const int cFORMAT,int Padding) {				//
	CNaphtA->FORMAT = VTINIT_compositeSCHEM(cFORMAT);			//
										//
	int ldx = CNaphtA->DX;							//
	int ldy = CNaphtA->DY;							//
	int lSize = CNaphtA->FORMAT.Size;					//
										//
	CNaphtA->FORMAT.StorageFormat = cFORMAT;				//
	CNaphtA->bytes_per_line	 = ( lSize ) * ldx;				//
	CNaphtA->padding	 = Padding;					//
	CNaphtA->naphtarray_size = (CNaphtA->padding + lSize ) * ldx * ldy;	//
										//
	CNaphtA->offsetX	 = ( _ALKR_REGSZ - 				//
	( CNaphtA->naphtarray_size % _ALKR_REGSZ ));				//
	if (CNaphtA->offsetX == _ALKR_REGSZ) {					//
		CNaphtA->offsetX = 0;						//
	};									//
};										//

VT_naphtha* VTINIT_naphtha(int sizeX,int sizeY,const int cFORMAT) {
	VT_naphtha* CNaphtA =
	(VT_naphtha*)malloc(sizeof(VT_naphtha));

	CNaphtA->LOCK 	= true;
	CNaphtA->DX 	= sizeX;
	CNaphtA->DY 	= sizeY;

	VTINIT_naphtArrayFORMAT(CNaphtA,cFORMAT,0);
	return CNaphtA;
};
// Usage : VT_naphtha RandomVariable = VTINIT_naphtha(120,90,RGBA32);		//

bool VTFREE_naphtArray(VT_naphtha* CNaphtA) {
	if (CNaphtA->LOCK == false) {free(CNaphtA->naphtArray);};
	return (CNaphtA->LOCK == false);
};
// Returns a bool : 1 if successful in freeing the memory,
// 0 if the naphtArray was locked
// -----------------------------------------------------------------------------//

void VTINIT_mallocnapht(VT_naphtha* CNaphtA) {
	CNaphtA->naphtArray = malloc(CNaphtA->naphtarray_size);
};
