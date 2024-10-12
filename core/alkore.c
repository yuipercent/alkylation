#include "alkore.h"

//--------------------------- AFFILIATED FUNCTIONS -----------------------------//
										//
static void VTINIT_naphtArrayFORMAT(						//
VT_naphtha CNaphtA,const int cFORMAT,int Padding) {				//
										//
	CNaphtA.FORMAT.GCID = VTEXTRACT_compositeFORMATARGUMENTS(cFORMAT,0);	//
	CNaphtA.FORMAT.BPCA = VTEXTRACT_compositeFORMATARGUMENTS(cFORMAT,8);	//
	CNaphtA.FORMAT.BFAA = VTEXTRACT_compositeFORMATARGUMENTS(cFORMAT,16);	//
	CNaphtA.FORMAT.Size = VTEXTRACT_compositeFORMATARGUMENTS(cFORMAT,24);	//
										//
	CNaphtA.FORMAT.StorageFormat = cFORMAT;					//
	CNaphtA.offsetX = (8-(CNaphtA.FORMAT.Size%8));				//
	CNaphtA.bytes_per_line = (CNaphtA.FORMAT.Size)*CNaphtA.DX;		//
	CNaphtA.padding = Padding;						//
	CNaphtA.naphtarray_size = 						//
	(CNaphtA.padding + CNaphtA.FORMAT.Size) * CNaphtA.DX;			//
};										//

VT_naphtha VTINIT_naphtha(int sizeX,int sizeY,const int cFORMAT) {
	VT_naphtha CNaphtA;
	CNaphtA.LOCK = true;
	VTINIT_naphtArrayFORMAT(CNaphtA,cFORMAT,0);
	return CNaphtA;
};
// Usage : VT_naphtha RandomVariable = VTINIT_naphtha(120,90,RGBA32);		//
// -----------------------------------------------------------------------------//

void VTINIT_mallocnapht(VT_naphtha CNaphtA) {
	CNaphtA.naphtArray = malloc(CNaphtA.naphtarray_size);
};
