/*
** File: seek_xview.c SCCS 8.7 - 7/8/94 
** Author:   M. Stemen
**
** Created:  7/21/93
** Edited:
**
**
** Purpose:
**  
*/


#ifndef FALSE
#define FALSE 0 
#endif

#ifndef TRUE
#define TRUE !FALSE
#endif

#define		PARENT_FOUND  		TRUE
#define		PARENT_NOT_FOUND  	FALSE

/* 	define colors used for the app. */

#define		WHITE           0
#define     WHEAT           1
#define     RED             2
#define     PURPLE          3
#define     BLACK           4
/* 	define flags used to determine the mode of operation */
#define		INFILE  		0
#define		OUTFILE 		1
/* 	define flags used to determine the targetFlag */
#define     DIRECTORY       0
#define     MFILE           1
/* 	define flags used in the buildPath function */
#define		ADD     		0
#define		REMOVE  		1
/* 	define flag used to determine operations for the Textsw string searches */
#define		FIRST			1
#define		NEXT			2
/* 	define the "signeture numbers" to determine file type */
#define		SIGNET_EMPTY		0
#define		SIGNET_EXC1			-2130509557
#define		SIGNET_EXC2			-2130509560
#define		SIGNET_WP1			-11055037
#define		SIGNET_WP2			1098216552
#define		SIGNET_Z			530419801
#define		SIGNET_CORE			525398
#define		SIGNET_ICON1		791289926
#define		SIGNET_ICON2		791289920
#define		SIGNET_SOUND		779316836
#define		SIGNET_SHELL1		589373487
#define		SIGNET_SHELL2		589377378
#define		SIGNET_MAIL			1181904749
#define		SIGNET_RAST			1504078485
#define		SIGNET_GIF			1195984440
#define		SIGNET_PS			622940243
#define		SIGNET_MAKE			587866912
#define		SIGNET_INFO			1380270404
#define		SIGNET_GIS			69556444
#define		SIGNET_IM			-134219128
#define		SIGNET_GRA 			1128353876
#define		SIGNET_PLT 			9993
#define		SIGNET_XRs			587866912
#define		SIGNET_XRe1			824194848
#define		SIGNET_XRe2			824193568
#define		SIGNET_XRr			173305658
#define		SIGNET_XRd1			1023
#define		SIGNET_XRd2			1535
#define		SIGNET_XRh1			589373537 /* 795373421 is the old one*/
#define		SIGNET_XRh2			589373537
#define     SIGNET_DIR          2
#define     SIGNET_LNK          3
#define     SIGNET_CHR          4
#define     SIGNET_SOCK         5
#define     SIGNET_PIPE         6 

/* 	define default pathnames */
/* 	define flags for the "look_up_all" function */
#define			PRIMARY 0
#define			SECONDARY 1

#include "seek_xview.h" 
#include <time.h>

/* 	global definition for functions contained in this file */

int     		nummatched = 0, currTog = 1, primePtr_index = 0, secondPtr_index = 0;
int				lastRow = 0, upFlag = FALSE, listIndex = 0;
int				listArray[BUFSIZ];
int				currPos;
Textsw_index	currTi = 0;
int				num_file_lines, total_file_bytes;
char    		primePtr_array[10][BUFSIZ], secondPtr_array[10][BUFSIZ];
unsigned		matchOp = 0;
char    		filename[BUFSIZ], currentPathName[BUFSIZ] = "", addfilename[BUFSIZ] = "";
Frame			vttyFrame;
Tty				vitty;
char 			leftFootStr[BUFSIZ];
char 			rightFootStr[BUFSIZ];
short			parentItem;
static	char	gotoPathName[BUFSIZ];
	
Textsw_index    first = 0 , last_plus_one = 0, current = 0;
Panel_item      tempitem;

/* 	begin function definitions */

	
void
look_up_all(Panel_item item, Event *event)


/* 	
	This function is called by various buttons and or functions.
   	Its purpose is to take a string from the "Search for:" line on the app.
	and determine if the string is associated with a file, directory, or is
	a "wildcard" string.
	If it is determined that the string is a file, then it is display in the
	Textsw. If it is determined that the string is a directory, then the 
	"read_dir" function is called to display a listing of that directory.
	If it is determined that the string is neither of the above, then it
	is treated as if it is a wildcard name for the current directory. 
	The current directory is displayed with only filenames that contain the
	string in there name, this is done by calling the "read_dir" and passing
	the string in to determine wildcard matches.
*/

{


   	char    word[BUFSIZ] = "", *newPath;
   	char    buf[BUFSIZ]; 
   	char    line[BUFSIZ], command[BUFSIZ + 10]; 
   	char    wordlist[10000];  
	char 	*token;
   	int     x = 1, y = 1, i = 0;
	int		goOn = FALSE;
   	int     soundexflag = 0;
   	char    *wordpt;
   	struct  stat            statbuff;
   	char    *pathptr;
	FILE	*pfp;
	

    i = strlen(primaryPath);
	/*
    if (primaryPath[i - 1] != '/') {
        strcat(primaryPath, "/");
       	xv_set(primarySearchPath, PANEL_VALUE, primaryPath, NULL);
	}
	*/


    i = strlen(secondaryPath);
	/*
    if (secondaryPath[i - 1] != '/') {
        strcat(secondaryPath, "/");
       	xv_set(secondarySearchPath, PANEL_VALUE, secondaryPath, NULL);
	}
	*/

	if (event != NULL) 
		if (event_is_down(event) && event_id(event) == BUT(3))
			return;
		else 
			goOn = TRUE;
	else
			goOn = TRUE;

	if (goOn) {
		switch ( (int) xv_get (item, PANEL_CLIENT_DATA)) {
	
	    	case prime:
	
				tempitem = primebutton;
	       		xv_set(word_item, PANEL_CLIENT_DATA, prime, NULL);
	       		xv_set(test_choice, PANEL_CLIENT_DATA, prime, NULL);
	       		xv_set(primebutton, PANEL_ITEM_COLOR, CMS_CONTROL_COLORS + RED, NULL);    
	       		xv_set(secondbutton, PANEL_ITEM_COLOR, CMS_CONTROL_COLORS + BLACK, NULL);  
	       		xv_set(textsw,  TEXTSW_BROWSING, FALSE, NULL);
	       		xv_set(frame, FRAME_BUSY, TRUE, NULL);
	       		flush_panel();  

	       		textsw_reset(textsw, x, y); 
	
	       		if (strlen (filename) < 1 )
	       			strcpy(filename, primaryPath); 
	
	       		if (strstr (filename, secondaryPath) != NULL)
	       			strcpy(filename, primaryPath); 
	
				if (strstr (filename, primaryPath) == NULL)
					if (item == primebutton && event != NULL)
	       				strcpy(filename, primaryPath); 
	       
	       		switch (targetFlag) {
	       			case MFILE:
	                    if ( (strlen ((char *)xv_get(word_item, PANEL_VALUE)) ) >=  1){
							if (strcmp((char *)xv_get(word_item, PANEL_VALUE), "..") != 0) {
								upFlag = FALSE;
	                        	newPath = buildPath(ADD, filename);
								strcpy(filename, newPath);
							}
							else {
								upFlag = TRUE;
	                        	newPath = buildPath(ADD, filename);
	                        	newPath = buildPath(REMOVE, filename);
								strcpy(filename, newPath);
							}

						}
	       				else {
	       					newPath = filename;
							strcpy(filename, newPath);
						}
	       
	       				if ((stat(filename, &statbuff)) == -1){
							/* fprintf(stdout, "Error\n%s\n", filename);
							fflush(stdout); */
	       					newPath = buildPath(REMOVE, filename);
							strcpy(filename, newPath);
	       					wordpt = (char *)xv_get(word_item, PANEL_VALUE);
	       					read_dir(wordpt, prime, filename); 
	       					xv_set(frame, FRAME_BUSY, FALSE, NULL);
	                        flush_panel();
							return;
						}
						 
	       
	
	       				switch (statbuff.st_mode & S_IFMT) {
	       					case S_IFREG:
	       
	       						xv_set(textsw, TEXTSW_FILE, newPath, NULL); 
	                            xv_set(frame, FRAME_BUSY, FALSE, NULL);
	                            if (xv_get(textsw , TEXTSW_LENGTH) < 1) {
	                                   noMatchFlag = TRUE;
	                                   flush_panel();
	                            }
	                            else {
									total_file_bytes = statbuff.st_size;
									num_file_lines = 0;
									sprintf(command, "wc -l %s", filename );
    								if ((pfp = popen (command, "r")) == NULL) {
        								notice_prompt (panel, NULL,
          								NOTICE_NO_BEEPING,         TRUE,
          								NOTICE_MESSAGE_STRINGS,    "Unable to open pipe:",
          								NULL,  
          								NULL);
    								}
									else {
										while((fgets(line, BUFSIZ, pfp)) != NULL) {
											token = strtok(line, " ");
											num_file_lines = atoi(token);
										}
										pclose(pfp);
									}
										
	

									if ((int)xv_get(subframe, FRAME_CMD_PUSHPIN_IN) == FALSE) {
	                                	xv_set(subframe, XV_SHOW, FALSE, NULL);
	                                	xv_set(panel2, XV_SHOW, FALSE, NULL);
	                                }		
	                            	query_toggle(INFILE);
								}
	                            flush_panel();
	       						break;
	       
	       					case S_IFDIR:
								xv_set(word_item, PANEL_VALUE, "", NULL);
	       						wordpt = (char *)xv_get(word_item, PANEL_VALUE);
	       						read_dir("",  prime, filename);
	       						xv_set(frame, FRAME_BUSY, FALSE, NULL);
	                            flush_panel();
	       						break;
	
	       					default:
	       						newPath = buildPath(REMOVE, filename);
								strcpy(filename, newPath);
	       						wordpt = (char *)xv_get(word_item, PANEL_VALUE);
	       						read_dir(wordpt, prime, filename);
	       						xv_set(frame, FRAME_BUSY, FALSE, NULL);
								xv_set(word_item, PANEL_VALUE, "", NULL);
	                            flush_panel();
	       						break;
	       				} /* end switch for stat file */
	       				break; /* case MFILE */
	
	       			case DIRECTORY:
	       				xv_set(textsw, TEXTSW_FILE, filename, NULL); 
	       				if (xv_get(textsw , TEXTSW_LENGTH) < 1) {
	       					strcpy(filename, primaryPath);
	       					newPath = buildPath(ADD, filename);
	       					strcpy(filename, newPath);
	       					strcat(newPath, tag); 
	       					xv_set(textsw, TEXTSW_FILE, newPath, NULL); 
						}
						else
							newPath = filename;
	       				if (xv_get(textsw , TEXTSW_LENGTH) < 1) {
	       					newPath = buildPath(REMOVE, filename);
	       					strcpy(filename, newPath);
	       					wordpt = (char *)xv_get(word_item, PANEL_VALUE);
	       					if (strlen(wordpt) != 0)
	       						newPath = buildPath(REMOVE, filename);
	       					strcpy(filename, newPath);
	       					read_dir(wordpt, prime, filename);
	       					noMatchFlag = TRUE;
	               			flush_panel();  
	       				}
	       				else {
							if ((int)xv_get(subframe, FRAME_CMD_PUSHPIN_IN) == FALSE) {
	                        	xv_set(subframe, XV_SHOW, FALSE, NULL);
	                            xv_set(panel2, XV_SHOW, FALSE, NULL);
							}
	       					query_toggle(INFILE);
	       					strcpy(filename, newPath);
	       				}
	               		flush_panel();  
	    				if (editFlag == FALSE)
	       					xv_set(textsw,  TEXTSW_BROWSING, TRUE, NULL);
	       				xv_set(frame, FRAME_BUSY, FALSE, NULL);
	       				break; /* case DIRECTORY */
	
	       		} /* end switch for targetFlag */
	
	
				append_menu(PRIMARY, filename);	
	
	       	break; /* case prime */
	
	
	        case second:
				tempitem = secondbutton;
	            xv_set(word_item, PANEL_CLIENT_DATA, second, NULL);
	            xv_set(test_choice, PANEL_CLIENT_DATA, second, NULL);
	            xv_set(secondbutton, PANEL_ITEM_COLOR, CMS_CONTROL_COLORS + RED, NULL);
	
	            xv_set(primebutton, PANEL_ITEM_COLOR, CMS_CONTROL_COLORS + BLACK, NULL);
	            xv_set(textsw,  TEXTSW_BROWSING, FALSE, NULL);
	            xv_set(frame, FRAME_BUSY, TRUE, NULL);
	            flush_panel();
	            textsw_reset(textsw, x, y);
	
	            if (strlen (filename) < 1 )
	                strcpy(filename, secondaryPath);
	            if (strstr (filename, primaryPath) != NULL)
	                strcpy(filename, secondaryPath);
	       		if (strstr (filename, secondaryPath) == NULL)
					if (item == secondbutton && event != NULL)
	                	strcpy(filename, secondaryPath);
	
	            switch (targetFlag) {
	                case MFILE:
	                    if ( (strlen ((char *)xv_get(word_item, PANEL_VALUE)) ) >=  1){
                            if (strcmp((char *)xv_get(word_item, PANEL_VALUE), "..") != 0) {
								upFlag = FALSE;
                                newPath = buildPath(ADD, filename);
                                strcpy(filename, newPath);
                            }
                            else {
								upFlag = TRUE;
                                newPath = buildPath(REMOVE, filename);
                                strcpy(filename, newPath);
                            }

						}
	       				else {
	       					newPath = filename;
							strcpy(filename, newPath);
						}
	       
	       				if ((stat(filename, &statbuff)) == -1){
	       					newPath = buildPath(REMOVE, filename);
							strcpy(filename, newPath);
	       					wordpt = (char *)xv_get(word_item, PANEL_VALUE);
	       					read_dir(wordpt, second, filename);
	       					xv_set(frame, FRAME_BUSY, FALSE, NULL);
	                        flush_panel();
							return;
						}
						 
	       
	       
	                    switch (statbuff.st_mode & S_IFMT) {
	                        case S_IFREG:
	       
	                            xv_set(textsw, TEXTSW_FILE, newPath, NULL);
	                            xv_set(frame, FRAME_BUSY, FALSE, NULL);
	                            if (xv_get(textsw , TEXTSW_LENGTH) < 1) {
	                                   noMatchFlag = TRUE;
	                                   flush_panel();
	                            }
	                            else {
									total_file_bytes = statbuff.st_size;
									num_file_lines = 0;
									sprintf(command, "wc -l %s", filename );
                                    if ((pfp = popen (command, "r")) == NULL) {
                                        notice_prompt (panel, NULL,
                                        NOTICE_NO_BEEPING,         TRUE,
                                        NOTICE_MESSAGE_STRINGS,    "Unable to open pipe:",
                                        NULL,
                                        NULL);
                                    }    
                                    else {
                                        while((fgets(line, BUFSIZ, pfp)) != NULL) {
											token = strtok(line, " ");
                                            num_file_lines = atoi(token);
                                        }  
                                        pclose(pfp);
                                    }   
									if ((int)xv_get(subframe, FRAME_CMD_PUSHPIN_IN) == FALSE) {
	                                	xv_set(subframe, XV_SHOW, FALSE, NULL);
	                                	xv_set(panel2, XV_SHOW, FALSE, NULL);
									}
	                                query_toggle(INFILE);
								}
	                            flush_panel();
	                            break;
	       
	                        case S_IFDIR:
	                            xv_set(word_item, PANEL_VALUE, "", NULL);
	                            wordpt = (char *)xv_get(word_item, PANEL_VALUE);
	                            read_dir("",  second, filename);
	                            xv_set(frame, FRAME_BUSY, FALSE, NULL);
	                            flush_panel();
	                            break;
	
	                        default:
	                            newPath = buildPath(REMOVE, filename);
	                            strcpy(filename, newPath);
	                            wordpt = (char *)xv_get(word_item, PANEL_VALUE);
	                            read_dir(wordpt, second, filename);
	                            xv_set(frame, FRAME_BUSY, FALSE, NULL);
	                            xv_set(word_item, PANEL_VALUE, "", NULL);
	                            flush_panel();
	                            break;
	                    } /* end switch for stat file */
	                    break; /* case MFILE */
	 
	                case DIRECTORY:
	       				xv_set(textsw, TEXTSW_FILE, filename, NULL); 
	       				if (xv_get(textsw , TEXTSW_LENGTH) < 1) {
	                    	strcpy(filename, secondaryPath);
	                    	newPath = buildPath(ADD, filename);
	                    	strcat(newPath, tag);
	                    	xv_set(textsw, TEXTSW_FILE, newPath, NULL);
						}
						else
							newPath = filename;
	                    if (xv_get(textsw , TEXTSW_LENGTH) < 1) {
	                        newPath = buildPath(REMOVE, filename);
	                        strcpy(filename, newPath);
	                        wordpt = (char *)xv_get(word_item, PANEL_VALUE);
	                        if (strlen(wordpt) != 0)
	                            newPath = buildPath(REMOVE, filename);
	                        strcpy(filename, newPath);
	                        read_dir(wordpt, second, filename);
	                        noMatchFlag = TRUE;
	                        flush_panel();
	                    }
	                    else {
	                        query_toggle(INFILE);
	                        strcpy(filename, newPath);
							if ((int)xv_get(subframe, FRAME_CMD_PUSHPIN_IN) == FALSE) {
	                        	xv_set(subframe, XV_SHOW, FALSE, NULL);
	                            xv_set(panel2, XV_SHOW, FALSE, NULL);
							}
	                    }
	                    flush_panel();
	                    if (editFlag == FALSE)
	                        xv_set(textsw,  TEXTSW_BROWSING, TRUE, NULL);
	                    xv_set(frame, FRAME_BUSY, FALSE, NULL);
	                    break; /* case DIRECTORY */
	 
	            } /* end switch for targetFlag */
	
	
				append_menu(SECONDARY, filename);	
	
	        break; /* case second */
	
		} /* end switch for client data */
	} /* end if continue */
}/* end of function "look_up_all" */

		
void
get_word(Panel_item item, Event *event)

