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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <utmp.h>
#include <sys/types.h>
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

#ifndef SENTRY_H     /* include only once */
#define SENTRY_H

#define MAXSTRINGSIZE BUFSIZ
#define GRAY 	0
#define BLACK 	1


#define CURSORSIZ 1024
#define ICONSIZ 4096

struct ICONSETUP {
	unsigned short cursor_bits[CURSORSIZ];
	unsigned short cursorm_bits[CURSORSIZ];
	unsigned short l_bits[ICONSIZ];         /* left pose */
	unsigned short lm_bits[ICONSIZ];
	unsigned short r_bits[ICONSIZ];         /* right pose */
	unsigned short rm_bits[ICONSIZ];
	unsigned short c_bits[ICONSIZ];         /* center pose */
	unsigned short cm_bits[ICONSIZ];
	unsigned short s1_bits[ICONSIZ];        /* siege phase 1 1st pose */
	unsigned short s1m_bits[ICONSIZ];
	unsigned short s2_bits[ICONSIZ];        /* siege phase 2 1st pose */
	unsigned short s2m_bits[ICONSIZ];
	unsigned short s3_bits[ICONSIZ];        /* siege phase 3 1st pose */
	unsigned short s3m_bits[ICONSIZ];
	unsigned short s4_bits[ICONSIZ];        /* siege phase 4 1st pose */
	unsigned short s4m_bits[ICONSIZ];
	unsigned short s5_bits[ICONSIZ];        /* siege phase 5 1st pose */
	unsigned short s5m_bits[ICONSIZ];
	unsigned short s6_bits[ICONSIZ];        /* siege phase 6 1st pose */
	unsigned short s6m_bits[ICONSIZ];
	unsigned short s1p_bits[ICONSIZ];       /* siege phase 1 2nd pose */
	unsigned short s1mp_bits[ICONSIZ];
	unsigned short s2p_bits[ICONSIZ];       /* siege phase 2 2nd pose */
	unsigned short s2mp_bits[ICONSIZ];
	unsigned short s3p_bits[ICONSIZ];       /* siege phase 3 2nd pose */
	unsigned short s3mp_bits[ICONSIZ];
	unsigned short s4p_bits[ICONSIZ];       /* siege phase 4 2nd pose */
	unsigned short s4mp_bits[ICONSIZ];
	unsigned short s5p_bits[ICONSIZ];       /* siege phase 5 2nd pose */
	unsigned short s5mp_bits[ICONSIZ];
	unsigned short s6p_bits[ICONSIZ];       /* siege phase 6 2nd pose */
	unsigned short s6mp_bits[ICONSIZ];
};

/* Now lets declare 3 sets of icons groups 
iconset[0] will be the tower set
iconset[1] will be the dog set
iconset[2] will be the defcon set
*/


struct ICONSETUP iconset[2];

/* Now let us define the sentry tower set */

static iconset[0].cursor_bits =  {
#include "sentry_cursorlong.icon" 
};

static iconset[0].cursorm_bits = { 
#include "sentry_cursormask.icon" 
};
 
static iconset[0].l_bits = { 
#include "sentryleft.icon" 
}; 
 
static iconset[0].lm_bits = { 
#include "sentryleft_mask.icon" 
}; 
 
static iconset[0].c_bits = { 
#include "sentrycenter.icon" 
}; 
 
static iconset[0].cm_bits = { 
#include "sentrycenter_mask.icon" 
}; 
 
static iconset[0].r_bits = { 
#include "sentryright.icon" 
}; 
 
static iconset[0].rm_bits = { 
#include "sentryright_mask.icon" 
};
 
static iconset[0].s1_bits = { 
#include "sentrysiege1.icon" 
};
 
static iconset[0].s1m_bits = { 
#include "sentrysiege1_mask.icon" 
};
 
static iconset[0].s2_bits = { 
#include "sentrysiege3.icon" 
};
 
static iconset[0].s2m_bits = { 
#include "sentrysiege3_mask.icon" 
};
 
static iconset[0].s3_bits = { 
#include "sentrysiege4.icon" 
};
 
static iconset[0].s3m_bits = { 
#include "sentrysiege4_mask.icon" 
};
 
static iconset[0].s4_bits = { 
#include "sentrysiege5.icon" 
};

static iconset[0].s4m_bits = { 
#include "sentrysiege5_mask.icon" 
};
 
static iconset[0].s5_bits = { 
#include "sentrysiege6.icon" 
};
 
static iconset[0].s5m_bits = { 
#include "sentrysiege6_mask.icon" 
};
 
static iconset[0].s6_bits = { 
#include "sentrysiege7.icon" 
};
 
static iconset[0].s6m_bits = { 
#include "sentrysiege7_mask.icon" 
};
 
static iconset[0].s1p_bits = { 
#include "sentrysiege1.icon" 
};
 
static iconset[0].s1mp_bits = { 
#include "sentrysiege1_mask.icon" 
};
 
