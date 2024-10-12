#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>
#include <xmmintrin.h>

#define VTDEFINE_compositeFORMAT(Name,BitPerColor,BitForAlpha,BitsAmount,GCID)	\
	unsigned const int Name = 						\
	((BitsAmount)<<(24) | ((BitPerColor)<<(16)) | ((BitForAlpha)<<(8)) | (GCID))
/** ----------------------- compositeFORMAT -------------------------
 * MAcro: Defines a compositeFORMAT as a global compile time constant
 *
 * Usage : VTDEFINE_compositeFORMAT(RGB,8,0,24,0);
 * 	Defines a compositeFORMAT named RGB with 8 bits per color
 * 	which uses 0 bits for alpha, stored on a total of 24 bits
 * 	and of global caracterizing identifier 0 ( The global color
 * 	format ID, for example RGB or LCH )
 *
 * ----------------------------------------------------------------
 *
 * Storage FOrmat : Stored as unsigned const int divided in 4
 * Bits 0-7	 allocated to GCID
 * Bits 8-15	 allocated to BitForAlpha argument
 * Bits 16-23	 allocated to BitPerColor argument
 * Bits 24-31	 allocated to Global bits amount argument
 * 
 * ----------------------------------------------------------------*/ 

#define VTEXTRACT_compositeFORMATARGUMENTS(Name,STBIT) ((Name)>>(STBIT)%8)
/** ----------------------- compositeEXTRACTION --------------------------
 *
 * Macro : EXtracts the given composite argument
 *
 * Usage : VTEXTRACT_compositeFORMATARGUMENTS(RGB16,BPCAindex);
 * 	Extracts the BitPerColor Argument of RGB16 compFORM
 * 0 = GCID,	8 = BPCA,	16 = BFAA,	24 = Amount of bits
 * ---------------------------------------------------------------------*/


#define VTDEFINE_compositePROTOCOLS(ColorFormatAmount)\
	int VTCONST_compositePROTOCOLS[(ColorFormatAmount)*(ColorFormatAmount)];\
/** ----------------------- compositePROTOCOLS -----------------------
 *
 * Macro: defines the global variable used for storing conversion protocols
 *
 * Usage: VTDEFINE_compositePROTOCOLS(2);
 *	Defines the VTCONST_compositePROTOCOLS constant to hold 5
 *	protocols : CLASSIC, RGB->RGB, RGB->LCH, LCH->LCH etc...
 *	The classic protocol is present regardless of argument
 *
 * -------------------------------------------------------------------*/

#define VTDEFINE_DEFAULTPRESETS()				\
	VTDEFINE_compositeFORMAT(RGBA32,8,8,32,0);		\
	VTDEFINE_compositeFORMAT(RGB,8,0,24,0);			\

VTDEFINE_DEFAULTPRESETS();

//=============================== NAPHTHA ======================================//
										//
static struct compositeFORMAT{							//
	unsigned char BPCA;		// Bit per color argument		//
	unsigned char BFAA;		// Bit per alpha argument		//
	unsigned char Size;		// Amount of bits per pixel		//
	unsigned char GCID;		// GLobal caracterizing identifier	//
	unsigned int StorageFormat;	// Total int for internal processing	//
}compositeFORMAT;								//
typedef struct VT_naphtha {							//
	bool LOCK;								//
	int DX;									//
	int DY;									//
	int offsetX;								//
	int padding;								//
	int bytes_per_line;							//
        void* naphtArray;							//
	int naphtarray_size;							//
	struct compositeFORMAT FORMAT;						//
}VT_naphtha;									//
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

int main() {
	VT_naphtha Joemama = VTINIT_naphtha(50,300,RGB);
	VTINIT_mallocnapht(Joemama);
	return 0;
};
