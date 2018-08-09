/*
** $Workfile:   play.h  $
** $Archive:   /home/dbi0/usr/jat/src/xview/sentry/archives/play.h_v  $
** Author:   Jason Trommetter
** Created:  Mon Feb 15 15:00:44 EST 1993
** $Revision:   1.0  $    $Date:   15 Feb 1993 16:06:36  $
**
** $Log:   /home/dbi0/usr/jat/src/xview/sentry/archives/play.h_v  $
**  
**     Rev 1.0   15 Feb 1993 16:06:36   jat
**  Initial revision.
**
** The use, disclosure, reproduction, modification, transfer, or
** transmittal of this work for any purpose in any form or by any
** means without the written permission of United Parcel Services is
** strictly prohibited.
**
** Confidential, Unpublished Property of United Parcel Services.
** Use and Distribution Limited Solely to Authorized Personnel.
**
** Copyright (c) 1993, United Parcel Service of America, Inc.
** All Rights Reserved.
**
** Purpose:
**
*/
#ifndef PLAY_H
#define PLAY_H

/* Prototypes */
int                 play (char *Ifile, unsigned volume);
void                sigint (void);
int                 reconfig (void);

#endif	/* PLAY_H */
