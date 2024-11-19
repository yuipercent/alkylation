#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#ifndef ALKC_COREINITD
#include "../core/alkore.h"
#endif

#define TRUETYPE 0x00010000
#define	OPENTYPE 0x4F54544F

enum _NTFONT_TABLETYPE{
	_NTFONT_TTP_CMAP = 0x636d6170,
	_NTFONT_TTP_GLYF = 0x676c7966,
	_NTFONT_TTP_HEAD = 0x68656164,
	_NTFONT_TTP_HHEA = 0x68686561,
	_NTFONT_TTP_LOCA = 0x6c6f6361,
	_NTFONT_TTP_MAXP = 0x6d617870,
	_NTFONT_TTP_NAME = 0x6e616d65,
	_NTFONT_TTP_POST = 0x706f7374,
	_NTFONT_TTP_OSD2 = 0x6f732f32,
	_NTFONT_TTP_KERN = 0x6b65726e,
	_NTFONT_TTP_GSUB = 0x67737562,
	_NTFONT_TTP_GPOS = 0x67706f73
};

enum _NTFONT_TABLETYPEINDEX{
	_NTFONT_TTPI_CMAP = 0x0001,
	_NTFONT_TTPI_GLYF = 0x0002,
	_NTFONT_TTPI_HEAD = 0x0004,
	_NTFONT_TTPI_HHEA = 0x0008,
	_NTFONT_TTPI_LOCA = 0x0010,
	_NTFONT_TTPI_MAXP = 0x0020,
	_NTFONT_TTPI_NAME = 0x0040,
	_NTFONT_TTPI_POST = 0x0080,
	_NTFONT_TTPI_OSD2 = 0x0100,
	_NTFONT_TTPI_KERN = 0x0200,
	_NTFONT_TTPI_GSUB = 0x0400,
	_NTFONT_TTPI_GPOS = 0x0800,
	
};

enum _NTFONT_TABLEFSFORMAT{
	_NTFONT_FSF_STORED,
	_NTFONT_FSF_FSREAD
};

typedef struct{
	uint32_t tag;
	uint32_t checksum;
	uint32_t offset;
	uint32_t len;
} _NTFONT_TABLEDT;

typedef struct{
	int16_t px;
	int16_t py;
} _NTFONT_POINT;

typedef struct{
	_NTFONT_POINT* points;
	double* coefs;
	unsigned char order;
}_NTFONT_BEZCURV;

// -< FS Structures >----------
//
typedef struct{
        uint32_t format;
        uint16_t num_tables;
        uint16_t search_range;
        uint16_t entry_selector;
        uint16_t range_shift;
}_NTFONT_TTHEADER;

typedef struct{
        uint32_t tag;
        uint32_t checksum;
        uint32_t offset;
        uint32_t length;
}_NTFONT_TABLERECORD;

typedef struct{
        _NTFONT_TTHEADER	header;
	_NTFONT_TABLERECORD*	records;

	uint16_t tablemap;
	char	 f_lock;
	FILE*	 srcfile;
}_NTFONT_TTFILE;

extern _NTFONT_TTFILE* _NTFONT_READTTF(const char* folder);

void _NTFONT_CLOSE(_NTFONT_TTFILE* cfile);

