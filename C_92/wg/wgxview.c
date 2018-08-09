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

#include "wgxview.h" 

void 
repeat_last(Panel_item item, Event *event)
{

	switch(lastFunctFlag)

	{
		case 0:
			look_up_all(item, event);
			break;
		case 1:
			look_up_sys(item, event);
			break;
		case 2:
			look_up_personal(item, event);
			break;
		default:
			break;
	}
}

void
look_up_all(Panel_item item, Event *event)

{
	lastFunctFlag = 0;
	noClearFlag = TRUE;
	noMatchFlag = FALSE;
	look_up_sys(item, event);
	if (noMatchFlag == TRUE) {
		look_up_personal(item, event);
		if (noMatchFlag == TRUE) {
		xv_set(mess_item, PANEL_VALUE, "No match found in", NULL) ;
		xv_set(mess_item2, PANEL_VALUE, "either the System or Personal", NULL) ;
		xv_set(mess_item3 , PANEL_VALUE, "Word Guide", NULL) ;
    	flush_panel();	
		}
	}
	noClearFlag = FALSE;
}

void
look_up_sys(item, event)

Panel_item		item;
Event			*event;

{

	char			word[BUFSIZ];
	char			buf[BUFSIZ]; 
	char			wordlist[10000];  
	char			filename[40];
	int				x = 1, y = 1;
	int				soundexflag = 0;

	if (noClearFlag != TRUE)
		lastFunctFlag = 1;
	xv_set(textsw,	TEXTSW_BROWSING, FALSE, NULL);
	xv_set(mess_item , PANEL_VALUE, "", NULL) ;
	xv_set(mess_item2 , PANEL_VALUE, "", NULL) ;
	xv_set(mess_item3 , PANEL_VALUE, "Searching System guide...", NULL) ;
	xv_set(frame, FRAME_BUSY, TRUE, NULL);
    flush_panel();	
	textsw_reset(textsw, x, y); 
	strcpy(filename, "/usr/tmp/wgfile.txt");
    strcpy(word,(char *)xv_get(word_item, PANEL_VALUE));	
	
	soundexflag = (int)xv_get(soundex_toggle, PANEL_VALUE);
	if (soundexflag == 0) {
		readfile_soundex("/usr/dict/words", word, (int)xv_get(soundex_slide, PANEL_VALUE, 1));
	}
	else
		readfile("/usr/dict/words", word, 1);
	
	xv_set(textsw, TEXTSW_FILE, filename, NULL); 

	if (xv_get(textsw , TEXTSW_LENGTH) < 2) {
		noMatchFlag = TRUE;
		xv_set(mess_item, PANEL_VALUE, "No match found in ", NULL) ;
		xv_set(mess_item2, PANEL_VALUE, "System Word Guide", NULL) ;
		xv_set(mess_item3, PANEL_VALUE, "",  NULL) ;
    	flush_panel();	
	}

	else {
		noMatchFlag = FALSE;
		xv_set(mess_item, PANEL_VALUE, "Done !!", NULL) ;
		xv_set(mess_item2 , PANEL_VALUE, num_lines_found, NULL) ;
		xv_set(mess_item3, PANEL_VALUE, "in the System guide",  NULL) ;
			if (max_word_len > 10) {
				xv_set(textsw, WIN_COLUMNS, max_word_len  + 7, NULL);
				window_fit(textsw);
				window_fit(frame);
			}
			else {
				xv_set(textsw, WIN_COLUMNS, 10, NULL);
				window_fit(textsw);
				window_fit(frame);
			}
    	flush_panel();	
	}

	xv_set(textsw,	TEXTSW_BROWSING, TRUE, NULL);
	xv_set(frame, FRAME_BUSY, FALSE, NULL);
}

