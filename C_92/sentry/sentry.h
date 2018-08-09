/*
** File:    %M% SCCS %I% - %G%
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

#ifndef SENTRY_H     /* include only once */
#define SENTRY_H


#include <sys/file.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <stropts.h>
#include <sys/audioio.h>

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>
#include <utmp.h>
#include <dirent.h>

#include <xview/xview.h>
#include <xview/frame.h>
#include <xview/panel.h>
#include <xview/svrimage.h>
#include <xview/icon.h>
#include <xview/notify.h>
#include <xview/notice.h>
#include <xview/textsw.h>
#include <xview/cms.h>
#include <xview/cursor.h>
#include <xview/defaults.h>

#include "setupicons.h"
#include "play.h"
#include "sort.h"
#include "seekmain.h"


#include </usr/demo/SOUND/include/multimedia/libaudio.h>
#include </usr/demo/SOUND/include/multimedia/audio_device.h>

#define T(str)	(dgettext("gaintool-labels", str))

#define AUDIO_IODEV "/dev/audio"
#define MAX_GAIN    100

#define FPRINTF (void) fprintf
#define SPRINTF (void) sprintf
#define STRCPY  (void) strcpy


#define MAXSTRINGSIZE BUFSIZ
#define GRAY 	0
#define BLACK 	1


		

enum handle {  
			   wtimeslide,
			   logtype,
			   wlogname,
			   rlogname,
			   printertype,
			   wsoundtype,
			   msoundtype,
			   sounddata,
               volume,
               file,
			   clear,
			   siege,
               button,
			   authlist,
			   seticon,
			   soundpath,
			   soundwar,
			   outputtype,
			   montype,
               mailtype,
			   soundmai,
			   mtimeslide,
            };

 

struct clickStruct {
	long	ClickTime;
	long	ClickUTime;
};

    
 
/* Global variables */ 
Frame           	frame, subframe, propframe, cmdframe, helpframe;
Panel           	panel, subpanel, proppanel, helppanel1, helppanel2, helppanel3, helppanel4, helppanel5, helppanel6, cmdpanel;

Xv_screen			screen;

Icon            	sentryicon, logo_icon;
 
Server_image        logo_image, logo_image_mask, head_phone_image, speaker_image, play_image, null_image, gen_icon, gen_l, gen_r, genm_l, genm_r, gen_c, genm_c, gen_s1, genm_s1, gen_s2, genm_s2, gen_s3, genm_s3, gen_s4, genm_s4, gen_s5, genm_s5, gen_s6, genm_s6, gen_s1p, genm_s1p, gen_s2p, genm_s2p, gen_s3p, genm_s3p, gen_s4p, genm_s4p, gen_s5p, genm_s5p, gen_s6p, genm_s6p; 

Server_image			seek_icon, seek_icon2,seek_icon3, mask_icon, file_icon, dir_icon, sys_icon, link_icon, sock_icon, pipe_icon, core_icon, compressed_icon, csource_icon, header_icon, object_icon, exe_icon, sound_icon, ps_icon, rast_icon, mail_icon, shell_icon, gif_icon, bm_icon, make_icon, sun_icon, info_icon, lib_icon, vi_icon,  empty_icon;

extern int     ff_dir,ff_file, ff_lnk, ff_chr, ff_sock, ff_fifo, ff_empty, ff_core, ff_compressed, ff_icon, ff_csource, ff_object, ff_header, ff_exe, ff_sound, ff_ps, ff_rast, ff_mail, ff_shell, ff_bm, ff_gif, ff_make, ff_info, ff_lib;

Xv_Cursor			generic_cursor;

Server_image		gen_cursor_svrimage, gen_cursorsi_mask;
Server_image		tower_demo, defcon_demo, dog_demo, boat_demo, trek_demo, tank_demo, ngtrek_demo;