/* 	
	This function simply retrieves whatever is typed on the "Search for:" line.
	It is called by various function thoughout this file.
*/
{
       char *worditem;

       xv_set (subframe, XV_X, xv_get(frame, XV_X), NULL);
        xv_set (subframe, XV_Y, xv_get(frame, XV_Y), NULL);
        xv_set (subframe, XV_SHOW, TRUE, NULL);
        xv_set (subframe, FRAME_CMD_PUSHPIN_IN, TRUE, NULL);
       worditem = get_sel_item();
       if (strcmp(worditem, "") != 0) 
       xv_set(word_add, PANEL_VALUE, worditem, NULL);
       else {
       worditem = (char *)xv_get(word_item, PANEL_VALUE);
       xv_set(word_add, PANEL_VALUE, worditem, NULL);
       }
}


int
done_proc(Panel_item item, Event *event)

/*
	This is the call back for the subframe
*/

{
       
       xv_set(subframe, XV_SHOW, FALSE, NULL); 
}

void
quit(Panel_item item)
/*
	This is the call back for the quit button
*/

{
	int	i;
    Frame framed;
       

	framed = (Frame)xv_get(item, PANEL_CLIENT_DATA);
	xv_destroy_safe(framed);
}

void
flush_subframe(void) 
/*
	This is a generic flush called by various functions
*/
{
       
       Display *display;
       display = (Display *)xv_get(subframe, XV_DISPLAY);
       XFlush(display);
}

void
flush_panel(void) 
/*
	This is a panel flush called by various functions
*/
{
       
       Display *display;
       display = (Display *)xv_get(panel, XV_DISPLAY);
       XFlush(display);
}

char *
get_sel_item(void)
{
/*
	This is the call back for the "get_prime_sel" function . 
	It makes a request to the selection server to "grab"
	highlighted strings from any window and return it to the calling function
	as a string pointer. 
*/
    Xv_Server       server;
    Seln_holder     holder;
    Seln_request    *response;
    char            *output_string;
    char            temp[BUFSIZ];


    server = (Xv_Server)xv_get(xv_get(frame, XV_SCREEN), SCREEN_SERVER);
    holder = selection_inquire(server, SELN_PRIMARY);
    response = selection_ask(server, &holder, SELN_REQ_CONTENTS_ASCII, NULL, NULL);
    strcpy(temp, response->data + sizeof (SELN_REQ_CONTENTS_ASCII));
    output_string = temp;

    return(output_string);
}

void
get_prime_sel(Panel_item item)
/*
	This is the call back for the grab button. It makes an attempt to grab 
	highlighted strings from any window and paste it to the "carrot" focus 
*/
{
    char    *temp_word;
	Panel_item	who_item;

	who_item = (Panel_item)xv_get(panel, PANEL_CARET_ITEM);
    temp_word = get_sel_item();
    xv_set(who_item, PANEL_VALUE, temp_word, NULL);

}

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

    win_set_kbd_focus(panel, xv_get(panel, XV_XID));

	if (op == PANEL_LIST_OP_DESELECT)
		return(op);

	if (interation != FIRST) {
		is_DoubleClick(event, FIRST, string);
		interation++;
	    xv_set(frame, FRAME_BUSY, FALSE, NULL);
	}
	else {
		if (is_DoubleClick(event, NEXT, string) == TRUE) {
	       		choiceptr = (char *)xv_get(test_choice, PANEL_LIST_STRING, row);
				if (viewFlag == 6 || viewFlag == 7) {
					token = strtok(choiceptr, " ");
					token = strtok(NULL, " ");
					token = strtok(NULL, " ");
				}
				if (viewFlag == 4 ) 
					token = strtok(choiceptr, " ");

				if (viewFlag == 5)  {
					token = strtok(choiceptr, " ");
				}

	       		if (token != NULL) {
	       				strl = strlen(token);
	       				bcopy (token, choice, strl);
	       		}
	       		else
						return(op);
	
	       		xv_set(mess_item, PANEL_VALUE, "", NULL);
	
	       		color = (int)xv_get(primebutton, PANEL_ITEM_COLOR);
	       		if (color == CMS_CONTROL_COLORS + BLACK)
	       				xv_set(test_choice, PANEL_CLIENT_DATA, second, NULL);
	       		else
	       				xv_set(test_choice, PANEL_CLIENT_DATA, prime, NULL);
	
				if (strcmp(choice, "..") != 0) {
					listArray[listIndex] = row;
					listIndex++;

					if ((Panel_item)xv_get( panel, PANEL_CARET_ITEM ) != goto_item && parentItem == PARENT_FOUND) 
	       				xv_set(word_item, PANEL_VALUE, choice, NULL);  
					else
	       				xv_set(word_item, PANEL_VALUE, "", NULL);  

	           		flush_panel();      
	      			look_up_all(item, event);
				}
				else {
					if (listIndex > 0)
						listIndex--;
	       				xv_set(word_item, PANEL_VALUE, choice, NULL);  
					/*
					newPath = buildPath(REMOVE, filename);
					strcpy(filename, newPath);
					*/
	           		flush_panel();      
	      			look_up_all(item, event);
				}
		} /* end if for if DOUBLE */
		else
	    	xv_set(frame, FRAME_BUSY, FALSE, NULL);

	} /* end else */
    win_set_kbd_focus(panel, xv_get(panel, XV_XID));
	xv_set(frame, FRAME_BUSY, FALSE, NULL);
}

int
quitpanel(Panel_item item)
{
    Frame tmpframe;
    Panel tmppanel;
    
 
    tmppanel = (Panel)xv_get(item, PANEL_PARENT_PANEL);
    tmpframe = (Frame)xv_get(tmppanel, XV_OWNER);
    xv_set(tmpframe, FRAME_CMD_PUSHPIN_IN, FALSE, NULL);
    xv_set(tmpframe, XV_SHOW, FALSE, NULL);
}

