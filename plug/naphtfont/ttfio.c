#ifndef _NTFONTCONST_COMMONDEFD
#include "common.c"
#endif

static inline void
_NTFONT_TESTFLOCK(_NTFONT_TTFILE* cfile) {
	if (cfile->f_lock == 'y') {
                printf("Segmentation Fault (core dumped) : \n[Alkylation]:/:naphtfont: illegal access to ttfile FILE attribute while locked.\n");
                exit(139);
	};
};

// --< fread functions >-----------
//
// -> Head
static inline void
_NTFONT_READ_TTFHEADER(_NTFONT_TTFILE* cfile) {
	
	_NTFONT_TESTFLOCK(cfile);
	_NTFONT_FREAD_SWAPEND32(&cfile->header.format,cfile->srcfile);
	fseek(cfile->srcfile,4,SEEK_SET);

	_NTFONT_FREAD_SWAPEND16(&cfile->header.num_tables,cfile->srcfile);
	fseek(cfile->srcfile,2,SEEK_CUR);

	_NTFONT_FREAD_SWAPEND16(&cfile->header.search_range,cfile->srcfile);
	fseek(cfile->srcfile,2,SEEK_CUR);

	_NTFONT_FREAD_SWAPEND16(&cfile->header.entry_selector,cfile->srcfile);
	fseek(cfile->srcfile,2,SEEK_CUR);

	_NTFONT_FREAD_SWAPEND16(&cfile->header.range_shift,cfile->srcfile);
	fseek(cfile->srcfile,2,SEEK_CUR);
};

// -> Table record
static inline void
_NTFONT_READ_TTRECORD(_NTFONT_TTFILE* cfile) {
	
	_NTFONT_TESTFLOCK(cfile);

};

// -> General interpreter
_NTFONT_TTFILE* _NTFONT_READTTF(const char* folder) {

	_NTFONT_TTFILE* cfile = (_NTFONT_TTFILE*)
	malloc(sizeof(_NTFONT_TTFILE));

	cfile->f_lock = 'n';
	cfile->srcfile = fopen(folder,"rb");
	_NTFONT_READ_TTFHEADER(cfile);

	if (cfile->header.format != TRUETYPE) {
		printf("[Alkylation]:/:naphtfont: TrueType is the only supported format for this version\n");
		exit(1);
	};
	return cfile;
};

void _NTFONT_CLOSE(_NTFONT_TTFILE* cfile) {
	fclose(cfile->srcfile);
	cfile->f_lock = 'y';
	cfile->srcfile = NULL;
};
