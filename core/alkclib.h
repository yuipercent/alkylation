#include <X11/Xlib.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef ALKC_FRONTENDMODE

#include "alkore.h"
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
	 *  							*/

#define ALKCDEFINE_WDPACKAGE(WDClass,initfc,openfc,loopfc)	\
								\
	typedef struct ALKC_STDWD{				\
		WDClass WDWRAPPER;				\
		bool running;					\
	}ALKC_STDWD;						\
								\
	ALKC_STDWD ALKC_INITWD					\
	(int dx, int dy){					\
		ALKC_STDWD toreturn;				\
		toreturn.WDWRAPPER = initfc(dx,dy);		\
		toreturn.running = true;			\
		return toreturn;				\
	};							\
	void ALKC_OPENWD(ALKC_STDWD wdhold) {			\
		openfc(wdhold.WDWRAPPER);			\
		wdhold.running = true;				\
	};							\
	bool ALKC_LOOPWD(ALKC_STDWD wd) {			\
		loopfc(wd.WDWRAPPER);				\
		return wd.running;				\
	};							\

