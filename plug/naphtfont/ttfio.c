#ifndef _NTFONTCONST_COMMONDEFD
#include "common.c"
#endif

extern inline void
_NTFONT_TESTFLOCK(_NTFONT_TTFILE* cfile) {
	if (cfile->f_lock == 'y') {
                printf("Segmentation Fault (core dumped) : \n[Alkylation]:/:naphtfont: illegal access to ttfile FILE attribute while locked.\n");
                exit(139);
	};
};

extern inline char _NTFONT_TESTFONT_ISSUPPORTED(uint32_t tag) {
	return (
		(tag == _NTFONT_TTP_CMAP) || (tag == _NTFONT_TTP_GLYF) ||
		(tag == _NTFONT_TTP_HEAD) || (tag == _NTFONT_TTP_HHEA) ||
		(tag == _NTFONT_TTP_LOCA) || (tag == _NTFONT_TTP_MAXP) ||
		(tag == _NTFONT_TTP_NAME) || (tag == _NTFONT_TTP_POST) ||
		(tag == _NTFONT_TTP_OSD2) || (tag == _NTFONT_TTP_KERN) ||
		(tag == _NTFONT_TTP_GSUB) || (tag == _NTFONT_TTP_GPOS)
	);
};

static inline uint16_t
_NTFONT_MAPSUPPORT(_NTFONT_TTFILE* cfile) {

	uint32_t supmap = 0;

	for (int itx = 0; itx < cfile->header.num_tables; ++itx) {
		_NTFONT_TABLERECORD* cRecord = &cfile->records[itx];
		switch (cRecord->tag) {
			case _NTFONT_TTP_CMAP:
				supmap |= _NTFONT_TTPI_CMAP;
			case _NTFONT_TTP_GLYF:
				supmap |= _NTFONT_TTPI_GLYF;
			case _NTFONT_TTP_HEAD:
				supmap |= _NTFONT_TTPI_HEAD;
			case _NTFONT_TTP_HHEA:
				supmap |= _NTFONT_TTPI_HHEA;
			case _NTFONT_TTP_LOCA:
				supmap |= _NTFONT_TTPI_LOCA;
			case _NTFONT_TTP_MAXP:
				supmap |= _NTFONT_TTPI_MAXP;
			case _NTFONT_TTP_NAME:
				supmap |= _NTFONT_TTPI_NAME;
			case _NTFONT_TTP_POST:
				supmap |= _NTFONT_TTPI_POST;
			case _NTFONT_TTP_OSD2:
				supmap |= _NTFONT_TTPI_OSD2;
			case _NTFONT_TTP_KERN:
				supmap |= _NTFONT_TTPI_KERN;
			case _NTFONT_TTP_GSUB:
				supmap |= _NTFONT_TTPI_GSUB;
			case _NTFONT_TTP_GPOS:
				supmap |= _NTFONT_TTPI_GPOS;
		};
	};
	return supmap;
};

// --< fread functions >-----------
//
// -> binary search for the tabletag
_NTFONT_TABLERECORD* _NTFONT_TTGET_TABLERECORD(_NTFONT_TTFILE* cfile, uint32_t tabletag) {

	int halfp = cfile->header.search_range >> 1;
	int ci = halfp;
	for (int itx = 0; itx < cfile->header.entry_selector; ++itx) {
	
		halfp = halfp >> 1;

		if (tabletag < cfile->records[ci].tag) {
			ci -= halfp;
		} else if (tabletag > cfile->records[ci].tag) {
			ci += halfp;
		} else {
			return &cfile->records[ci];
		};
	};

	for (int itx = cfile->header.search_range; 
	itx < (cfile->header.num_tables); ++itx) {
		if (cfile->records[itx].tag == tabletag) {
		return &cfile->records[itx];
		};
	};
	
	return NULL;
};

// -> General interpreter
_NTFONT_TTFILE* _NTFONT_READTTF(const char* folder,char read_mode) {

	_NTFONT_TTFILE* cfile = (_NTFONT_TTFILE*)
	malloc(sizeof(_NTFONT_TTFILE));

	cfile->f_lock = 'n';
	cfile->srcfile = fopen(folder,"rb");
	fseek(cfile->srcfile,0,SEEK_SET);
	
	// -> Loads the file header
	_NTFONT_FREAD_LIEND32(cfile->srcfile,&cfile->header,0,4);
	_NTFONT_FREAD_LIEND16(cfile->srcfile,&cfile->header,2,8);
	cfile->header.search_range /= 16;
	cfile->header.range_shift  /= 16;

	if (cfile->header.format != TRUETYPE) {
		printf("[Alkylation]:/:naphtfont: TrueType is the only supported format for this version\n");
		exit(1);
};
	
	// - Init table records - - - - - - - - - - - - - - - - - - - -	//
									//
	int allocSZ = sizeof(_NTFONT_TABLERECORD)*cfile->header.num_tables;
	cfile->records = (_NTFONT_TABLERECORD*)malloc(allocSZ);		//
	_NTFONT_FREAD_LIEND32(cfile->srcfile,cfile->records,0,allocSZ);	//
									//
	cfile->tablemap = _NTFONT_MAPSUPPORT(cfile);			//
	
	// -> Read table : 'head'
	//_NTFONT_FREAD_LIEND16(cfile->srcfile,&cfile->table_head,0,4);
	//fseek(cfile->srcfile,12,SEEK_CUR);
	//_NTFONT_FREAD_LIEND16(cfile->srcfile,&cfile->table_head,2,4);
	//fseek(cfile->srcfile,16,SEEK_CUR);
	//_NTFONT_FREAD_LIEND16(cfile->srcfile,&cfile->table_head,4,18);

	return cfile;
};

void _NTFONT_CLOSE(_NTFONT_TTFILE* cfile) {
	fclose(cfile->srcfile);
	cfile->f_lock = 'y';
	cfile->srcfile = NULL;
};