static iconset[0].s2p_bits = { 
#include "sentrysiege3.icon" 
};
 
static iconset[0].s2mp_bits = { 
#include "sentrysiege3_mask.icon" 
};
 
static iconset[0].s3p_bits = { 
#include "sentrysiege4.icon" 
};
 
static iconset[0].s3mp_bits = { 
#include "sentrysiege4_mask.icon" 
};
 
static iconset[0].s4p_bits = { 
#include "sentrysiege5.icon" 
};
 
static iconset[0].s4mp_bits = { 
#include "sentrysiege5_mask.icon" 
};
 
static iconset[0].s5p_bits = { 
#include "sentrysiege6.icon" 
};
 
static iconset[0].s5mp_bits = { 
#include "sentrysiege6_mask.icon" 
};
 
static iconset[0].s6p_bits = { 
#include "sentrysiege7.icon" 
};

static iconset[0].s6mp_bits = { 
#include "sentrysiege7_mask.icon" 
};

/* now lets define the dog icon set */

static iconset[1].cursor_bits = {
#include "dogbone.icon" 
};

static iconset[1].cursorm_bits = {
#include "dogbonemask.icon" 
};

static iconset[1].l_bits = {  
#include "dogl.icon" 
}; 

static iconset[1].lm_bits = {  
#include "doglm.icon" 
}; 

static iconset[1].c_bits = {  
#include "dogc.icon" 
}; 

static iconset[1].cm_bits = {  
#include "dogcm.icon" 
}; 
static iconset[1].r_bits = {  
#include "dogr.icon" 
}; 
static iconset[1].rm_bits = {  
#include "dogrm.icon" 
}; 
static iconset[1].s1_bits = {  
#include "dogs1.icon" 
};
static iconset[1].s1m_bits = {  
#include "dogs1m.icon" 
};
static iconset[1].s2_bits = {  
#include "dogs2.icon" 
};
static iconset[1].s2m_bits = {  
#include "dogs2m.icon" 
};
static iconset[1].s3_bits = {  
#include "dogs3.icon" 
};
static iconset[1].s3m_bits = {  
#include "dogs3m.icon" 
};
static iconset[1].s4_bits = {  
#include "dogs4.icon" 
};
static iconset[1].s4m_bits = {  
#include "dogs4m.icon" 
};
static iconset[1].s5_bits = {  
#include "dogs5.icon" 
};
static iconset[1].s5m_bits = {  
#include "dogs5m.icon" 
};
static iconset[1].s6_bits = {  
#include "dogs6.icon" 
};
static iconset[1].s6m_bits = {  
#include "dogs6m.icon" 
};
static iconset[1].s1_bits = {  
#include "dogs1p.icon" 
};
static iconset[1].s1m_bits = {  
#include "dogs1mp.icon" 
};
static iconset[1].s2_bits = {  
#include "dogs2p.icon" 
};
static iconset[1].s2m_bits = {  
#include "dogs2mp.icon" 
};
static iconset[1].s3_bits = {  
#include "dogs3p.icon" 
};
static iconset[1].s3m_bits = {  
#include "dogs3mp.icon" 
};
static iconset[1].s4_bits = {  
#include "dogs4p.icon" 
};
static iconset[1].s4m_bits = {  
#include "dogs4mp.icon" 
};
static iconset[1].s5_bits = {  
#include "dogs5p.icon" 
};
static iconset[1].s5m_bits = {  
#include "dogs5mp.icon" 
};

static iconset[1].s6_bits = {  
#include "dogs6p.icon" 
}; 

static iconset[1].s6m_bits = {  
#include "dogs6mp.icon" 
};


/* now lets define the defcon icon set */

