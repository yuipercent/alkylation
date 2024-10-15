#ifndef ALKC_COREINITD

#include "../core/alkore.h"
#endif

/**========================== NAPHTSCHEM ========================================
 * A simulated naphtha :
 * When an instruction that modifies the naphtarray is executed on it,
 * the instruction is not executed but stored for later and will
 * be executed on the naphtarray buffer directly instead of going
 * through an intermediary
 *
 *  /!/ Depending on the use you're making of this structure, this can be
 * 	counter-productive as the arguments of the instructions executed
 * 	on it are entirely copied, which could result in an overall
 * 	decrease in performance							*/

typedef struct VT_naphtschem{
	int DX;
	int DY;
	int offsetX;
	int padding;
	int bytes_per_line;
}VT_naphtschem;

