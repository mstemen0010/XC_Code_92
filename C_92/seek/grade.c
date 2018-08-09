/*
** File: grade.c SCCS 1.2 - 7/8/94 
** Author:   M. Stemen
**
** Created:  2/22/94
** Edited:
**
**
** Purpose:
**
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <xview/sun.h>
#include <string.h>
#include <errno.h>
#include "seek_main.h"

#ifndef FALSE
	#define FALSE 0	
#endif

#ifndef TRUE
	#define TRUE 1 
#endif

#define     SIGNET_EMPTY        0
#define     SIGNET_EXC1         -2130509557
#define     SIGNET_EXC2         -2130509560
#define     SIGNET_WP1          -11055037
#define     SIGNET_WP2          1098216552
#define     SIGNET_Z            530419801
#define     SIGNET_CORE         525398
#define     SIGNET_ICON1        791289926
#define     SIGNET_ICON2        791289920
#define     SIGNET_SOUND        779316836
#define     SIGNET_SHELL1       589373487
#define     SIGNET_SHELL2       589377378
#define     SIGNET_MAIL         1181904749
#define     SIGNET_RAST         1504078485
#define     SIGNET_GIF          1195984440
#define     SIGNET_PS           622940243
#define     SIGNET_MAKE         587866912
#define     SIGNET_INFO         1380270404
#define     SIGNET_GIS          69556444
#define     SIGNET_IM           -134219128
#define     SIGNET_GRA          1128353876
#define     SIGNET_PLT          9993
#define     SIGNET_XRs          587866912
#define     SIGNET_XRe1         824194848
#define     SIGNET_XRe2         824193568
#define     SIGNET_XRr          173305658
#define     SIGNET_XRd1         1023
#define     SIGNET_XRd2         1535
#define     SIGNET_XRh1         589373537 /* 795373421 is the old one*/
#define     SIGNET_XRh2         589373537
#define     SIGNET_PKZIP        1347093252
#define     SIGNET_DIR         	2
#define     SIGNET_LNK         	3
#define     SIGNET_CHR         	4
#define     SIGNET_SOCK         5
#define     SIGNET_PIPE        	6

int grade_file (struct fileprofile *filepro, char *pathname, char *buffname);


int
grade_file(struct fileprofile *filepro, char *pathname, char *buffname)

