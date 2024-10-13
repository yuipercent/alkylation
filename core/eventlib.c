#include "eventlib.h"

void ALKI_ELISTAppend(				//
ALKI_EVENTLIST* Elist, ALKCEVENT AppendEvent) {	//
// -----------------------------------------------
	Elist->Events[Elist->HeadIndex] = AppendEvent;
	// Increases the indent of the Headindex
	Elist->HeadIndex = 
	(Elist->HeadIndex + 1) % ALKICONST_EVENTN;
};

ALKCEVENT ALKI_ELISTGetEvent(ALKI_EVENTLIST Elist) {
	ALKCEVENT& ToReturnEvent =
	Elist.Events[Elist.CurrentPos];
};
