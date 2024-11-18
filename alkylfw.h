#define ALKC_FRONTENDMODE

// --< OS specific library include >----//
//					//
#ifdef _WIN32				//
#include "srclib/alkc_windows.h"	//
#endif					//
					//
#ifdef __unix				//
#include "srclib/alkc_x11.h"		//
#endif					//
					//
#ifdef __APPLE__			//
#include "srclib/alkc_apl.h"		//
#endif					//
// -------------------------------------//

#ifndef ALKC_COREINITD

#include "core/alkore.h"
#endif

// ====================================================

#ifndef ALKC_EMBED

#include "plug/naphtools.h"
#include "plug/naphtfont.h"
#else
// Planned lightweight librairies
#endif

#define STDWD  ALKC_STDWD
#define InitWD ALKC_INITWD
#define OpenWD ALKC_OPENWD
#define LoopWD ALKC_LOOPWD
#define naphtFORMAT	VTINIT_naphtFORMAT
#define naphtha		VTINIT_naphtha

#define napht VT_naphtha

#define RGB ((const struct compositeFORMAT) {	\
		.BPCA = 8,			\
		.BFAA = 0,			\
		.Size = 3,			\
		.padding = 0,			\
		.GCID = 128			\
		})

// RGB32 : 8 bit per color, 0 for alpha, 8 padding for 4 bytes
#ifndef ALKC_EMBED
#define RGB32 ((const struct compositeFORMAT) {	\
		.BPCA = 8,			\
		.BFAA = 0,			\
		.Size = 4,			\
		.padding = 8,			\
		.GCID = 128			\
		})

#define RGBA32 ((const struct compositeFORMAT) {\
		.BPCA = 8,			\
		.BFAA = 8,			\
		.Size = 4,			\
		.padding = 0,			\
		.GCID = 192			\
		})

enum ALKYLWDconfigs{
	ALKCDEFAULT = 34493962240,
	ALKCDEFAULTALPHA = 34494488576
}ALKYLWDconfigs;
#else

#define ALKCDEFAULT 34493962240
#endif
