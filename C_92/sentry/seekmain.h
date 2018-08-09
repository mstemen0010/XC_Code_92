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

#ifndef WGMAIN_H	/* include only once */
#define	WGMAIN_H

#define TEMPSORT "/usr/tmp/dictsort.txt"
#define TEMPFILE "/usr/tmp/wgfile.txt"

#include <stdio.h>
#include <xview/xview.h>
#include <xview/window.h>
#include <xview/panel.h>
#include <xview/textsw.h>
#include <xview/frame.h>
#include <xview/svrimage.h>
#include <xview/notice.h>
#include <xview/notify.h>
#include <xview/icon.h>
#include <xview/font.h>

Icon	icon;
char    wgFontName[100];

int  	ff_dir, ff_file, ff_lnk, ff_chr, ff_sock, ff_fifo, ff_empty, ff_core, ff_compressed, ff_icon, ff_csource, ff_object, ff_header, ff_exe, ff_aml, ff_sound, ff_ps, ff_rast, ff_mail, ff_shell, ff_wp, ff_bm, ff_gif, ff_make, ff_info, ff_lib, ff_gis, ff_im, ff_gra, ff_plt, ff_XRe, ff_XRs, ff_XRh, ff_XRd, ff_XRr;

extern int						targetFlag, viewFlag, lastView;
int								editFlag;
extern  char     primaryPath[BUFSIZ], secondaryPath[BUFSIZ], secondaryNameVal[BUFSIZ], primaryNameVal[BUFSIZ], tag[BUFSIZ], emaxed[BUFSIZ];

extern  Server_image    seek_icon, seek_icon2, seek_icon3, mask_icon, file_icon, dir_icon, sys_icon, link_icon, pipe_icon, sock_icon, core_icon, compressed_icon, csource_icon, object_icon, header_icon, exe_icon, aml_icon, sound_icon, ps_icon, rast_icon, mail_icon, shell_icon, wp_icon, bm_icon, gif_icon, make_icon, info_icon, lib_icon, gis_icon, im_icon, gra_icon, plt_icon, vi_icon, XRe_icon, XRs_icon, XRh_icon, XRd_icon, XRr_icon, empty_icon;

Xv_font	font;

struct fileprofile{
	Server_image	file_icon;
	off_t   		file_size;
};
	

/*  Local Prototypes */

void child_create
(
void
);
 
extern Notify_value seek_event_hand
(
Panel panel, Event *event, Notify_arg arg, Notify_event_type type 
);

#endif
