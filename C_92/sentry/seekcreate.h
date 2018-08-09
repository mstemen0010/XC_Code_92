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
#include <xview/rect.h>
#include <xview/panel.h>
#include <xview/frame.h>
#include <xview/svrimage.h>
#include <xview/dragdrop.h>
#include <xview/tty.h>
#include <xview/notice.h>
#include <xview/notify.h>
#include <xview/textsw.h>
#include <xview/icon.h>
#include <xview/font.h>
#include <xview/cms.h>
#include <xview/openmenu.h>

extern enum handle {
				blank1,
				blank2,
                prime,
                second,
                all,
				button,
				choice,
            };

Frame					frame, subframe, subframe2, propframe;
Menu					nullmenu, default_textsw;
Menu_item			    pmi[10];	
Menu_item			    smi[10];	
Cms						cms;
Dnd						dnd;
Xv_drop_site			drop_site;
Icon					icon, icon2;
Server_image			seek_icon, seek_icon2,seek_icon3, mask_icon, file_icon, dir_icon, sys_icon, link_icon, sock_icon, pipe_icon, core_icon, compressed_icon, csource_icon, header_icon, object_icon, exe_icon, aml_icon, sound_icon, ps_icon, rast_icon, mail_icon, shell_icon, wp_icon, gif_icon, bm_icon, make_icon, sun_icon, info_icon, lib_icon, gis_icon, im_icon, gra_icon, plt_icon, vi_icon, XRh_icon, XRr_icon, XRd_icon, XRe_icon, XRs_icon, empty_icon;
Panel					panel, panel2, panel3,  proppanel;
Textsw					textsw;
Panel_item				primebutton, secondbutton, grab_word, propsOn, quit_button, done_button, filter_button, prime_toCurr, second_toCurr;
Menu					prime_menu, second_menu; 

extern int     ff_dir,ff_file, ff_lnk, ff_chr, ff_sock, ff_fifo, ff_empty, ff_core, ff_compressed, ff_icon, ff_csource, ff_object, ff_header, ff_exe, ff_aml, ff_sound, ff_ps, ff_rast, ff_mail, ff_shell, ff_wp, ff_bm, ff_gif, ff_make, ff_info, ff_lib, ff_gis, ff_im, ff_gra, ff_plt, ff_XRe, ff_XRs, ff_XRh, ff_XRd, ff_XRr;


Panel_item 				ffdir_image, fffile_image, fflnk_image, ffchr_image, ffsock_image, fffifo_image, ffempty_image, ffcore_image, ffcompressed_image, fficon_image, ffcsource_image, ffobject_image, ffheader_image, ffexe_image, ffaml_image, ffsound_image, ffps_image, ffrast_image, ffmail_image, ffshell_image, ffwp_image, ffbm_image, ffgif_image, ffmake_image, ffinfo_image, fflib_image, ffgis_image, ffim_image, ffgra_image, ffplt_image, ffXRe_image, ffXRs_image, ffXRh_image, ffXRd_image, ffXRr_image;

Panel_item 				ffdir_choice, fffile_choice, fflnk_choice, ffchr_choice, ffsock_choice, fffifo_choice, ffempty_choice, ffcore_choice, ffcompressed_choice, fficon_choice, ffcsource_choice, ffobject_choice, ffheader_choice, ffexe_choice, ffaml_choice, ffsound_choice, ffps_choice, ffrast_choice, ffmail_choice, ffshell_choice, ffwp_choice, ffbm_choice, ffgif_choice, ffmake_choice, ffinfo_choice, fflib_choice, ffgis_choice, ffim_choice, ffgra_choice, ffplt_choice, ffXRe_choice, ffXRs_choice, ffXRh_choice, ffXRd_choice, ffXRr_choice;

Panel_item				word_item, soundex_toggle, soundex_slide;
Panel_item				mess_item, mess_item2, mess_item3, mess_item4, goto_item; 
Panel_item				primarySearchPath, secondarySearchPath, primaryName, secondaryName, emaxName, tagName, targetChoice;

Panel_item 				word_add;
Panel_item 				test_choice;
Panel_item				view_choice;
int						 quit();
int						targetFlag, viewFlag, lastView;
extern int						editFlag;
Textsw					textsw;
Frame					frame;
char					authuser[BUFSIZ], homepath[BUFSIZ], my_argv[BUFSIZ];
extern char		primaryPath[BUFSIZ], secondaryPath[BUFSIZ], secondaryNameVal[BUFSIZ], primaryNameVal[BUFSIZ], emaxed[BUFSIZ], tag[BUFSIZ];

extern		Xv_font		font;

extern void repeat_last
(
Panel_item item, Event *event
);

extern void look_up_all
(
Panel_item item, Event *event
);

extern void look_up_all
(
Panel_item item, Event *event
);

static unsigned short icon_bits[] = {
#include "seek.icon"
};

static unsigned short icon_bits2[] = {
#include "seek2.icon"
};

static unsigned short icon_bits3[] = {
#include "seek3.icon"
};

static unsigned short vi_icon_bits[] = {
#include "/home/mw/usr/mgs/release/seek/SeekVi.icon"
};

static unsigned short mask_bits[] = {
#include "seekm.icon"
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

extern void toggle_filter
(
Panel_item item, int value, Event *event
);

extern void toggle_soundex
(
Panel_item item
);

extern void show_filter
(
void
);

extern void
get_prime_sel
(
Panel_item item
);

extern int
quitpanel
(
Panel_item item
);

extern int
done_proc
(
Panel_item item, Event *event
);

extern int 
list_notify_proc 
( 
Panel_item item, char *string, Xv_opaque client_data, Panel_list_op op, Event *event, int row 
); 

extern Notify_value seek_event_hand 
( 
Panel panel, Event *event, Notify_arg arg, Notify_event_type type
); 

extern void query_toggle
(
int togType
);

extern void toggle_done
(
void 
);

extern int  prop_OnOff 
( 
Panel_item item, Event *event
); 
extern void
apply_funct(void);

extern int target_toggle
(
Panel_item item, Event *event
); 

extern void	prime_menu_proc
(
Menu menu,	Menu_item menu_item
); 


extern void	second_menu_proc
(
Menu menu,	Menu_item menu_item
); 

int append_menu
(
int menuType, char * pathname, Event *event
);

extern void goto_funct
(
Panel_item item, Event *event
); 

extern void set_current_loc
(
Panel_item item, Event *event
); 

extern void control_toggle
(
Panel_item item, Event *event
); 


#endif