int
read_dir(char *word, int dirtype, char *pathptr)
{
	/* strutures */
    struct  stat    	statbuff;
	struct fileprofile	filepro;

	/* structure pointers */
    struct dirent 		*dp;

	/* char strings */
	char				sortfile[] = "/usr/tmp/temp";
    char  				choice[BUFSIZ] = {""};
    char        		buffname[BUFSIZ], searchstr[BUFSIZ];
    char        		filestr[BUFSIZ];
	char				filler[BUFSIZ];
    char        		mypathname[BUFSIZ];
    char    			tempfile[BUFSIZ], messstr[BUFSIZ];
    char    			statpath[BUFSIZ];
	char 				home[BUFSIZ];
	char				intStr[BUFSIZ];
    char        		child[5];
    char        		parent[5];

	/* char string pointers */
    char    			*newPath;
	char				*tmpptr, *tmpptr2;
	char				*choiceptr;
    char    			*token;

	/* file pointers */
    DIR         		*dirp;
	FILE				*fp, *outfp, *samplefp;

	/* ints and flags */
	unsigned			blen;
	off_t				file_size;

    int         		matchcount = 0, index = 0, i = 0, errflag = 0, strl = 0;
	int					numRead, numToRead = 8;
	int					strLenMax = 0;
	int					strLenMaxMax = 0;
	int					strLenCurr = 0;
	int					showFlag = TRUE;
	int					enterFlag = TRUE;
	int 				filtered_flag = FALSE;
	int					status;
	int					rowCnt, parentRow = -1;


	strcpy(home, getenv("HOME"));
	
	strcpy (mypathname, pathptr);
	
	if (dirtype == second) {
		xv_set(word_item, PANEL_CLIENT_DATA, second, NULL);
	    xv_set(test_choice, PANEL_CLIENT_DATA, second, NULL);
	}
	else {
		xv_set(word_item, PANEL_CLIENT_DATA, prime, NULL);
		xv_set(test_choice, PANEL_CLIENT_DATA, prime, NULL);
	}
	       
	xv_set(subframe, XV_SHOW, FALSE, NULL);
	strcpy(child, ".");
	if (targetFlag != DIRECTORY) 
		strcpy(parent, "...");
	else
		strcpy(parent, "..");
	
    if ((outfp = fopen (sortfile, "w")) == NULL) {
        notice_prompt (panel, NULL,
          NOTICE_NO_BEEPING,         TRUE,
          NOTICE_MESSAGE_STRINGS,    "Unable to open sort file",
          NULL,  
          NULL);
    }
	
	if (nummatched > matchcount  && nummatched != 1)   
		xv_set(test_choice, PANEL_LIST_DELETE_ROWS, matchcount, nummatched - 1, NULL); 
	
	/*
	stat(mypathname, &statbuff);
	*/
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


							if (strcmp(home, mypathname) == 0) {
								if (statbuff.st_mode & S_IRUSR )  
									showFlag = TRUE;
								else 
									showFlag = FALSE;
							}
							else  {
								if (statbuff.st_mode & S_IRUSR || statbuff.st_mode & S_IRGRP || statbuff.st_mode & S_IROTH)  
									showFlag = TRUE;
								else 
									showFlag = FALSE;
							}
								
							if (showFlag) {
								strcat(buffname, "\n");
								blen = strlen(buffname);
								fwrite(buffname, blen, 1, outfp);
								matchcount++;
							}
							showFlag = FALSE;

						} /* end of 5th if  "searchstr cmp" */
					} /* end of 4th if "parent cmp "  */
				} /* end of 3rd if "child cmp "  */
			} /* end of 2nd if " strcpy to buffname from dp->d_name != NULL" */
		}    /* end of for "readdir" */
	    /* flush_subframe(); */
	    closedir(dirp);
	} /* end of 1st if "dirp != NULL" */
	else {
        if (errno == ENOENT) {
            sprintf (messstr, "Unable to open directory %s Going up one.\n", mypathname);
            xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
           
            newPath = (REMOVE, filename);
            strcpy(filename, newPath);
            return(0);
        }
        if (errno == EACCES) {
            sprintf (messstr, "Permission Denied on open %s", filename);
            xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
            newPath = (REMOVE, filename);
            strcpy(filename, newPath);
            return(0);
        }
        sprintf (messstr, "Errno is: %d", errno);
        xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
		
    } /* end of else */

	fclose(outfp);

	sort_file(sortfile, matchcount);

	/* end of build a file list */


	/* begining of find longest length of the file size str */

	if (viewFlag == 7 || viewFlag == 6 ) {
		/* open and read to find the longest file size */
	    if ((fp = fopen (sortfile, "r")) == NULL) {
	        notice_prompt (panel, NULL,
	          NOTICE_NO_BEEPING,         TRUE,
	          NOTICE_MESSAGE_STRINGS,    "Unable to reopen sort file",
	          NULL,  
	          NULL);
	    }
		else {
	
			while(fscanf(fp, "%s", buffname) > 0) {
	    		strcpy(statpath, mypathname);
				strl = strlen(statpath);
	   		 	if (statpath[strl - 1] != '/') 
	    		strcat(statpath, "/");
	    		strcat(statpath, buffname);
	    		strcat(statpath, "/");
	        	lstat(statpath, &statbuff);
				file_size = statbuff.st_size;
				sprintf(intStr, "%d", file_size);
	        	strLenCurr = strlen(intStr);
	
				if (strLenCurr >= strLenMax) 
					strLenMax = strLenCurr;
			}
			fclose(fp);
		}
		strLenMax += 10;
		strLenMaxMax += strLenMax;
		strLenMaxMax *= 8;
	}

	/* end of find longest length of the file size str */

	/* begining of file grading */

    if ((fp = fopen (sortfile, "r")) == NULL) {
        notice_prompt (panel, NULL,
          NOTICE_NO_BEEPING,         TRUE,
          NOTICE_MESSAGE_STRINGS,    "Unable to reopen sort file",
          NULL,  
          NULL);
    }

	while(fscanf(fp, "%s", buffname) >= 1) {
	    if(strcmp(buffname, "..") == 0) 
			parentRow = i;
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



		if (viewFlag == 5 || viewFlag == 7 ) {
	    	if (grade_file(&filepro, statpath, buffname) != NULL){
				gen_icon = filepro.file_icon;
				enterFlag = TRUE;
			}
			else {
				filtered_flag = TRUE;
				enterFlag = FALSE;
			  	matchcount--; 
			}

		} /* end of if viewflag */

			file_size = filepro.file_size;
			sprintf(intStr, "%d", file_size);
	        strLenCurr = strlen(intStr);
	
			strcpy(filestr, "");
			strcpy(filler, "");
			for (index = 0; index < strLenMax - strLenCurr; index++) {
				strcat(filler, ".");
			}
			if (viewFlag == 7 || viewFlag == 6) /* all */ 
				sprintf(filestr, "%d %s %s ", file_size, filler, buffname);
			if (viewFlag == 2 || viewFlag == 3 ) /* only file_size */
				sprintf(filestr, "%d ", file_size);
			if (viewFlag == 4 || viewFlag == 5 ) /* only buffname */
				sprintf(filestr, "%s ", buffname);
	
			/*
			fprintf(stdout, "%s\n", filestr);
			fflush(stdout);
			*/
	
			if (viewFlag == 4 || viewFlag == 6) { /* only file name or file size */
		    	xv_set(test_choice, 
		    		PANEL_LIST_DELETE, i,
		    		PANEL_LIST_INSERT, i, 
		    		PANEL_LIST_STRING, i, filestr,
		    		NULL);
			}
	
		if (enterFlag) {
			if (viewFlag == 5 || viewFlag == 7) { /* filetype and either or file name, file size */
		    	xv_set(test_choice, 
		    		PANEL_LIST_DELETE, i,
		    		PANEL_LIST_INSERT, i, 
					PANEL_LIST_GLYPH, i, gen_icon,
		    		PANEL_LIST_STRING, i, filestr,
		    		NULL);
			}
	    	i++;
		}


	} /* end of while fgets */
	if ((parentRow > -1) && ((Panel_item)xv_get( panel, PANEL_CARET_ITEM ) != goto_item)) {
		parentItem = PARENT_FOUND;
		xv_set(test_choice, PANEL_LIST_SELECT, parentRow, TRUE, NULL);
		xv_set(word_item, PANEL_VALUE, "..", NULL);
	}
	else {
		parentItem = PARENT_NOT_FOUND;
		xv_set(word_item, PANEL_VALUE, "", NULL);
		xv_set(test_choice, PANEL_LIST_SELECT, 0, TRUE, NULL);
        choiceptr = (char *)xv_get(test_choice, PANEL_LIST_STRING, 0);
        if (viewFlag == 6 || viewFlag == 7) {
        	token = strtok(choiceptr, " ");
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");
        }
        if (viewFlag == 4 )
             token = strtok(choiceptr, " ");

        if (viewFlag == 5)  
             token = strtok(choiceptr, " ");

        if (token != NULL) {
         	strl = strlen(token);
            bcopy (token, choice, strl);
        }
		/*
        xv_set(word_item, PANEL_VALUE, choice, NULL);
		*/
        flush_panel();
	}
	

	fclose(fp);
	unlink(sortfile);
	sprintf (messstr, "Directory listing for %s ", mypathname);
	/*
	xv_set(test_choice, PANEL_LIST_TITLE, messstr, NULL);
	*/
	nummatched = matchcount;
	if (nummatched != 0 ) {
		/* 
		xv_set(test_choice, PANEL_LIST_WIDTH, strLenMaxMax, NULL);
		*/
		xv_set(test_choice, PANEL_LIST_WIDTH, 0, NULL);
	    if (targetFlag == DIRECTORY) {
	    	sprintf (messstr, "Unable to find match for %s, please select one from the following...", searchstr);
		xv_set(test_choice, PANEL_LIST_TITLE, "Candidate List", NULL);
		}
	    else {
			if (matchcount == 1) 
	    	sprintf (messstr, "Found %d match for pathname: %s",matchcount, pathptr);
			else
	    	sprintf (messstr, "Found %d matches for pathname: %s",matchcount, pathptr);
			xv_set(goto_item, PANEL_VALUE, pathptr, NULL);
			strcpy(gotoPathName, pathptr);
		}
		strcpy(currentPathName, mypathname);
	    xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
	    xv_set(subframe, XV_SHOW, TRUE, NULL);
	    xv_set(panel2, XV_SHOW, TRUE, NULL);
	}
	else {
	       xv_set(subframe, XV_SHOW, FALSE, NULL);
	       xv_set(panel2, XV_SHOW, FALSE, NULL);
	       nummatched = 0;
		   if (filtered_flag) 
				sprintf (messstr, "All the file types that were found were filtered");
		   else
	       		sprintf (messstr, "Unable to find match for \"%s\" in %s ", searchstr, mypathname);
	       xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
	       xv_set(subframe, FRAME_CMD_PUSHPIN_IN, FALSE, NULL);
	       xv_set(subframe, XV_SHOW, FALSE, NULL); 
	       xv_set(panel2, XV_SHOW, FALSE, NULL);  
	       xv_set(frame, FRAME_BUSY, FALSE, NULL);
    	   win_set_kbd_focus(panel, xv_get(panel, XV_XID));
           xv_set(word_item, PANEL_VALUE, "", NULL);
	       flush_panel();
	}
	/*
	xv_set(panel2, XV_WIDTH, (int)xv_get(test_choice, PANEL_LIST_WIDTH) + 50, NULL);
	xv_set(subframe, XV_WIDTH, (int)xv_get(test_choice, PANEL_LIST_WIDTH) + 50, NULL);
	*/
	window_fit(panel2);
	window_fit(subframe);
    win_set_kbd_focus(panel, xv_get(panel, XV_XID));
	
} /* end of function */


