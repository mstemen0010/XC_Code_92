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
#include <xview/font.h>
#include <xview/tty.h>
#include <errno.h>
#include <dirent.h>
#include "list.h"
   
#define		FIRST			1
#define		NEXT			2

extern void sort_file ( char filename[BUFSIZ], int lines);

char *
read_dir(char *word, char *pathptr)
{
	Frame				subframe;
	Panel				subpanel;
	Server_image		gen_icon;

	char				sortfile[] = "/usr/tmp/temp";
    DIR         		*dirp;
    struct dirent 		*dp;
    char        		buffname[BUFSIZ], searchstr[BUFSIZ];
    char        		mypathname[BUFSIZ];
    char        		filestr[BUFSIZ];
    int         		matchcount = 0, index = 0, i = 0, errflag = 0, strl = 0;
    char        		child[5];
    char        		parent[5];
    char    			*token;
    char    			tempfile[BUFSIZ], messstr[BUFSIZ];
    char        		*filelist[BUFSIZ * 2];
    char        		*content;
	char				*bit;
    char    			statpath[BUFSIZ];
    char    			tidbit[BUFSIZ];
    struct  stat    	statbuff;
    char    			*newPath;
	char				*tmpptr, *tmpptr2;
	FILE				*fp, *outfp, *samplefp;
	char				typeBuff;
	int					numRead, numToRead = 8, enterFlag = 0, filtered_flag;
	unsigned			blen;
	off_t				file_size;
	long				tadbit;
	char				intStr[BUFSIZ];
	struct fileprofile	filepro;
	int					status;
	int					showFlag;

	subframe = (Frame)xv_create(NULL, FRAME_CMD,
		XV_SHOW,				TRUE,
		FRAME_SHOW_RESIZE_CORNER, TRUE,
        FRAME_LABEL,            "",
        WIN_COLUMNS,            40,
        WIN_ROWS,               20,
        NULL);

   subpanel = (Panel)xv_create(subframe, PANEL,
		XV_SHOW,				TRUE,
        WIN_COLUMNS,            40,
        WIN_ROWS,               20,
        PANEL_LAYOUT,           PANEL_VERTICAL,
        FRAME_CMD_PUSHPIN_IN,   TRUE,
        NULL);

test_choice = (Panel_item)xv_create(subpanel, PANEL_LIST,
			PANEL_LIST_INSERT_DUPLICATE,	FALSE,
			PANEL_READ_ONLY,				TRUE,
			PANEL_LIST_MODE,				PANEL_LIST_READ,
			PANEL_LIST_DISPLAY_ROWS,		10,
            PANEL_LIST_ROW_HEIGHT,   		35,
            PANEL_LIST_WIDTH,           	500,
            PANEL_LIST_TITLE,           	"		Directory list",
            PANEL_NOTIFY_PROC,      		list_notify_proc,
            NULL);

	file_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    file_bits,
			NULL);    	

	dir_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    dir_bits,
			NULL);    	

	sys_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    sys_bits,
			NULL);    	

	link_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    link_bits,
			NULL);    	

	pipe_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    pipe_bits,
			NULL);    	

	sock_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    sock_bits,
			NULL);    	

	core_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    core_bits,
			NULL);    	

	compressed_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    compressed_bits,
			NULL);    	

	csource_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    csource_bits,
			NULL);    	

	object_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    object_bits,
			NULL);    	

	header_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    header_bits,
			NULL);    	

	exe_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    exe_bits,
			NULL);    	

	aml_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    aml_bits,
			NULL);    	

	sound_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    sound_bits,
			NULL);    	

	ps_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    ps_bits,
			NULL);    	

	rast_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    rast_bits,
			NULL);    	

	mail_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    mail_bits,
			NULL); 
	shell_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    shell_bits,
			NULL);    	

	wp_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    wp_bits,
			NULL);    	

	bm_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    bm_bits,
			NULL);    	

	gif_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    gif_bits,
			NULL);    	

	make_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    make_bits,
			NULL);    	

	info_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    info_bits,
			NULL);    	

	lib_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    lib_bits,
			NULL);    	

	gis_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    gis_bits,
			NULL);    	

	im_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    im_bits,
			NULL);    	

	gra_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    gra_bits,
			NULL);
	plt_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    plt_bits,
			NULL);    	

	XRs_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    XRs_bits,
			NULL);    	

	XRh_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    XRh_bits,
			NULL);    	

	XRr_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    XRr_bits,
			NULL);    	

	XRe_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    XRe_bits,
			NULL);    	


	XRd_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    XRd_bits,
			NULL);    	

	empty_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    empty_bits,
			NULL);    	

	
	strcpy (mypathname, pathptr);
	
	       
	strcpy(child, ".");
	strcpy(parent, "..");
	
    if ((outfp = fopen (sortfile, "w")) == NULL) {
        notice_prompt (subpanel, NULL,
          NOTICE_NO_BEEPING,         TRUE,
          NOTICE_MESSAGE_STRINGS,    "Unable to open sort file",
          NULL,  
          NULL);
		  return;
    }
	
	strcpy(searchstr, word);
	
	dirp = opendir(mypathname);
	
	if(errno == 0  || errno == ENOENT && dirp != NULL){ /* 1st if */
		for(dp = readdir(dirp); dp != NULL; dp = readdir(dirp)){ /* 1st for */
	    	if(strcpy(buffname, dp->d_name) != NULL )  { /* 2nd if */
	        	if(strcmp(buffname, child) != 0){ /* 3rd if */
	            	if(strcmp(buffname, parent) != 0){ /* 4th if */
						if (strstr (buffname, searchstr) != NULL) { /* 5th if */
	        				strcpy(statpath, mypathname);
				        	strl = strlen(statpath);
				        	if (statpath[strl - 1] != '/')
	       			     		strcat(statpath, "/");
				        	strcat(statpath, buffname);
				        	lstat(statpath, &statbuff);
							#ifdef DEBUG
								fprintf(stdout, "Stating %s\n", statpath);
								fflush (stdout);
							#endif

							if (statbuff.st_mode & S_IRUSR || statbuff.st_mode & S_IRGRP || statbuff.st_mode & S_IROTH)  
								showFlag = TRUE;
							else 
								showFlag = FALSE;
								
							if (showFlag) {
								strcat(buffname, "\n");
								blen = strlen(buffname);
								fwrite(buffname, blen, 1, outfp);
								matchcount++;
							}
							showFlag = FALSE;
						} /* end of 5th if  "searchstr cmp" */
					} /* end of 4th if "child cmp "  */
				} /* end of 3rd if "parent cmp "  */
			} /* end of 2nd if " strcpy to buffname from dp->d_name != NULL" */
		}    /* end of for "readdir" */
	    closedir(dirp);
	} /* end of 1st if "dirp != NULL" */
	
	fclose(outfp);

	sort_file(sortfile, matchcount);

	/* end of build a file list */


	/* begining of file grading */

    if ((fp = fopen (sortfile, "r")) == NULL) {
        notice_prompt (subpanel, NULL,
          NOTICE_NO_BEEPING,         TRUE,
          NOTICE_MESSAGE_STRINGS,    "Unable to reopen sort file",
          NULL,  
          NULL);
    }

	while(fscanf(fp, "%s", buffname) >= 1) {
	    strcpy(statpath, mypathname);
		strl = strlen(statpath);
	    if (statpath[strl - 1] != '/') 
	    	strcat(statpath, "/");
	    strcat(statpath, buffname);
	    strcat(statpath, "/");

	#ifdef DEBUG
		fprintf(stdout, "lstat path is %s", statpath);
		fflush(stdout);
	#endif



	    if (grade_file(&filepro, statpath, buffname) != NULL){
			gen_icon = filepro.file_icon;
			enterFlag = TRUE;
		}
		else {
			filtered_flag = TRUE;
			enterFlag = FALSE;
			matchcount--; 
		}


	
		if (enterFlag) {
		    	xv_set(test_choice, 
		    		PANEL_LIST_DELETE, i,
		    		PANEL_LIST_INSERT, i, 
					PANEL_LIST_GLYPH, i, gen_icon,
		    		PANEL_LIST_STRING, i, buffname,
		    		NULL);
	    	i++;
		}


	} /* end of while fgets */

	fclose(fp);
	unlink(sortfile);
	xv_set(subframe, XV_SHOW, TRUE, NULL);
	xv_set(subpanel, XV_SHOW, TRUE, NULL);
	window_fit(subframe);
	window_fit(subpanel);
} /* end of function */
int
list_notify_proc (Panel_item item, char *string, Xv_opaque client_data, Panel_list_op op, Event *event, int row )
{
       
static	int		interation;
	Frame 		tmpframe;
    Panel 		tmppanel;
    int       	i;
    char  		choice[BUFSIZ] = {""};
    char  		*choiceptr, *pathptr, *wordptr, *token;
    struct  stat statbuff;
    char 		*newPath;
    int      	strl;
    int      	color;


	if (op == PANEL_LIST_OP_DESELECT)
		return(op);

	if (interation != FIRST) {
		is_DoubleClick(event, FIRST, string);
		interation++;
	}
	
	else {
		if (is_DoubleClick(event, NEXT, string) == TRUE) {
	       		choiceptr = (char *)xv_get(test_choice, PANEL_LIST_STRING, row);
				token = strtok(choiceptr, " ");
	       		if (token != NULL) {
	       				strl = strlen(token);
	       				bcopy (token, choice, strl);
	       		}
	       		else
						return(op);
	
				if (strcmp(choice, "..") != 0) {
	       			xv_set(prop_warnName, PANEL_VALUE, choice, NULL);  
				}
				else {
	       			xv_set(prop_warnName, PANEL_VALUE, choice, NULL);  
				}
		} /* end if for if DOUBLE */

	} /* end else */
}
int 
is_DoubleClick(Event *event, int type, char *string)
{

static 	struct 	clickStruct current;
static 	struct 	clickStruct last;
static  char	*lastStr;
static  int		mouseFlag;

		struct 	timeval		timer;
		long		intervalTime;
		long		intervalUTime;
		long		interval = 1;       /* time out time in secs. */
		long		uinterval = 0; /* time out time in mircosecs. */
		int		timeout = 0;
		int		isDouble;
		   

	
	timeout = defaults_get_integer("openWindows.multiClickTimeout", "OpenWindows.MultiClickTimeout", 4) * 100000; 
	uinterval = timeout;

	timer = event->ie_time;

	/* initilize the click loop */
	
	if (type == FIRST) { 
		current.ClickTime = timer.tv_sec;
		current.ClickUTime = timer.tv_usec;
		last.ClickTime = timer.tv_sec;
		last.ClickUTime = timer.tv_usec;
		lastStr = string;
	}
	else if (type == NEXT) {
		current.ClickTime = timer.tv_sec;
		current.ClickUTime = timer.tv_usec;
		intervalTime = current.ClickTime - last.ClickTime;
		intervalUTime = current.ClickUTime - last.ClickUTime;
		if (strcmp(string, lastStr) == 0){
			if (event_action(event) == ACTION_SELECT && intervalUTime <= uinterval) { 
				if (intervalTime <= interval) { 
	#ifdef DEBUG
					fprintf (stdout, "Did not Time out. interval time %d was < %d mircoseconds\n", intervalUTime, uinterval);
					fprintf (stdout, "Did not Time out. interval time %d was < %d seconds\n", intervalTime, interval);
					fprintf (stdout, "Double click is : %d \n\n", isDouble);
	#endif
					fflush(stdout);
					isDouble = TRUE;
				}
				else {
				isDouble = FALSE;
	#ifdef DEBUG
					fprintf (stdout, "Timed out. uinterval time %d was > %d mircoseconds\n", intervalUTime, uinterval);
					fprintf (stdout, "Timed out. uinterval time %d was > %d seconds\n", intervalTime, interval);
					fprintf (stdout, "Double click is : %d \n\n", isDouble);
	#endif
					fflush(stdout); }
			}
			else {
	#ifdef DEBUG
				fprintf (stdout, "Timed out. uinterval time %d was > %d mircoseconds\n", intervalUTime, uinterval);
				fprintf (stdout, "Timed out. uinterval time %d was > %d seconds\n", intervalTime, interval);
				fprintf (stdout, "Double click is : %d \n\n", isDouble);
	#endif
				fflush(stdout);
				isDouble = FALSE;
			}
		}
		else {
#ifdef DEBUG
			fprintf (stdout, "String values do not match C:%s & L:%s\n", string, lastStr);
			fflush(stdout);
	#endif
		}
	last.ClickTime = current.ClickTime;
	last.ClickUTime = current.ClickUTime;
	lastStr = string;
	}
	return(isDouble);
}