void
look_up_personal(item, event)
Panel_item		item;
Event			*event;
{

	char			word[BUFSIZ];
	char			buf[BUFSIZ]; 
	char			wordlist[10000];  
	char			filename[40];
	int				x = 1, y = 1;
	int				soundexflag = 0;

	if (noClearFlag != TRUE)
		lastFunctFlag = 2;
	strcpy(my_argv, homepath); 
	strcat(my_argv, "/.dictionary.txt");

	xv_set(textsw,	TEXTSW_BROWSING, FALSE, NULL);
	if (noClearFlag == TRUE) {
		xv_set(mess_item3, PANEL_VALUE, "Searching Personal guide...",  NULL);
    	flush_panel();	
		usleep(150000);
	}
	else {
		xv_set(mess_item, PANEL_VALUE, "",  NULL) ;
		xv_set(mess_item2, PANEL_VALUE, "",  NULL) ;
		xv_set(mess_item3, PANEL_VALUE, "Searching Personal guide...",  NULL);
    	flush_panel();	
	}

	xv_set(frame, FRAME_BUSY, TRUE, NULL);
    flush_panel();	
	textsw_reset(textsw, x, y); 
	strcpy(filename, "/usr/tmp/wgfile.txt");
    strcpy(word,(char *)xv_get(word_item, PANEL_VALUE));	
    soundexflag = (int)xv_get(soundex_toggle, PANEL_VALUE);
    if (soundexflag == 0) 
        readfile_soundex(my_argv, word, (int)xv_get(soundex_slide, PANEL_VALUE, 1));
    else
        readfile(my_argv, word, 1);
 	  
	xv_set(textsw, TEXTSW_FILE, filename, NULL); 
	if (xv_get(textsw , TEXTSW_LENGTH) < 2)
	{
		noMatchFlag = TRUE;
		system("/bin/rm /usr/tmp/wgfile.txt");
		xv_set(mess_item, PANEL_VALUE, "No match found in ", NULL) ;
		xv_set(mess_item2, PANEL_VALUE, "Personal Word Guide", NULL) ;
		xv_set(mess_item3, PANEL_VALUE, "",  NULL) ;
    	flush_panel();	
	} 	
	else {
		noMatchFlag = FALSE;
		xv_set(mess_item, PANEL_VALUE, "Done !!", NULL) ;
		xv_set(mess_item2 , PANEL_VALUE, num_lines_found, NULL) ;
		xv_set(mess_item3, PANEL_VALUE, "in your Personal word guide",  NULL) ;
		if (max_word_len > 10) {
			xv_set(textsw, WIN_COLUMNS, max_word_len  + 7, NULL);
			window_fit(textsw);
			window_fit(frame);
		}
		else {
			xv_set(textsw, WIN_COLUMNS, 10, NULL);
			window_fit(textsw);
			window_fit(frame);
		}
	}
	xv_set(textsw,	TEXTSW_BROWSING, TRUE, NULL);
	xv_set(frame, FRAME_BUSY, FALSE, NULL);
}

void
toggle_soundex(Panel_item item)

{
		
	switch ( (int) xv_get (item, PANEL_VALUE)) {

        case 0:

        	xv_set(soundex_slide, PANEL_INACTIVE, FALSE, NULL);
            break;

        case 1:
            xv_set(soundex_slide, PANEL_INACTIVE, TRUE, NULL);
            break;


        default:
                break;

    }
}

void
get_word(item, event)
Panel_item			item;
Event				*event;

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

void
delete_word(item, event)
Panel_item			item; 
Event				*event;

