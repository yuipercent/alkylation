#include <stdint.h>

#define ALKC_FRONTENDMODE
// Used to know wether alkore.h is being defined
// in frontend or backend to avoid conflict

#ifndef ALKC_COREINITD

#include "core/alkore.h"
#endif

// ====================================================
#include "plug/naphtools.h"

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