{
    char            tidbit[BUFSIZ];
	char			*tmpptr;
    struct  stat    statbuff;
    long            tadbit;
	FILE			*fp;
	int 			value;


    
	
		if( lstat(pathname, &statbuff) == 0){
			filepro->file_size = statbuff.st_size;

        	switch (statbuff.st_mode & S_IFMT) {
                case S_IFREG:
                     if ((fp = fopen (pathname, "r")) != NULL) {
                     	tadbit = 0;
                        fread(&tadbit, sizeof(long), 1, fp);
                        #ifdef DEBUG
                        	fprintf(stdout, "File name: %s \n", buffname);
                            fprintf(stdout, "Tadbit hex: %h \n", tadbit);
                            fprintf(stdout, "Tadbit long: %l \n\n", tadbit);
                            fprintf(stdout, "Tadbit decimal: %d \n\n", tadbit);
                        #endif
                        fclose(fp);
                    }
					else 
						return(NULL);

				if (! ff_file)
						value = NULL;
				else {
						filepro->file_icon = file_icon;
						value = 1;
				}

                    if (strstr(buffname, "README") != NULL || strstr(buffname, "readme") != NULL || strstr(buffname, "READ.ME") != NULL || strstr(buffname, "read.me") != NULL)
                    	if (strlen(buffname) == 6 || strlen(buffname) == 7)
							if (! ff_info) 
								value = NULL;
							else {
								filepro->file_icon = info_icon;
								value = 1;
							}
                    if (tadbit == SIGNET_MAKE)
                    	if (strstr(buffname, "Make") != NULL || strstr(buffname, "make") != NULL)
                        	if (strlen(buffname) == 8)
							if (! ff_make) 
								value = NULL;
							else {
								filepro->file_icon = make_icon;
								value = 1;
							}

                    if (statbuff.st_size  == 0)
						if (! ff_empty) 
							value = NULL;
						else {
							filepro->file_icon = empty_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_CORE)
						if (! ff_core) 
							value = NULL;
						else {
							filepro->file_icon = core_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_PLT)
						if (! ff_plt) 
							value = NULL;
						else {
							filepro->file_icon = plt_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_GRA)
						if (! ff_gra) 
							value = NULL;
						else {
							filepro->file_icon = gra_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_IM)
						if (! ff_im) 
							value = NULL;
						else {
							filepro->file_icon = im_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_GIS)
						if (! ff_gis) 
							value = NULL;
						else {
							filepro->file_icon = gis_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_GIF)
						if (! ff_gif) 
							value = NULL;
						else {
							filepro->file_icon = gif_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_PS)
						if (! ff_ps) 
							value = NULL;
						else {
							filepro->file_icon = ps_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_ICON1 || tadbit == SIGNET_ICON2)
						if (! ff_bm) 
							value = NULL;
						else {
							filepro->file_icon = bm_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_WP1 || tadbit == SIGNET_WP2)
						if (! ff_wp) 
							value = NULL;
						else {
							filepro->file_icon = wp_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_RAST)
						if (! ff_rast) 
							value = NULL;
						else {
							filepro->file_icon = rast_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_MAIL)
						if (! ff_mail) 
							value = NULL;
						else {
							filepro->file_icon = mail_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_SHELL1 || tadbit == SIGNET_SHELL2)
						if (! ff_shell) 
							value = NULL;
						else {
							filepro->file_icon = shell_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_EXC1 || tadbit == SIGNET_EXC2)
						if (! ff_exe) 
							value = NULL;
						else {
							filepro->file_icon = exe_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_SOUND)
						if (! ff_sound) 
							value = NULL;
						else {
							filepro->file_icon = sound_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_XRs)
                        if ((tmpptr = strstr(buffname, "script")) != NULL )
						if (! ff_XRs) 
							value = NULL;
						else {
							filepro->file_icon = XRs_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_XRd1 || tadbit == SIGNET_XRd2)
						if (! ff_XRd) 
							value = NULL;
						else {
							filepro->file_icon = XRd_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_XRh1 || tadbit == SIGNET_XRh2)
						if (! ff_XRh) 
							value = NULL;
						else {
							filepro->file_icon = XRh_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_XRe1 || tadbit == SIGNET_XRe2)
						if (! ff_XRe) 
							value = NULL;
						else {
							filepro->file_icon = XRe_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_XRr)
						if (! ff_XRr) 
							value = NULL;
						else {
							filepro->file_icon = XRr_icon;
							value = 1;
						}

                    if (tadbit == SIGNET_PKZIP)
						if (! ff_pkzip) 
							value = NULL;
						else {
							filepro->file_icon = pkzip_icon;
							value = 1;
						}

                    if ((tmpptr = strstr(buffname, ".exe")) != NULL )
                        if (strlen(tmpptr) == 4)
                        if (! ff_dos)
                            value = NULL;
                        else {
                            filepro->file_icon = dos_icon;
                            value = 1;
                        }

                    if ((tmpptr = strstr(buffname, ".Z")) != NULL )
                    	if (strlen(tmpptr) == 2)
						if (! ff_compressed) 
							value = NULL;
						else {
							filepro->file_icon = compressed_icon;
							value = 1;
						}

                    if ((tmpptr = strstr(buffname, ".c")) != NULL )
                        if (strlen(tmpptr) == 2)
						if (! ff_csource) 
							value = NULL;
						else {
							filepro->file_icon = csource_icon;
							value = 1;
						}

                    if ((tmpptr = strstr(buffname, ".a")) != NULL )
                    	if (strlen(tmpptr) == 2)
						if (! ff_lib) 
							value = NULL;
						else {
							filepro->file_icon = lib_icon;
							value = 1;
						}

                    if ((tmpptr = strstr(buffname, ".h")) != NULL )
                    	if (strlen(tmpptr) == 2)
						if (! ff_header) 
							value = NULL;
						else {
							filepro->file_icon = header_icon;
							value = 1;
						}

                    if ((tmpptr = strstr(buffname, ".o")) != NULL )
                    	if (strlen(tmpptr) == 2)
						if (! ff_object) 
							value = NULL;
						else {
							filepro->file_icon = object_icon;
							value = 1;
						}

                    if ((tmpptr = strstr(buffname, ".aml")) != NULL
)
                        if (strlen(tmpptr) == 4) 
						if (! ff_aml) 
							value = NULL;
						else {
							filepro->file_icon = aml_icon;
							value = 1;
						}
                	break;
                    case S_IFLNK:
					if (! ff_lnk) 
						value = NULL;
						else {
							filepro->file_icon = link_icon;
							value = 1;
						}
                    break;
                    case S_IFSOCK:
					if (! ff_sock) 
						value = NULL;
						else {
							filepro->file_icon = sock_icon;
							value = 1;
						}
                    break;
                    case S_IFCHR:
					if (! ff_chr) 
						value = NULL;
						else {
							filepro->file_icon = sys_icon;
							value = 1;
						}
                    break;
                    case S_IFIFO:
					if (! ff_fifo) 
						value = NULL;
						else {
							filepro->file_icon = pipe_icon;
							value = 1;
						}
                    break;
                    case S_IFDIR:
					if (! ff_dir) 
						value = NULL;
						else {
							filepro->file_icon = dir_icon;
							value = 1;
						}
                    break;

				default:
                    break;
        	} /* end of lstat switch */
    	}
	return(value);
}


