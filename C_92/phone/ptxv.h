/*
** File:     phonetool.h	SCCS: 1.8 - 4/26/93
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

#ifndef PTXV_H		/* include only once */
#define	PTXV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <fcntl.h>
#include <stropts.h>
#include <sys/ioctl.h>
#include <sys/file.h>
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
#include <xview/seln.h>
#include <sun/audioio.h>
#include "play.h"

#include </usr/demo/SOUND/include/multimedia/libaudio.h>
#include </usr/demo/SOUND/include/multimedia/audio_device.h>

#define T(str)	(dgettext("gaintool-labels", str))

#define AUDIO_IODEV "/dev/audio"
#define MAX_GAIN    100

#define FPRINTF (void) fprintf
#define SPRINTF (void) sprintf
#define STRCPY  (void) strcpy   

#define SCREENCOLOR     0
#define DISMISSCOLOR    1
#define CONFIRMCOLOR   	2
#define FILECOLOR 	   	3	
#define SUPPORTCOLOR    4
#define BASECOLOR 	    5
#define NUM_COLORS 		6
#define MAXBUF 1024
#define TEMPFILE "/usr/tmp/pbtemp.txt"
#define TEMPSORTFILE "/usr/tmp/pbtemp.srt"

Xv_screen   screen;

extern Xv_singlecolor colors[6]; 

extern Xv_singlecolor nocolors[6]; 
 
/* Global Variables */
extern Panel_item      mess_item, mess_item2, mess_item3, mess_item4;

extern Panel_item      word_item, word_add, word_upd, lname_add, fname_add,
                phone_add, ext_add, note_add, addr_add;

extern Panel_item      addinsert_but, lname_upd, fname_upd, phone_upd,
                ext_upd, note_upd, addr_upd, updinsert_but; 

extern Panel_item		prop_infile, prop_editor, prop_color, editbutton, apply_button, 
				prop_current, prop_print, george;
extern Panel_item      soundex_tol_slide, prop_soundex_toggle, soundex_field_toggle; 

extern Panel_item	    color_choice, ptred_slider, ptgreen_slider, ptblue_slider;	

extern Panel_item		print_help, color_help, search_help, info_help, person_help, 
				exportfname;

extern Panel_item		findlast_but, findmatch_but, findnext_but;
extern Panel_item dial_number, dial_sound_output, dial_vol_slider;

extern char            oldLabel[BUFSIZ], newLabel[BUFSIZ]; 

char            printer[BUFSIZ], authuser[BUFSIZ], homepath[BUFSIZ], 
				compfilename[BUFSIZ], compfilenamealt[BUFSIZ], line[BUFSIZ], 
				updateline[BUFSIZ], matchline[BUFSIZ],infilename[BUFSIZ], 
				personfilename[BUFSIZ], defaultfilename[BUFSIZ], 
				defaultcompname[BUFSIZ], preffile[BUFSIZ];

char			printlist[10][10], exportfile[BUFSIZ], current_match[BUFSIZ];
char			word[BUFSIZ];

int             lastchoice, colorflag, prcount, prflag, rmtempfileflag, edflag, viewupd, viewadd, viewprops, viewutx;
int		 soundexFlag,soundexNameFlag,  soundexOn, soundexSlide;

Audio_info		Info;				/* saved state */
int         	Audio_fd;           /* ctl device fd */
char*           Audio_device = AUDIO_IODEV; /* device name */
char*           Audio_ctldev;           /* control dev name */

char*           prog;               /* program name */


Textsw          textsw, updtextsw;

extern Panel           panel, addpanel, textpanel, updtxtpanel, updpanel, proppanel, querypanel, 
				helppanel, dialpanel, exportfnamepanel;

Frame           frame, propframe, updframe, addframe, updtextframe, 
				queryframe, dialframe, helpframe, exportfnameframe;

Menu			nullmenu;

Server_image        phonebook_icon, mask_icon, phone_image, phword_image, 
					bkword_image;

extern	Server_image	head_phone_image, speaker_image, null_image, play_image; 
Icon                icon;

Panel_message_item  phoneimage, phimage, bkimage;

Cms				phonetoolcms, oldcms, newcms;

long			lastpos, currpos;
int				lastindex = 0;

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
            };
 
/*  Global Prototypes */

Notify_value
sigpoll_handler
(
Notify_client client, int sig, Notify_signal_mode when
);

void
update_panels
(
void
);

void
audio_open
(
void
);
void
apply_funct
(
Panel_item item, Event *event 
);

void  clear_screen
(
Panel_item item
);

void create_children
(
void
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

void delete_line 
(
Panel_item item
);

void sort_file
(
char filename[BUFSIZ], int lines
);

int stsrt 
(
const void *ptra, const void *ptrb
);

void insert_upd 
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

int get_pan_values 
(
Panel panel, Panel_item item
);

void clear_pan_values 
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

extern int readfile
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

void writerc_file
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
char *rcprinter
);
void changecomp_file
(
Panel_item item
);
void help
(
Panel_item item, Event *event
);
void dial
(
Panel_item item, Event *event
);

char * convert_number
(
Panel_item item
);

void dial_it
(
Panel_item item
);

void flash_color
(
int colornum
);


 
 
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
 
void sound_output
(
Panel_item item, int value, Event event
);

char * read_rc
(
void
);

void reset_all
(
void
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

void
getinfo
(
Audio_info  *ap
);


void
toggle_soundex
(
Panel_item item
);


#endif