{
	char			quote_word[BUFSIZ], numLines[BUFSIZ], line[BUFSIZ], *word, pathname[BUFSIZ], cmd[BUFSIZ];
	FILE			*fp1, *fp2;
	int				numOcc = 0, firstOcc = 0, result;

	if ((fp1 = fopen (TEMPFILE, "w")) == NULL) 
    { 
    	printf ("error opening TEMPFILE \n" ); 
        notice_prompt (panel, NULL, 
        NOTICE_NO_BEEPING,         TRUE, 
        NOTICE_MESSAGE_STRINGS,    "Error openfile file:", TEMPFILE, 
        " Unable to search...", NULL, 
        NULL); 
    }

	word = (char *)xv_get(word_add, PANEL_VALUE);	
	if (strcmp(word, "") == 0) 
 		notice_prompt (panel2, NULL, 
        NOTICE_NO_BEEPING,         TRUE, 
        NOTICE_MESSAGE_STRINGS,    "No word to seach for.", 
        " Please enter a Word", NULL, 
        NULL); 
	else {

	sprintf (quote_word, "\"%s\"", word);
	strcpy(pathname, homepath);
	strcat(pathname, "/.dictionary.txt");
	numOcc = readfile(pathname, word, 0);
	sprintf (numLines, "%d", numOcc);
	if (numOcc == 1) {
		if ((fp2 = fopen (pathname, "r")) == NULL) {
 					 notice_prompt (panel2, NULL, 
                     NOTICE_NO_BEEPING,         TRUE, 
                     NOTICE_MESSAGE_STRINGS,    "Error openfile file:", pathname, 
                                                " Unable to delete word...", NULL, 
                     NULL); 
        }
        else {
			fseek (fp2, 0L, 0L); 
      		strcpy (line, ""); 
      		while(fscanf (fp2, "%s\n", line) == 1) 
      		{   
            	if (strcmp(line, word) != 0 )  
                	writeline(fp1, line); 
  
      		}
		}	  
        xv_set (mess_item, PANEL_VALUE, "Deleted word:", NULL);
        xv_set (mess_item2, PANEL_VALUE, quote_word, NULL);
        xv_set (mess_item3, PANEL_VALUE, "in your Personal Word Guide ", NULL);
        flush_panel();
		fclose(fp1);
		fclose(fp2);

		strcpy(cmd, "/bin/mv ");
		strcat(cmd, TEMPFILE);
		strcat(cmd, " ");
		strcat(cmd, pathname);
		system(cmd);

		unlink(TEMPFILE);
	}

	else if (numOcc == 0) {

            notice_prompt (panel2, NULL,
                      NOTICE_NO_BEEPING,         TRUE,
                      NOTICE_MESSAGE_STRINGS,
                      quote_word,
                      "was NOT found in your personal word guide.",
                    "",
                      NULL,
                      NULL);
	}

	else if (numOcc > 1) {
            result = notice_prompt (panel2, NULL,
                      NOTICE_NO_BEEPING,         TRUE,
                      NOTICE_MESSAGE_STRINGS,
					  numLines,
					  "Occurances of the word:",
                      quote_word,
                      "found in your personal word guide.",
                    "",
                    "Do you wish to delete all but one ? ",
                      NULL,
                      NOTICE_BUTTON_YES,      "Yes",
                      NOTICE_BUTTON_NO,       "No, Delete all",
                      NULL);

          switch(result) {

              case NOTICE_YES:
                  xv_set (mess_item, PANEL_VALUE, "Deleted all but one occurance of", NULL);
                  xv_set (mess_item2, PANEL_VALUE, "in your Personal Word Guide ", NULL);
                  xv_set (mess_item3, PANEL_VALUE, quote_word, NULL);
                  flush_panel();

				if ((fp2 = fopen (pathname, "r")) == NULL) {
                     notice_prompt (panel2, NULL,
                     NOTICE_NO_BEEPING,         TRUE,
                     NOTICE_MESSAGE_STRINGS,    "Error openfile file:", pathname,
                                                " Unable to delete words...", NULL,
                     NULL);
        		}
        		else {   
            		fseek (fp2, 0L, 0L); 
            		strcpy (line, "");  
            		while(fscanf (fp2, "%s\n", line) == 1) 
            		{     
                		if (strcmp(line, word) == 0) {
							  if (firstOcc == 0)  {
                    				writeline(fp1, line); 
                    				firstOcc ++;
							  }
                		}  
                		else 
                    		writeline(fp1, line); 
 
            		}
        		}
        		fclose(fp1);
        		fclose(fp2);
 
				strcpy(cmd, "/bin/mv ");
				strcat(cmd, TEMPFILE);
				strcat(cmd, " ");
				strcat(cmd, pathname);
				system(cmd);

				unlink(TEMPFILE);

                break;
 
              case NOTICE_NO:
                  xv_set (mess_item, PANEL_VALUE, "deleted all occurances of", NULL);
                  xv_set (mess_item2, PANEL_VALUE, quote_word, NULL);
                  xv_set (mess_item3, PANEL_VALUE, "in your Personal Word Guide", NULL);
                  flush_panel();
				  if ((fp2 = fopen (pathname, "r")) == NULL) {
                     notice_prompt (panel2, NULL,
                     NOTICE_NO_BEEPING,         TRUE,
                     NOTICE_MESSAGE_STRINGS,    "Error openfile file:", pathname,
                                                " Unable to delete words...", NULL,
                     NULL);
                }
                else {   
                    fseek (fp2, 0L, 0L);
                    strcpy (line, "");
                    while(fscanf (fp2, "%s\n", line) == 1)
                    {    
                        if (strcmp(line, word) != 0) 
                            writeline(fp1, line);
 
                    }
                }
                fclose(fp1);
                fclose(fp2);
 
                strcpy(cmd, "/bin/mv ");
                strcat(cmd, TEMPFILE);
                strcat(cmd, " ");
                strcat(cmd, pathname);
                system(cmd);
	
				unlink(TEMPFILE);

                  break;
              case NOTICE_FAILED:
                  xv_set (mess_item, PANEL_VALUE, "Unable to pop-up ", NULL);
                  break;
              default:
                  xv_set (mess_item, PANEL_VALUE, "Unknown choice ", NULL);
                  break;
          }
	
		if ((fp2 = fopen (pathname, "r")) == NULL){
 					 notice_prompt (panel2, NULL, 
                     NOTICE_NO_BEEPING,         TRUE, 
                     NOTICE_MESSAGE_STRINGS,    "Error openfile file:", pathname, 
                                                " Unable to delete word...", NULL, 
                     NULL); 
        }
        else {
			fseek (fp2, 0L, 0L); 
      		strcpy (line, ""); 
      		while(fscanf (fp2, "%s\n", line) == 1) 
      		{   
            	if (strcmp(line, word) == 0 && firstOcc == 0)  {
                	writeline(fp1, line); 
					firstOcc ++;
				}
				else 
                	writeline(fp1, line); 
  
      		}
		}
		fclose(fp1);
		fclose(fp2);
	}
	}


}