Panel_item 			sentry_state, list_warn_choice, list_mail_choice;
Panel_item          intruder, prop_setSoundphase, prop_sound_output, prop_testSound, prop_setSoundwarn, prop_setSoundmail, prop_warnSound, prop_warn_slide, prop_mail_slide, wprop_sound,mprop_sound, prop_volume, prop_soundPath, prop_recfile, prop_subject_line;
Panel_item		    prop_log_toggle, prop_monitor_toggle, prop_rlogname, prop_wlogname, prop_authlist;	
Panel_item			sound_help, info_help, file_help, time_help, siege_help;
Panel_item          clear_file, view_log, prop_warn,prop_mailSound, props_button, prop_siege, prop_print, icon_swapper, prop_mfilename;

Textsw				sound_helptw, info_helptw, file_helptw, time_helptw, siege_helptw;

Textsw				textsw;
FILE                *fp;
char                founduser[MAXSTRINGSIZE], authuserlist[BUFSIZ], Sound[BUFSIZ], rcprinter[BUFSIZ];
char				subjectLine[BUFSIZ];
char            printlist[10][10];
char				printer[BUFSIZ];
int         		monflag, soflag= 1, logflag = 0, prcount, prflag, swflag = 1, nosoundflag = 1, noWarnSoundFlag = 1, noMailSoundFlag = 1, norecordflag = 1 , mail_slide_value = 30, warn_slide_value = 30, volume_value = 5, time_value, sound_value, logview, viewpanel, helpview, whoFlag = 1, mailFlag = 1;
int                 intcount = 0 , clearflag , nosiegeflag , icount, siegeflag;
char                intlog[100][5]; 
int                 intlognum [100][1];
char 				mfilename[BUFSIZ];
Cms					sentrycms;
unsigned long		foreground_index, background_index;

char                *hostname[20], homepath[BUFSIZ], dlogfile[BUFSIZ], rlogfile[BUFSIZ], defaultlog[BUFSIZ], authuser[BUFSIZ];
Menu                nullmenu;
char                WarningSound[BUFSIZ], MailSound[BUFSIZ];
char                SoundPath1[BUFSIZ] = "/usr/demo/SOUND/sounds/";
char                soundPath[BUFSIZ]; 
char                RcFile[BUFSIZ];
FILE                *infp;
char                *temp;
int                 iconflag;

int			Audio_pausefd = -1;		/* real device fd */
Audio_info		Info;				/* saved state */
int         	Audio_fd;           /* ctl device fd */
char*           Audio_device = AUDIO_IODEV; /* device name */
char*           Audio_ctldev;           /* control dev name */
char*           prog;               /*program name */ 


/* Structures */

struct itimerval    mailtimer;
struct itimerval    warntimer;

struct users {
	char        name[8];
	char        host[16];
	int			found;
	int         unauthorized;
};


unsigned short playbits[] = { 
#include "../icons/play.icon" 
};

unsigned short nullbits[] = { 
#include "../icons/null16.icon" 
};

unsigned short headphonebits[] = { 
#include "../icons/headphones.icon" 
};

unsigned short speakerbits[] = { 
#include "../icons/speaker.icon" 
};

unsigned short logobits[] = { 
#include "../icons/sentrylogo.icon" 
};

unsigned short logombits[] = { 
#include "../icons/sentrylogomask.icon" 
};

static unsigned short filebits[] = {
#include "../icons/Generic_Doc_glyph.icon"
};

static unsigned short dirbits[] = {
#include "../icons/Folder_closed_glyph.icon"
};

static unsigned short sysbits[] = {
#include "../icons/Console_glyph.icon"
};

static unsigned short corebits[] = {
#include "../icons/coredoc.icon"
};

static unsigned short linkbits[] = {
#include "../icons/linkicon.icon"
};

static unsigned short pipebits[] = {
#include "../icons/pipeicon.icon"
};

static unsigned short sockbits[] = {
#include "../icons/sockicon.icon"
};

