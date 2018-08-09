/*
** File:     ptcreate.h	SCCS: 1.1 - 5/5/93
** Author:   Matt Stemen
**
** Created:  12/11/1992
** Edited:
**
** The use, disclosure, reproduction, modification, transfer, or
** transmittal of this work for any purpose in any form or by any
** means without the written permission of United Parcel Services is
** strictly prohibited.
**
** Confidential, Unpublished Property of United Parcel Services.
** Use and Distribution Limited Solely to Authorized Personnel.
**
** Copyright (c) 1992, United Parcel Service of America, Inc.
** All Rights Reserved.
*/

#ifndef PTCREATE_H		/* include only once */
#define	PTCREATE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <xview/xview.h>
#include <xview/panel.h>
#include <xview/frame.h>
#include <xview/svrimage.h>
#include <xview/tty.h>
#include <xview/notice.h>
#include <xview/notify.h>
#include <xview/textsw.h>
#include <xview/icon.h>
#include <xview/openmenu.h>
#include <xview/cms.h>
#include <xview/screen.h>
#include "play.h"


#define SCREENCOLOR     0
#define DISMISSCOLOR    1
#define CONFIRMCOLOR   	2
#define FILECOLOR 	   	3	
#define SUPPORTCOLOR    4
#define BASECOLOR 	    5
#define NUM_COLORS 		6
#define MAXBUF 1024
#define TEMPFILE "/usr/tmp/pbtemp.txt"

extern Xv_singlecolor colors[6];
 
extern Xv_singlecolor nocolors[6];

extern void control_output_proc();

/* Global Variables */
Panel_item      mess_item, mess_item2, mess_item3, mess_item4;

Panel_item      word_item, word_add, word_upd, lname_add, fname_add,
                phone_add, ext_add, note_add, addr_add;

Panel_item      addinsert_but, lname_upd, fname_upd, phone_upd,
                ext_upd, note_upd, addr_upd, updinsert_but, findnext_but, findmatch_but, findlast_but, delete_but; 

Panel_item		prop_infile, prop_editor, prop_color, editbutton, apply_button;
Panel_item		soundex_tol_slide, prop_soundex_toggle, soundex_field_toggle, prop_current, prop_print, george;

Panel_item	    color_choice, ptred_slider, ptgreen_slider, ptblue_slider;	

Panel_item		print_help, color_help, search_help, info_help, person_help, 
				exportfname;

Panel_item		dial_number, dial_sound_output, dial_vol_slider;

Textsw			print_helptw, color_helptw, search_helptw, info_helptw, person_helptw;

char            printer[BUFSIZ], authuser[BUFSIZ], homepath[BUFSIZ], 
				compfilename[BUFSIZ], compfilenamealt[BUFSIZ], line[BUFSIZ], 
				updateline[BUFSIZ], matchline[BUFSIZ],infilename[BUFSIZ], 
				personfilename[BUFSIZ], defaultfilename[BUFSIZ], 
				defaultcompname[BUFSIZ], preffile[BUFSIZ];

char			printlist[10][10], exportfile[BUFSIZ];

int             propeditflag, colorflag, prcount, prflag, rmtempfileflag, edflag, viewupd, viewadd, viewprops, viewutx;
extern	int		soundexFlag, soundexNameFlag, soundexSlide;

Textsw          textsw, updtextsw;

Panel           panel, addpanel, updtxtpanel, updpanel, proppanel, querypanel, dialpanel, helppanel, exportfnamepanel, textpanel;

Panel			helppanel1, helppanel2, helppanel3, helppanel4, helppanel5, helppanel6; 

Frame           frame, propframe, updframe, addframe, updtextframe, 
				queryframe, dialframe, helpframe, exportfnameframe;

Menu			nullmenu;

Server_image        ff_icon, rw_icon, dial_icon, dial_image, phonebook_icon, mask_icon, phone_image, phword_image, head_phone_image, speaker_image, play_image, null_image, bkword_image;

