/*

Copyright 2022, dettus@dettus.net

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this 
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


*/

#ifndef	THEME_ELEMENTS_H
#define	THEME_ELEMENTS_H
// the information in this file was taken from the "Winamp 2.X skinnig tutorial" Version 1.5.0, copyright by Fyre
#define	ELEMENTS_NUM	409
#define	SOURCES_NUM	16

// The WinAmp Skins have Elements. 
// A lot of them.
// To make development within this project easier, an enum can be used to address each one of them individually.
typedef enum 
{
// from avs.bmp
	AVS_CLOSE_BUTTON_PRESSED=0,
	AVS_UPPER_LEFT_CORNER,
	AVS_TOP_FILLER,
	AVS_UPPER_RIGHT_CORNER,
	AVS_LEFT_FILLER,
	AVS_RIGHT_FILLER,
	AVS_LOWER_LEFT_CORNER,
	AVS_BOTTOM_FILLER,
	AVS_LOWER_RIGHT_CORNER,

// from balance.bmp
	BALANCE_CENTERED,
	BALANCE_FILLER0,
	BALANCE_FILLER1,
	BALANCE_FILLER2,
	BALANCE_FILLER3,
	BALANCE_FILLER4,
	BALANCE_24LEFTORRIGHT,
	BALANCE_FILLER5,
	BALANCE_33LEFTORRIGHT,
	BALANCE_FILLER6,
	BALANCE_FILLER7,	
	BALANCE_40LEFTORRIGHT,
	BALANCE_FILLER8,
	BALANCE_49LEFTORRIGHT,
	BALANCE_FILLER9,
	BALANCE_58LEFTORRIGHT,
	BALANCE_FILLER10,
	BALANCE_66LEFTORRIGHT,
	BALANCE_FILLER11,
	BALANCE_FILLER12,
	BALANCE_74LEFTORRIGHT,
	BALANCE_FILLER13,
	BALANCE_82LEFTORRIGHT,
	BALANCE_FILLER14,
	BALANCE_91LEFTORRIGHT,
	BALANCE_FILLER15,
	BALANCE_FILLER16,
	BALANCE_100LEFTORRIGHT,
	BALANCE_SLIDER_PRESSED,
	BALANCE_SLIDER_UNPRESSED,

// from cbuttons.bmp
	CBUTTONS_PREV_BUTTON_UNPRESSED,
	CBUTTONS_PLAY_BUTTON_UNPRESSED,
	CBUTTONS_PAUSE_BUTTON_UNPRESSED,
	CBUTTONS_STOP_BUTTON_UNPRESSED,
	CBUTTONS_NEXT_BUTTON_UNPRESSED,
	CBUTTONS_OPEN_BUTTON_UNPRESSED,
	CBUTTONS_PREV_BUTTON_PRESSED,
	CBUTTONS_PLAY_BUTTON_PRESSED,
	CBUTTONS_PAUSE_BUTTON_PRESSED,
	CBUTTONS_STOP_BUTTON_PRESSED,
	CBUTTONS_NEXT_BUTTON_PRESSED,
	CBUTTONS_OPEN_BUTTON_PRESSED,

// from eq_ex.bmp	
	EQEX_EQUALIZER_WINDOWSHADE_ACTIVE,
	EQEX_VOLUMECONTROL_ACTIVE,
	EQEX_BALANCECONTROL_ACTIVE,
	EQEX_EQUALIZER_WINDOWSHADE_INACTIVE,
	EQEX_VOLUMECONTROL_INACTIVE,
	EQEX_BALANCECONTROL_INACTIVE,
	EQEX_VOLUMESLIDER_LOW,
	EQEX_VOLUMESLIDER_MEDIUM,
	EQEX_VOLUMESLIDER_HIGH,
	EQEX_BALANCESLIDER_LEFT,
	EQEX_BALANCESLIDER_MIDDLE,
	EQEX_BALANCESLIDER_RIGHT,
	EQEX_WINDOWSHADE_BUTTON_PRESSED,
	EQEX_CLOSEBUTTON_UNPRESSED,
	EQEX_MAXIMIZEBUTTON_PRESSED,
	EQEX_CLOSEBUTTON_PRESSED,

// from eqmain.bmp
	EQMAIN_EQUALIZER_TITLEBAR,
	EQMAIN_EQUALIZER_MAIN_DISPLAY,
	EQMAIN_EQUALIZER_MINIDISPLAY,
	EQMAIN_EQUALIZER_ON,
	EQMAIN_AUTOMATIC_EQUALIZATION,
	EQMAIN_OPEN_PRESET_MENU,
	EQMAIN_20DB_RESET,
	EQMAIN_PREAMP_BAR,
	EQMAIN_60HZ_BAR,
	EQMAIN_170HZ_BAR,
	EQMAIN_310HZ_BAR,
	EQMAIN_600HZ_BAR,
	EQMAIN_1KHZ_BAR,
	EQMAIN_3KHZ_BAR,
	EQMAIN_6KHZ_BAR,
	EQMAIN_12KHZ_BAR,
	EQMAIN_14KHZ_BAR,
	EQMAIN_16KHZ_BAR,
	EQMAIN_0DB_RESET,
	EQMAIN_M20DB_RESET,
	EQMAIN_CLOSE_BUTTON_UNPRESSED,
	EQMAIN_EQUALIZER_OFF_UNPRESSED,
	EQMAIN_AUTO_OFF_UNPRESSED,
	EQMAIN_EQUALIZER_ON_UNPRESSED,
	EQMAIN_AUTO_ON_UNPRESSED,
	EQMAIN_EQUALIZER_OFF_PRESSED,
	EQMAIN_AUTO_OFF_PRESSED,
	EQMAIN_EQUALIZER_ON_PRESSED,
	EQMAIN_AUTO_ON_PRESSED,
	EQMAIN_CLOSE_BUTTON_PRESSED,
	EQMAIN_EQUALIZER_TITLEBAR_ACTIVE,
	EQMAIN_EQUALIZER_TITLEBAR_INACTIVE,
	EQMAIN_EQUALIZER_SLIDER_UNPRESSED,
	EQMAIN_M2000DB_BAR,
	EQMAIN_M1875DB_BAR,
	EQMAIN_M1714DB_BAR,
	EQMAIN_M1571DB_BAR,
	EQMAIN_M1429DB_BAR,
	EQMAIN_M1286DB_BAR,
	EQMAIN_M1143DB_BAR,
	EQMAIN_M1000DB_BAR,
	EQMAIN_M0857DB_BAR,
	EQMAIN_M0714DB_BAR,
	EQMAIN_M0571DB_BAR,
	EQMAIN_M0428DB_BAR,
	EQMAIN_M0285DB_BAR,
	EQMAIN_M0142DB_BAR,
	EQMAIN_PRESET_BUTTON_UNPRESSED,
	EQMAIN_EQUALIZER_SLIDER_PRESSED,
	EQMAIN_PRESET_BUTTON_PRESSED,
	EQMAIN_P0142DB_BAR,
	EQMAIN_P0285DB_BAR,
	EQMAIN_P0428DB_BAR,
	EQMAIN_P0571DB_BAR,
	EQMAIN_P0714DB_BAR,
	EQMAIN_P0857DB_BAR,
	EQMAIN_P1000DB_BAR,
	EQMAIN_P1143DB_BAR,
	EQMAIN_P1286DB_BAR,
	EQMAIN_P1429DB_BAR,
	EQMAIN_P1571DB_BAR,
	EQMAIN_P1714DB_BAR,
	EQMAIN_P1857DB_BAR,
	EQMAIN_P2000DB_BAR,
	EQMAIN_ACTUAL_EQUALIZER_MINIDISPLAY,
	EQMAIN_SPLINE_LINE,
	EQMAIN_PREAMP_LINE,

// from main.bmp
	MAIN_MAIN_DISPLAY,
	MAIN_SONG_INFO_DISPLAY,
	MAIN_KBPS_DISPLAY,
	MAIN_KHZ_DISPLAY,
	MAIN_VISUALIZATION_WINDOW,
	MAIN_INFO,

// from mb (minibrowser)
	MB_UPPER_LEFT_CORNERPIECE_ACTIVE,
	MB_TITLEBAR_ACTIVE,
	MB_TOP_FILLERS_ACTIVE,
	MB_UPPER_RIGHT_CORNERPIECE_ACTIVE,
	MB_UPPER_LEFT_CORNERPIECE_INACTIVE,
	MB_TITLEBAR_INACTIVE,
	MB_TOPFILLERS_INACTIVE,
	MB_UPPER_RIGHT_CORNERPIECE_INACTIVE,
	MB_BOTTOM_LEFT_CONTROLBAR,
	MB_LEFT_SIDE_FILLERS,
	MB_RIGHT_SIDE_FILLERS,
	MB_CLOSE_BUTTON_PRESSED,
	MB_BACK_BUTTON_PRESSED,
	MB_FORWARD_BUTTON_PRESSED,
	MB_STOP_BUTTON_PRESSED,
	MB_RELOAD_BUTTON_PRESSED,
	MB_OPTIONS_BUTTON_PRESSED,
	MB_BACK_BUTTON_UNPRESSED,
	MB_FORWARD_BUTTON_UNPRESSED,
	MB_STOP_BUTTON_UNPRESSED,
	MB_RELOAD_BUTTON_UNPRESSED,
	MB_OPTIONS_BUTTON_UNPRESSED,
	MB_URL_DISPLAY_BAR_LEFT_END,
	MB_BOTTOM_RIGHT_CONTROL_BAR,
	MB_BOTTOM_FILLER,
	MB_URL_DISPLAY_BAR_RIGHT_END,
	MB_DISPLAY_BAR_FILLER,
	MB_RESIZE_CONTROL,

// from monoster.bmp
	MONOSTER_STEREO_ACTIVE,
	MONOSTER_MONO_ACTIVE,
	MONOSTER_STEREO_INACTIVE,
	MONOSTER_MONO_INACTIVE,

// from numbers.bmp
	NUMBERS_0,
	NUMBERS_1,
	NUMBERS_2,
	NUMBERS_3,
	NUMBERS_4,
	NUMBERS_5,
	NUMBERS_6,
	NUMBERS_7,
	NUMBERS_8,
	NUMBERS_9,
	NUMBERS_BLANK,

// from playpause.bmp
	PLAYPAUSE_PLAY_INDICATOR,
	PLAYPAUSE_PAUSE_INDICATOR,
	PLAYPAUSE_STOP_INDICATOR,
	PLAYPAUSE_FILLER,
	PLAYPAUSE_START_OF_SONG_INDICATOR,
	PLAYPAUSE_END_OF_SONG_INDICATOR,

// from pledit.bmp
	PLEDIT_UPPER_LEFT_CORNERPIECE_ACTIVE,
	PLEDIT_PLAYLIST_TITLEBAR_ACTIVE,
	PLEDIT_TOP_FILLERS_ACTIVE,
	PLEDIT_UPPER_RIGHT_CORNERPIECE_ACTIVE,
	PLEDIT_BOTTOM_FILLERS,
	PLEDIT_VISUALIZATION_MINISCREEN,
	PLEDIT_UPPER_LEFT_CORNERPIECE_INACTIVE,
	PLEDIT_PLAYLIST_TITLEBAR_INACTIVE,
	PLEDIT_TOP_FILLERS_INACTIVE,
	PLEDIT_UPPER_RIGHT_CORNERPIECE_INACTIVE,
	PLEDIT_LEFT_SIDE_FILLERS,
	PLEDIT_RIGHT_SIDE_FILLERS_LEFT_BAR,
	PLEDIT_RIGHT_SIDE_FILLERS_SCROLL_GROOVE,
	PLEDIT_RIGHT_SIDE_FILLERS_RIGHT_BAR,
	PLEDIT_CLOSE_BUTTON_PRESSED,
	PLEDIT_WINDOWSHADE_BUTTON_PRESSED,
	PLEDIT_WINDOWSHADE_LEFT_END,
	PLEDIT_WINDOWSHADE_RIGHT_END_ACTIVE,
	PLEDIT_MAXIMIZE_BUTTON_PRESSED,
	PLEDIT_SCROLL_BUTTON_UNPRESSED,
	PLEDIT_SCROLL_BUTTON_PRESSED,
	PLEDIT_WINDOWSHADE_MIDDLE_FILLERS,
	PLEDIT_WINDOWSHADE_RIGHT_END_INACTIVE,
	PLEDIT_BOTTOM_LEFT_CONTROL_BAR,
	PLEDIT_BOTTOM_RIGHT_CONTROL_BAR,
	PLEDIT_PAGE_UP_BUTTON,
	PLEDIT_PAGE_DOWN_BUTTON,
	PLEDIT_ADD_BUTTON,
	PLEDIT_REMOVE_BUTTON,
	PLEDIT_SELECTION_BUTTON,
	PLEDIT_MISCELLANEOUS_BUTTON,
	PLEDIT_LIST_BUTTON,
	PLEDIT_TIME_STATUS_BUTTON,
	PLEDIT_RESIZE_CONTROL,
	PLEDIT_PREVIOUS_CONTROL,
	PLEDIT_PLAY_CONTROL,
	PLEDIT_PAUSE_CONTROL,
	PLEDIT_STOP_CONTROL,
	PLEDIT_NEXT_CONTROL,
	PLEDIT_OPEN_CONTROL,
	PLEDIT_CURRENT_TIME_DISPLAY_MINUTES,
	PLEDIT_CURRENT_TIME_DISPLAY_SECONDS,
	PLEDIT_ADD_URL_BUTTON_UNPRESSED,
	PLEDIT_ADD_URL_BUTTON_PRESSED,
	PLEDIT_DECORATION_BAR_ADD,
	PLEDIT_REMOVE_ALL_BUTTON_UNPRESSED,
	PLEDIT_REMOVE_ALL_BUTTON_PRESSED,
	PLEDIT_DECORATION_BAR_REMOVE,
	PLEDIT_INVERT_SELECTION_BUTTON_UNPRESSED,
	PLEDIT_INVERT_SELECTION_BUTTON_PRESSED,
	PLEDIT_DECORATION_BAR_SELECTION,
	PLEDIT_SORT_LIST_BUTTON_UNPRESSED,
	PLEDIT_SORT_LIST_BUTTON_PRESSED,
	PLEDIT_DECORATION_BAR_MISC,
	PLEDIT_NEW_LIST_BUTTON_UNPRESSED,
	PLEDIT_NEW_LIST_BUTTON_PRESSED,
	PLEDIT_DECORATION_BAR_LIST,
	PLEDIT_ADD_DIR_BUTTON_UNPRESSED,
	PLEDIT_ADD_DIR_BUTTON_PRESSED,
	PLEDIT_CROP_BUTTON_UNPRESSED,
	PLEDIT_CROP_BUTTON_PRESSED,
	PLEDIT_SELECT_NONE_BUTTON_UNPRESSED,
	PLEDIT_SELECT_NONE_BUTTON_PRESSED,
	PLEDIT_FILE_INFO_BUTTON_UNPRESSED,
	PLEDIT_FILE_INFO_BUTTON_PRESSED,
	PLEDIT_SAVE_LIST_BUTTON_UNPRESSED,
	PLEDIT_SAVE_LIST_BUTTON_PRESSED,
	PLEDIT_ADD_FILE_BUTTON_UNPRESSED,
	PLEDIT_ADD_FILE_BUTTON_PRESSED,
	PLEDIT_REMOVE_FILE_BUTTON_UNPRESSED,
	PLEDIT_REMOVE_FILE_BUTTON_PRESSED,
	PLEDIT_SELECT_ALL_BUTTON_UNPRESSED,
	PLEDIT_SELECT_ALL_BUTTON_PRESSED,
	PLEDIT_MISC_OPTIONS_BUTTON_UNPRESSED,
	PLEDIT_MISC_OPTIONS_BUTTON_PRESSED,
	PLEDIT_LOAD_LIST_BUTTON_UNPRESSED,
	PLEDIT_LOAD_LIST_BUTTON_PRESSED,
	PLEDIT_MISC_REMOVE_BUTTON_UNPRESSED,
	PLEDIT_MISC_REMOVE_BUTTON_PRESSED,

// from posbar.bmp
	POSBAR_SONG_PROGRESS_BAR,
	POSBAR_SONG_SLIDER_UNPRESSED,
	POSBAR_SONG_SLIDER_PRESSED,

// from shufrep.bmp
	SHUFREP_NO_REPEAT_UNPRESSED,
	SHUFREP_NO_SHUFFLE_UNPRESSED,
	SHUFREP_NO_REPEAT_PRESSED,
	SHUFREP_NO_SHUFFLE_PRESSED,
	SHUFREP_REPEAT_UNPRESSED,
	SHUFREP_SHUFFLE_UNPRESSED,
	SHUFREP_REPEAT_PRESSED,
	SHUFREP_SHUFFLE_PRESSED,
	SHUFREP_NO_EQUALIZER_UNPRESSED,
	SHUFREP_NO_PLAYLIST_UNPRESSED,
	SHUFREP_NO_EQUALIZER_PRESSED,
	SHUFREP_NO_PLAYLIST_PRESSED,
	SHUFREP_EQUALIZER_UNPRESSED,
	SHUFREP_PLAYLIST_UNPRESSED,
	SHUFREP_EQUALIZER_PRESSED,
	SHUFREP_PLAYLIST_PRESSED,

// from text.bmp
	TEXT_A,
	TEXT_B,
	TEXT_C,
	TEXT_D,
	TEXT_E,
	TEXT_F,
	TEXT_G,
	TEXT_H,
	TEXT_I,
	TEXT_J,
	TEXT_K,
	TEXT_L,
	TEXT_M,
	TEXT_N,
	TEXT_O,
	TEXT_P,
	TEXT_Q,
	TEXT_R,
	TEXT_S,
	TEXT_T,
	TEXT_U,
	TEXT_V,
	TEXT_W,
	TEXT_X,
	TEXT_Y,
	TEXT_Z,
	TEXT_QUOTATION_MARK,
	TEXT_AT_SYMBOL,
	TEXT_TIME_DISPLAY_BACKGROUND,
	TEXT_TITLE_DISPLAY_SPACE,
	TEXT_0,
	TEXT_1,
	TEXT_2,
	TEXT_3,
	TEXT_4,
	TEXT_5,
	TEXT_6,
	TEXT_7,
	TEXT_8,
	TEXT_9,
	TEXT_ELLIPSIS,
	TEXT_PERIOD,
	TEXT_COLON,
	TEXT_LEFT_PARENTHESIS,
	TEXT_RIGHT_PARENTHESIS,
	TEXT_DASH,
	TEXT_APOSTROPHE,
	TEXT_EXCLAMATION_MARK,
	TEXT_UNDERSCORE,
	TEXT_PLUS_SYMBOL,
	TEXT_BACK_SLASH,
	TEXT_SLASH,
	TEXT_LEFT_BRACKET,
	TEXT_RIGHT_BRACKET,
	TEXT_CARROT,
	TEXT_AMPERSAND,
	TEXT_PERCENT,
	TEXT_COMMA,
	TEXT_EQUAL,
	TEXT_DOLLAR,
	TEXT_POUND,
	TEXT_A_CIRCUMFLEX,
	TEXT_O_UMLAUT,
	TEXT_A_UMLAUT,
	TEXT_QUESTION_MARK,
	TEXT_ASTERISK,
	TEXT_KBPS_DISPLAY_SPACE,

// from titlebar.bmp
	TITLEBAR_MENU_BUTTON_UNPRESSED,
	TITLEBAR_MINIMIZE_BUTTON_UNPRESED,
	TITLEBAR_EXIT_BUTTON_UNPRESSED,
	TITLEBAR_NORMAL_TITLEBAR_ACTIVE,
	TITLEBAR_CLUTTERBAR_SHOWN,
	TITLEBAR_CLUTTERBAR_HIDDEN,
	TITLEBAR_MENU_BUTTON_PRESSED,
	TITLEBAR_MINIMIZE_BUTTON_PRESSED,
	TITLEBAR_EXIT_BUTTON_PRESSED,
	TITLEBAR_NORMAL_TITLEBAR_INACTIVE,
	TITLEBAR_WINDOWSHADE_BUTTON_UNPRESSED,
	TITLEBAR_WINDOWSHADE_BUTTON_PRESSED,
	TITLEBAR_MAXIMIZE_BUTTON_UNPRESSED,
	TITLEBAR_MAXIMIZE_BUTTON_PRESSED,
	TITLEBAR_WINDOWSHADE_TITLEBAR_ACTIVE,
	TITLEBAR_SONG_PROGRESS_BAR,
	TITLEBAR_SONG_PROGRESS_CONTROLS,
	TITLEBAR_WINDOWSHADE_TITLEBAR_INACTIVE,
	TITLEBAR_CLUTTERBAR_O_PRESSED,
	TITLEBAR_CLUTTERBAR_A_PRESSED,
	TITLEBAR_CLUTTERBAR_I_PRESSED,
	TITLEBAR_CLUTTERBAR_D_PRESSED,
	TITLEBAR_CLUTTERBAR_V_PRESSED,
	TITLEBAR_ALTERNATIVE_TITLEBAR_ACTIVE,
	TITLEBAR_ALTERNATIVE_TITLEBAR_INACTIVE,

// from volume.bmp
	VOLUME_000_001,
	VOLUME_003_005,
	VOLUME_007_009,
	VOLUME_011_013,
	VOLUME_015_017,
	VOLUME_019_021,
	VOLUME_023_025,
	VOLUME_027_029,
	VOLUME_031,
	VOLUME_033_035,
	VOLUME_037_039,
	VOLUME_041_043,
	VOLUME_045_047,
	VOLUME_049_050,
	VOLUME_052_054,
	VOLUME_056_058,
	VOLUME_060_062,
	VOLUME_064,
	VOLUME_066_068,
	VOLUME_070_072,
	VOLUME_074_076,
	VOLUME_078_080,
	VOLUME_082_084,
	VOLUME_086_088,
	VOLUME_090_092,
	VOLUME_094_096,
	VOLUME_098,
	VOLUME_100,
	VOLUME_SLIDER_PRESSED,
	VOLUME_SLIDER_UNPRESSED,

// and a "NONE" element
	ELEMENT_NONE
} eElementID;
typedef enum
{
	AVS_BMP=0,
	BALANCE_BMP,
	CBUTTONS_BMP,
	EQ_EX_BMP,
	EQMAIN_BMP,
	MAIN_BMP,
	MB_BMP,
	MONOSTER_BMP,
	NUMBERS_BMP,
	PLAYPAUS_BMP,
	PLEDIT_BMP,
	POSBAR_BMP,
	SHUFREP_BMP,
	TEXT_BMP,
	TITLEBAR_BMP,
	VOLUME_BMP
} eElementSourceFile;
// Where in the .BMP files are the elements located? 
// They are all rectangular, and have an upper left corner (X,Y) and dimensions (X,Y)
typedef struct _tElementSource
{
	eElementSourceFile sourcefile;	// Which source file?
	int startx;
	int starty;
	int dimx;
	int dimy;
	eElementID id;		// Which element?

	// where to put it in the destination pixel buffer?
	int destx;		// -1: nowhere
	int desty;		// -1: nowhere
} tElementSource;
extern const tElementSource cElementSources[ELEMENTS_NUM];
#define	ELEMENT_X(id)      (cElementSources[(id)].startx)
#define	ELEMENT_Y(id)      (cElementSources[(id)].starty)
#define	ELEMENT_DESTX(id)  (cElementSources[(id)].destx)
#define	ELEMENT_DESTY(id)  (cElementSources[(id)].desty)
#define	ELEMENT_DESTX2(id) ((cElementSources[(id)].destx)+(cElementSources[(id)].dimx))
#define	ELEMENT_DESTY2(id) ((cElementSources[(id)].desty)+(cElementSources[(id)].dimy))
#define	ELEMENT_WIDTH(id)  (cElementSources[(id)].dimx)
#define	ELEMENT_HEIGHT(id) (cElementSources[(id)].dimy)

#define	ELEMENT_POS(id) ELEMENT_X(id),ELEMENT_Y(id)

	
#endif
