#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/** ----------------------------------------------------
 * Sets the environments variables for pre processing
 * of naphtha code
 * 
 * -> _ALKR_SIMDMODE : bool, represents if SIMD is ON
 * -> _ALKR_PARAMODE : bool, same but for pthread
 * -> _ALKR_REGTYPE  : type, the type of the SIMD registers
 * -> _ALKR_REGSZ    : int,  size in bytes of the REGTYPE */

#ifdef __SSE__

#include <xmmintrin.h>
#include <emmintrin.h>
#define _ALKR_SIMDMODE 1

#ifdef __AVX__

        #include <immintrin.h>
        #define _ALKR_REGTYPE __m256
        #define _ALKR_REGSZ 32
#else

        #define _ALKR_REGTYPE __m128
        #define _ALKR_REGSZ 16
#endif

#else

#define _ALKR_SIMDMODE 0
#define _ALKR_REGTYPE uint64_t
#define _ALKR_REGSZ 8
#endif

 #ifdef _POSIX_THREADS 

#include <pthread.h>
#define _ALKR_PARAMODE 1
#else

#define _ALKR_PARAMODE 0
#endif

#define _ALKR_ASINTRINSICS(VarName,Color)		 \
	_ALKR_REGTYPE VarName = (_ALKR_REGTYPE)0;	 \
	for (int fill = 0; fill < Color.Size/8; ++fill) {\
	}

// -------------------------------------------------------
//
// Rate of buffer adaptation

#define ALKORE_ROBA_DX 50
// When the size of the window excedes the
// buffer's it increases the buffer's dx
// by this amount
#define ALKORE_ROBA_DY 25
// Same but for DY

#define ALKC_COREINITD
// Used to avoid conflict in case a compatiblity
// library was included before the core

#define VTINIT_compositeFORMAT(BitPerColor,BitForAlpha,BitsAmount,GCID)	\
	((BitPerColor)<<(24) | ((BitForAlpha)<<(16)) | ((BitsAmount)<<(8)) | (GCID))
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
 * Bits 8-15	 allocated to Global bits amount argument
 * Bits 16-23	 allocated to BitPerColor argument
 * Bits 24-31	 allocated to BitForAlpha argument
 * 
 * ----------------------------------------------------------------*/ 

#define VTEXTRACT_compositeFORMATARGUMENTS(Name,STBIT) (((Name)>>(STBIT))%256)
/** ----------------------- compositeEXTRACTION --------------------------
 *
 * Macro : EXtracts the given composite argument
 *
 * Usage : VTEXTRACT_compositeFORMATARGUMENTS(RGB16,BPCAindex);
 *                                                            
~                            	Extracts the BitPerColor Argument of RGB16 compFORM
 * 0 = GCID,	8 = Amount of bits,	16 = BPCA,	24 = BFAA
 * ---------------------------------------------------------------------*/


#define VTDEFINE_compositePROTOCOLS(ColorFormatAmount)\
	int VTCONST_compositePROTOCOLS[(ColorFormatAmount)*(ColorFormatAmount)];
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
	VTDEFINE_compositeFORMAT(RGB,8,0,24,0);			

//=============================== NAPHTHA ======================================//
										//
static struct compositeFORMAT{							//
	unsigned char BPCA;		// Bit per color argument		//
	unsigned char BFAA;		// Bit per alpha argument		//
	unsigned char Size;		// Amount of bits per pixel		//
	unsigned char GCID;		// GLobal caracterizing identifier	//
	unsigned int StorageFormat;	// Total int for internal processing	//
	_ALKR_REGTYPE IntriReg;							//
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
VT_naphtha* CNaphtA,const int cFORMAT,int Padding);				//
										//
VT_naphtha* VTINIT_naphtha(int sizeX,int sizeY,const int cFORMAT);		//
// Usage : VT_naphtha RandomVariable = VTINIT_naphtha(120,90,RGBA32);		//
										//
bool VTFREE_naphtArray(VT_naphtha* CNaphtA);					//
// Returns if the function was successful					//
// -----------------------------------------------------------------------------//

void VTINIT_mallocnapht(VT_naphtha* CNaphtA);

