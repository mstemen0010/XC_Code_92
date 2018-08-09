/*
** File: ptmain.h SCCS: 1.1  - 5/5/93 
**
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

#ifndef PTMAIN_H	/* include only once */
#define	PTMAIN_H

#include <stdio.h>
#include <math.h>
#include <xview/xview.h>
#include <xview/panel.h>
#include <xview/frame.h>
#include <xview/svrimage.h>
#include <xview/notice.h>
#include <xview/notify.h>
#include <xview/icon.h>
#include <xview/cms.h>
#include <xview/screen.h>


#define SCREENCOLOR     0
#define DISMISSCOLOR    1
#define CONFIRMCOLOR   	2
#define FILECOLOR 	   	3	
#define SUPPORTCOLOR    4
#define BASECOLOR 	    5
#define SELECTCOLOR 	6
#define NUM_COLORS 		6
#define MAXBUF 1024
#define TEMPFILE "/usr/tmp/pbtemp.txt"

Xv_singlecolor colors[] = {
        { 255, 255, 255 },  /* white */
        { 205,   92,  92},  /* red   */
        {  34, 139,   34},  /* green  */
        { 93,  71,  139 }, /* purple */
        { 139, 62, 47  }, /* coral */
        { 0,     0,   0 }, /* black */
		{ 255,  255, 255}, /* select */
};

Xv_singlecolor nocolors[] = {
        { 255, 255, 255 },  /* white */
        {   0,   0,   0 },  /* red   */
        {   0,   0,   0 },  /* green  */
        {   0,   0,   0 }, /* purple */
        {   0,   0,   0 }, /* coral */
        {   0,   0,   0 }, /* black */
		{ 	0,   0,   0 }, /* select */
};
 
/* Global Variables */

char			oldLabel[BUFSIZ], newLabel[BUFSIZ];

char            printer[BUFSIZ], authuser[BUFSIZ], homepath[BUFSIZ], 
				compfilename[BUFSIZ], compfilenamealt[BUFSIZ], line[BUFSIZ], 
				updateline[BUFSIZ], matchline[BUFSIZ],infilename[BUFSIZ], 
				personfilename[BUFSIZ], defaultfilename[BUFSIZ], 
				defaultcompname[BUFSIZ], preffile[BUFSIZ];

int             lastchoice = 0, propeditflag, colorflag, edflag, defprinter;
extern int		soundexFlag, soundSlide, soundexNameFlag;


char * printer_found;

Frame           frame;
extern	Frame	dialframe;

Menu			nullmenu;

Server_image        phonebook_icon, mask_icon, phone_image, phword_image, 
					bkword_image, head_phone_image, speaker_image, play_image, null_image;

Icon                icon;

Panel_message_item  phoneimage, phimage, bkimage;
extern Panel_item      prop_editor, prop_infile,  george, prop_soundex_toggle, soundex_field_toggle;

Cms				phonetoolcms, oldcms, newcms;
 
 
/*  Global Prototypes */
void create_children
(
void
);

extern void audio_open
(
void
);

void getprint_list
(
char *rcprinter
);
 
extern 
int 
batchreadfile_soundex 
(char file[60], char matchword[100], int tol, int fieldValue); 

void batchreadfile
(
char file[60], char matchword[100]
); 

void writerc_file
(
void
);

int read_rc 
( 
void
); 

extern void
update_panels
(
void
);


extern Notify_value
sigpoll_handler
(
Notify_client client, int sig, Notify_signal_mode when
);


        
static unsigned short icon_bits[] = {
#include "phonebook.icon"
};
 
static unsigned short mask_bits[] = {
#include "phonebook_mask.icon"
};
 
static unsigned short image_bits[] = {
#include "phoneimage.icon"
};
 
static unsigned short phword_bits[] = {
#include "phimage.icon"
};
 
static unsigned short bkword_bits[] = {
#include "bkimage.icon"
};
 

#endif