void
textsw_event_hand
( Xv_window window, Event *event, Notify_arg arg ,Notify_event_type type)
{
	Textsw_index t = 0, lineNum = 0;
    char    messstr[BUFSIZ];
	char   str[BUFSIZ];
	char   footStr[BUFSIZ];
	FILE	*fp;
	int		temp;

		
		#ifdef DEBUG
			sprintf(footStr, "Textsw event ID is: %d", event_action(event));	
			xv_set(frame, FRAME_RIGHT_FOOTER, footStr, NULL );
		#endif

		if (event_action(event) == LOC_WINENTER && currTog == INFILE) {
			if (currTog == INFILE) {
                lineNum = what_line_number(filename);
                sprintf(leftFootStr, "Current line number:%ld",lineNum);               
                if (currTi >= 0)
                    sprintf(rightFootStr, "Current character position:%ld",currTi);    
                xv_set(frame, FRAME_LEFT_FOOTER, leftFootStr, NULL );
                xv_set(frame, FRAME_RIGHT_FOOTER, rightFootStr, NULL );                
				currPos = lineNum;
			}
				win_set_kbd_focus(window, xv_get(window, XV_XID));
		}
 		if (event_action(event) == LOC_WINENTER && currTog == OUTFILE) {   
                win_set_kbd_focus(panel, xv_get(panel, XV_XID));
        }
		
 		if (event_action(event) == LOC_WINEXIT && currTog == OUTFILE) {   
                win_set_kbd_focus(panel, xv_get(panel, XV_XID));
        }
		
 		if (event_action(event) == KBD_USE && currTog == OUTFILE) {   
                win_set_kbd_focus(panel, xv_get(panel, XV_XID));
        }
		

 		if (event_action(event) == LOC_WINEXIT && currTog == INFILE) {   
                win_set_kbd_focus(panel, xv_get(panel, XV_XID));
        }

		if (event_is_key_top(event) && event_id(event) == KEY_TOP(1) && event_is_down(event)){
				win_set_kbd_focus(panel, xv_get(panel, XV_XID));

		}
		if (event_action(event) ==  ACTION_SELECT && currTog == INFILE) {
				lineNum = what_line_number(filename);
				sprintf(leftFootStr, "Current line number:%ld",lineNum);
				if (currTi >= 0) 
					sprintf(rightFootStr, "Current character position:%ld",currTi);
				xv_set(frame, FRAME_LEFT_FOOTER, leftFootStr, NULL );
				xv_set(frame, FRAME_RIGHT_FOOTER, rightFootStr, NULL );
				currPos = lineNum;
		}

        if (event_action(event) ==  ACTION_ADJUST && currTog == INFILE) {
                lineNum = what_line_number(filename);
                sprintf(leftFootStr, "Current line number:%ld",lineNum);               
                if (currTi >= 0)
                    sprintf(rightFootStr, "Current character position:%ld",currTi);
                xv_set(frame, FRAME_LEFT_FOOTER, leftFootStr, NULL );
                xv_set(frame, FRAME_RIGHT_FOOTER, rightFootStr, NULL );                
				currPos = lineNum;
        }
            if (event_action(event) == ACTION_GO_DOCUMENT_START){
                if (event_is_down(event)) {
                    if (currTog == INFILE) {
                        xv_set(textsw, TEXTSW_FIRST, 0, NULL);

						lineNum = what_line_number(filename);

                        sprintf(leftFootStr, "Current line position:%d", lineNum);
						if (currTi >= 0) 
							sprintf(rightFootStr, "Current character position:%ld",currTi);
                        xv_set(frame, FRAME_LEFT_FOOTER, leftFootStr, NULL );
						xv_set(frame, FRAME_RIGHT_FOOTER, rightFootStr, NULL );
						currPos = lineNum;
                    }   
                }
			}

            if (event_action(event) == ACTION_GO_DOCUMENT_END){
                if (event_is_down(event)) {
                    if (currTog == INFILE) {
                        xv_set(textsw, TEXTSW_FIRST, total_file_bytes - 1,
NULL);
						lineNum = what_line_number(filename);

                        sprintf(leftFootStr, "Current line position:%d", lineNum);
						if (currTi >= 0) 
							sprintf(rightFootStr, "Current character position:%ld",currTi);
                        xv_set(frame, FRAME_LEFT_FOOTER, leftFootStr, NULL );
						xv_set(frame, FRAME_RIGHT_FOOTER, rightFootStr, NULL );
						currPos = lineNum;
                    }   
                }
			}
			if (event_action(event) ==  ACTION_GO_CHAR_FORWARD) {
				if (event_is_down(event)) {
					lineNum = what_line_number(filename);
					sprintf(leftFootStr, "Current line position:%ld",lineNum);
					if (currTi >= 0) 
						sprintf(rightFootStr, "Current character position:%ld",currTi);
					xv_set(frame, FRAME_LEFT_FOOTER, leftFootStr, NULL );
					xv_set(frame, FRAME_RIGHT_FOOTER, rightFootStr, NULL );
					currPos = lineNum;
					return;
				}
			}
            if (event_action(event) ==  ACTION_GO_CHAR_BACKWARD) {
                if (event_is_down(event)) { 
                    lineNum = what_line_number(filename);
                    sprintf(leftFootStr, "Current line position:%ld",lineNum);                
					if (currTi >= 0) 
						sprintf(rightFootStr, "Current character position:%ld",currTi);
                    xv_set(frame, FRAME_LEFT_FOOTER, leftFootStr, NULL );      
					xv_set(frame, FRAME_RIGHT_FOOTER, rightFootStr, NULL );
                    currPos = lineNum;
                    return;
                }  
            }   
			if (event_action(event) ==  ACTION_GO_COLUMN_BACKWARD) {
				lineNum = what_line_number(filename);
				sprintf(leftFootStr, "Current line position:%ld",lineNum);
				if (currTi >= 0) 
					sprintf(rightFootStr, "Current character position:%ld",currTi);
				xv_set(frame, FRAME_LEFT_FOOTER, leftFootStr, NULL );
				xv_set(frame, FRAME_RIGHT_FOOTER, rightFootStr, NULL );
				currPos = lineNum;
            }     

            if (event_action(event) ==  ACTION_GO_COLUMN_FORWARD) {
				lineNum = what_line_number(filename);
				sprintf(leftFootStr, "Current line position:%ld",lineNum);
				if (currTi >= 0) 
					sprintf(rightFootStr, "Current character position:%ld",currTi);
				xv_set(frame, FRAME_LEFT_FOOTER, leftFootStr, NULL );
				xv_set(frame, FRAME_RIGHT_FOOTER, rightFootStr, NULL );
				currPos = lineNum;
				return;
			}

		if (event_action(event) ==  WIN_REPAINT)
			return;
}


Notify_value 
seek_event_hand  
( Panel panel, Event *event, Notify_arg arg, Notify_event_type type )

