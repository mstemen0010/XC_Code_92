/*
** File: %M% SCCS %I% - %G%
** Author:   M. Stemen
**
** Created:  7/21/93
** Edited:
**
**
** Purpose:
**  
*/

/*
*/

#include "wgcreateall.h" 

void
child_create(void)
{

/*    font = (Xv_Font)xv_find(frame, FONT, FONT_NAME, "helvetica", NULL);  */

    nullmenu = (Menu) xv_create (NULL, MENU, NULL);

	dictionary_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				64,
			XV_HEIGHT,				64,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    icon_bits,
			NULL);    	

	mask_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				64,
			XV_HEIGHT,				64,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    mask_bits,
			NULL);    	

	panel = (Panel)xv_create(frame, PANEL, 
			PANEL_LAYOUT,			PANEL_VERTICAL,
			XV_HEIGHT,				325,
			WIN_COLUMNS,			35,  
			NULL); 

	word_item = (Panel_item)xv_create(panel, PANEL_TEXT,
			PANEL_LABEL_STRING,		"Word: ",
			PANEL_VALUE_DISPLAY_LENGTH, 15,
			PANEL_VALUE_STORED_LENGTH,	BUFSIZ - 1,
			PANEL_NOTIFY_PROC,		look_up_all,
			NULL);

	xv_create(panel, PANEL_BUTTON, 
			PANEL_LABEL_STRING,     "Search system word guide",
			PANEL_NOTIFY_PROC,		look_up_sys,
			NULL);

	xv_create(panel, PANEL_BUTTON, 
			PANEL_LABEL_STRING,     "Search personal word guide",
			PANEL_NOTIFY_PROC,		look_up_personal,
			NULL);

	xv_create(panel, PANEL_BUTTON, 
			PANEL_LABEL_STRING,     "Add/Delete item in personal guide",
			PANEL_NOTIFY_PROC,		get_word,
			NULL);
	soundex_toggle = (Panel_item) xv_create(panel, PANEL_CHOICE, 
			PANEL_READ_ONLY,			TRUE,
			PANEL_LABEL_STRING,		"Soundex",
			PANEL_CHOICE_STRINGS,   "On", "Off", NULL,
			PANEL_VALUE,			1,
			PANEL_NOTIFY_PROC,		toggle_soundex,
			NULL);

	soundex_slide = (Panel_item) xv_create(panel, PANEL_SLIDER,
			PANEL_READ_ONLY,			TRUE,
			PANEL_INACTIVE,			TRUE,
			PANEL_LABEL_STRING,		"Tolerance",
			PANEL_SLIDER_END_BOXES,	TRUE,
			PANEL_MIN_VALUE,		0,
			PANEL_MAX_VALUE,		100,
			PANEL_VALUE,			16,
			PANEL_SHOW_VALUE,		FALSE,
			PANEL_SHOW_RANGE,		FALSE,
			PANEL_SLIDER_WIDTH,     100,
			PANEL_NOTIFY_PROC,		repeat_last,
			PANEL_MIN_TICK_STRING,	"0",
			PANEL_MAX_TICK_STRING,	"100",
			PANEL_TICKS,			1,
			NULL);

	xv_set (panel, PANEL_LAYOUT, PANEL_HORIZONTAL, NULL);

	grab_word = (Panel_item) xv_create(panel, PANEL_BUTTON, 
			PANEL_LABEL_STRING,     "Grab highlighted choice",
			PANEL_NOTIFY_PROC,		get_prime_sel,
			PANEL_CLIENT_DATA,		frame,
			NULL);

	(void) xv_create(panel, PANEL_BUTTON, 
			PANEL_LABEL_STRING,     "Quit",
			PANEL_NOTIFY_PROC,		quit,
			PANEL_CLIENT_DATA,		frame,
			NULL);

	mess_item = (Panel_item)xv_create(panel, PANEL_TEXT,
			PANEL_READ_ONLY,			TRUE,
			PANEL_VALUE_UNDERLINED,		FALSE,
			PANEL_VALUE_DISPLAY_LENGTH, 25,
			PANEL_VALUE_STORED_LENGTH,	BUFSIZ - 1,
			NULL);

	mess_item2 = (Panel_item)xv_create(panel, PANEL_TEXT,
			PANEL_READ_ONLY,			TRUE,
			PANEL_VALUE_UNDERLINED,		FALSE,
			PANEL_VALUE_DISPLAY_LENGTH, 25,
			PANEL_VALUE_STORED_LENGTH,	BUFSIZ - 1,
			NULL);

	mess_item3 = (Panel_item)xv_create(panel, PANEL_TEXT,
			PANEL_READ_ONLY,			TRUE,
			PANEL_VALUE_UNDERLINED,		FALSE,
			PANEL_VALUE_DISPLAY_LENGTH, 25,
			PANEL_VALUE_STORED_LENGTH,	BUFSIZ - 1,
			NULL);


	textsw = (Textsw)xv_create(frame, TEXTSW, 
			/* WIN_RIGHT_OF,				panel, */
			WIN_MENU,				nullmenu,
			XV_HEIGHT,				325,
			WIN_COLUMNS,			15,  
			TEXTSW_DISABLE_CD, 		TRUE,
			TEXTSW_DISABLE_LOAD, 	TRUE,
			TEXTSW_BROWSING,        TRUE,
			TEXTSW_MEMORY_MAXIMUM,  2000000,
			XV_FONT,				font,
			NULL); 

	icon = (Icon)xv_create(frame, ICON, 
			ICON_IMAGE,				dictionary_icon,
			ICON_MASK_IMAGE,		mask_icon,
			ICON_TRANSPARENT,		TRUE,
			XV_X,					100,
			XV_Y,					100,
			NULL);

    subframe = (Frame)xv_create(frame, FRAME_CMD,
            XV_WIDTH,               300,
            XV_HEIGHT,              50,
            XV_X,                   xv_get(frame, XV_X),
            XV_Y,                   xv_get(frame, XV_Y),
            FRAME_LABEL,            "Add  Word to personal word guide",            NULL);
    panel2 = (Panel)xv_create(subframe, PANEL,
			FRAME_CMD_PUSHPIN_IN,   TRUE,
            WIN_ROWS,               10,
            WIN_COLUMNS,            25,
            NULL);

    word_add = (Panel_item)xv_create(panel2, PANEL_TEXT,
            PANEL_LABEL_STRING,     "Word: ",
            PANEL_VALUE_DISPLAY_LENGTH, 25,
            PANEL_VALUE_STORED_LENGTH,  BUFSIZ - 1,
            PANEL_NOTIFY_PROC,      add_word,
            NULL);

	xv_set(panel2, PANEL_LAYOUT, PANEL_HORIZONTAL, NULL);

	(void)	xv_create(panel2, PANEL_BUTTON,
				PANEL_LABEL_STRING,     "Add",
				PANEL_CLIENT_DATA,		frame,
            	PANEL_NOTIFY_PROC,      add_word,
				NULL);

	(void)	xv_create(panel2, PANEL_BUTTON,
				PANEL_LABEL_STRING,     "Delete",
				PANEL_CLIENT_DATA,		frame,
            	PANEL_NOTIFY_PROC,      delete_word,
				NULL);

	(void)	xv_create(panel2, PANEL_BUTTON,
				PANEL_LABEL_STRING,     "Dismiss",
				PANEL_CLIENT_DATA,		frame,
            	PANEL_NOTIFY_PROC,      quitpanel,
				NULL);

	window_fit(panel2);
	window_fit(subframe);

}
