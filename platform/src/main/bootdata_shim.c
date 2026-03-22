/* Placeholder bootdata symbols for Apple bring-up builds. */
unsigned char gam_win1_winT_model[8];
unsigned char gam_win2_winT_model[8];

unsigned char gam_win1_cursor_model[8];

unsigned char gam_win1_moji_model[8];
unsigned char gam_win1_moji2_model[8];
unsigned char gam_win1_moji3_model[8];

unsigned char gam_win2_moji_model[8];
unsigned char gam_win3_moji_model[8];

unsigned char nintendo_376x104[8];
unsigned char logo_nin_v[8];
unsigned char logo_ninT_model[8];

void* my_malloc_current;
int osAppNMIBuffer[16];

unsigned char save_game_image;
void* nesrom_filename_ptrs;

unsigned int nesinfo_tags_size;
unsigned char* nesinfo_tags_start;
unsigned char* nesinfo_tags_end;

unsigned int nesinfo_data_size;
unsigned char* nesinfo_data_start;
unsigned char* nesinfo_data_end;

unsigned char InputValid[4];
unsigned int InputData[4];
unsigned int InputButton[4];
unsigned int InputTrigger[4];
unsigned int InputRepeat[4];
unsigned int InputRepeatCount[4];

unsigned char tcs_bad;
unsigned char ics_bad;

unsigned char famicomCommon[0xB8];