void
add_word(item, event)
Panel_item			item; 
Event				*event;

{
	char			quote_word[BUFSIZ], word[BUFSIZ], pathname[BUFSIZ];
	FILE				*fp;
	int				num_match = 0, result; 

	strcpy(word,(char *)xv_get(word_add, PANEL_VALUE));	
	if (strcmp(word, "") == 0) 
 		notice_prompt (panel2, NULL, 
        NOTICE_NO_BEEPING,         TRUE, 
        NOTICE_MESSAGE_STRINGS,    "No word to add", 
        " Please enter a Word", NULL, 
        NULL); 
	else {
	sprintf (quote_word, "\"%s\"", word);
	strcpy(pathname, homepath);
	strcat(pathname, "/.dictionary.txt");
	num_match = readfile(pathname, word, 0);
	if (num_match == 0){
		if ((fp = fopen(pathname, "a")) == NULL) 
	    	{	
				xv_set(mess_item, PANEL_VALUE, "Unable to open ", NULL) ;
				xv_set(mess_item2, PANEL_VALUE, "Personal Word Guide", NULL) ;
				xv_set(mess_item3, PANEL_VALUE, "", NULL) ;
    			flush_panel();	
			}
		else 
		{ 
			fprintf(fp, "%s\n", word);
			fclose(fp);
            xv_set (mess_item, PANEL_VALUE, quote_word, NULL);
            xv_set (mess_item2, PANEL_VALUE, "added to", NULL);
            xv_set (mess_item3, PANEL_VALUE, "your Personal Word Guide ", NULL);
    		flush_panel();	
		}
	}
	else {
			result = notice_prompt (panel2, NULL,
                      NOTICE_NO_BEEPING,         TRUE,
                      NOTICE_MESSAGE_STRINGS,
					  quote_word,
                      "is already in your personal word guide.",
                    "",
                    "Do you still wish to add it? ",
                      NULL,
                      NOTICE_BUTTON_YES,      "Yes",
                      NOTICE_BUTTON_NO,       "No",
                      NULL);

          switch(result) {

              case NOTICE_YES:
                  xv_set (mess_item, PANEL_VALUE, quote_word, NULL);
                  xv_set (mess_item2, PANEL_VALUE, "added again to", NULL);
                  xv_set (mess_item3, PANEL_VALUE, "your Personal Word Guide ", NULL);
    			  flush_panel();	
				  if ((fp = fopen(pathname, "a")) == NULL) 
	    		  {	
				  		xv_set(mess_item, PANEL_VALUE, "Unable to open ", NULL) ;
						xv_set(mess_item2, PANEL_VALUE, "Personal Word Guide", NULL) ;
						xv_set(mess_item3, PANEL_VALUE, "", NULL) ;
    					flush_panel();	
			      }
				  else 
				  { 
						fprintf(fp, "%s\n", word);
						fclose(fp);
		          }
                  break;
 
              case NOTICE_NO:
                  xv_set (mess_item, PANEL_VALUE, "Word NOT added. ", NULL);
                  xv_set (mess_item2, PANEL_VALUE, " ", NULL);
                  xv_set (mess_item3, PANEL_VALUE, " ", NULL);
    			  flush_panel();	
                  break;
              case NOTICE_FAILED:
                  xv_set (mess_item, PANEL_VALUE, "Unable to pop-up ", NULL);
                  break;
              default:
                  xv_set (mess_item, PANEL_VALUE, "Unknown choice ", NULL);
                  break;
          }
	}
	}
	
}

void
quit(item)
	Panel_item 		item;
{
	Frame framed = (Frame)xv_get(item, PANEL_CLIENT_DATA);
	textsw_reset(textsw, 1, 1); 
	xv_destroy_safe(framed);
}

void
flush_panel(void) 
{
	
	Display *display;
	display = (Display *)xv_get(frame, XV_DISPLAY);
	XFlush(display);
}

char *
get_sel_item(void)
{
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
{
    char    *temp_word;

    temp_word = get_sel_item();
    xv_set(word_item, PANEL_VALUE, temp_word, NULL);

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

