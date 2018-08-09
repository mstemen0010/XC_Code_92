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

struct fileprofile{
	Server_image	file_icon;
	off_t   		file_size;
};

struct clickStruct {
	long	ClickTime;
	long	ClickUTime;
};

Server_image			seek_icon, seek_icon2,seek_icon3, mask_icon, file_icon, dir_icon, sys_icon, link_icon, sock_icon, pipe_icon, core_icon, compressed_icon, csource_icon, header_icon, object_icon, exe_icon, aml_icon, sound_icon, ps_icon, rast_icon, mail_icon, shell_icon, wp_icon, gif_icon, bm_icon, make_icon, sun_icon, info_icon, lib_icon, gis_icon, im_icon, gra_icon, plt_icon, vi_icon, XRh_icon, XRr_icon, XRd_icon, XRe_icon, XRs_icon, empty_icon;

extern int     ff_dir,ff_file, ff_lnk, ff_chr, ff_sock, ff_fifo, ff_empty, ff_core, ff_compressed, ff_icon, ff_csource, ff_object, ff_header, ff_exe, ff_aml, ff_sound, ff_ps, ff_rast, ff_mail, ff_shell, ff_wp, ff_bm, ff_gif, ff_make, ff_info, ff_lib, ff_gis, ff_im, ff_gra, ff_plt, ff_XRe, ff_XRs, ff_XRh, ff_XRd, ff_XRr;

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


Panel_item          test_choice;
extern	Panel_item	prop_warnName;

int
list_notify_proc 
(
Panel_item item, char *string, Xv_opaque client_data, Panel_list_op op, Event *event, int row 
);

char *
read_dir 
( 
char *word, char *pathptr
); 

int is_DoubleClick
(
Event *event, int type, char *string
);

#endif