Icon                icon;

Panel_message_item  phoneimage, phimage, bkimage;

Cms				phonetoolcms, oldcms, newcms;

 
/* type definitions */
 
/*
** tokens used in various areas to decide which menu item
** has been selected.
*/
enum handle {  lnameadd,
                lnameupd,
                fnameadd,
                fnameupd,
                phoneadd,
                phoneupd,
                addradd,
                addrupd,
                noteadd,
                noteupd,
                extadd,
                extupd,
                button,
                search,
				personal,
				writerc,
				printertype,
				colortype,
				colorclass, 
				format,
				soundex,
            };
 
/*  Global Prototypes */
void
apply_funct
(
Panel_item item, Event *event 
);

void create_children
(
void
);

void  clear_screen
(
Panel_item item
); 
 
void updateexport
(
void
);

void look_up_sys 
(
Panel_item item
);

void look_personal
(
Panel_item item
);
void add_panel
 (
Panel_item item
);
void upd_panel 
(
Panel_item item
);
void upd_textsw 
(
Panel_item item
);
void updatecolor 
(
Panel panel, Panel_item item
);
void editor 
(
Panel_item item
);
Notify_value add_line 
(
Panel_item item
);

void find_next_match 
(
Panel_item item
);

void find_last_match 
(
Panel_item item
);

void find_match 
(
Panel_item item
);

void insert_upd 
(
Panel_item item
);

void delete_line 
(
Panel_item item
);

void insert_add 
(
Panel_item item
);

void get_exportfile
(
Panel_item item
);

void get_pan_values 
(
Panel panel, Panel_item item
);

unsigned save_textsw 
(
Panel_item item
);

void EventProc
(
Xv_Window window
);

int  quitprg
(
Panel_item item
);

int  quitpanel 
(
Panel_item item
);

void readfile
(
char file[60], char matchword[100]
);

void writeline
(
FILE *fp, char *str
);

void uppercase
(
char *str
);

int  props
(
Panel_item item
);

void propchange_edit
(
Panel_item item
);

void findcolor_base
(
Panel_item item
);

void alter_color
(
Panel_item item
);

void propchange_color
(
Panel_item item
);

void propchange_print
(
Panel_item item
);

extern void writerc_file
(
void
);
void nullfunct
(
Panel_item item
);
void print_list
(
Panel_item item
);
 
void getprint_list
(
void
);
void changecomp_file
(
Panel_item item
);
void help
(
Panel_item item, Event *event
);

extern char * convert_number
(
Panel_item item
);

extern void dial_it 
( 
Panel_item item 
); 
 
void dial
(
Panel_item item, Event *event
);

void reset_all 
( 
void 
); 

unsigned short play_bits[] = {
#include "../icons/play.icon"
};

unsigned short null_bits[] = {
#include "../icons/null16.icon"
};

unsigned short head_phone_bits[] = {
#include "../icons/headphones.icon"
};

unsigned short speaker_bits[] = {
#include "../icons/speaker.icon"
};

static unsigned short ff_bits[] = {
#include "../icons/arrowf.icon"
};

static unsigned short rw_bits[] = {
#include "../icons/arrowb.icon"
};

static unsigned short dial_bits[] = {
#include "../icons/Autodial.icon"
};
 
static unsigned short icon_bits[] = {
#include "../icons/phonebook.icon"
};
 
static unsigned short mask_bits[] = {
#include "../icons/phonebookmask.icon"
};
 
static unsigned short image_bits[] = {
#include "../icons/phoneimage.icon"
};
 
static unsigned short phword_bits[] = {
#include "../icons/phimage.icon"
};
 
static unsigned short bkword_bits[] = {
#include "../icons/bkimage.icon"
};
 
extern void sound_output
(
Panel_item item, int value, Event event
);

extern void 
get_prime_sel 
( 
Panel_item item 
);

extern  void 
toggle_soundex
(
Panel_item item
); 
 
#endif
