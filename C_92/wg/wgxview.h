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

#ifndef WGXVIEW_H	/* include only once */
#define	WGXVIEW_H

#include <stdio.h>
#include <xview/xview.h>
#include <xview/panel.h>
#include <xview/frame.h>
#include <xview/svrimage.h>
#include <xview/notice.h>
#include <xview/notify.h>
#include <xview/textsw.h>
#include <xview/icon.h>
#include <xview/seln.h>
#include "wgmain.h"


extern 	Frame			frame, subframe;
extern	Panel			panel, panel2;  
extern	Textsw			textsw;
extern 	Panel_item		mess_item, mess_item2, mess_item3, mess_item4;
extern 	Panel_item		soundex_toggle, soundex_slide;
extern	Panel_item		word_item, word_add;
extern	char			my_argv[BUFSIZ];
extern	char			num_lines_found[100];
extern  int				max_word_len;
		int				noMatchFlag = FALSE;
		int				noClearFlag = FALSE;
		int				lastFunctFlag = 1;

void
repeat_last
(
Panel_item item, Event *event
);

void look_up_all
(
Panel_item item, Event *event
);


void look_up_sys
(
Panel_item item, Event *event
);

void look_up_personal
(
Panel_item item, Event *event
);

void toggle_soundex
(
Panel_item item
);

void get_word
(
Panel_item item, Event *event
);

void add_word
(
Panel_item item, Event *event
);

void flush_panel
(
void
);

extern void quit
(
Panel_item item
);

char *
get_sel_item
(
void
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
