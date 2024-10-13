#include "srclib/alkc_x11.h"
#include "alkylfw.h"

int main() {
	ALKC_STDWD* wd = ALKC_INITWD(250,480);
	ALKC_OPENWD(wd);
	napht* test = VTINIT_naphtha(250,5,RGB);
	while (ALKC_LOOPWD(wd)) {
		
	};
	return 0;
};