{
	  Textsw_index lineNum = 0;
	  static	Textsw_index	myIndex;
      static  	Panel_item      item;
	  static	int				flag;
	  int		bytes_per_line;
	  FILE		*pfp;
      Xv_Window window;
	  Textsw_index newpos;
	  int	  	widthOfFrame;
	  int		myconst = 20;	
	  int		divisor = 5;
	  Rect		*rect, *tmprect;
      char    	messstr[BUFSIZ];
      char    	command[BUFSIZ];
	  char		footStr[BUFSIZ];
	  char		tempStr[BUFSIZ];
	  int		win_no = 0;
	  int		first_vis = 0, last_vis = 0;
	  int		visdiff;
	  int		rowSel;
      int      	strl;
	  char		*my_argv1[] = {"shelltool","-bg", "wheat","-c", "vi", filename, NULL} ;
	  char      editPath[BUFSIZ];
      char  		choice[BUFSIZ] = {""};
	  char 		*choiceptr;
	char 	*token;
	char	*tmpstr;
	char	*tmpPath;
		
       
		strcpy(editPath, filename);
		if ( (event_y(event) <= (short)xv_get(primebutton, XV_Y)) && (event_x(event) <= (short)xv_get(filter_button, XV_X)) ){ 
			if (event_action(event) == ACTION_SELECT && currTog == OUTFILE)  {
		       		xv_set(word_item, PANEL_CLIENT_DATA, prime, NULL);
		       		xv_set(test_choice, PANEL_CLIENT_DATA, prime, NULL);
		       		xv_set(primebutton, PANEL_ITEM_COLOR, CMS_CONTROL_COLORS + RED, NULL);    
		       		xv_set(secondbutton, PANEL_ITEM_COLOR, CMS_CONTROL_COLORS + BLACK, NULL);  
	       			strcpy(filename, primaryPath); 
					tempitem = primebutton;
			}
	
			if (event_action(event) == ACTION_ADJUST && currTog == OUTFILE)  {
		            xv_set(word_item, PANEL_CLIENT_DATA, second, NULL);
		            xv_set(test_choice, PANEL_CLIENT_DATA, second, NULL);
		            xv_set(secondbutton, PANEL_ITEM_COLOR, CMS_CONTROL_COLORS + RED, NULL);
		
		       		xv_set(primebutton, PANEL_ITEM_COLOR, CMS_CONTROL_COLORS + BLACK, NULL);    
	       			strcpy(filename, secondaryPath); 
					tempitem = secondbutton;
			}
			if (event_action(event) == ACTION_MENU && currTog == OUTFILE)  
				if (tempitem != 0)
					look_up_all(tempitem, event);
			
		}

        if ( (event_action(event) ==  ACTION_GO_COLUMN_BACKWARD) && (event_is_down(event)) ) {
			if (currTog == INFILE) {
	            window = (Xv_Window)xv_get(textsw, OPENWIN_NTH_VIEW, win_no);
	            win_set_kbd_focus(window, xv_get(window, XV_XID));
	                lineNum = what_line_number(filename);
	                sprintf(leftFootStr, "Current line number:%ld",lineNum);
	                if (currTi >= 0)
	                    sprintf(rightFootStr, "Current character position:%ld",currTi);
	                xv_set(frame, FRAME_LEFT_FOOTER, leftFootStr, NULL );
	                xv_set(frame, FRAME_RIGHT_FOOTER, rightFootStr, NULL );                
					currPos = lineNum;
	            return;
			}
			if (currTog == OUTFILE) {
				if ((Panel_item)xv_get(panel, PANEL_CARET_ITEM) == word_item){
					usleep(100000);
					rowSel = (int)xv_get(test_choice, PANEL_LIST_FIRST_SELECTED);
					xv_set(test_choice, PANEL_LIST_SELECT, rowSel - 1, TRUE);
					rowSel = (int)xv_get(test_choice, PANEL_LIST_FIRST_SELECTED);
	       			choiceptr = (char *)xv_get(test_choice, PANEL_LIST_STRING, rowSel);
                	if (viewFlag == 6 || viewFlag == 7) {
                    	token = strtok(choiceptr, " ");
                    	token = strtok(NULL, " ");
                    	token = strtok(NULL, " ");
                	}
                	if (viewFlag == 4 )
                    	token = strtok(choiceptr, " ");
 
                	if (viewFlag == 5)  {
                    	token = strtok(choiceptr, " ");
                	}
 
                	if (token != NULL) {
                        strl = strlen(token);
                        bcopy (token, choice, strl);
                	}
	       			xv_set(word_item, PANEL_VALUE, choice, NULL);  
	           		flush_panel();      
					return;
				}
                else {
                    usleep(100000);
                    rowSel = (int)xv_get(test_choice, PANEL_LIST_FIRST_SELECTED);
                    xv_set(test_choice, PANEL_LIST_SELECT, rowSel - 1, TRUE);
                    rowSel = (int)xv_get(test_choice, PANEL_LIST_FIRST_SELECTED);
                    choiceptr = (char *)xv_get(test_choice, PANEL_LIST_STRING, rowSel);
                    if (viewFlag == 6 || viewFlag == 7) {
                        token = strtok(choiceptr, " ");
                        token = strtok(NULL, " ");
                        token = strtok(NULL, " ");
                    }
                    if (viewFlag == 4 )
                        token = strtok(choiceptr, " ");
 
                    if (viewFlag == 5)  {
                        token = strtok(choiceptr, " ");
                    }
 
                    if (token != NULL) {
                        strl = strlen(token);
                        bcopy (token, choice, strl);
                    }
 
                    tmpstr = (char *)xv_get(goto_item,  PANEL_VALUE);
 
                    if (strcmp(tmpstr, gotoPathName ) != 0) {
                        tmpPath = buildPath(REMOVE, tmpstr);
                        strcpy(tempStr, tmpPath);
                        strcat(tempStr, "/");
                        strcat(tempStr, choice);
                    }
                    else {
                        strcpy(tempStr, tmpstr);
                        strcat(tempStr, "/");
                        strcat(tempStr, choice);
                    }
                    xv_set(goto_item, PANEL_VALUE, tempStr, NULL);
                    flush_panel();
                }
			}
        }

        if ( (event_action(event) ==  ACTION_GO_COLUMN_FORWARD) && (event_is_down(event)) ) {
			if (currTog == INFILE) {
	        	window = (Xv_Window)xv_get(textsw, OPENWIN_NTH_VIEW, win_no);
	            win_set_kbd_focus(window, xv_get(window, XV_XID));
	                lineNum = what_line_number(filename);
	                sprintf(leftFootStr, "Current line number:%ld",lineNum);
	                if (currTi >= 0)
	                    sprintf(rightFootStr, "Current character position:%ld",currTi);
	                xv_set(frame, FRAME_LEFT_FOOTER, leftFootStr, NULL );
	                xv_set(frame, FRAME_RIGHT_FOOTER, rightFootStr, NULL );                
					currPos = lineNum;
	            return;
			}
            if (currTog == OUTFILE) {
				if ((Panel_item)xv_get(panel, PANEL_CARET_ITEM) == word_item){
					usleep(100000);
                	rowSel = (int)xv_get(test_choice, PANEL_LIST_FIRST_SELECTED);
                	xv_set(test_choice, PANEL_LIST_SELECT, rowSel + 1, TRUE);          
                	rowSel = (int)xv_get(test_choice, PANEL_LIST_FIRST_SELECTED);
	       			choiceptr = (char *)xv_get(test_choice, PANEL_LIST_STRING, rowSel);
                	if (viewFlag == 6 || viewFlag == 7) {
                    	token = strtok(choiceptr, " ");
                    	token = strtok(NULL, " ");
                    	token = strtok(NULL, " ");
                	}
                	if (viewFlag == 4 )
                    	token = strtok(choiceptr, " ");
 
                	if (viewFlag == 5)  {
                    	token = strtok(choiceptr, " ");
                	}
 
                	if (token != NULL) {
                        strl = strlen(token);
                        bcopy (token, choice, strl);
                	}
                	xv_set(word_item, PANEL_VALUE, choice, NULL);
                	flush_panel();
					return;
				}
				else {
                    usleep(100000);
                    rowSel = (int)xv_get(test_choice, PANEL_LIST_FIRST_SELECTED);
                    xv_set(test_choice, PANEL_LIST_SELECT, rowSel + 1, TRUE);
                    rowSel = (int)xv_get(test_choice, PANEL_LIST_FIRST_SELECTED);
                    choiceptr = (char *)xv_get(test_choice, PANEL_LIST_STRING, rowSel);
                    if (viewFlag == 6 || viewFlag == 7) {
                        token = strtok(choiceptr, " ");
                        token = strtok(NULL, " ");
                        token = strtok(NULL, " ");
                    }
                    if (viewFlag == 4 )
                        token = strtok(choiceptr, " ");
 
                    if (viewFlag == 5)  {
                        token = strtok(choiceptr, " ");
                    }
 
                    if (token != NULL) {
                        strl = strlen(token);
                        bcopy (token, choice, strl);
                    }

					tmpstr = (char *)xv_get(goto_item,  PANEL_VALUE);

					if (strcmp(tmpstr, gotoPathName ) != 0) {
						tmpPath = buildPath(REMOVE, tmpstr);
						strcpy(tempStr, tmpPath);
						if (strlen (tempStr) > 1)
							strcat(tempStr, "/");
						strcat(tempStr, choice);
					}
					else {
						strcpy(tempStr, tmpstr);
						if (strlen (tempStr) > 1)
							strcat(tempStr, "/");
						strcat(tempStr, choice);
					}
                    xv_set(goto_item, PANEL_VALUE, tempStr, NULL);
                    flush_panel();
				}
            }   
        }

		if (event_action(event) ==  WIN_REPAINT) {
	       	notify_next_event_func(panel, (Notify_event) event, arg, type);
			return;
		}

		if (event_is_key_top(event) && event_id(event) == KEY_TOP(1) && event_is_down(event)){
    			window = (Xv_Window)xv_get(textsw, OPENWIN_NTH_VIEW, win_no);
				win_set_kbd_focus(window, xv_get(window, XV_XID));
				return;
		}

		if ((window = event_window(event)) == panel && currTog == INFILE) {
 			if (event_action(event) == LOC_WINENTER) {   
				win_set_kbd_focus(window, xv_get(window, XV_XID));
			}
 			if (event_action(event) == LOC_WINEXIT) {   
				;
			}
		}
		if (flag != 1) {
    		window = (Xv_Window)xv_get(textsw, OPENWIN_NTH_VIEW, win_no);
   	 		xv_set(window,
            	WIN_EVENT_PROC,         textsw_event_hand,
				WIN_CONSUME_EVENTS,
				WIN_NO_EVENTS, LOC_WINENTER, LOC_WINEXIT, WIN_ASCII_EVENTS, WIN_MOUSE_BUTTONS, LOC_MOVE, LOC_DRAG, KBD_USE, KBD_DONE,  WIN_REPAINT, NULL,
            	NULL);
			flag++;
		}


	  
        if (event_xevent(event)->xkey.state & 64) {
			if (event_is_ascii(event) && event_is_down(event)) {
	       		switch(event_action(event)) {
					case 0:
						return;
			
				   	case 120: /* x */
					  if (event_is_down(event)) {
						if (editFlag == FALSE) {
							editFlag = TRUE;
				       		sprintf (messstr, "Editing is ON");
				       		xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
							xv_set(textsw, WIN_MENU, default_textsw, NULL);
							if (currTog == INFILE) {
			    				xv_set(icon, 
									ICON_IMAGE, 		seek_icon3,
									ICON_MASK_IMAGE, 	mask_icon,
									ICON_TRANSPARENT,	TRUE,
					 				NULL);
							}
							
						}
						else {
							editFlag = FALSE;
				       		sprintf (messstr, "Editing is OFF");
				       		xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
							xv_set(textsw, WIN_MENU, nullmenu, NULL);
							if (currTog == INFILE) {
			    				xv_set(icon, 
									ICON_IMAGE, 		seek_icon2,
									ICON_MASK_IMAGE, 	mask_icon,
									ICON_TRANSPARENT,	TRUE,
					 				NULL);
							}
							
						}
					}
			       		break;
			       case 103: /* g */
			       		get_prime_sel(item);
			       		break;
			       
			       case 100: /*  d done*/
			       		if ((int)xv_get(primebutton, PANEL_INACTIVE) == TRUE) 
			       		query_toggle(OUTFILE);
			       		break;
			
			       case 101: /* e  emacs */
					if (event_is_down(event)) {
						if (editFlag == TRUE) {
			       			switch(currTog) {
							
			       				case INFILE:    
							    strcpy(emaxed, (char *)xv_get(emaxName, PANEL_VALUE));	
			
			                    sprintf (messstr, "Creating emacs epoch session...");
			                    xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
			 
								sprintf(command, "%s %s & ", emaxed, editPath );
                                    if ((pfp = popen (command, "r")) == NULL) {
                                        notice_prompt (panel, NULL,
                                        NOTICE_NO_BEEPING,         TRUE,
                                        NOTICE_MESSAGE_STRINGS,    "Unable to execute your emacs edit command ",
                                        NOTICE_MESSAGE_STRINGS,    "Check the syntax",
                                        NULL,
                                        NULL);
                                    }
									else
                                        pclose(pfp);

			                    sprintf (messstr, "");
			                    xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
			                    break;
			
								default:
									break;
							}
						}
					}
					break;
			
				   case 118: /* v */
					if (event_is_down(event)) {
						if (editFlag == TRUE) {
			       			switch(currTog) {
							
			       				case INFILE:    
			
				       			sprintf (messstr, "Creating vi session...");
				       			xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
			
			    				vttyFrame = (Frame)xv_create(frame, FRAME_CMD,
									XV_FONT,				font,
			            			FRAME_LABEL,            editPath,
			            			NULL);
			
			
								vitty = (Tty)xv_create(vttyFrame, TTY,
									WIN_FONT,				font,
									WIN_ROWS,		24,
									WIN_COLUMNS,	80,
									TTY_ARGV,		my_argv1,	
									NULL);
								window_fit(vttyFrame);
								sleep(1);	
				       			sprintf (messstr, "");
				       			xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
			       				break;
			
								default:
									break;
							}
						}
					}
					break;
					default:
  
	       				notify_next_event_func(panel, (Notify_event) event, arg, type);
	       				return;
	       				break;
	       		}
			}
		}
		else {

       	switch(event_action(event)) {

			case 0:
				return;
				break;

			case WIN_RESIZE:
				panel_paint(panel, PANEL_NO_CLEAR);
       			break;

			case 9: /* tab ctrl i */
				if (event_is_down(event))
					panel_advance_caret(panel);
				break;

			case 13:
				if ((Panel_item)xv_get(panel, PANEL_CARET_ITEM) == word_item){
					if (! event_shift_is_down(event)){
						if (currTog == INFILE) {
							if(event_is_down(event)){
								matchOp = 0;
	           	    		 	first = last_plus_one; 
								find_match();
							}
						}
						else
	       					notify_next_event_func(panel, (Notify_event) event, arg, type);
					}
					else {
						if (currTog == INFILE) {
							if(event_is_down(event)){
								matchOp = 1;
	           	    		 	last_plus_one = first; 
								find_match();
							}
						}
						else
	       					notify_next_event_func(panel, (Notify_event) event, arg, type);
					}
				}
				else
	       			notify_next_event_func(panel, (Notify_event) event, arg, type);

       			break;
				

       	default:
				/*
				fprintf(stdout, "Here I am");
				fflush(stdout);
				*/
				#ifdef DEBUG
				sprintf(footStr, "Panel event ID is: %d", event_action(event));	
				xv_set(frame, FRAME_LEFT_FOOTER, footStr, NULL );
				#endif 
       			notify_next_event_func(panel, (Notify_event) event, arg, type);
       			return;
       			break;
       	}
	}
	
}
void
query_toggle(int togType)
{
       char    messstr[BUFSIZ];
       char    *newPath;
		int		x = 100, y = 100, result = 0;
		Display	*display;
		

		currTog = togType;
       switch(togType) {
       case INFILE:    
		currPos = 1;
		if (editFlag) {
    		xv_set(icon, 
				ICON_IMAGE, 		seek_icon3,
				ICON_MASK_IMAGE, 	mask_icon,
				ICON_TRANSPARENT,	TRUE,
		 		NULL);
		}
		else {
    		xv_set(icon, 
				ICON_IMAGE, 		seek_icon2,
				ICON_MASK_IMAGE, 	mask_icon,
				ICON_TRANSPARENT,	TRUE,
		 		NULL);
		}
       first = 0;
       xv_set(primebutton, PANEL_INACTIVE, TRUE, NULL);
       xv_set(secondbutton, PANEL_INACTIVE, TRUE, NULL);
	   xv_set(goto_item, XV_SHOW, TRUE, NULL);
       sprintf (messstr, "Enter a string to search for, Press \"Done\" or \"Alt D\" to continue");
       xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
       xv_set(word_item, PANEL_LABEL_STRING, "String to search for: ", NULL);
       /* xv_set(word_item, PANEL_NOTIFY_PROC, find_match, NULL); */
       xv_set(done_button, XV_SHOW, TRUE, NULL);
       xv_set(filter_button, XV_SHOW, FALSE, NULL);
	   xv_set(frame, FRAME_LABEL, filename, NULL);
	   xv_set(goto_item, PANEL_LABEL_STRING, "Goto Line #:", NULL);
       xv_set(word_item, PANEL_VALUE, "", NULL);
       xv_set(goto_item, PANEL_VALUE, filename, NULL);
       break;

       case OUTFILE: 
    	xv_set(icon, 
			ICON_IMAGE, 		seek_icon,
			ICON_MASK_IMAGE, 	mask_icon,
			ICON_TRANSPARENT,	TRUE,
		 	NULL);
		if ((int)xv_get(textsw, TEXTSW_MODIFIED) == TRUE) {
			if (editFlag == TRUE) {
					result = notice_prompt (panel, NULL,
		                      NOTICE_NO_BEEPING,         TRUE,
		                      NOTICE_MESSAGE_STRINGS,
		                      "WARNING",
		                      "You have made edits to this file",
		                      "	",
		                      "Do you wish to save ?",
		                    "",
		                      NULL,
		                      NOTICE_BUTTON_YES,      "Yes",
		                      NOTICE_BUTTON_NO,       "No",
		                      NULL);
		          switch(result) {
		              case NOTICE_YES:
							textsw_save(textsw, x, y);
		       				sprintf (messstr, "Saved file: %s", filename );
		       				xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
		                  break;
		
		              case NOTICE_NO:
		       				sprintf (messstr, "Did not Save file: %s", filename );
		       				xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
		                  break;
		              case NOTICE_FAILED:
		                  xv_set (mess_item, PANEL_VALUE, "Unable to pop-up ",
		NULL);             
		                  break;
		              default:
		                  xv_set (mess_item, PANEL_VALUE, "Unknown choice ", NULL);               
		                  break;
		          }        
			}
		}
	   xv_set(frame, FRAME_LEFT_FOOTER, "", NULL );
	   xv_set(frame, FRAME_RIGHT_FOOTER, "", NULL );
       flush_panel();  
	   textsw_reset(textsw, x, y);
       xv_set(primebutton, PANEL_INACTIVE, FALSE, NULL);
       xv_set(secondbutton, PANEL_INACTIVE, FALSE, NULL);
       sprintf (messstr, "");
       xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
       xv_set(word_item, PANEL_LABEL_STRING, "Search for: ", NULL);
       xv_set(word_item, PANEL_NOTIFY_PROC, look_up_all, NULL);
       xv_set(word_item, PANEL_VALUE, "", NULL);
       xv_set(done_button, XV_SHOW, FALSE, NULL);
       xv_set(filter_button, XV_SHOW, TRUE, NULL);
	   xv_set(frame, FRAME_LABEL, "Seek - V8.7" , NULL);
       newPath = buildPath(REMOVE, filename);
       strcpy(filename, newPath);
	   xv_set(goto_item, PANEL_LABEL_STRING, "Goto:", NULL);
	   xv_set(goto_item, PANEL_VALUE, "", NULL);
		if (targetFlag == DIRECTORY)
	   		xv_set(goto_item, XV_SHOW, FALSE, NULL);
       break;
       }
}

