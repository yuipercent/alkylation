#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>

//#include "eventlib.h"

#ifndef ALKC_FRONTENDMODE

#include "alkore.h"
#define NAPHTBUFFERMODE VTINIT_compositeFORMAT(8,0,24,0)
#endif

#define ALKC_EVENTSAMOUNT 5

#define ALKCDEFINE_EVENTMAPPING(EntryType,TypeClass,EventAmount)\
								\
	struct ALKISCHEM_EVENTMAPPING{				\
		TypeClass KEYS[EventAmount];			\
		int VALUES[EventAmount];			\
		int EVENTAMOUNT;				\
	}ALKI_EVENTMAPPING;					\
								\
	static struct ALKISCHEM_EVENTMAPPING 			\
	ALKCEVENT_INITMAP() {					\
		struct ALKISCHEM_EVENTMAPPING toreturn;		\
		toreturn.EVENTAMOUNT = 0;			\
		return toreturn;				\
	};							\
								\
	void ALKCEVENT_MAP(TypeClass CEventID,			\
	struct ALKISCHEM_EVENTMAPPING Mapping){			\
		if (Mapping.EVENTAMOUNT >= EventAmount) {	\
			printf("IndexError: Cannot map events beyond the pre allocated amount : %d",EventAmount);	exit(139);\
		};						\
		Mapping.KEYS[Mapping.EVENTAMOUNT] = CEventID;	\
		Mapping.VALUES[Mapping.EVENTAMOUNT] = 0;	\
		Mapping.EVENTAMOUNT += 1;			\
		return;						\
	};							\
								\
	//======================================================/

	/**------------------------------------------------------
	 * ALKCDEFINE_EVENTMAPPING DOCUMENTATION :		\
	 * ------------------------------------------------------
	 *  Defines the structures based on the current		\
	 *  environment for event processing			\
	 *							\
	 *  Usage : ALKCDEFINE_EVENTMAPPING(XEvent,int,6);	\
	 *  Defines the EVENTMAPPING to map an XEvent with a	\
	 *  type identifier of type "int" with an amount of 6	\
	 *  events at total.					\
	 *  							\
	 * - - - - - - - - - - - - - - - - - - - - - - - - - - -\
	 * The macro defines the following:			\
	 *							\
	 * -> struct ALKISCHEM_EVENTMAPPING			\
	 *  	# A mapping of events, links the event to	\
	 *  	# the extractor, AKA the function by which	\
	 *  	# an inputted event is converted into an ALKORE	\
	 *  	# compatible event.				\
	 * 	# Event of index x is linked to the extractor	\
	 * 	# of index x, for example if KEYS[0] is the	\
	 * 	# mouseclick event, function EXTRACTOR[0] is	\
	 * 	# executed on KEYS[0]				\
	 * 							\
	 * -> function ALKCEVENT_INITMAP:			\
	 *  	# Returns an initialized Event mapping		\
	 *  							\
	 * -> function ALKCEVENT_MAP:				\
	 *  	# Assigns the event of identifier CEventID	\
	 *  	# to the extractor				\
	 *-----------------------------------------------------*/

#define ALKCDEFINE_WDPACKAGE(WDClass,initfc,	\
			     openfc, loopfc)			\
								\
	typedef struct ALKC_STDWD{				\
		VT_naphtha*	Buffer;				\
		WDClass*	WDWRAPPER;			\
		bool 		running;			\
	}ALKC_STDWD;						\
								\
	ALKC_STDWD* ALKC_INITWD					\
	(int dx, int dy){					\
		ALKC_STDWD* toreturn =				\
		(ALKC_STDWD*)malloc(sizeof(ALKC_STDWD));	\
								\
		toreturn->WDWRAPPER	 = initfc(dx,dy);	\
		toreturn->running	 = true;		\
		return toreturn;				\
	};							\
	void ALKC_OPENWD(ALKC_STDWD* wdhold) {			\
		openfc(wdhold->WDWRAPPER);			\
		wdhold->running = true;				\
	};							\
	bool ALKC_LOOPWD(ALKC_STDWD* wd) {			\
		loopfc(wd->WDWRAPPER);				\
		return wd->running;				\
	};							\
	void ALKC_SWAPBUFFER(ALKC_STDWD* wd,int nDX,int nDY) {	\
		free(wd->Buffer);				\
		wd->Buffer = VTINIT_naphtha(nDX,nDY,		\
					NAPHTBUFFERMODE);	\
	};							\

	/**------------------------------------------------------
	 * ALKCDEFINE_WDPACKAGE DOCUMENTATION :		\
	 * ------------------------------------------------------
	 *  Maps the OS-specific functions to the ALkylation	\
	 *  Compatibility Library functions			\
	 *							\
	 * Arguments are as follows:				\
	 * -> WDClass						\
	 *  	# Insert here the structure used to hold datas	\
	 * -> initfc						\
	 *  	# Insert here the function to instantiante	\
	 *  	# an object of WDClass				\
	 * -> openfc						\
	 *  	# Insert here the function used to open		\
	 *  	# the window					\
	 * -> loopfc						\
	 *  	# Insert here the function used to check wether	\
	 *  	# the main loop is still running or not		\
	 *							\
	 * All functions inputed here should be			\
	 * extern inline functions				\
	 * 							\
	 * - - - - - - - - - - - - - - - - - - - - - - - - - - -\
	 * Defined functions are the following:			\
	 * 							\
	 * -> ALKC_INITWD					\
	 *   # returns an initialized window			\
	 * -> ALKC_OPENWD					\
	 *   # preconfig window for opening			\
	 * -> ALKC_LOOPWD					\
	 *   # Returns a bool of if the window shall still run	\
	 *   # AND extracts the current event			\
	 *   							\
	 * -----------------------------------------------------\
*/
