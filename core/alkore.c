#include "alkore.h"

//--------------------------- AFFILIATED FUNCTIONS -----------------------------//
										//
static void VTINIT_naphtArrayFORMAT(						//
VT_naphtha* CNaphtA,const int cFORMAT,int Padding) {				//
										//
	CNaphtA->FORMAT.GCID = VTEXTRACT_compositeFORMATARGUMENTS(cFORMAT,0);	//
	CNaphtA->FORMAT.BPCA = VTEXTRACT_compositeFORMATARGUMENTS(cFORMAT,8);	//
	CNaphtA->FORMAT.BFAA = VTEXTRACT_compositeFORMATARGUMENTS(cFORMAT,16);	//
	CNaphtA->FORMAT.Size = VTEXTRACT_compositeFORMATARGUMENTS(cFORMAT,24);	//
	int ldx = CNaphtA->DX;							//
	int lSize = CNaphtA->FORMAT.Size;					//
										//
	CNaphtA->FORMAT.StorageFormat = cFORMAT;				//
	CNaphtA->offsetX = ( 8 - ( lSize % 8 ));				//
	CNaphtA->bytes_per_line = ( lSize ) * ldx;				//
	CNaphtA->padding = Padding;						//
	CNaphtA->naphtarray_size = 						//
	(CNaphtA->padding + lSize ) * ldx;					//
};										//

VT_naphtha* VTINIT_naphtha(int sizeX,int sizeY,const int cFORMAT) {
	VT_naphtha* CNaphtA =
	(VT_naphtha*)malloc(sizeof(VT_naphtha));

	CNaphtA->LOCK = true;
	CNaphtA->DX = 	sizeX;
	CNaphtA->DY = 	sizeY;

	VTINIT_naphtArrayFORMAT(CNaphtA,cFORMAT,0);
	return CNaphtA;
};
// Usage : VT_naphtha RandomVariable = VTINIT_naphtha(120,90,RGBA32);		//
// -----------------------------------------------------------------------------//

void VTINIT_mallocnapht(VT_naphtha* CNaphtA) {
	CNaphtA->naphtArray = malloc(CNaphtA->naphtarray_size);
};
