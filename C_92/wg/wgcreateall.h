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

#ifndef WGCREATEALL_H	/* include only once */
#define	WGCREATEALL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <xview/xview.h>
#include <xview/panel.h>
#include <xview/frame.h>
#include <xview/svrimage.h>
#include <xview/tty.h>
#include <xview/notice.h>
#include <xview/notify.h>
#include <xview/textsw.h>
#include <xview/icon.h>
#include <xview/font.h>
#include <xview/openmenu.h>


Frame					frame, subframe;
Menu					nullmenu;
Icon					icon;
Server_image			dictionary_icon, mask_icon;
Panel					panel, panel2,  prop_panel;
Textsw					textsw;
Panel_item				word_item, soundex_toggle, soundex_slide, grab_word;
Panel_item				mess_item, mess_item2, mess_item3, mess_item4; 
Panel_item 				word_add;
int						 quit();
Textsw					textsw;
Frame					frame;
char					authuser[BUFSIZ], homepath[BUFSIZ], my_argv[BUFSIZ];
extern		Xv_font		font;

extern void repeat_last
(
Panel_item item, Event *event
);

extern void look_up_all
(
Panel_item item, Event *event
);

extern void look_up_sys
(
Panel_item item, Event *event
);

extern void look_up_personal
(
Panel_item item, Event *event
);


static unsigned short icon_bits[] = {
#include "dictionary.icon"
};

static unsigned short mask_bits[] = {
#include "dictionary_mask.icon"
};

extern void delete_word
(
Panel_item item, Event *event
);

extern void add_word
(
Panel_item item, Event *event
);

extern void get_word
(
Panel_item item, Event *event
);

extern void toggle_soundex
(
Panel_item item
);

void
get_prime_sel
(
Panel_item item
);

int
quitpanel
(
Panel_item item
);


#endif