void
show_filter(void)
{
	xv_set(subframe2, XV_SHOW, TRUE, NULL);
	xv_set(panel3, XV_SHOW, TRUE, NULL);
}
void
toggle_done(void)
{
       query_toggle(OUTFILE);  
}

void
toggle_filter(Panel_item item, int value, Event *event)
{
		switch ((int)xv_get(item, PANEL_CLIENT_DATA)) {
			case choice:
			  if (value == 2) {
				/* PANEL_EACH_ITEM(panel3, item) */
					if( item != ffdir_choice) { 
						ff_dir = FALSE;
						xv_set(ffdir_choice, PANEL_VALUE, ff_dir, NULL);
					}
					else
						ff_dir = TRUE;
					if( item != fffile_choice) {
						ff_file = FALSE;
						xv_set(fffile_choice, PANEL_VALUE, ff_file, NULL);
					}
					else
						ff_file = TRUE;
					if( item != fflnk_choice) {
						ff_lnk = FALSE;
						xv_set(fflnk_choice, PANEL_VALUE, ff_lnk, NULL);
					}
					else
						ff_lnk = TRUE;
					if( item != ffchr_choice) {
						ff_chr = FALSE;
						xv_set(ffchr_choice, PANEL_VALUE, ff_chr, NULL);
					}
					else
						ff_chr = TRUE;
					if( item != ffsock_choice) {
						ff_sock = FALSE;
						xv_set(ffsock_choice, PANEL_VALUE, ff_sock, NULL);
					}
					else
						ff_sock = TRUE;
					if( item != fffifo_choice) {
						ff_fifo = FALSE;
						xv_set(fffifo_choice, PANEL_VALUE, ff_fifo, NULL);
					}
					else
						ff_fifo = TRUE;
					if( item != ffempty_choice) {
						ff_empty = FALSE;
						xv_set(ffempty_choice, PANEL_VALUE, ff_empty, NULL);
					}
					else
						ff_empty = TRUE;
					if( item != ffcore_choice) {
						ff_core = FALSE;
						xv_set(ffcore_choice, PANEL_VALUE, ff_core, NULL);
					}
					else
						ff_core = TRUE;
					if( item != ffcompressed_choice) {
						ff_compressed = FALSE;
						xv_set(ffcompressed_choice, PANEL_VALUE, ff_compressed, NULL);
					}
					else
						ff_compressed = TRUE;
					if( item != ffcsource_choice) {
						ff_csource = FALSE;
						xv_set(ffcsource_choice, PANEL_VALUE, ff_csource, NULL);
					}
					else
						ff_csource = TRUE;
					if( item != ffobject_choice) {
						ff_object = FALSE;
						xv_set(ffobject_choice, PANEL_VALUE, ff_object, NULL);
					}
					else
						ff_object = TRUE;
					if( item != ffheader_choice) {
						ff_header = FALSE;
						xv_set(ffheader_choice, PANEL_VALUE, ff_header, NULL);
					}
					else
						ff_header = TRUE;
					if( item != ffexe_choice) {
						ff_exe = FALSE;
						xv_set(ffexe_choice, PANEL_VALUE, ff_exe, NULL);
					}
					else
						ff_exe = TRUE;
					if( item != ffaml_choice) {
						ff_aml = FALSE;
						xv_set(ffaml_choice, PANEL_VALUE, ff_aml, NULL);
					}
					else
						ff_aml = TRUE;
					if( item != ffsound_choice) {
						ff_sound = FALSE;
						xv_set(ffsound_choice, PANEL_VALUE, ff_sound, NULL);
					}
					else
						ff_sound = TRUE;
					if( item != ffps_choice) {
						ff_ps = FALSE;
						xv_set(ffps_choice, PANEL_VALUE, ff_ps, NULL);
					}
					else
						ff_ps = TRUE;
					if( item != ffrast_choice) {
						ff_rast = FALSE;
						xv_set(ffrast_choice, PANEL_VALUE, ff_rast, NULL);
					}
					else
						ff_rast = TRUE;
					if( item != ffmail_choice) {
						ff_mail = FALSE;
						xv_set(ffmail_choice, PANEL_VALUE, ff_mail, NULL);
					}
					else
						ff_mail = TRUE;
					if( item != ffshell_choice) {
						ff_shell = FALSE;
						xv_set(ffshell_choice, PANEL_VALUE, ff_shell, NULL);
					}
					else
						ff_shell = TRUE;
					if( item != ffwp_choice) {
						ff_wp = FALSE;
						xv_set(ffwp_choice, PANEL_VALUE, ff_wp, NULL);
					}
					else
						ff_wp = TRUE;
					if( item != ffbm_choice) {
						ff_bm = FALSE;
						xv_set(ffbm_choice, PANEL_VALUE, ff_bm, NULL);
					}
					else
						ff_bm = TRUE;
					if( item != ffgif_choice) {
						ff_gif = FALSE;
						xv_set(ffgif_choice, PANEL_VALUE, ff_gif, NULL);
					}
					else
						ff_gif = TRUE;
					if( item != ffmake_choice) {
						ff_make = FALSE;
						xv_set(ffmake_choice, PANEL_VALUE, ff_make, NULL);
					}
					else
						ff_make = TRUE;
					if( item != ffinfo_choice) {
						ff_info = FALSE;
						xv_set(ffinfo_choice, PANEL_VALUE, ff_info, NULL);
					}
					else
						ff_info = TRUE;
					if( item != fflib_choice) {
						ff_lib = FALSE;
						xv_set(fflib_choice, PANEL_VALUE, ff_lib, NULL);
					}
					else
						ff_lib = TRUE;
					if( item != ffgis_choice) {
						ff_gis = FALSE;
						xv_set(ffgis_choice, PANEL_VALUE, ff_gis, NULL);
					}
					else
						ff_gis = TRUE;
					if( item != ffim_choice) {
						ff_im = FALSE;
						xv_set(ffim_choice, PANEL_VALUE, ff_im, NULL);
					}
					else
						ff_im = TRUE;
					if( item != ffgra_choice) {
						ff_gra = FALSE;
						xv_set(ffgra_choice, PANEL_VALUE, ff_gra, NULL);
					}
					else
						ff_gra = TRUE;
					if( item != ffplt_choice) {
						ff_plt = FALSE;
						xv_set(ffplt_choice, PANEL_VALUE, ff_plt, NULL);
					}
					else
						ff_plt = TRUE;
					if( item != ffXRe_choice) {
						ff_XRe = FALSE;
						xv_set(ffXRe_choice, PANEL_VALUE, ff_XRe, NULL);
					}
					else
						ff_XRe = TRUE;
					if( item != ffXRs_choice) {
						ff_XRs = FALSE;
						xv_set(ffXRs_choice, PANEL_VALUE, ff_XRs, NULL);
					}
					else
						ff_XRs = TRUE;
					if( item != ffXRh_choice) {
						ff_XRh = FALSE;
						xv_set(ffXRh_choice, PANEL_VALUE, ff_XRh, NULL);
					}
					else
						ff_XRh = TRUE;
					if( item != ffXRd_choice) {
						ff_XRd = FALSE;
						xv_set(ffXRd_choice, PANEL_VALUE, ff_XRd, NULL);
					}
					else
						ff_XRd = TRUE;
					if( item != ffXRr_choice) {
						ff_XRr = FALSE;
						xv_set(ffXRr_choice, PANEL_VALUE, ff_XRr, NULL);
					}
					else
						ff_XRr = TRUE;

					if( item != ffdos_choice) {
						ff_dos = FALSE;
						xv_set(ffdos_choice, PANEL_VALUE, ff_dos, NULL);
					}
					else
						ff_dos = TRUE;

					if( item != ffpkzip_choice) {
						ff_pkzip = FALSE;
						xv_set(ffpkzip_choice, PANEL_VALUE, ff_pkzip, NULL);
					}
					else
						ff_pkzip = TRUE;

				/* PANEL_END_EACH */
			  }

			  else {
					if( item == ffdir_choice)
						ff_dir = (value == 0 ? FALSE : TRUE);
					if( item == fffile_choice)
						ff_file = (value == 0 ? FALSE : TRUE);
					if( item == fflnk_choice)
						ff_lnk = (value == 0 ? FALSE : TRUE);
					if( item == ffchr_choice)
						ff_chr = (value == 0 ? FALSE : TRUE);
					if( item == ffsock_choice)
						ff_sock = (value == 0 ? FALSE : TRUE);
					if( item == fffifo_choice)
						ff_fifo = (value == 0 ? FALSE : TRUE);
					if( item == ffempty_choice)
						ff_empty = (value == 0 ? FALSE : TRUE);
					if( item == ffcore_choice)
						ff_core = (value == 0 ? FALSE : TRUE);
					if( item == ffcompressed_choice)
						ff_compressed = (value == 0 ? FALSE : TRUE);
					if( item == ffcsource_choice)
						ff_csource = (value == 0 ? FALSE : TRUE);
					if( item == ffobject_choice)
						ff_object = (value == 0 ? FALSE : TRUE);
					if( item == ffheader_choice)
						ff_header = (value == 0 ? FALSE : TRUE);
					if( item == ffexe_choice)
						ff_exe = (value == 0 ? FALSE : TRUE);
					if( item == ffaml_choice)
						ff_aml = (value == 0 ? FALSE : TRUE);
					if( item == ffsound_choice)
						ff_sound = (value == 0 ? FALSE : TRUE);
					if( item == ffps_choice)
						ff_ps = (value == 0 ? FALSE : TRUE);
					if( item == ffrast_choice)
						ff_rast = (value == 0 ? FALSE : TRUE);
					if( item == ffmail_choice)
						ff_mail = (value == 0 ? FALSE : TRUE);
					if( item == ffshell_choice)
						ff_shell = (value == 0 ? FALSE : TRUE);
					if( item == ffwp_choice)
						ff_wp = (value == 0 ? FALSE : TRUE);
					if( item == ffbm_choice)
						ff_bm = (value == 0 ? FALSE : TRUE);
					if( item == ffgif_choice)
						ff_gif = (value == 0 ? FALSE : TRUE);
					if( item == ffmake_choice)
						ff_make = (value == 0 ? FALSE : TRUE);
					if( item == ffinfo_choice)
						ff_info = (value == 0 ? FALSE : TRUE);
					if( item == fflib_choice)
						ff_lib = (value == 0 ? FALSE : TRUE);
					if( item == ffgis_choice)
						ff_gis = (value == 0 ? FALSE : TRUE);
					if( item == ffim_choice)
						ff_im = (value == 0 ? FALSE : TRUE);
					if( item == ffgra_choice)
						ff_gra = (value == 0 ? FALSE : TRUE);
					if( item == ffplt_choice)
						ff_plt = (value == 0 ? FALSE : TRUE);
					if( item == ffXRe_choice)
						ff_XRe = (value == 0 ? FALSE : TRUE);
					if( item == ffXRs_choice)
						ff_XRs = (value == 0 ? FALSE : TRUE);
					if( item == ffXRh_choice)
						ff_XRh = (value == 0 ? FALSE : TRUE);
					if( item == ffXRd_choice)
						ff_XRd = (value == 0 ? FALSE : TRUE);
					if( item == ffXRr_choice)
						ff_XRr = (value == 0 ? FALSE : TRUE);
					if( item == ffdos_choice)
						ff_dos = (value == 0 ? FALSE : TRUE);
					if( item == ffpkzip_choice)
						ff_pkzip = (value == 0 ? FALSE : TRUE);
				  }
			break;
			case button:
					PANEL_EACH_ITEM(panel3, item)
						xv_set(item, PANEL_VALUE, 1, NULL);
					PANEL_END_EACH
						ff_dir = TRUE;
						ff_file = TRUE;
						ff_lnk = TRUE;
						ff_chr = TRUE;
						ff_sock = TRUE;
						ff_fifo = TRUE;
						ff_empty = TRUE;
						ff_core = TRUE;
						ff_compressed = TRUE;
						ff_csource = TRUE;
						ff_object = TRUE;
						ff_header = TRUE;
						ff_exe = TRUE;
						ff_aml = TRUE;
						ff_sound = TRUE;
						ff_ps = TRUE;
						ff_rast = TRUE;
						ff_mail = TRUE;
						ff_shell = TRUE;
						ff_wp = TRUE;
						ff_bm = TRUE;
						ff_gif = TRUE;
						ff_make = TRUE;
						ff_info = TRUE;
						ff_lib = TRUE;
						ff_gis = TRUE;
						ff_im = TRUE;
						ff_gra = TRUE;
						ff_plt = TRUE;
						ff_XRe = TRUE;
						ff_XRs = TRUE;
						ff_XRh = TRUE;
						ff_XRd = TRUE;
						ff_XRr = TRUE;
						ff_dos = TRUE;
						ff_pkzip = TRUE;
			break;
			
		}
}