static iconset[2].cursor_bits = { 
#include "misslecursor.icon" 
};
static iconset[2].cursorm_bits = { 
#include "misslecursor.icon" 
};
static iconset[2].l_bits[] = { 
#include "defcon5.icon" 
}; 
static iconset[2].lm_bits[] = { 
#include "defcon5.icon" 
}; 
static iconset[2].c_bits = { 
#include "defcon5c.icon" 
}; 
static iconset[2].cm_bits = { 
#include "defcon5c.icon" 
}; 
static iconset[2].r_bits = { 
#include "defcon5.icon" 
}; 
static iconset[2].rm_bits = { 
#include "defcon5.icon" 
}; 
static iconset[2].s1_bits = { 
#include "defcon4.icon" 
};
static iconset[2].s1m_bits = { 
#include "defcon4.icon" 
};
static iconset[2].s2_bits = { 
#include "defcon3.icon" 
};
static iconset[2].s2m_bits = { 
#include "defcon3.icon" 
};
static iconset[2].s3_bits = { 
#include "defcon2.icon" 
};
static iconset[2].s3m_bits = { 
#include "defcon2.icon" 
};
static iconset[2].s4_bits = { 
#include "defcon1.icon" 
};
static iconset[2].s4m_bits = { 
#include "defcon1.icon" 
};
static iconset[2].s5_bits = { 
#include "thatsall.icon" 
};
static iconset[2].s5m_bits = { 
#include "thatsallm.icon" 
};
static iconset[2].s6_bits = { 
#include "thatsreallyall.icon" 
};
static iconset[2].s6m_bits = { 
#include "thatsreallyallm.icon" 
};
static iconset[2].s1p_bits = { 
#include "defcon4c.icon" 
};
static iconset[2].s1mp_bits = { 
#include "defcon4c.icon" 
};
static iconset[2].s2p_bits = { 
#include "defcon3c.icon" 
};
static iconset[2].s2mp_bits{ 
#include "defcon3c.icon" 
};
static iconset[2].s3p_bits{ 
#include "defcon2c.icon" 
};
static iconset[2].s3mp_bits{ 
#include "defcon2c.icon" 
};
static iconset[2].s4p_bits{ 
#include "defcon1c.icon" 
};
static iconset[2].s4mp_bits{ 
#include "defcon1c.icon" 
};
static iconset[2].s5p_bits{ 
#include "thatsallp.icon" 
};
static iconset[2].s5mp_bits{ 
#include "thatsallmp.icon" 
};
static iconset[2].s6p_bits{ 
#include "thatsreallyallp.icon" 
}; 
static iconset[2].s6mp_bits{ 
#include "thatsreallyallmp.icon" 
};


enum handle {  timeslide,
			   logtype,
			   wlogname,
			   rlogname,
			   printertype,
			   soundtype,
			   sounddata,
               volume,
               file,
			   clear,
			   siege,
               button,
			   authlist,
			   seticon,
            
};

 


    
 
/* Global variables */ 

Xv_screen			screen;
 
Server_image        gen_icon, gen_l, gen_r, genm_l, genm_r, gen_c, genm_c, gen_s1, genm_s1, gen_s2, genm_s2, gen_s3, genm_s3, gen_s4, genm_s4, gen_s5, genm_s5, gen_s6, genm_s6, gen_s1p, genm_s1p, gen_s2p, genm_s2p, gen_s3p, genm_s3p, gen_s4p, genm_s4p, gen_s5p, genm_s5p, gen_s6p, genm_s6p; 

Xv_Cursor			generic_cursor;
Server_image		gen_cursor_svrimage, gen_cursorsi_mask;
Server_image		tower_demo, defcon_demo, dog_demo;

Icon            	sentryicon;
Panel_item 			sentry_state;
Panel_item          intruder, prop_slide, prop_sound, prop_volume, prop_recfile;
Panel_item          clear_file, view_log, prop_warn, props_button, prop_siege, prop_print, icon_swapper;
Panel_item		    prop_log_toggle, prop_rlogname, prop_wlogname, prop_authlist;	
Panel_item			sound_help, info_help, file_help, time_help, siege_help;
Textsw				sound_helptw, info_helptw, file_helptw, time_helptw, siege_helptw;
Frame           	frame, propframe, cmdframe, helpframe;
Panel           	panel, proppanel, helppanel1, helppanel2, helppanel3, helppanel4, helppanel5, helppanel6, cmdpanel;
Textsw				textsw;
FILE                *fp;
char                founduser[MAXSTRINGSIZE], authuserlist[BUFSIZ], Sound[BUFSIZ];
char            printlist[10][10];
char				printer[BUFSIZ];
int         		logflag = 0, prcount, prflag, swflag = 1, nosoundflag = 1, norecordflag = 1 , slide_value = 30, volume_value = 5, time_value, sound_value, logview, viewpanel, helpview;
int                 intcount = 0 , clearflag , nosiegeflag , icount, siegeflag;
char                intlog[100][5]; 
int                 intlognum [100][1];
Cms					sentrycms;
static	Xv_singlecolor 	colors[] = {
						{119, 136, 153},
						{  0,   0,   0},
					};

static Xv_singlecolor sentrycursorbg, sentrycursorfg; 

/* Structures */

struct itimerval    timer;

struct users {
	char        user[10];
	char        host[10];
	int         flag;
};

/* Global prototype */ 
void create_all
(
void
); 
  
Notify_value  watch_who
(
Panel_item item
);
void sound_toggle
(
Panel_item item, Event *event
);
void log_toggle
(
Panel_item item, Event *event
);
void apply_props
(
Panel panel, Panel_item item
);
int props 
(
Panel_item item, Event *event
);
int clearlog
(
Panel_item item, Event *event
);
void viewlog
(
Panel_item item, Event *event
);
void nullfunct
(
Panel_item item
);
int quitpanel
(
Panel_item item
);
int view
(
Panel_item item
);
void help
(
Panel_item item, Event *event
);
void callplay
(
char *sound, unsigned vol, int sv
);
void getprint_list
(
void
);
void propchange_print
(
Panel_item item
);
void print_list
(
Panel_item item
);

void set_iconset
(
void
);




#endif
