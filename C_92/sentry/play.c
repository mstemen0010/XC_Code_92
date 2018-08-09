/*
** $Workfile:   play.c  $
** $Archive:   /home/dbi0/usr/jat/src/xview/sentry/archives/play.c_v  $
** Author: Sun Microsystems, Inc.
** $Revision:   1.0  $    $Date:   15 Feb 1993 16:06:30  $
**
** $Log:   /home/dbi0/usr/jat/src/xview/sentry/archives/play.c_v  $
**  
**     Rev 1.0   15 Feb 1993 16:06:30   jat
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
** Copyright (c) 1989 by Sun Microsystems, Inc.
** 
** Copyright (c) 1993, United Parcel Service of America, Inc.
** All Rights Reserved.
**
** Purpose:  Play a sound file on the audio device.  This was
**           originally a stand-alone program from Sun Microsystems.
**           I grabbed it and modified it so that it could be used as
**           a library routine.  This is designed for use in xview
**           programs, it does not print out any errors.
**
*/
#ifdef SPARC
static char     cFileID[] = "$Header:   /home/dbi0/usr/jat/src/xview/sentry/archives/play.c_v   1.0   15 Feb 1993 16:06:30   jat  $"
#endif

#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/signal.h>

#include <stropts.h>
#include <sys/ioctl.h>

#include <multimedia/libaudio.h>
#include <multimedia/audio_device.h>
#include <multimedia/audio_hdr.h>
#include <multimedia/audio_filehdr.h>
#include <multimedia/audio_errno.h>

#include "play.h"

char		*Stdin = "stdin";
unsigned char	buf[1024 * 64];		/* size should depend on sample_rate */


#define	MAX_GAIN		(100)		/* maximum gain */

/*
 * This defines the tolerable sample rate error as a ratio between the
 * sample rates of the audio data and the audio device.
 */
#define	SAMPLE_RATE_THRESHOLD	(.01)

unsigned	Volume = ~0;		/* output volume */
double		Savevol;		/* saved volume level */
int		Verbose = FALSE;	/* verbose messages */
int		Immediate = FALSE;	/* don't hang waiting for device */
char		*Audio_dev = "/dev/audio";

int		Audio_fd = -1;		/* file descriptor for audio device */
Audio_hdr	Dev_hdr;		/* audio header for device */
Audio_hdr	File_hdr;		/* audio header for file */

/*
 * Play an audio file.
 */
int
play (char *Ifile, unsigned volume)
{
  int                   i;
  int		        cnt;
  int		        err;
  int		        ifd;
  int		        stdinseen;
  double		vol;
  struct stat	        st;
  struct sigvec	        vec;

  /* Validate and open the audio device */
  err = stat (Audio_dev, &st);
  if (err < 0) 
    {
      return (FALSE);
    }
  if (!S_ISCHR (st.st_mode)) 
    {
      return (FALSE);
    }

  /* Try it quickly, first */
  Audio_fd = open (Audio_dev, O_WRONLY | O_NDELAY);
  if ((Audio_fd < 0) && (errno == EBUSY)) 
    {
      if (Immediate) 
        {
          return (FALSE);
        }
      /* Now hang until it's open */
      Audio_fd = open (Audio_dev, O_WRONLY);
    }
  if (Audio_fd < 0) 
    {
      return (FALSE);
    }

  /* Get the device output encoding configuration */
  if (audio_get_play_config(Audio_fd, &Dev_hdr) != AUDIO_SUCCESS) 
    {
      return (FALSE);
    }

  if (volume != ~0) 
    {
      Volume = volume;
      vol = (double) Volume / (double) MAX_GAIN;
      (void) audio_get_play_gain (Audio_fd, &Savevol);
      err = audio_set_play_gain (Audio_fd, &vol);
      if (err != AUDIO_SUCCESS) {
        return (FALSE);
      }
    }

  /* Set up SIGINT handler to flush output */
  vec.sv_handler = sigint;
  vec.sv_mask = 0;
  vec.sv_flags = 0;
  (void) sigvec(SIGINT, &vec, (struct sigvec *)NULL);

  if ((ifd = open(Ifile, O_RDONLY, 0)) < 0) 
    {
      return (FALSE);
    }

  /* Check to make sure this is an audio file */
  err = audio_read_filehdr (ifd, &File_hdr, (char *)NULL, 0);

  if (err != AUDIO_SUCCESS) 
    {
      goto closeinput;
    }

  /* Check the device configuration */
  if (audio_cmp_hdr (&Dev_hdr, &File_hdr) != 0) 
    {
      /*
       * The device does not match the input file. Wait for any old
       * output to drain, then attempt to reconfigure the audio device
       * to match the input data.
       */
      if (audio_drain (Audio_fd, FALSE) != AUDIO_SUCCESS) 
        {
          return (FALSE);
        }
      if (!reconfig())
        goto closeinput;
    }

  /*
   * At this point, we're all ready to copy the data.
   */
  while ((cnt = read (ifd, (char *) buf, sizeof (buf))) >= 0) 
    {
      /* If input EOF, write an eof marker */
      err = write (Audio_fd, (char *)buf, cnt);

      if (err != cnt) 
        {
          break;
        }
      if (cnt == 0)
        break;
    }

closeinput:
  (void) close (ifd);		/* close input file */

  /*
   * Though drain is implicit on close(), it's performed here for the
   * sake of completeness, and to ensure that the volume is reset
   * after all output is complete.
   */
  (void) audio_drain (Audio_fd, FALSE);
  if (Volume != ~0) 
    {
      (void) audio_set_play_gain (Audio_fd, &Savevol);
    }

  (void) close (Audio_fd);			/* close output */
  return (TRUE);
}

void
sigint (void)
{
	/* flush output queues before exiting */
	if (Audio_fd >= 0) 
          {
            (void) audio_flush_play (Audio_fd);
            if (Volume != ~0)
              (void) audio_set_play_gain (Audio_fd, &Savevol);
            (void) close(Audio_fd);			/* close output */
          }
	exit (1);
}


/*
 * Try to reconfigure the audio device to match the file encoding.  If
 * this fails, we should attempt to make the input data match
 * thedevice encoding.  For now, we give up on this file.
 *
 * Returns TRUE if successful.  Returns FALSE if not.
 */
int
reconfig(void)
{
  int                   err;
  char	                msg[AUDIO_MAX_ENCODE_INFO];

  Dev_hdr = File_hdr;
  err = audio_set_play_config (Audio_fd, &Dev_hdr);

  switch (err) 
    {
    case AUDIO_SUCCESS:
      return (TRUE);

    case AUDIO_ERR_NOEFFECT:
      /*
       * Couldn't change the device.  Check to see if we're nearly
       * compatible.  audio_cmp_hdr() returns >0 if only sample rate
       * difference. 
       */
      if (audio_cmp_hdr (&Dev_hdr, &File_hdr) > 0) 
        {
          double                    ratio;

          ratio = (double) abs ((int)
                                (Dev_hdr.sample_rate - File_hdr.sample_rate)) /
                                  (double) File_hdr.sample_rate;
          if (ratio <= SAMPLE_RATE_THRESHOLD) 
            {
              return (TRUE);
            }
          return (FALSE);
        }
      (void) audio_enc_to_str (&File_hdr, msg);
      return (FALSE);

    default:
      return (FALSE);
    }
}