void
find_match(void)
{
	   Textsw_index t = 0, lineNum = 0;
       Textsw_index     pos = 0;
       char    *buffp, buff[BUFSIZ];
	   char    *bp, *ep;
       char    messstr[BUFSIZ];
       unsigned	buf_len;
       unsigned                flags = 0;
       
       buffp = (char *)xv_get(word_item, PANEL_VALUE); 
	   if (buffp != NULL)
			strcpy(buff, buffp);
       buf_len = strlen(buff);
	   bp = &buff[0];
	   ep = &buff[buf_len - 2];

       pos = textsw_find_bytes(textsw, &first, &last_plus_one, buff, buf_len, matchOp);
       if (pos > 0) {
       		textsw_set_selection(textsw, first, last_plus_one, 17);
       		xv_set(textsw, TEXTSW_INSERTION_POINT, last_plus_one, NULL);
				/*
	   		if (matchOp == 0) {

       			first = last_plus_one; 
			}
	   		if (matchOp == 1) {

       			last_plus_one = first;
			}

				*/
			/*
	   		xv_set(textsw, TEXTSW_FIRST, first, NULL);
	   		currPos = (int)xv_get(textsw, TEXTSW_FIRST_LINE);
	   		xv_set(textsw, TEXTSW_FIRST_LINE, currPos + 4, NULL);
			*/
			
			textsw_possibly_normalize(textsw, first);

            lineNum = what_line_number(filename);
       		sprintf (messstr, "Found \"%s\" at line # %d", buff, lineNum);
            sprintf(leftFootStr, "Current line number:%ld",lineNum);
            if (currTi >= 0)
            	sprintf(rightFootStr, "Current character position:%ld",currTi);
            xv_set(frame, FRAME_LEFT_FOOTER, leftFootStr, NULL );
            xv_set(frame, FRAME_RIGHT_FOOTER, rightFootStr, NULL );                
			currPos = lineNum;

       		xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
       }
       else {
       		sprintf (messstr, "Unable to find match for the string \"%s\" ", buff);
       				xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
					/*
       				(void) window_bell(textsw);
					*/
       }
}

int  
prop_OnOff 
( Panel_item item, Event *event) 
{

       switch ( (int) xv_get (item, PANEL_CLIENT_DATA)) {
       case FALSE:
       xv_set(propframe, XV_SHOW, FALSE, NULL);
       break;
       case TRUE:
       xv_set(propframe, XV_SHOW, TRUE, NULL);
       break;
       }
}

void
apply_funct(void)
{
    char            path[BUFSIZ], preffile[BUFSIZ];
       char    *buff;
    FILE       *fp;
       

	   strcpy(emaxed, (char *)xv_get(emaxName, PANEL_VALUE));	
	   viewFlag = (int)xv_get(view_choice, PANEL_VALUE);
	   lastView = viewFlag;
	   xv_set(panel, WIN_EVENT_PROC, seek_event_hand, NULL);

       strcpy (filename, primaryPath);
       xv_set(word_item, PANEL_CLIENT_DATA, prime, NULL);
       xv_set(test_choice, PANEL_CLIENT_DATA, prime, NULL);
       
       
       buff = (char *)xv_get(primarySearchPath, PANEL_VALUE);
       if (buff != NULL){
       		strcpy(primaryPath, buff);
       		strcpy(filename, buff);
		}

       buff = (char *)xv_get(secondarySearchPath, PANEL_VALUE);
       if (buff != NULL)
       		strcpy(secondaryPath, buff);

       buff = (char *)xv_get(primaryName, PANEL_VALUE);
       if (buff != NULL) {
       strcpy(primaryNameVal, buff);
       xv_set(primebutton, PANEL_LABEL_STRING, primaryNameVal, NULL);
       }

       buff = (char *)xv_get(secondaryName, PANEL_VALUE);
       if (buff != NULL) {
       strcpy(secondaryNameVal, buff);
       xv_set(secondbutton, PANEL_LABEL_STRING, secondaryNameVal, NULL);
       }

       buff = (char *)xv_get(tagName, PANEL_VALUE);
       if (buff != NULL) {
       strcpy(tag, buff);
       }

    strcpy(path, getenv("HOME"));
    strcpy (preffile, path);
    strcat (preffile, "/.seekrc");

    if ((fp = fopen (preffile, "w")) == NULL) {
        notice_prompt (panel, NULL,
          NOTICE_NO_BEEPING,         TRUE,
          NOTICE_MESSAGE_STRINGS,    "Unable to open preferance file",
          "Perferance will not be saved...",
          NULL,  
          NULL);
        }
        else {   
        fprintf (fp, "%d~%s~%s~%s~%s~%s~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%s~",targetFlag, primaryPath, secondaryPath, primaryNameVal, secondaryNameVal, tag, viewFlag, ff_dir, ff_file, ff_lnk, ff_chr, ff_sock, ff_fifo, ff_empty, ff_core, ff_compressed, ff_csource, ff_object, ff_header, ff_exe, ff_aml, ff_sound, ff_ps, ff_rast, ff_mail, ff_shell, ff_wp, ff_bm, ff_gif, ff_make, ff_info, ff_lib, ff_gis, ff_im, ff_gra, ff_plt, ff_XRe, ff_XRs, ff_XRh, ff_XRd, ff_XRr, ff_dos, ff_pkzip, emaxed);
            fflush (fp);
            fclose(fp);
        }

}
int
target_toggle(Panel_item item, Event *event)
{
       xv_set(tagName, PANEL_INACTIVE, (int)xv_get(targetChoice, PANEL_VALUE), NULL);
       targetFlag = (int)xv_get(targetChoice, PANEL_VALUE);
	   if (targetFlag == DIRECTORY)
		  xv_set(goto_item, XV_SHOW, FALSE, NULL);
	   if (targetFlag == MFILE)
		  xv_set(goto_item, XV_SHOW, TRUE, NULL);
}

char *
buildPath(int  operation, char *pathptr)
{
       char    *word;
       int     pathLength, seekPos, currentPos;
       char    tmpPath[BUFSIZ] = "", *tmpPathptr;
	   char    *tmpPtr;

       word = (char *)xv_get(word_item, PANEL_VALUE);
       pathLength = strlen(pathptr);
       switch(operation) {
       
       case ADD:

       if (pathptr[pathLength - 1] != '/') 
       strcat(pathptr, "/");
       if (strcmp (word , "..") != 0) {
			tmpPtr = strstr(pathptr, word);
       		if (tmpPtr == NULL) 
       			strcat(pathptr, word);         
			else {
				if (strlen(tmpPtr) != strlen(word)) 
       				strcat(pathptr, word);         
			}
			
       }
			
       break;
       case REMOVE:
       if (pathLength == 1) {
       if (pathptr[pathLength - 1] != '/') 
       strcat(pathptr, "/");
       break;
       }

       tmpPathptr = pathptr;
       while (*tmpPathptr != '\0') 
       *tmpPathptr++;
       *tmpPathptr--;
       *tmpPathptr--;

       /* find the 2nd to last '/' in the pathname */

       for (seekPos = (pathLength - 2); seekPos > 0; seekPos--) {
       if (*tmpPathptr != '/') 
       *tmpPathptr--; 
       else 
       break;
       }

       bcopy(pathptr, tmpPath, seekPos);
       pathptr = tmpPath;
       if (strlen(pathptr) <= 1) 
       strcat(pathptr, "/");
       break;
       }

       return(pathptr);
}

void    
prime_menu_proc ( Menu menu , Menu_item menu_item) 
{
	char 	*tempPtr;

	if (menu == prime_menu) 
	{
		tempPtr = (char *)xv_get(menu_item, MENU_STRING);
		if (tempPtr != NULL ) {
			if (strcmp(tempPtr, primaryPath) != 0) {
				strcpy(filename, tempPtr); 
				look_up_all(primebutton, NULL);
			}
		}
		else
			return;
	}
	else
			return;
}
 
 
void    
second_menu_proc ( Menu menu , Menu_item menu_item)
{
	char 	*tempPtr;

	if (menu == second_menu) 
	{
		tempPtr = (char *)xv_get(menu_item, MENU_STRING);
		if (tempPtr != NULL) {
			if (strcmp(tempPtr, secondaryPath) != 0 ) {
				strcpy(filename, tempPtr); 
				look_up_all(secondbutton, NULL);
			}
		}
		else
			return;
	}
	else
		return;
	
}

