#define ALKC_FRONTENDMODE
// Used to know wether alkore.h is being defined
// in frontend or backend to avoid conflict

#ifndef ALKC_COREINITD

#include "core/alkore.h"
#endif

#define AlkcWD ALKC_STDWD
#define InitWD ALKC_INITWD
#define OpenWD ALKC_OPENWD
#define LoopWD ALKC_LOOPWD

#define napht VT_naphtha

enum ALKYLcompositeSCHEMS{
	RGBA32 = VTINIT_compositeFORMAT(8,8,32,0),
	RGB = VTINIT_compositeFORMAT(8,0,24,0)
}ALKYLcompositeSCHEMS;

