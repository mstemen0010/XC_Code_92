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
#include <xview/panel.h>
#include <xview/frame.h>
#include <xview/svrimage.h>
#include <xview/notice.h>
#include <xview/notify.h>
#include <xview/icon.h>
#include <xview/font.h>

Frame	frame;
Icon	icon;
char	authuser[BUFSIZ], homepath[BUFSIZ];
char    wgFontName[100];
Xv_font	font;

/*  Local Prototypes */

void child_create
(
void
);
 

#endif
