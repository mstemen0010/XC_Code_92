/*
** File:     genfunct.h	SCCS: 1.1 - 5/5/93
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

#ifndef PTGEN_H		/* include only once */
#define	PTGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <xview/xview.h>
#include <xview/panel.h>
#include <xview/frame.h>
#include <xview/notice.h>
#include <xview/textsw.h>
#include <xview/cms.h>

#define MAXBUF 1024
#define TEMPFILE "/usr/tmp/wgfile.txt"
#define TEMPSORT "/usr/tmp/dictsort.txt" 
 


extern Xv_singlecolor colors[6];

extern Xv_singlecolor nocolors[6];

/* Global Variables */


char            printer[BUFSIZ], authuser[BUFSIZ], homepath[BUFSIZ], 
				compfilename[BUFSIZ], compfilenamealt[BUFSIZ], line[BUFSIZ], 
				updateline[BUFSIZ], matchline[BUFSIZ],infilename[BUFSIZ], 
				personfilename[BUFSIZ], defaultfilename[BUFSIZ], 
				defaultcompname[BUFSIZ], preffile[BUFSIZ];

char			printlist[10][10], exportfile[BUFSIZ];

int             colorflag, prcount, prflag, rmtempfileflag, edflag, viewupd, 
				viewadd, viewprops, viewutx;


extern Panel           panel, proppanel;

Frame           frame, propframe;
int				max_word_len = 0;

Panel_item     prop_print, soundex_slide;

char			num_lines_found[100];

extern Panel_item	mess_item;
    
 
/*  Global Prototypes */

void batchreadfile
(
char file[60], char matchword[100]
);

int calc
(
char* s1, char* s2
);

int readfile
(
char file[60], char matchword[100], int match_word
);

void writeline
(
FILE *fp, char *str
);

void uppercase
(
char *str
);

void getprint_list
(
char *rcprinter
);

void sort_file
(
char filename[BUFSIZ], int lines
);

void stsrt
(
char *strings[], int num
);

void  alphatize_string
(
char *str
);

char *
remove_double_con
(
char *str
);

#endif