static unsigned short compressedbits[] = {
#include "../icons/Compressed_glyph.icon"
};

static unsigned short csourcebits[] = {
#include "../icons/Code_csource_glyph.icon"
};

static unsigned short headerbits[] = {
#include "../icons/Code_cheader_glyph.icon"
};

static unsigned short objectbits[] = {
#include "../icons/Code_object_glyph.icon"
};

static unsigned short exebits[] = {
#include "../icons/Generic_SunOS_prog_glyph.icon"
};

static unsigned short sunbits[] = {
#include "../icons/Generic_SunOS_prog_glyph.icon"
};

static unsigned short soundbits[] = {
#include "../icons/SunAudio_Alt_glyph.icon"
};

static unsigned short psbits[] = {
#include "../icons/PostScript_Doc_glyph.icon"
};

static unsigned short rastbits[] = {
#include "../icons/SunRaster_glyph.icon"
};

static unsigned short mailbits[] = {
#include "../icons/Mailfile_glyph.icon"
};

static unsigned short shellbits[] = {
#include "../icons/Shell_script_glyph.icon"
};

static unsigned short bmbits[] = {
#include "../icons/SunIcon_glyph.icon"
};

static unsigned short gifbits[] = {
#include "../icons/GIF_glyph.icon"
};

static unsigned short makebits[] = {
#include "../icons/Makefile_glyph.icon"
};

static unsigned short infobits[] = {
#include "../icons/Info_doc_glyph.icon"
};

static unsigned short libbits[] = {
#include "../icons/Code_lib_glyph.icon"
};


static unsigned short emptybits[] = {
#include "../icons/Empty_doc_glyph.icon"
};   

/* Global prototype */ 
void createall ( void); 
void getlist ( Panelitem item, int soundType);
int readdir ( char *word, char *pathptr, int soundType);
void  watchmail ( void);
void  watchwho ( void);
void testsound
(
int whichsound
);

void soundtoggle
(
Panelitem item, Event *event
);
void logtoggle
(
Panelitem item, Event *event
);
void applyprops
(
Panel panel, Panelitem item
);
int props 
(
Panelitem item, Event *event
);
int clearlog
(
Panelitem item, Event *event
);
void viewlog
(
Panelitem item, Event *event
);
void nullfunct
(
Panelitem item
);
int quitpanel
(
Panelitem item
);
int view
(
Panelitem item
);
void help
(
Panelitem item, Event *event
);
void callplay
(
char *sound, unsigned vol, int sv
);
void getprintlist
(
char *rcprinter
);
void propchangeprint
(
Panelitem item
);
void printlist
(
Panelitem item
);

void seticonset
(
void
);
int
listnotifyproc 
(
Panelitem item, char *string, Xvopaque clientdata, Panellistop op, Event *event, int row 
);

int isDoubleClick
(
Event *event, int type, char *string
);

void 
soundoutput
(
Panelitem item, int value, Event event
); 


void
audioopen
(
void
);

void 
getinfo
(
Audioinfo  *ap
);

void
whichwarnchoice
(
Panelitem item, int value
);

void
whichmailchoice
(
Panelitem item, int value
);

Notifyfunc
sigpollhandler
(
Notifyclient client, int sig, Notifysignalmode when
);

void
updatepanels
(
void
);

void 
playvolumeproc
(
Panelitem item, int value, Event *event
);

unsigned 
scalegain
(
    unsigned    g 
);

unsigned
unscalegain
(
    unsigned    g
);

Notifyvalue
montoggle
(
	void 
);

Notifyvalue
montoggle1
(
	void 
);

Notifyvalue
montoggle2
(
	void 
);

void
nofunct
(
	void
);

void
soundflagtoggle
(
Panelitem item, Event *event
);

void
showphasechoice
(
Panelitem item, Event *event, int value
);

extern int gradefile (struct fileprofile *filepro, char *pathname, char *buffname);

#endif


