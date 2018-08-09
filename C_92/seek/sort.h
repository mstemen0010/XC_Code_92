/*
** File:     phonetool.h	SCCS: 1.8 - 4/26/93
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

#ifndef PTXV_H		/* include only once */
#define	PTXV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <fcntl.h>
#include <stropts.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <xview/xview.h>
#include <xview/panel.h>
#include <xview/frame.h>


#define MAXBUF 1024
#define TEMPFILE "/usr/tmp/pbtemp.txt"
#define TEMPSORTFILE "/usr/tmp/tmpseek.srt"

 
/* Global Variables */
extern Panel_item      mess_item;

void sort_file
(
char filename[BUFSIZ], int lines
);

int stsrt 
(
const void *ptra, const void *ptrb
);

#endif
