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


#include <sun/audioio.h>

#include <stdio.h>
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

#include "setupicons.h"
#include "play.h"


#include </usr/demo/SOUND/multimedia/libaudio.h>
#include </usr/demo/SOUND/multimedia/audio_device.h>

#define T(str)	(dgettext("gaintool-labels", str))

#define AUDIO_IODEV "/dev/audio"
#define MAX_GAIN    100

#define FPRINTF (void) fprintf
#define SPRINTF (void) sprintf
#define STRCPY  (void) strcpy


#define MAXSTRINGSIZE BUFSIZ
#define GRAY 	0
#define BLACK 	1


		

extern enum handle {  
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

 

extern struct fileprofile{
	Server_image	file_icon;
	off_t   		file_size;
};

extern struct clickStruct {
	long	ClickTime;
	long	ClickUTime;
};

    
 
/* Global variables */ 
extern Frame           	frame, subframe, propframe, cmdframe, helpframe;
extern Panel           	panel, subpanel, proppanel, helppanel1, helppanel2, helppanel3, helppanel4, helppanel5, helppanel6, cmdpanel;

extern Xv_screen			screen;

extern Icon            	sentryicon, logo_icon;
 
extern Server_image        logo_image, logo_image_mask, head_phone_image, speaker_image, play_image, null_image, gen_icon, gen_l, gen_r, genm_l, genm_r, gen_c, genm_c, gen_s1, genm_s1, gen_s2, genm_s2, gen_s3, genm_s3, gen_s4, genm_s4, gen_s5, genm_s5, gen_s6, genm_s6, gen_s1p, genm_s1p, gen_s2p, genm_s2p, gen_s3p, genm_s3p, gen_s4p, genm_s4p, gen_s5p, genm_s5p, gen_s6p, genm_s6p; 

extern Server_image			seek_icon, seek_icon2,seek_icon3, mask_icon, file_icon, dir_icon, sys_icon, link_icon, sock_icon, pipe_icon, core_icon, compressed_icon, csource_icon, header_icon, object_icon, exe_icon, aml_icon, sound_icon, ps_icon, rast_icon, mail_icon, shell_icon, wp_icon, gif_icon, bm_icon, make_icon, sun_icon, info_icon, lib_icon, gis_icon, im_icon, gra_icon, plt_icon, vi_icon, XRh_icon, XRr_icon, XRd_icon, XRe_icon, XRs_icon, empty_icon;

extern int     ff_dir,ff_file, ff_lnk, ff_chr, ff_sock, ff_fifo, ff_empty, ff_core, ff_compressed, ff_icon, ff_csource, ff_object, ff_header, ff_exe, ff_aml, ff_sound, ff_ps, ff_rast, ff_mail, ff_shell, ff_wp, ff_bm, ff_gif, ff_make, ff_info, ff_lib, ff_gis, ff_im, ff_gra, ff_plt, ff_XRe, ff_XRs, ff_XRh, ff_XRd, ff_XRr;

extern Xv_Cursor			generic_cursor;

extern Server_image		gen_cursor_svrimage, gen_cursorsi_mask;
extern Server_image		tower_demo, defcon_demo, dog_demo, boat_demo, trek_demo, tank_demo, ngtrek_demo;

extern Panel_item 			sentry_state, list_warn_choice, list_mail_choice;
extern Panel_item          intruder, prop_setSoundphase, prop_sound_output, prop_testSound, prop_setSoundwarn, prop_setSoundmail, prop_warnSound, prop_warn_slide, prop_mail_slide, wprop_sound,mprop_sound, prop_volume, prop_soundPath, prop_recfile;
extern Panel_item		    prop_log_toggle, prop_monitor_toggle, prop_rlogname, prop_wlogname, prop_authlist;	
extern Panel_item			sound_help, info_help, file_help, time_help, siege_help;
extern Panel_item          clear_file, view_log, prop_warn,prop_mailSound, props_button, prop_siege, prop_print, icon_swapper, prop_mfilename;

extern Textsw				sound_helptw, info_helptw, file_helptw, time_helptw, siege_helptw;

extern Textsw				textsw;
extern FILE                *fp;
extern char                founduser[MAXSTRINGSIZE], authuserlist[BUFSIZ], Sound[BUFSIZ], rcprinter[BUFSIZ];
extern char            printlist[10][10];
extern char				printer[BUFSIZ];
extern int         		monflag, soflag= 1, logflag = 0, prcount, prflag, swflag = 1, nosoundflag = 1, noWarnSoundFlag = 1, noMailSoundFlag = 1, norecordflag = 1 , mail_slide_value = 30, warn_slide_value = 30, volume_value = 5, time_value, sound_value, logview, viewpanel, helpview, whoFlag = 1, mailFlag = 1;
extern int                 intcount = 0 , clearflag , nosiegeflag , icount, siegeflag;
extern char                intlog[100][5]; 
extern int                 intlognum [100][1];
extern char 				mfilename[BUFSIZ];
extern Cms					sentrycms;
extern unsigned long		foreground_index, background_index;

extern char                *hostname[20], homepath[BUFSIZ], dlogfile[BUFSIZ], rlogfile[BUFSIZ], rlogfile[BUFSIZ], defaultlog[BUFSIZ], authuser[BUFSIZ];
extern Menu                nullmenu;
extern char                WarningSound[BUFSIZ], MailSound[BUFSIZ];
extern char                SoundPath1[BUFSIZ] = "/usr/demo/SOUND/sounds/";
extern char                soundPath[BUFSIZ]; 
extern char                RcFile[BUFSIZ];
extern FILE                *infp;
extern char                *temp;
extern int                 iconflag;

extern int			Audio_pausefd = -1;		/* real device fd */
extern int			Audio_fd;			/* ctl device fd */
extern Audio_info		Info;				/* saved state */
extern int         	Audio_fd;           /* ctl device fd */
extern char*           Audio_device = AUDIO_IODEV; /* device name */
extern char*           Audio_ctldev;           /* control dev name */
extern char*           prog;               /*program name */ 


/* Structures */

extern struct itimerval    mailtimer;
extern struct itimerval    warntimer;

extern struct users {
	char        user[10];
	char        host[10];
	int         flag;
};


extern struct              users old[100];

extern unsigned short play_bits[] = { 
#include "/local/misc/C/sentrydir/icons/play.icon" 
};

extern unsigned short null_bits[] = { 
#include "/local/misc/C/sentrydir/icons/null16.icon" 
};

extern unsigned short head_phone_bits[] = { 
#include "/local/misc/C/sentrydir/icons/headphones.icon" 
};

extern unsigned short speaker_bits[] = { 
#include "/local/misc/C/sentrydir/icons/speaker.icon" 
};

extern unsigned short logo_bits[] = { 
#include "/local/misc/C/sentrydir/icons/sentry_logo.icon" 
};

extern unsigned short logo_mbits[] = { 
#include "/local/misc/C/sentrydir/icons/sentry_logo_mask.icon" 
};

static unsigned short file_bits[] = {
#include "/local/openwin30/share/include/images/Generic_Doc_glyph.icon"
};

static unsigned short dir_bits[] = {
#include "/local/openwin30/share/include/images/Folder_closed_glyph.icon"
};

static unsigned short sys_bits[] = {
#include "/local/openwin30/share/include/images/Console_glyph.icon"
};

static unsigned short core_bits[] = {
#include "/home/toolset/licensed/openwin30/include/images/coredoc.icon"
};

static unsigned short link_bits[] = {
#include "/local/misc/C/seek/link_icon.icon"
};

static unsigned short pipe_bits[] = {
#include "/local/misc/C/seek/pipe_icon.icon"
};

static unsigned short sock_bits[] = {
#include "/local/misc/C/seek/sock_icon.icon"
};

static unsigned short compressed_bits[] = {
#include "/home/toolset/licensed/openwin30/include/images/Compressed_glyph.icon"
};

static unsigned short csource_bits[] = {
#include "/home/toolset/licensed/openwin30/include/images/Code_csource_glyph.icon"
};

static unsigned short header_bits[] = {
#include "/home/toolset/licensed/openwin30/include/images/Code_cheader_glyph.icon"
};

static unsigned short object_bits[] = {
#include "/home/toolset/licensed/openwin30/include/images/Code_object_glyph.icon"
};

static unsigned short exe_bits[] = {
#include "/local/openwin30/share/include/images/Generic_SunOS_prog_glyph.icon"
};

static unsigned short sun_bits[] = {
#include "/local/openwin30/share/include/images/Generic_SunOS_prog_glyph.icon"
};
static unsigned short aml_bits[] = {
#include "/local/openwin30/share/include/images/Code_aml_glyph.icon"
};

static unsigned short sound_bits[] = {
#include "/local/openwin30/share/include/images/SunAudio_Alt_glyph.icon"
};

static unsigned short ps_bits[] = {
#include "/local/openwin30/share/include/images/PostScript_Doc_glyph.icon"
};

static unsigned short rast_bits[] = {
#include "/local/openwin30/share/include/images/SunRaster_glyph.icon"
};

static unsigned short mail_bits[] = {
#include "/local/openwin30/share/include/images/Mailfile_glyph.icon"
};

static unsigned short shell_bits[] = {
#include "/local/openwin30/share/include/images/Shell_script_glyph.icon"
};

static unsigned short wp_bits[] = {
#include "/local/openwin30/share/include/images/Doc_wp_glyph.icon"
};

static unsigned short bm_bits[] = {
#include "/local/openwin30/share/include/images/SunIcon_glyph.icon"
};

static unsigned short gif_bits[] = {
#include "/local/openwin30/share/include/images/GIF_glyph.icon"
};
static unsigned short make_bits[] = {
#include "/local/openwin30/share/include/images/Makefile_glyph.icon"
};

static unsigned short info_bits[] = {
#include "/local/openwin30/share/include/images/Info_doc_glyph.icon"
};

static unsigned short lib_bits[] = {
#include "/local/openwin30/share/include/images/Code_lib_glyph.icon"
};

static unsigned short gis_bits[] = {
#include "/local/openwin30/share/include/images/GISRaster_glyph.icon"
};

static unsigned short im_bits[] = {
#include "/local/openwin30/share/include/images/IMRaster_glyph.icon"
};

static unsigned short gra_bits[] = {
#include "/local/openwin30/share/include/images/GRA_glyph.icon"
};

static unsigned short plt_bits[] = {
#include "/local/openwin30/share/include/images/PLT_glyph.icon"
};

static unsigned short XRs_bits[] = {
#include "/local/openwin30/share/include/images/XR_Script_glyph.icon"
};

static unsigned short XRe_bits[] = {
#include "/local/openwin30/share/include/images/XR_Event_glyph.icon"
};

static unsigned short XRd_bits[] = {
#include "/local/openwin30/share/include/images/XR_Data_glyph.icon"
};

static unsigned short XRh_bits[] = {
#include "/local/openwin30/share/include/images/XR_Header_glyph.icon"
};

static unsigned short XRr_bits[] = {
#include "/local/openwin30/share/include/images/XR_Report_glyph.icon"
};

static unsigned short empty_bits[] = {
#include "/local/openwin30/share/include/images/Empty_doc_glyph.icon"
};   
/* Global prototype */ 
extern void create_all
(
void
); 
  
extern void get_list
(
Panel_item item, int soundType
);

extern int
read_dir 
( 
char *word, char *pathptr, int soundType
);


extern void  watch_mail
(
void
);

extern void  watch_who
(
void
);
extern void test_sound
(
int whichsound
);

extern void sound_toggle
(
Panel_item item, Event *event
);
extern void log_toggle
(
Panel_item item, Event *event
);
extern void apply_props
(
Panel panel, Panel_item item
);
extern int props 
(
Panel_item item, Event *event
);
extern int clearlog
(
Panel_item item, Event *event
);
extern void viewlog
(
Panel_item item, Event *event
);
extern void nullfunct
(
Panel_item item
);
extern int quitpanel
(
Panel_item item
);
extern int view
(
Panel_item item
);
extern void help
(
Panel_item item, Event *event
);
extern void callplay
(
char *sound, unsigned vol, int sv
);
extern void getprint_list
(
char *rcprinter
);
extern void propchange_print
(
Panel_item item
);
extern void print_list
(
Panel_item item
);

extern void set_iconset
(
void
);
extern int list_notify_proc 
(
Panel_item item, char *string, Xv_opaque client_data, Panel_list_op op, Event *event, int row 
);

extern int is_DoubleClick
(
Event *event, int type, char *string
);

extern void 
sound_output
(
Panel_item item, int value, Event event
); 


extern void
audio_open
(
void
);

extern void 
getinfo
(
Audio_info  *ap
);

extern void
which_warn_choice
(
Panel_item item, int value
);

extern void
which_mail_choice
(
Panel_item item, int value
);

extern Notify_value
sigpoll_handler
(
Notify_client client, int sig, Notify_signal_mode when
);

extern void
update_panels
(
void
);

extern void 
play_volume_proc
(
Panel_item item, int value, Event *event
);

extern unsigned 
scale_gain
(
    unsigned    g 
);

extern unsigned
unscale_gain
(
    unsigned    g
);

extern Notify_value
mon_toggle
(
	void 
);

extern Notify_value
mon_toggle1
(
	void 
);

extern Notify_value
mon_toggle2
(
	void 
);

extern void
no_funct
(
	void
);

extern void
sound_flag_toggle
(
Panel_item item, Event *event
);

extern void
show_phase_choice
(
Panel_item item, Event *event, int value
);

#endif
