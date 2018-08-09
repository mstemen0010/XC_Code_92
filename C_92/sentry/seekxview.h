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
#include <sys/types.h>
#include <sys/stat.h>
#include <X11/Intrinsic.h>
#include <xview/xview.h>
#include <xview/panel.h>
#include <xview/frame.h>
#include <xview/svrimage.h>
#include <xview/notice.h>
#include <xview/notify.h>
#include <xview/textsw.h>
#include <xview/icon.h>
#include <xview/seln.h>
#include <xview/cms.h>
#include <xview/font.h>
#include <xview/tty.h>
#include <errno.h>
#include <dirent.h>
#include "seek_main.h"


struct clickStruct {
	long	ClickTime;
	long	ClickUTime;
};

enum handle {
				blank1,
				blank2,
				prime,
				second,
				all,
				button,
				choice,
			};

extern 	Frame			frame, propframe;
		Frame			subframe, subframe2;
extern  Cms				cms;
extern	Panel			panel, panel2, panel3, proppanel;  
		Panel			panel2;  
extern	Textsw			textsw;
extern  Panel_item      primebutton, secondbutton, done_button, filter_button, grab_word, propsOn, quit_button, prime_toCurr, second_toCurr;
extern	Menu            prime_menu, second_menu, nullmenu, default_textsw; 
extern 	Menu_item       pmi[10]; 
extern	Menu_item       smi[10]; 
extern 	Panel_item		goto_item, mess_item, mess_item2, mess_item3, mess_item4;
extern 	Panel_item		soundex_toggle, soundex_slide;
extern	Panel_item		word_item, word_add;
extern	Panel_item              primarySearchPath, secondarySearchPath, primaryName, secondaryName, emaxName, tagName, targetChoice; 

extern	Icon			icon, icon2;

extern	Panel_item      fffile_choice, ffdir_choice, fflnk_choice, ffchr_choice, ffsock_choice, fffifo_choice, ffempty_choice, ffcore_choice, ffcompressed_choice, fficon_choice, ffcsource_choice, ffobject_choice, ffheader_choice, ffexe_choice, ffaml_choice, ffsound_choice, ffps_choice, ffrast_choice, ffmail_choice, ffshell_choice, ffwp_choice, ffbm_choice, ffgif_choice, ffmake_choice, ffinfo_choice, fflib_choice, ffgis_choice, ffim_choice, ffgra_choice, ffplt_choice, ffXRe_choice, ffXRs_choice, ffXRh_choice, ffXRd_choice, ffXRr_choice;

extern int	ff_dir, ff_file, ff_lnk, ff_chr, ff_sock, ff_fifo, ff_empty, ff_core, ff_compressed, ff_icon, ff_csource, ff_object, ff_header, ff_exe, ff_aml, ff_sound, ff_ps, ff_rast, ff_mail, ff_shell, ff_wp, ff_bm, ff_gif, ff_make, ff_info, ff_lib, ff_gis, ff_im, ff_gra, ff_plt, ff_XRe, ff_XRs, ff_XRh, ff_XRd, ff_XRr;

extern	Server_image	seek_icon, seek_icon2, seek_icon3, mask_icon, file_icon, dir_icon, sys_icon, link_icon, pipe_icon, sock_icon, core_icon, compressed_icon, csource_icon, object_icon, header_icon, exe_icon, aml_icon, sound_icon, ps_icon, rast_icon, mail_icon, shell_icon, wp_icon, bm_icon, gif_icon, make_icon, info_icon, lib_icon, gis_icon, im_icon, gra_icon, plt_icon, vi_icon, XRe_icon, XRs_icon, XRh_icon, XRd_icon, XRr_icon, empty_icon;

extern  Xv_Font			font;

Server_image			gen_icon;

Panel_item              test_choice;
Panel_item              view_choice;
extern	char			my_argv[BUFSIZ];
extern	char			num_lines_found[100];
extern  int				max_word_len, targetFlag, editFlag, viewFlag, lastView;
		int				noMatchFlag = FALSE;
		int				noClearFlag = FALSE;
		int				lastFunctFlag = 1;

char     primaryPath[BUFSIZ], secondaryPath[BUFSIZ], secondaryNameVal[BUFSIZ], primaryNameVal[BUFSIZ], emaxed[BUFSIZ], tag[BUFSIZ];

void
repeat_last
(
Panel_item item, Event *event
);

void look_up_all
(
Panel_item item, Event *event
);


void look_up_all
(
Panel_item item, Event *event
);

void get_word
(
Panel_item item, Event *event
);

void flush_subpanel
(
void
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

int 
read_dir 
( 
char *word, int dirtype, char *pathptr
); 

int
list_notify_proc 
(
Panel_item item, char *string, Xv_opaque client_data, Panel_list_op op, Event *event, int row 
);

int 
done_proc 
( 
Panel_item item, Event *event 
); 

void
create_cand_list
(
void
);

Notify_value seek_event_hand
(
Panel panel, Event *event, Notify_arg arg, Notify_event_type type 
);

void textsw_event_hand
( 
Xv_window window, Event *event, Notify_arg arg 
);

void toggle_filter
(
Panel_item item, int value, Event  *event
);
 
void query_toggle
(
int togType
);

void toggle_done
(
void
);

void show_filter  
(
void 
);

void find_match
(
void
);

int
prop_OnOff
(
Panel_item item, Event *event 
);

void
apply_funct(void);

int target_toggle
( 
Panel_item item, Event *event
); 

char * buildPath
(
int	operation, char	*pathptr
);

int		append_menu
(
int menuType, char *pathname
);

void    prime_menu_proc
(
Menu menu,  Menu_item menu_item
);
 
 
void    second_menu_proc
(
Menu menu,  Menu_item menu_item
);
 
void goto_funct 
( 
Panel_item item, Event *event
);

 
void set_current_loc 
(
Panel_item item, Event *event
);

int is_DoubleClick
(
Event *event, int type, char *string
);
void control_toggle
(
Panel_item item, Event *event
);
#endif

