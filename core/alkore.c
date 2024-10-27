#include "alkore.h"

//-------------------- VISUAL SYSTEM AFFILIATED FUNCTIONS ----------------------//
										//
extern void VTINIT_naphtFORMAT							//
(VT_naphtha* CNaphtA,struct compositeFORMAT cFORMAT) {				//
										//
	CNaphtA->FORMAT		 = cFORMAT;					//
										//
	int ldx = CNaphtA->DX;							//
	int ldy = CNaphtA->DY;							//
	int lSize 		 = CNaphtA->FORMAT.Size;			//
	//printf("lSize = %d | ldx = %d | ldy = %d\n",lSize,ldx,ldy);		//
										//
	CNaphtA->bytes_per_line	 = ( lSize ) * ldx;				//
	CNaphtA->naphtarray_size = ( lSize ) * ldx * ldy;			//
										//
	CNaphtA->offsetX	 = ( _ALKRS_REGSZ - 				//
	( CNaphtA->naphtarray_size % _ALKRS_REGSZ ));				//
	if (CNaphtA->offsetX == _ALKRS_REGSZ) {					//
		CNaphtA->offsetX = 0;						//
	};									//
										//
	CNaphtA->naphtArray = malloc(CNaphtA->naphtarray_size);			//
	CNaphtA->LOCK = false;							//
};										//

VT_naphtha* VTINIT_naphtha(int sizeX,int sizeY,struct compositeFORMAT cFORMAT) {
	VT_naphtha* CNaphtA =
	(VT_naphtha*)malloc(sizeof(VT_naphtha));

	CNaphtA->LOCK 	= true;
	CNaphtA->DX 	= sizeX;
	CNaphtA->DY 	= sizeY;

	VTINIT_naphtFORMAT(CNaphtA,cFORMAT);
	return CNaphtA;
};

// Usage : VT_naphtha RandomVariable = VTINIT_naphtha(120,90,RGBA32);		//

bool VTFREE_naphtArray(VT_naphtha* CNaphtA) {
	if (CNaphtA->LOCK == false) {
		free(CNaphtA->naphtArray);
		CNaphtA->LOCK = true;
		CNaphtA->naphtArray = NULL;
		return true;
	};
	return false;
};
// Returns a bool : 1 if successful in freeing the memory,
// 0 if the naphtArray was locked
// -----------------------------------------------------------------------------//

void VT_naphtLock(VT_naphtha* CNaphtA) {
	CNaphtA->LOCK = !CNaphtA->LOCK;
};

void VT_naphTestLock(VT_naphtha* CNaphtA) {
        if (CNaphtA->LOCK) {
                printf("Segmentation Fault (core dumped) : \n[Alkylation]: illegal access to     napht attributes while locked.\n");
                exit(139);
        };
};

