#define EDB_DEFINED

enum EVENTDB_MouseButtonsENUM{
	EDB_MouseLEFT = (unsigned char)0,
	EDB_MouseRIGHT = (unsigned char)2,
	EDB_MouseMIDDLE = (unsigned char)1,
	EDB_MouseALT1 = (unsigned char)3,
	EDB_MouseALT2 = (unsigned char)4,
	EDB_MouseALT3 = (unsigned char)5,
	EDB_MouseALT4 = (unsigned char)6
};

enum EVENTDB_KeyboardKEYSENUM{
	EDB_KeyB_0 = 48,
	EDB_KEYB_1,
	EDB_KEYB_2,
	EDB_KEYB_3,
	EDB_KEYB_4,
	EDB_KEYB_5,
	EDB_KEYB_6,
	EDB_KEYB_7,
	EDB_KEYB_8,
	EDB_KEYB_9,
	EDB_KEYB_COLON,
	EDB_KEYB_SEMICOLON,
	EDB_KEYB_INFERIOR,
	EDB_KEYB_EQUALS,
	EDB_KEYB_SUPERIOR,
	EDB_KEYB_QUESTIONMARK,
	EDB_KEYB_ATSIGN,
	EDB_KEYB_A,
	EDB_KEYB_B,
	EDB_KEYB_C,
	EDB_KEYB_D,
	EDB_KEYB_E,
	EDB_KEYB_F,
	EDB_KEYB_G,
	EDB_KEYB_H,
	EDB_KEYB_I,
	EDB_KEYB_J,
	EDB_KEYB_K,
	EDB_KEYB_L,
	EDB_KEYB_M,
	EDB_KEYB_N,
	EDB_KEYB_O,
	EDB_KEYB_P,
	EDB_KEYB_Q,
	EDB_KEYB_R,
	EDB_KEYB_S,
	EDB_KEYB_T,
	EDB_KEYB_U,
	EDB_KEYB_V,
	EDB_KEYB_X,
	EDB_KEYB_Y,
	EDB_KEYB_Z,
	EDB_KEYB_a = 97,
	EDB_KEYB_b,
	EDB_KEYB_c,
	EDB_KEYB_d,
	EDB_KEYB_e,
	EDB_KEYB_f,
	EDB_KEYB_g,
	EDB_KEYB_h,
	EDB_KEYB_i,
	EDB_KEYB_j,
	EDB_KEYB_k,
	EDB_KEYB_l,
	EDB_KEYB_m,
	EDB_KEYB_n,
	EDB_KEYB_o,
	EDB_KEYB_p,
	EDB_KEYB_q,
	EDB_KEYB_r,
	EDB_KEYB_s,
	EDB_KEYB_t,
	EDB_KEYB_u,
	EDB_KEYB_v,
	EDB_KEYB_w,
	EDB_KEYB_x,
	EDB_KEYB_y,
	EDB_KEYB_z,
};

struct EVENTDB_MouseCLICK{
	int px;
	int py;
	unsigned int Button;
}ALKCEVENTDB_MouseCLICK;

struct EVENTDB_KeyboardPRESS{
	unsigned int KEY;
	unsigned int Type;
}ALKCEVENTDB_KeyboardPRESS;

typedef union ALKCEVENT{
	struct EVENTDB_MouseCLICK ALKE_MouseP;
	struct EVENTDB_KeyboardPRESS ALKE_KeyB;
}ALKCEVENT;
