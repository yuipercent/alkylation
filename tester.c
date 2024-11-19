#include "alkylfw.h"

int main() {
	ALKC_STDWD* wd = ALKC_INITWD(250,400,RGB32);
	//naphtFORMAT(wd->Buffer,RGB,8);
	ALKC_OPENWD(wd);
	_NTFONT_TTFILE* abc = _NTFONT_READTTF("/doc/code/alkylation/plug/naphtfont/defaultfonts/Consolas.ttf");
	_NTFONT_CLOSE(abc);
	while (ALKC_LOOPWD(wd)) {
	};
	return 0;
};
