#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/** ----------------------------------------------------
 * Sets the environments variables for pre processing
 * of naphtha code
 * 
 * -> _ALKR_SIMDMODE : bool, represents if SIMD is ON
 * -> _ALKR_PARAMODE : bool, same but for pthread
 * -> _ALKR_REGTYPE  : type, the type of the SIMD registers
 * -> _ALKR_REGSZ    : int,  size in bytes of the REGTYPE */

#ifndef _ALKR_SIMD_CONTEXTCLIB
#include "simdclib.h"
#define _ALKR_SIMD_CONTEXTCLIB
#endif

/** ================ ALKORE SIMD IMPLEMENTATION DOC ==================//
 * */
// --------------------------------------------------------------
//
// Rate of buffer adaptation

#define ALKORE_ROBA_DX 100
// When the size of the window excedes the
// buffer's it increases the buffer's dx
// by this amount
#define ALKORE_ROBA_DY 70
// Same btbh viens on se suicide ut for DY

#define ALKC_COREINITD
// Used to avoid conflict in case a compatiblity
// library was included before the core

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

//=============================== NAPHTHA ======================================//
										//
extern struct compositeFORMAT{							//
	unsigned char BPCA;		// Bit per color argument		//
	unsigned char BFAA;		// Bit per alpha argument		//
	unsigned char Size;		// Amount of bytes per pixel		//
	unsigned char GCID;		// GLobal caracterizing identifier	//
	unsigned char padding;							//
}compositeFORMAT;								//
typedef struct VT_naphtha {							//
	bool lock;								//
	int dx;									//
	int dy;									//
	int offsetX;								//
	int bytes_per_line;							//
        void* naphtArray;							//
	int naphtarray_size;							//
	struct compositeFORMAT format;						//
}VT_naphtha;									//
//--------------------------- AFFILIATED FUNCTIONS -----------------------------//
										//
extern void VTINIT_naphtFORMAT(							//
VT_naphtha* CNaphtA,struct compositeFORMAT cFORMAT);				//
										//
VT_naphtha* VTINIT_naphtha(int sizeX,int sizeY,struct compositeFORMAT cFORMAT);	//
// Usage : VT_naphtha RandomVariable = VTINIT_naphtha(120,90,RGBA32);		//
										//
bool VTFREE_naphtArray(VT_naphtha* CNaphtA);					//
// Returns if the function was successful					//
// -----------------------------------------------------------------------------//

// --< Core datas of a window >---------//
//					//
typedef struct WDinfo{			//
	int dx;				//
	int dy;				//
	VT_naphtha* buffer;		//
	struct compositeFORMAT format;	//
}WDinfo;				//
//					//
// -------------------------------------//
// Since ALKC_STDWD is only determined at
// compilation this serves as a standardized
// data holder for all modules

void VTINIT_mallocnapht(VT_naphtha* CNaphtA);

extern void VT_naphtLock(VT_naphtha* CNaphtA);

extern void VT_naphTestLock(VT_naphtha* CNaphtA);