int
append_menu(int menuType, char *pathname)
{

int     				index, i, found = FALSE;
char    				*tempPtr;

	/* if (targetFlag == DIRECTORY) {
		i = strlen(pathname);
		if (pathname[i] == '/') {
	    	pathname = buildPath(REMOVE, filename);
			strcat(pathname, "script");
		}
	}
	*/ 

switch(menuType) {


	case PRIMARY:
        if ((strcmp(pathname, primaryPath) == 0) && primePtr_index != 0) {
			return;
		}
        /* set the default */
		if (primePtr_index == 0) {
			for ( i = 0; i <= 9; i++)
				strcpy(primePtr_array[i],"");
			
			primePtr_index = 1;
        	strcpy(primePtr_array[0], primaryPath);
			xv_set(pmi[0], MENU_STRING, primePtr_array[0], NULL);
			xv_set(pmi[0], MENU_NOTIFY_PROC, prime_menu_proc, NULL);
    		xv_set(prime_menu, MENU_APPEND_ITEM, pmi[0], NULL);
			break;
		}

        strcpy(primePtr_array[0], primaryPath);
		xv_set(pmi[0], MENU_STRING, primePtr_array[0], NULL);

        if (primePtr_index <= 9 ) {
            for (i = 1; i <= primePtr_index; i++){
                if (strcmp(primePtr_array[i], pathname) == 0) 
                    found = TRUE;
            }

            if (found == FALSE){
				i = (int)xv_get(prime_menu, MENU_NITEMS);
				if (i <= 9  ) 
    				xv_set(prime_menu, MENU_APPEND_ITEM, pmi[i], NULL);
                strcpy(primePtr_array[primePtr_index], pathname);
                primePtr_index++;
            }

		}
        else {
            /* swap the old values */
            for (i = 0; i <= 9; i++){
                if (strcmp(primePtr_array[i], pathname) == 0) 
                    found = TRUE;
			}

			if (found == FALSE) {
            	for (index = 1; index < 9; index++) {
        			strcpy(primePtr_array[index], primePtr_array[index + 1]);
                }
        		strcpy(primePtr_array[9], pathname);
			}
        }


			for(i = 1; i <= 9; i++) {
				xv_set(pmi[i], MENU_STRING, primePtr_array[i], NULL);
				xv_set(pmi[i], MENU_NOTIFY_PROC, prime_menu_proc, NULL);
			}
		break;

    case SECONDARY:
 
        if ((strcmp(pathname, secondaryPath) == 0) && secondPtr_index != 0)
            return;
        /* set the default */

        if (secondPtr_index == 0) {
            for ( i = 0; i <= 9; i++)
            strcpy(secondPtr_array[i], "");
            secondPtr_index = 1;
        	strcpy(secondPtr_array[0], secondaryPath);
            xv_set(smi[0], MENU_STRING, secondPtr_array[0], NULL);
            xv_set(smi[0], MENU_NOTIFY_PROC, second_menu_proc, NULL);
    		xv_set(second_menu, MENU_APPEND_ITEM, smi[0], NULL);
            break;
        } /* end if */
        strcpy(secondPtr_array[0], secondaryPath);

        xv_set(smi[0], MENU_STRING, secondPtr_array[0], NULL);
 
        if (secondPtr_index <= 9 ) {
            for (i = 1; i <= secondPtr_index; i++){
                if (strcmp(secondPtr_array[i], pathname) == 0)
                    found = TRUE;
            }
 
            if (found == FALSE){
				i = (int)xv_get(second_menu, MENU_NITEMS);
				if (i <= 9  ) 
    				xv_set(second_menu, MENU_APPEND_ITEM, smi[i], NULL);

                strcpy(secondPtr_array[secondPtr_index], pathname);
                secondPtr_index++;
            }
        } /* end of 1st if */
 
        else {
            /* swap the old values */
            for (i = 0; i <= 9; i++){
                if (strcmp(secondPtr_array[i], pathname) == 0)
                    found = TRUE;
            }
 
            if (found == FALSE) {
                for (index = 1; index < 9; index++) {
                    strcpy(secondPtr_array[index], secondPtr_array[index + 1]);
                }
                strcpy(secondPtr_array[9], pathname);
            }
        }
 
 
        for(i = 1; i <= 9; i++) {
        	xv_set(smi[i], MENU_STRING, secondPtr_array[i], NULL);
            xv_set(smi[i], MENU_NOTIFY_PROC, second_menu_proc, NULL);
        }
        break;

		default:
        break;
	} /* end of switch */
	return;
	
}

 
void 
goto_funct ( Panel_item item, Event *event)
{
	Textsw_index t = 0, lineNum = 0;
    DIR         		*dirp, *sirp;
    struct dirent 		*dp;
	char *token;
    char *tmpPathName, *tmpPathName2, altPathName[BUFSIZ], newPathName[BUFSIZ], *usrName, tempSeg[BUFSIZ];
	char *varName;
	int	 color;
	int	 pos;
	Textsw_index newpos;
	char messstr[BUFSIZ];
	char 	home[BUFSIZ], dirName[BUFSIZ];
   	struct  stat            statbuff;
	int		found = FALSE;

	strcpy(home, getenv("HOME"));
	strcpy(newPathName,(char *)xv_get(goto_item, PANEL_VALUE));
	strcpy(gotoPathName,newPathName);


switch(currTog) {
	
	case OUTFILE:  
		strcpy(tempSeg, newPathName);
		if ((token = strstr(newPathName, "$")) != NULL) {
			varName = &tempSeg[1];
			if ((tmpPathName = getenv(varName)) != NULL){
				strcpy(newPathName, tmpPathName);
				if ((dirp = opendir(newPathName)) != NULL) {
					closedir(dirp);
					sprintf(messstr, "Expanding $%s to %s, Opening...", varName, newPathName);
					xv_set(mess_item, PANEL_VALUE, messstr, NULL);
					
				}
				else {
					sprintf(messstr, "$%s does not expand to a vaild directory ", varName);
					xv_set(mess_item, PANEL_VALUE, messstr, NULL);
					return;
				}
			}
			else {
				sprintf(messstr, "No such environment variable as $%s", varName);
				xv_set(mess_item, PANEL_VALUE, messstr, NULL);
				return;
			}

		}

		if ((token = strstr(newPathName, "~")) != NULL) 
			if (strlen(token) == 1) 
				strcpy(newPathName, home);

		else if (strlen(token) > 1) {
			strcpy(newPathName, "/home");
			usrName = &tempSeg[1];
			dirp = opendir(newPathName);
			if(errno == 0  || errno == ENOENT && dirp != NULL){ 
				for(dp = readdir(dirp); dp != NULL; dp = readdir(dirp)){ 
	    			if(strcpy(dirName, dp->d_name) != NULL )  {
						strcpy(altPathName, newPathName);
	        			if(strcmp(dirName, "..") != 0) {
	            			if(strcmp(dirName, ".") != 0) {
								if (altPathName[strlen(altPathName) - 1] != '/')
                    				strcat(altPathName, "/");
                    			strcat(altPathName, dirName);
                    			strcat(altPathName, "/usr/");
                    			strcat(altPathName, usrName);
								if ((sirp = opendir(altPathName)) != NULL) {
									found = TRUE;
									strcpy(newPathName, altPathName);
									closedir(sirp);
            						sprintf (messstr, "Opening %s...", altPathName);
            						xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
									break;
								}
								else {
        							if (errno == EACCES) {
            							sprintf (messstr, "Permission Denied on open %s", altPathName);
            							xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
            							return;
									}
        						}

							}
						}
					}
				} /* end of for */
				closedir(dirp);
			}
			if (! found ) {
				sprintf(messstr, "No such user as %s", strtok(usrName, "/") );
				xv_set(mess_item, PANEL_VALUE, messstr, NULL);
				return;
			}
		}

		if (newPathName != NULL) {
			if (strstr(newPathName, ".." ) != NULL) {
				tmpPathName = buildPath(REMOVE, newPathName);
				strcpy(newPathName, tmpPathName);
				tmpPathName = buildPath(REMOVE, newPathName);
				strcpy(newPathName, tmpPathName);
			}
			xv_set(goto_item, PANEL_VALUE, newPathName, NULL);
			
				
       		color = (int)xv_get(secondbutton, PANEL_ITEM_COLOR);
       		if (color == CMS_CONTROL_COLORS + RED)
       			xv_set(goto_item, PANEL_CLIENT_DATA, second, NULL);
       		else
       			xv_set(goto_item, PANEL_CLIENT_DATA, prime, NULL);
			strcpy(filename, newPathName);
			look_up_all(item, event);
		}
	break;
	case INFILE:
		pos = atoi((char *)xv_get(goto_item, PANEL_VALUE));
		newpos = textsw_index_for_file_line(textsw, pos - 1);
		
		if (newpos == TEXTSW_CANNOT_SET) {
			newpos = textsw_index_for_file_line(textsw, pos - 1);
			sprintf(messstr, "There are only %d lines in the file", num_file_lines );
			xv_set(mess_item, PANEL_VALUE, messstr, NULL);
		}
		else {
			sprintf(messstr, "Setting view to line: %d", pos );
			xv_set(mess_item, PANEL_VALUE, messstr, NULL);
			textsw_possibly_normalize(textsw, newpos);
			xv_set(textsw, TEXTSW_INSERTION_POINT, newpos, NULL);
			textsw_set_selection(textsw, newpos, newpos + 4, 17);
			first = newpos;
			last_plus_one = newpos;
            lineNum = what_line_number(filename);
            sprintf(leftFootStr, "Current line number:%ld",lineNum);
            if (currTi >= 0)
            	sprintf(rightFootStr, "Current character position:%ld",currTi);
            xv_set(frame, FRAME_LEFT_FOOTER, leftFootStr, NULL );
            xv_set(frame, FRAME_RIGHT_FOOTER, rightFootStr, NULL );
            currPos = lineNum;
		}
	break;
	}
}

void 
set_current_loc ( Panel_item item, Event *event)

{
	if (item == prime_toCurr) {
		if (strlen(currentPathName) > 1)
			strcpy(primaryPath, currentPathName);
		xv_set(primarySearchPath, PANEL_VALUE, currentPathName, NULL);
		xv_set(pmi[0], MENU_STRING, currentPathName, NULL);
	}
	if (item == second_toCurr) {
		if (strlen(currentPathName) > 1)
			strcpy(secondaryPath, currentPathName);
		xv_set(secondarySearchPath, PANEL_VALUE, currentPathName, NULL);
		xv_set(smi[0], MENU_STRING, currentPathName, NULL);
	}
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
void 
control_toggle ( Panel_item item, Event *event )
{
	int 	Flag;
    char    messstr[BUFSIZ];

	Flag = (int)xv_get(view_choice, PANEL_VALUE);
	if ( Flag == 0 || Flag == 1 || Flag == 2 || Flag == 3 ) {
		xv_set(view_choice, PANEL_VALUE, lastView, NULL);
        sprintf (messstr, "Illegal choice set, reseting...");
        xv_set(mess_item, PANEL_VALUE, messstr, NULL) ;
	}
	else 
		lastView = Flag;
}

Textsw_index
what_line_number(char *filename)
{
	int				temp;
	Textsw_index 	tempTi = 0, count = 0, numLines = 1;
	FILE			*fp;

	tempTi = (Textsw_index)xv_get(textsw, TEXTSW_INSERTION_POINT);

    if ((fp = fopen (filename, "r")) == NULL) {
    	notice_prompt (panel, NULL,
        NOTICE_NO_BEEPING,         TRUE,
        NOTICE_MESSAGE_STRINGS,    "Unable to open: ", filename, "for count", NULL,
        NULL);
    }
    else {
    	while ( (temp = getc(fp))  != EOF) {
        	if (count != tempTi) {
            	if (temp == 10)
                	numLines++;
                count++;
            }
            else 
            	temp = EOF;
    	}
        fclose(fp);
    }
	currTi = tempTi;
	return(numLines);
}
