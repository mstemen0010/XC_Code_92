/*
** File: ptxview.c SCCS 2.8 - 1/6/94
** Author:   Matthew Stemen 
**
** Created:  04 Jan 1993 
** Edited:
**
**
** Purpose: Allows user to search company phone list and to keep a
**          personal phone list.
**  
*/

#include "ptxv.h"


void
look_up_sys (Panel_item item)
{

    char                  num_matches[BUFSIZ], quote_word[BUFSIZ], buf[BUFSIZ], wordlist[10000];
                          
    int                   x = 1, 
                          y = 1;
    FILE                  *fp;
    int					  num_matches_found = 0;

    xv_set (textsw, TEXTSW_BROWSING, FALSE, NULL);
    xv_set (mess_item, PANEL_VALUE, "", NULL);
    xv_set (mess_item2, PANEL_VALUE, "",  NULL);
    xv_set (mess_item3, PANEL_VALUE, "",  NULL);
    strcpy (word, (char *) xv_get (word_item, PANEL_VALUE));
    textsw_reset (textsw, x, y); 
    strcpy (infilename, compfilename );
    if (strlen (word) < 1) {
        notice_prompt (panel, NULL,
        NOTICE_NO_BEEPING,         TRUE,
        NOTICE_MESSAGE_STRINGS,    "Must enter something"
        " to search for", NULL,
        NULL);
    }
    else {
    	if ((fp = fopen (infilename, "r")) == NULL) {
      	notice_prompt (panel, NULL,
          NOTICE_MESSAGE_STRINGS,    "Unable to open company phone file"
          " Check location under properties", 
		"Change if necessary..", NULL,
          NULL);
		
      	}
		else{
			fclose(fp);


			if (soundexOn) 
      	 		num_matches_found = readfile_soundex (infilename, word, (int)xv_get(soundex_tol_slide, PANEL_VALUE));
			else
      	 		num_matches_found = readfile(infilename, word);

			if (num_matches_found > 1) 
         		sprintf (num_matches, "%d matches found for", num_matches_found);
			else
         		sprintf (num_matches, "%d match found for", num_matches_found);

         	sprintf (quote_word, "the string \"%s\"", word);
        	xv_set (textsw, TEXTSW_FILE, TEMPFILE, NULL); 
          
        	if (xv_get (textsw, TEXTSW_LENGTH) < 1) {
            	xv_set (mess_item, PANEL_VALUE, "No match in System Phone"
                    " book", NULL);
            	xv_set (mess_item2, PANEL_VALUE, "Trying Personal Phone"
                    " book...", NULL);
			    XFlush((Display *)xv_get(frame, XV_DISPLAY));
                usleep(500000);
            	strcpy (infilename, personfilename);
				if (soundexOn) 
      	 			num_matches_found = readfile_soundex (infilename, word, (int)xv_get(soundex_tol_slide, PANEL_VALUE));
				else
      	 			num_matches_found = readfile(infilename, word);
			if (num_matches_found > 1) 
         		sprintf (num_matches, "%d matches found for", num_matches_found);
			else
         		sprintf (num_matches, "%d match found for", num_matches_found);

         		sprintf (quote_word, "the string \"%s\"", word);
            	xv_set (textsw, TEXTSW_FILE, TEMPFILE, NULL); 
        		if (xv_get (textsw, TEXTSW_LENGTH) < 1)
          			xv_set (mess_item3, PANEL_VALUE, "Still not found ", NULL);
        		else {
    				xv_set (mess_item, PANEL_VALUE, num_matches, NULL);
    				xv_set (mess_item2, PANEL_VALUE, quote_word,  NULL);
    				xv_set (mess_item3, PANEL_VALUE, "in your personal phone file",  NULL);
            		xv_set (textsw, TEXTSW_BROWSING, TRUE, NULL);
            		/* textsw_scroll_lines (textsw, -10000); */
          		}
			}
   
            else 
            {
    			xv_set (mess_item, PANEL_VALUE, num_matches, NULL);
    			xv_set (mess_item2, PANEL_VALUE, quote_word,  NULL);
    			xv_set (mess_item3, PANEL_VALUE, "in the company phone file",  NULL);
 			}

        }

	}
}
void 
clear_screen(Panel_item item)
{
    char                  buf[BUFSIZ], blank[] = "                             ";
                          
    int                   x = 1, 
                          y = 1;
    FILE                  *fp;

    xv_set (textsw, TEXTSW_BROWSING, FALSE, NULL);
    xv_set (mess_item, PANEL_VALUE, "", NULL);
    xv_set (mess_item2, PANEL_VALUE, "",  NULL);
    xv_set (mess_item3, PANEL_VALUE, "",  NULL);
    strcpy (word, blank);
    textsw_reset (textsw, x, y); 
    strcpy (infilename, personfilename );
    	if ((fp = fopen (infilename, "r")) == NULL) {
      	notice_prompt (panel, NULL,
          NOTICE_MESSAGE_STRINGS,    "Unable to clear screen",
          NULL);
		fclose(fp);
		
      }
	else {

		fclose(fp);
		if (soundexOn) 
      		readfile_soundex (infilename, word, (int)xv_get(soundex_tol_slide, PANEL_VALUE));
		else
      	 	readfile(infilename, word);
        xv_set (textsw, TEXTSW_INSERT_FROM_FILE, TEMPFILE, NULL); 
          
	}
}


void
look_personal (Panel_item item)
{
    char                  buf[BUFSIZ], wordlist[10000];
    char                  num_matches[BUFSIZ], quote_word[BUFSIZ];
    int                   x = 1, 
                          y = 1;
    int					  num_matches_found = 0;

    xv_set (textsw, TEXTSW_BROWSING, FALSE, NULL);
    xv_set (mess_item, PANEL_VALUE, "", NULL) ;
    xv_set (mess_item2, PANEL_VALUE, "",  NULL) ;
    xv_set (mess_item3, PANEL_VALUE, "",  NULL) ;
    strcpy (infilename, personfilename);
    textsw_reset (textsw, x, y); 
    strcpy (word, (char *) xv_get (word_item, PANEL_VALUE));      
    if (strlen (word) < 1) 
    {
        notice_prompt (panel, NULL,
                       NOTICE_NO_BEEPING,         TRUE,
                       NOTICE_MESSAGE_STRINGS,    "Must enter something"
                                                  " to search for",
                                                  NULL,
                       NULL);
    }
    else {
			if (soundexOn) 
      			num_matches_found = readfile_soundex (infilename, word, (int)xv_get(soundex_tol_slide, PANEL_VALUE));
			else
      	 		num_matches_found = readfile(infilename, word);
			if (num_matches_found > 1) 
         		sprintf (num_matches, "%d matches found for", num_matches_found);
			else
         		sprintf (num_matches, "%d match found for", num_matches_found);
         sprintf (num_matches, "%d matches found for", num_matches_found);
         sprintf (quote_word, "the string \"%s\"", word);
    
        xv_set (textsw, TEXTSW_FILE, TEMPFILE, NULL); 
    	if (xv_get (textsw , TEXTSW_LENGTH) < 1)
        {
        	xv_set (mess_item, PANEL_VALUE, "No match in ", NULL);
        	xv_set (mess_item2, PANEL_VALUE, "Personal Phone book", NULL);
      	}   
      	else
      	{
    		xv_set (textsw, TEXTSW_BROWSING, TRUE, NULL);
    		xv_set (mess_item, PANEL_VALUE, num_matches, NULL);
    		xv_set (mess_item2, PANEL_VALUE, quote_word,  NULL);
    		xv_set (mess_item3, PANEL_VALUE, "in your personal phone file",  NULL);
    		/* textsw_scroll_lines (textsw, -10000); */
	  	}
    }
}

void
help(Panel_item item, Event *event)
{
      xv_set (helpframe, XV_X, xv_get(frame, XV_X) - 2, NULL);
      xv_set (helpframe, XV_Y, xv_get(frame, XV_Y) + 96, NULL);
      xv_set(helpframe, XV_SHOW, TRUE, NULL);
}

char *
get_sel_item(void)
{
	Xv_Server		server;
	Seln_holder		holder;
	Seln_request	*response;
	char			*output_string;
	char 			temp[BUFSIZ];
	

	server = (Xv_Server)xv_get(xv_get(frame, XV_SCREEN), SCREEN_SERVER);
	holder = selection_inquire(server, SELN_PRIMARY);
	response = selection_ask(server, &holder, SELN_REQ_CONTENTS_ASCII, NULL, NULL);
	strcpy(temp, response->data + sizeof (SELN_REQ_CONTENTS_ASCII));
	output_string = temp;

	return(output_string);
}

void
dial(Panel_item item, Event *event)
{
	char *number;
    Audio_info  aif;
    Audio_info  naif;
	int		value, stat, errno;
	

    xv_set (dialframe, XV_X, xv_get(frame, XV_X) - 2, NULL);
    xv_set (dialframe, XV_Y, xv_get(frame, XV_Y) + 96, NULL);
    xv_set(dialframe, XV_SHOW, TRUE, NULL);
	xv_set(dialframe, FRAME_CMD_PUSHPIN_IN, TRUE, NULL);
	xv_set(dialpanel, PANEL_CARET_ITEM, dial_number ,NULL);
	number = get_sel_item();
	xv_set(dial_number, PANEL_VALUE, number, NULL);
	audio_open();
	update_panels();
	getinfo(&naif);
    value = (naif.play.port == AUDIO_SPEAKER ? 1 : 0);
	xv_set(dial_sound_output, PANEL_VALUE, value, NULL); 
}

void
add_panel(Panel_item item)
{
    FILE					*fp;
    int					result;
    char 					readline[BUFSIZ];

    if ((fp = fopen (personfilename, "r+")) == NULL) {

      	result = notice_prompt (panel, NULL,
                      NOTICE_NO_BEEPING,         TRUE,
                      NOTICE_MESSAGE_STRINGS,
                      "A Personal Phone file does not exist under directory",
					"",
					personfilename,
					"",
                      "Create it?",
                      NULL,
                      NOTICE_BUTTON_YES,      "Yes",
                      NOTICE_BUTTON_NO,       "No",
                      NULL);
          switch(result) {
              case NOTICE_YES:
                  xv_set (mess_item, PANEL_VALUE, "Creating file... ", NULL);
                  xv_set (mess_item2, PANEL_VALUE, " ", NULL);
                  xv_set (mess_item3, PANEL_VALUE, " ", NULL);
				fp = (fopen (personfilename, "a+"));
                  if (fp == NULL) {

          			notice_prompt (panel, NULL,
                      NOTICE_NO_BEEPING,         TRUE,
                      NOTICE_MESSAGE_STRINGS,
                      "Unable to create file...",
                      " You may be trying to access a directoy",
					" where you do not have read/write privileges",
                      NULL,
                      NULL);
          		}
				else {
        				fprintf (fp, " ~|~ ~ ~\n");
                  	fclose (fp);
                  	xv_set (mess_item3, PANEL_VALUE, "Done !" , NULL);
				}
                  break;

              case NOTICE_NO:
                  xv_set (mess_item, PANEL_VALUE, "NOT creating file ", NULL);
                  xv_set (mess_item2, PANEL_VALUE, " ", NULL);
                  xv_set (mess_item3, PANEL_VALUE, " ", NULL);
                  break;
              case NOTICE_FAILED:
                  xv_set (mess_item, PANEL_VALUE, "Unable to pop-up ", NULL);
                  break;
              default:
                  xv_set (mess_item, PANEL_VALUE, "Unknown choice ", NULL);
                  break;
          }
    }
    if ((fp = fopen(personfilename, "r+")) != NULL) {
        fgets(readline, MAXBUF, fp);
        if ((strstr(readline, "~|~")) != NULL)
        	edflag = 1;
        else
        	edflag = 0;
    fclose(fp);
    }
    else  
	   edflag = 2;

    if  (edflag == 1){
		xv_set (addframe, XV_X, xv_get(frame, XV_X), NULL);
		xv_set (addframe, XV_Y, xv_get(frame, XV_Y), NULL);
    		xv_set (addframe, XV_SHOW, TRUE, NULL);
		xv_set(addframe, FRAME_CMD_PUSHPIN_IN, TRUE, NULL);
    		window_fit(addpanel); 
    		window_fit(addframe);
    }
    else if (edflag == 0) {

                notice_prompt (panel, NULL,
                               NOTICE_NO_BEEPING,         TRUE,
                               NOTICE_MESSAGE_STRINGS,    "To add to your phone file", 
                               "select 'edit', add your line, and then save", 
                               NULL,
                               NULL);
    }                   

}
void
editor(Panel_item item)
{
	FILE *fp;

	if (edflag == 1)  {
		upd_panel(item);
    		clear_pan_values (updpanel, item);   
		xv_set(updpanel, PANEL_CARET_ITEM, word_upd ,NULL);
		xv_set(updframe, FRAME_CMD_PUSHPIN_IN, TRUE, NULL);
	}
      else {
		
        	if ((fp = fopen (personfilename, "r+")) == NULL) {
        		notice_prompt (panel, NULL,
              NOTICE_NO_BEEPING,         TRUE,
              NOTICE_MESSAGE_STRINGS,    "Error opening file:", personfilename,
                                                  " Try again", NULL,
              NULL);
		}
		else
			upd_textsw (item);
	}
}		  
void
upd_textsw(Panel_item item )
{
	  xv_set (updtextframe, XV_X, xv_get(frame, XV_X), NULL);
	  xv_set (updtextframe, XV_Y, xv_get(frame, XV_Y), NULL);
	  xv_set (updtextsw, TEXTSW_FILE,  personfilename, NULL);
        xv_set(updtextframe, XV_SHOW, TRUE, NULL);
}


void
upd_panel(Panel_item item)
{
	  xv_set (updframe, XV_X, xv_get(frame, XV_X), NULL);
	  xv_set (updframe, XV_Y, xv_get(frame, XV_Y), NULL);
        xv_set(updframe, XV_SHOW, TRUE, NULL);
}

Notify_value
add_line (Panel_item item)
{
    return(PANEL_NEXT);
}

void
find_last_match (Panel_item item)
{
    Frame                 updframe;
    FILE                  *fp;
    char                  *panel_string;
    int                   nomatchflag = 1, nullflag = 0, cnt = 0;
    char                  tempword[80];
    char                  templine[BUFSIZ], panel_value[BUFSIZ];
    char                  *token, *matchtoken;   
    int                   getvalue; 
    long				    start, count = 0, curpos, CURPOS;
    char					ch;
	int						firstn = FALSE, secondn = FALSE;
	int						tempindex;

    strcpy (infilename, personfilename);
	strcpy (tempword, word);
    strcpy (word, (char *) xv_get (word_upd, PANEL_VALUE)); 
	if (strcmp (word, tempword) != 0)
		find_match(item);	

    if (strlen(word) < 1) {
    		notice_prompt (panel, NULL, 
          NOTICE_NO_BEEPING,         TRUE,
          NOTICE_MESSAGE_STRINGS,    "Enter a string to search for in your personal Phone book",
          " at the 'Search for: ' prompt",
          NULL, 
          NULL);
		  xv_set(findlast_but, PANEL_INACTIVE, TRUE, NULL);
		  xv_set(findnext_but, PANEL_INACTIVE, TRUE, NULL);
    }
    else {
        strcpy (tempword, word);
        uppercase (tempword);

        if ((fp = fopen (infilename, "r+")) == NULL) {  /* 1st if */
            xv_set (mess_item, PANEL_VALUE, "Unable to open ", NULL);
            xv_set (mess_item2, PANEL_VALUE, "Personal phone book", NULL);
            xv_set (mess_item3, PANEL_VALUE, "Try again...", NULL);
        } 
        else { 
			xv_set(findnext_but, PANEL_INACTIVE, FALSE, NULL);
			rewind(fp);
			if (lastindex == 1) 
               nomatchflag = 2;
			else{
				tempindex = lastindex - 1;
				while (count < tempindex ) {
					if (nomatchflag != 0) {
         					if (fgets (line, MAXBUF, fp) != NULL) { 
								strcpy (templine, line);
                   		 		uppercase (templine);
                   		 		if (strstr (templine, tempword) != NULL) {
									count++;
									if (count == lastindex - 1){
                   		 				nomatchflag = 0;
                   		     			strcpy (matchline, line);
									}
                   		 		}
							}
            				else
                				nomatchflag = 2;
					}
				}
			}

 			if (nomatchflag == 2) {
				xv_set(findlast_but, PANEL_INACTIVE, TRUE, NULL);

           /*            	notice_prompt (updpanel, NULL,
                	NOTICE_NO_BEEPING,         TRUE,
                    NOTICE_MESSAGE_STRINGS,    "No More Matches Found...",
                    NULL,
                   	NULL); 
			*/
            }
            else {
				if ( (token = strtok (line, "~")) == NULL)
                	nullflag = 1;

            	PANEL_EACH_ITEM (updpanel, item)           
                   
            		switch ( (int) xv_get(item, PANEL_CLIENT_DATA) ) {
                		case search: break;
 
                   		default:
 
                    	if (! nullflag) {
                          	if (strcmp(token, "|") != 0) {
                            	strcpy (panel_value, token);
                               	xv_set (item, PANEL_VALUE, panel_value, NULL);
                               	if ( (token = strtok (NULL, "~")) == NULL)
                               		nullflag = 1;
                          	}
                          	else {
                          		if ( (token = strtok (NULL, "~")) == NULL)
                                	nullflag = 1;
                                    strcpy (panel_value, token);
                                    xv_set (item, PANEL_VALUE, panel_value, NULL);           
                                if ( (token = strtok (NULL, "~")) == NULL)
                                    nullflag = 1;
                           }
                    	} 
                    	else {
                    		strcpy (panel_value, "None Found");
                        	xv_set (item, PANEL_VALUE, panel_value, NULL);
                    	}
                    	break;
                	} /* end of switch */
               	PANEL_END_EACH
              
			} 
            
		if (lastindex >= 2) {
			lastindex--;
	  		currpos = ftell(fp);
		}
      	fclose (fp);
		}
	}
}
	
void
find_next_match (Panel_item item)
{
    FILE                  *fp;
    char                  *panel_string;
    int                   nomatchflag = 1, nullflag = 0, cnt = 0;
    char                  tempword[80];
    char                  templine[BUFSIZ], panel_value[BUFSIZ];
    char                  *token, *matchtoken;   
    int                   getvalue, curpos; 
    long 			        temppos;

	strcpy (current_match, line);
    strcpy (infilename, personfilename);
	strcpy (tempword, word);
    strcpy (word, (char *) xv_get (word_upd, PANEL_VALUE)); 
	if (strcmp (word, tempword) != 0)
		find_match(item);	

    if (strlen(word) < 1) {
    		notice_prompt (panel, NULL, 
          NOTICE_NO_BEEPING,         TRUE,
          NOTICE_MESSAGE_STRINGS,    "Enter a string to search for in your personal Phone book",
          " at the 'Search for: ' prompt",
          NULL, 
          NULL);
		  xv_set(findlast_but, PANEL_INACTIVE, TRUE, NULL);
		  xv_set(findnext_but, PANEL_INACTIVE, TRUE, NULL);
    }
    else {
        strcpy (tempword, word);
        uppercase (tempword);

        if ((fp = fopen (infilename, "r+")) == NULL) {
            xv_set (mess_item, PANEL_VALUE, "Unable to open ", NULL);
            xv_set (mess_item2, PANEL_VALUE, "Personal phone book", NULL);
            xv_set (mess_item3, PANEL_VALUE, "Try again...", NULL);
        } 
        else {
		  fseek(fp, currpos, 0L);
		  curpos = ftell(fp);
		
		  lastpos = currpos;
            while (nomatchflag == 1) {
                if (fgets (line, MAXBUF, fp) != NULL) { 
                    strcpy (templine, line);
                    uppercase (templine);
                    if (strstr (templine, tempword) != NULL) {
                        nomatchflag = 0; 
                        strcpy (matchline, line);
                    }
            	  }
                else
                    nomatchflag = 2;
            }
        	  if (nomatchflag == 2) {
				xv_set(findnext_but, PANEL_INACTIVE, TRUE, NULL);
              /*  notice_prompt (updpanel, NULL,
                               NOTICE_NO_BEEPING,         TRUE,
                               NOTICE_MESSAGE_STRINGS,    "No More Matches Found...", 
                               NULL,
                               NULL); */ 
			  xv_set(updpanel, PANEL_CARET_ITEM, word_upd, NULL);
         	  }                   
         	  else {
			  lastindex ++;
			  if ( (token = strtok (line, "~")) == NULL)
				nullflag = 1;
                PANEL_EACH_ITEM (updpanel, item){
				
	  			switch ( (int) xv_get(item, PANEL_CLIENT_DATA) ) {
						case search: break;

						default: 

                          if (! nullflag) {
                          	if (strcmp(token, "|") != 0) {
                            		strcpy (panel_value, token);  
                            		xv_set (item, PANEL_VALUE, panel_value, NULL);
			  					if ( (token = strtok (NULL, "~")) == NULL)
									nullflag = 1;
                          	}
                        		else {
			  					if ( (token = strtok (NULL, "~")) == NULL)
									nullflag = 1;
                            		strcpy (panel_value, token);  
                            		xv_set (item, PANEL_VALUE, panel_value, NULL);
			  					if ( (token = strtok (NULL, "~")) == NULL)
									nullflag = 1;
                         		     } 
							break;
						}
						else{ 
                            		strcpy (panel_value, "None Found");  
                            		xv_set (item, PANEL_VALUE, panel_value, NULL);
						}	
                  }
			  }
		}
                PANEL_END_EACH
        }
	  currpos = ftell(fp);
        fclose (fp);
		strcpy (current_match, line);
		xv_set(findlast_but, PANEL_INACTIVE, FALSE, NULL);
    }
}

void
find_match (Panel_item item)
{
    Frame                 updframe;
    FILE                  *fp;
    char                  *panel_string;
    int                   nomatchflag = 1, nullflag = 0, cnt = 0;
    char                  tempword[80];
    char                  templine[BUFSIZ], panel_value[BUFSIZ];
    char                  *token, *matchtoken;   
    int                   getvalue; 
    long 			        temppos;

	lastindex = 1;
	xv_set(findnext_but, PANEL_INACTIVE, FALSE, NULL);
    strcpy (infilename, personfilename);
    strcpy (word, (char *) xv_get (word_upd, PANEL_VALUE));
    if (strlen(word) < 1) {
    		notice_prompt (panel, NULL, 
          NOTICE_NO_BEEPING,         TRUE,
          NOTICE_MESSAGE_STRINGS,    "Enter a string to search for in your personal Phone book",
          " at the 'Search for: ' prompt",
          NULL, 
          NULL);
		  xv_set(findlast_but, PANEL_INACTIVE, TRUE, NULL);
		  xv_set(findnext_but, PANEL_INACTIVE, TRUE, NULL);
    }
    else {
		xv_set(findlast_but, PANEL_INACTIVE, TRUE, NULL);
        strcpy (tempword, word);
        uppercase (tempword);

        if ((fp = fopen (infilename, "r+")) == NULL) {
            xv_set (mess_item, PANEL_VALUE, "Unable to open ", NULL);
            xv_set (mess_item2, PANEL_VALUE, "Personal phone book", NULL);
            xv_set (mess_item3, PANEL_VALUE, "Try again...", NULL);
        } 
        else {
            while (nomatchflag == 1) {
                temppos = ftell(fp);
                if (fgets (line, MAXBUF, fp) != NULL) { 
                    strcpy (templine, line);
                    uppercase (templine);
                    if (strstr (templine, tempword) != NULL) {
                        nomatchflag = 0; 
                        strcpy (matchline, line);
                    }
            	  }
                else
                    nomatchflag = 2;
            }
        	  if (nomatchflag == 2) {
                notice_prompt (updpanel, NULL,
                               NOTICE_NO_BEEPING,         TRUE,
                               NOTICE_MESSAGE_STRINGS,    "No Matches Found...", 
                               NULL,
                               NULL);
		  		xv_set(findlast_but, PANEL_INACTIVE, TRUE, NULL);
		  		xv_set(findnext_but, PANEL_INACTIVE, TRUE, NULL);
         	  }                   
         	  else {
    			  xv_set(updpanel, PANEL_CARET_ITEM, lname_upd, NULL);
                lastpos = temppos;
				lastindex = 1;
			  if ( (token = strtok (line, "~")) == NULL)
				nullflag = 1;
                PANEL_EACH_ITEM (updpanel, item){
				
	  			switch ( (int) xv_get(item, PANEL_CLIENT_DATA) ) {
						case search: break;

						default: 

                          if (! nullflag) {
                          	if (strcmp(token, "|") != 0) {
                            		strcpy (panel_value, token);  
                            		xv_set (item, PANEL_VALUE, panel_value, NULL);
			  					if ( (token = strtok (NULL, "~")) == NULL)
									nullflag = 1;
                          	}
                        		else {
			  					if ( (token = strtok (NULL, "~")) == NULL)
									nullflag = 1;
                            		strcpy (panel_value, token);  
                            		xv_set (item, PANEL_VALUE, panel_value, NULL);
			  					if ( (token = strtok (NULL, "~")) == NULL)
									nullflag = 1;
                         		     } 
							break;
						}
						else{ 
                            		strcpy (panel_value, "None Found");  
                            		xv_set (item, PANEL_VALUE, panel_value, NULL);
						}	
                  }
			  }
		}
                PANEL_END_EACH
        }
	  currpos = ftell(fp);
        fclose (fp);
		strcpy (current_match, line);
    }
} 


void
insert_upd (Panel_item item)
{
    FILE                  *infp, *outfp;
    char                  readline[BUFSIZ], upperreadline[BUFSIZ],
                          upprmatchline[BUFSIZ]; 
    char                  cmd[40];
    int					num_lines_read = 0;
    char					old_value[BUFSIZ];
	int						matchFlag = TRUE;

    strcpy (old_value, (char *)xv_get(word_upd, PANEL_VALUE));

    if (strlen(old_value) > 0) 
    {
        strcpy (infilename, personfilename);
        if ((infp = fopen (infilename, "r")) == NULL) {
            xv_set (mess_item, PANEL_VALUE, "Unable to open ", NULL) ;
            xv_set (mess_item2, PANEL_VALUE, "Personal phone book", NULL) ;
            xv_set (mess_item3, PANEL_VALUE, "for update....", NULL) ;
        }
        if ((outfp = fopen (TEMPFILE, "w")) == NULL) {
            xv_set (mess_item, PANEL_VALUE, "Unable to open ", NULL) ;
            xv_set (mess_item2, PANEL_VALUE, "Temp file under /usr/tmp", NULL) ;
            xv_set (mess_item3, PANEL_VALUE, "Try again...", NULL) ;
        } 
        else {
            rmtempfileflag = 1;
            get_pan_values (updpanel, item);  
			
            while(fgets (readline, MAXBUF, infp) != NULL && line[0] != '\n') {
                if (strcmp (readline, "\n") != 0) {
                    num_lines_read++;
                    strcpy (upperreadline, readline);
                    strcpy (upprmatchline, matchline);
                    uppercase (upperreadline);
                    uppercase (upprmatchline);
                    if (strstr (upperreadline, upprmatchline) != NULL) {
						if (strstr (readline, updateline) == NULL) { 
                        	fprintf (outfp, "%s\n", updateline);
                        	fflush (outfp);
						}
						else {
        					notice_prompt (updpanel, NULL,
        					NOTICE_NO_BEEPING,         TRUE,
        					NOTICE_MESSAGE_STRINGS,    "None of the information has been changed.",
        					"Not Updating Personal phone file", NULL,
        					NULL);
                        	fprintf (outfp, "%s\n", readline);
                        	fflush (outfp);
							matchFlag = FALSE;
						}

                    }
                    else {
                        fprintf (outfp, "%s\n", readline);
                        fflush (outfp);
                    }
                }
            } 
        } 
        fclose (infp);
        fclose (outfp);
        strcpy (cmd, "/bin/cp ");
        strcat (cmd, TEMPFILE);
        strcat (cmd, " ");
        strcat (cmd, infilename);
        system (cmd);
        unlink (TEMPFILE);

        rmtempfileflag = 0;

		if (matchFlag == TRUE) {
        	sort_file(infilename, num_lines_read);
        	clear_pan_values (updpanel, item);   
        	xv_set(updpanel, PANEL_CARET_ITEM, word_upd, NULL); 
		}
    }
    else
    {
        notice_prompt (updpanel, NULL,
        NOTICE_NO_BEEPING,         TRUE,
        NOTICE_MESSAGE_STRINGS,    "You Must enter something"
        " to search for", "Before You Select this function", NULL,
        NULL);
    }
	
}

void
sort_file (char filename[BUFSIZ], int lines)
{
	char 	**lineptrs = (char **)malloc(lines*sizeof(char *));
	char 	buff[BUFSIZ];
	char 	*linebuff;
	char                cmd[40];
	int		i = 0, k, len_str;
	FILE                *infp, *outfp;
	
	

	if ((infp = fopen (filename, "r")) == NULL)
    {
		xv_set (mess_item, PANEL_VALUE, "Unable to open ", NULL) ;
		xv_set (mess_item2, PANEL_VALUE, "Personal phone book", NULL) ;
		xv_set (mess_item3, PANEL_VALUE, "for sort....", NULL) ;
    }
    else {
    	if ((outfp = fopen (TEMPSORTFILE, "w")) == NULL)
     	 {
     	   		xv_set (mess_item, PANEL_VALUE, "Unable to open ", NULL) ;
     	   		xv_set (mess_item2, PANEL_VALUE, "Temp sort file under /usr/tmp", NULL) ;
     	   		xv_set (mess_item3, PANEL_VALUE, "Try again...", NULL) ;
     	 } 
    	else {
				fseek(infp, 0, 0);
     	   		rmtempfileflag = 1;
				fseek (infp, 0L, 0L);
      			while(fgets (buff, MAXBUF, infp) != NULL) {
					if (buff[0] != '\n') {
						len_str = strlen(buff);
						lineptrs[i] = (char *)malloc (len_str + 1 * sizeof(char));
						strcpy(lineptrs[i], buff);
						i++;
					}		
				}
				qsort(lineptrs, i, sizeof(char **), stsrt);
        		for (k = 0; k < i; k++) {
	  				fputs(lineptrs[k], outfp);
					/* free(lineptrs[k]);  */
				}
    	  		fclose (infp);
    	  		fclose (outfp);
    	  		strcpy (cmd, "/bin/cp ");
    	  		strcat (cmd, TEMPSORTFILE);
    	  		strcat (cmd, " ");
    	  		strcat (cmd, infilename);
    	  		system (cmd);
				unlink(TEMPSORTFILE);
		}
	/*	free(lineptrs);	 */
	}
						
}
    
int
stsrt(const void *ptra, const void *ptrb)
{
 		return(strcmp(*((char **)ptra),*((char **) ptrb))); 
#if 0
		if (*ptra < *ptrb) 
				return(*ptrb);
		else if (*ptra > *ptrb) 
				return(*ptra);
#endif
}
/* 
void 
stsrt(char **strings, int num)
{
	char 		*temp;
	int			top, seek;
        
	for (top = 0; top < num; top++)
		for (seek = top + 1; seek < num; seek++)
			if (strcmp(strings[top], strings[seek]) > 0)
			{
				temp = strings[top];
				strings[top] = strings[seek];
				strings[seek] = temp;
			}
		
}

*/

void
delete_line (Panel_item item)
{
    FILE                  *infp, *outfp;
    char                  readline[BUFSIZ], upperreadline[BUFSIZ],
                          upprmatchline[BUFSIZ]; 
    char                  cmd[40];
    int           		num_lines_read = 0;
    char					old_value[BUFSIZ];
	int						result;

    result = notice_prompt (panel, NULL,
                    NOTICE_NO_BEEPING,         TRUE,
					NOTICE_MESSAGE_STRINGS,
				    "Are you sure you wish to do this ???",
                     	NULL,
					NOTICE_BUTTON_YES,      "Yes, Delete it",
					NOTICE_BUTTON_NO,       "Oops, No",
                     	NULL);
	if (result == NOTICE_NO)
		return;

    strcpy (old_value, (char *)xv_get(word_upd, PANEL_VALUE));
    if (strlen(old_value) > 0) 
    {
        strcpy (infilename, personfilename);
        if ((infp = fopen (infilename, "r")) == NULL)
          {
            xv_set (mess_item, PANEL_VALUE, "Unable to open ", NULL) ;
            xv_set (mess_item2, PANEL_VALUE, "Personal phone book", NULL) ;
            xv_set (mess_item3, PANEL_VALUE, "for update....", NULL) ;
          }
        if ((outfp = fopen (TEMPFILE, "w")) == NULL)
          {
            xv_set (mess_item, PANEL_VALUE, "Unable to open ", NULL) ;
            xv_set (mess_item2, PANEL_VALUE, "Temp file under /usr/tmp", NULL) ;
            xv_set (mess_item3, PANEL_VALUE, "Try again...", NULL) ;
          } 
        else 
          {
            rmtempfileflag = 1;
            get_pan_values (updpanel, item);  
            while(fgets (readline, MAXBUF, infp) != NULL && line[0] != '\n')
              {
                if (strcmp (readline, "\n") != 0)
                  {
                    strcpy (upperreadline, readline);
                    strcpy (upprmatchline, matchline);
                    uppercase (upperreadline);
                    uppercase (upprmatchline);
                    if (strstr (upperreadline, upprmatchline) != NULL)
                      {
      /*                  fprintf (outfp, "\n");
                        fflush (outfp);   */
                      }
                    else 
                      {
                        fprintf (outfp, "%s\n", readline);
                        fflush (outfp);
                      }
                  num_lines_read++;
                  }
              } 
          } 
        fclose (infp);
        fclose (outfp);
        strcpy (cmd, "/bin/cp ");
        strcat (cmd, TEMPFILE);
        strcat (cmd, " ");
        strcat (cmd, infilename);
        system (cmd);
        strcpy (cmd,"/bin/rm ");
        strcat (cmd,TEMPFILE);
        system (cmd); 
        rmtempfileflag = 0;
        sort_file(infilename, num_lines_read);
        clear_pan_values (updpanel, item);
        xv_set(word_upd, PANEL_VALUE, old_value, NULL);
        xv_set(updpanel, PANEL_CARET_ITEM, word_upd, NULL); 
    }
    else
    {
        notice_prompt (updpanel, NULL,
        NOTICE_NO_BEEPING,         TRUE,
        NOTICE_MESSAGE_STRINGS,    "You Must enter something"
        " to search for", "Before You Select this function", NULL,
        NULL);
    }
	
}

void
insert_add (Panel_item item)
{
    FILE                  *fp;
    char                  pathname[BUFSIZ], value[BUFSIZ];
    char					*prompt;
    char                  readline[BUFSIZ];
    int					result;
    int           		num_lines_read = 0;
    int					all_blank = FALSE;

    strcpy (infilename, personfilename);
    if ((fp = fopen (personfilename, "r+")) == NULL) 
      {   
        result = notice_prompt (panel, NULL,
                     	NOTICE_NO_BEEPING,         TRUE,
					NOTICE_MESSAGE_STRINGS,
				    "File does not exist under home directory",
					"             Create it? ",
                     	NULL,
					NOTICE_BUTTON_YES,      "Yes",
					NOTICE_BUTTON_NO,       "No",
                     	NULL);
		switch(result) {
			case NOTICE_YES:
     		   		xv_set (mess_item, PANEL_VALUE, "Creating file ", NULL);
     		   		xv_set (mess_item2, PANEL_VALUE, " ", NULL);
     		   		xv_set (mess_item3, PANEL_VALUE, " ", NULL);
     		   		fp = fopen (personfilename, "a+");
        			fprintf (fp, "%s\n", line);
			   	fclose (fp);
     		   		xv_set (mess_item3, PANEL_VALUE, "Done !" , NULL);
				break;
			case NOTICE_NO:
     		   		xv_set (mess_item, PANEL_VALUE, "NOT creating file ", NULL);
     		   		xv_set (mess_item2, PANEL_VALUE, " ", NULL);
     		   		xv_set (mess_item3, PANEL_VALUE, " ", NULL);
				break;
			case NOTICE_FAILED:
     		   		xv_set (mess_item, PANEL_VALUE, "Unable to pop-up ", NULL);
				break;
			default:
     		   		xv_set (mess_item, PANEL_VALUE, "Unknown choice ", NULL);
				break;
      	}
    }
    else  
    	fclose (fp);
	
	if ((fp = fopen (personfilename, "r+")) == NULL) {   

        notice_prompt (panel, NULL,
        NOTICE_NO_BEEPING,         TRUE,
		NOTICE_MESSAGE_STRINGS,
		"Unable to open personal phone file.",
		"Try pressing to <Add to...> button again",
        NULL,
         NULL);
	}

    else {

		
    	all_blank = get_pan_values (addpanel, item);
    	if (all_blank == FALSE) 
    	{
    
    		fseek (fp, 0, 2);
      		fprintf (fp, "%s\n", line);
    		strcpy (line, " ");
    		fseek (fp, 0, 0);


      		while(fgets (readline, MAXBUF, fp) != NULL && line[0] != '\n')
       			if (strcmp (readline, "\n") != 0)
					num_lines_read++;
    		fclose (fp);
    		sort_file(infilename, num_lines_read);
    		clear_pan_values (addpanel, item);
    		xv_set(addpanel, PANEL_CARET_ITEM, lname_add, NULL);
    	}
    	else
    	{
        	notice_prompt (addpanel, NULL,
        	NOTICE_NO_BEEPING,         TRUE,
        	NOTICE_MESSAGE_STRINGS,    "You Must enter something"
        	" on at least One of the lines", "Before You may Select this function", NULL,
        	NULL);
    	}
	}
}

void
updateexport(void)
{
	strcpy( exportfile, (char *)xv_get(exportfname, PANEL_VALUE));
	xv_set(exportfnameframe, XV_SHOW, FALSE, NULL);
}


void 
get_exportfile(Panel_item item)
{
	if((int) xv_get(item, PANEL_VALUE) == (prcount + 1) ){
		xv_set (exportfnameframe, XV_X, xv_get(frame, XV_X), NULL);
		xv_set (exportfnameframe, XV_Y, xv_get(frame, XV_Y), NULL);
    		xv_set (exportfnameframe, XV_SHOW, TRUE, NULL);
	}
	else
    		xv_set (exportfnameframe, XV_SHOW, FALSE, NULL);
}
			
void
clear_pan_values(Panel panel, Panel_item item)
{
    

    PANEL_EACH_ITEM (panel, item)
	  switch ( (int) xv_get(item, PANEL_CLIENT_DATA) ){

			case search:
				xv_set(item, PANEL_VALUE, "", NULL);
				break;

			case lnameadd: 
			case lnameupd: 

				xv_set(item, PANEL_VALUE, "", NULL);
				break;

			case fnameadd: 
			case fnameupd: 

				xv_set(item, PANEL_VALUE, "", NULL);
				break;
                          
			case phoneadd:
			case phoneupd:

				xv_set(item, PANEL_VALUE, "", NULL);
				break;
                          
			case extadd: 
			case extupd: 

				xv_set(item, PANEL_VALUE, "", NULL);
				break;
                          
			case addradd: 
			case addrupd: 

				xv_set(item, PANEL_VALUE, "", NULL);
				break;

			case noteadd: 
			case noteupd: 

				xv_set(item, PANEL_VALUE, "", NULL);
				break;

			default: 
				break;
	}
        
    PANEL_END_EACH
}

int
get_pan_values(Panel panel, Panel_item item)
{
    
    char                  value[BUFSIZ];
    int                   spflag = 1, handle;
	int					  allBlank = TRUE;

    PANEL_EACH_ITEM (panel, item)
        spflag = 1;
	  switch ( (int) xv_get(item, PANEL_CLIENT_DATA) ){

			case lnameadd: 
			case lnameupd: 

				strcpy (value, (char *)xv_get(item, PANEL_VALUE));    
            		if  (strlen (value) > 0) 
				{ 
               		strcpy (line, value);     
                		strcat (line, "~");
                		spflag = 0;
						allBlank = FALSE;
              	}
            		else
              		spflag = 2;
				break;

			case fnameadd: 
			case fnameupd: 

				strcpy (value, (char *) xv_get (item, PANEL_VALUE));        
              	if  (strlen (value) > 0) { 
                 		strcat (line, value);   
                 		strcat (line, "~");
                 		spflag = 0;
						allBlank = FALSE;
               	}
             		else
                		spflag = 2;
				break;
                          
			case phoneadd:
			case phoneupd:

			 	strcpy (value, (char *) xv_get (item, PANEL_VALUE));  
            		if (strlen (value) > 0) { 
                		strcat (line, value);     
                		strcat (line, "~");
                		spflag = 0;
						allBlank = FALSE;
              		}
            		else
              		spflag = 2;
				break;
                          
			case extadd: 
			case extupd: 

				strcpy (value, (char *) xv_get (item, PANEL_VALUE));  
            		if  (strlen(value) > 0) { 
                		strcat (line, value);     
                		strcat (line, "~|~");
                		spflag = 0;
						allBlank = FALSE;
            		}
            		else
              		spflag = 3;
				break;
                          
			case addradd: 
			case addrupd: 

				strcpy (value, (char *) xv_get (item, PANEL_VALUE));        
              	if  (strlen(value) > 0) { 
                 		strcat (line, value);   
                 		strcat (line, "~|~");
                 		spflag = 0;
						allBlank = FALSE;
               	}
              	else
                		spflag = 3;
				break;

			case noteadd: 
			case noteupd: 

				strcpy (value, (char *) xv_get (item, PANEL_VALUE));        
              	if (strlen (value) > 0) { 
                  		strcat (line, value);   
                  		strcat (line, "~");
                  		spflag = 0;
						allBlank = FALSE;
                }
              	else
                		spflag = 2;
				break;

			default: 
				break;
	}
        
        if (spflag == 2)
          strcat(line, "*~");
        if (spflag == 3)
          strcat(line, "*~|~");
    PANEL_END_EACH
      strcpy (updateline, line);
	  return(allBlank);
}

int
quitprg (Panel_item item)
{
    char                  cmd[40];
    Frame                 framed;

    framed = (Frame) xv_get (item, PANEL_CLIENT_DATA);
    textsw_reset (textsw, 1, 1);
    xv_destroy_safe (framed);
    if (rmtempfileflag)
      {
        strcpy (cmd,"/bin/rm ");
        strcat (cmd, TEMPFILE);
        system(cmd);
      }
}

void
updatecolor(Panel tmppanel, Panel_item item)
{
	

	PANEL_EACH_ITEM (tmppanel, item)
		switch ( (int) xv_get(item, PANEL_ITEM_COLOR) ) {
			case CMS_CONTROL_COLORS + SCREENCOLOR:
			    xv_set(item, PANEL_ITEM_COLOR, CMS_CONTROL_COLORS + SCREENCOLOR, NULL);
			break;

			case CMS_CONTROL_COLORS + DISMISSCOLOR:
			    xv_set(item, PANEL_ITEM_COLOR, CMS_CONTROL_COLORS + DISMISSCOLOR, NULL);
			break;

			case CMS_CONTROL_COLORS + CONFIRMCOLOR:
			    xv_set(item, PANEL_ITEM_COLOR, CMS_CONTROL_COLORS + CONFIRMCOLOR, NULL);
			break;

			case CMS_CONTROL_COLORS + FILECOLOR:
			    xv_set(item, PANEL_ITEM_COLOR, CMS_CONTROL_COLORS + FILECOLOR, NULL);
			break;

			case CMS_CONTROL_COLORS + BASECOLOR:
			    xv_set(item, PANEL_ITEM_COLOR, CMS_CONTROL_COLORS + BASECOLOR, NULL);
			break;
			
			default:
			break;
	}
	PANEL_END_EACH
}

int
quitpanel(Panel_item item)
{
	Frame tmpframe;
	Panel tmppanel;
	

	viewupd = 0;
      viewadd = 0;
	viewprops = 0;
	viewutx = 0;
	tmppanel = (Panel)xv_get(item, PANEL_PARENT_PANEL);
	tmpframe = (Frame)xv_get(tmppanel, XV_OWNER);
	xv_set(tmpframe, FRAME_CMD_PUSHPIN_IN, FALSE, NULL);
	xv_set(tmpframe, XV_SHOW, FALSE, NULL);
    xv_set (exportfnameframe, XV_SHOW, FALSE, NULL);
}
int
props (Panel_item item)
{ 

	  xv_set (propframe, XV_X, xv_get(frame, XV_X), NULL);
	  xv_set (propframe, XV_Y, xv_get(frame, XV_Y), NULL);
        xv_set(propframe, XV_SHOW, TRUE, NULL);
	  xv_set(propframe, FRAME_CMD_PUSHPIN_IN, TRUE, NULL);
       
}
void
propchange_print (Panel_item item)
{
	int i;
	
	if ((int)xv_get(prop_print, PANEL_VALUE) == (prcount + 1)) {
		if (strcmp(exportfile, "") != 0) {
			strcpy (printer, "File");
		}
	}
	else {
		for (i = 0; i <= prcount; i++)
			if (((int)xv_get(item, PANEL_VALUE)) == i){
				strcpy (printer, printlist[i]);
				prflag = i;
			}
	}

}
	
void
propchange_edit (Panel_item item)
{
	int 	choosen;

	choosen = (int) xv_get (item, PANEL_VALUE); 
/* 
	fprintf (stdout, "Choosen:  %d\n", choosen);
	fprintf (stdout, "Last choice was:  %d\n\n", lastchoice);
	fflush (stdout);
*/

	switch (choosen) {

		case 0:
				xv_set(item, PANEL_VALUE, lastchoice, NULL);
				break;

		case 1:	
				if (lastchoice == 5) {
					xv_set(item, PANEL_VALUE, 5, NULL);
                	xv_set (prop_infile, PANEL_READ_ONLY, FALSE, NULL);
					xv_set(prop_infile, PANEL_VALUE_UNDERLINED, TRUE,  NULL); 
					xv_set(prop_infile, PANEL_INACTIVE, FALSE, NULL);
					edflag = 0;
					lastchoice = 5;
				}
			
				if (lastchoice == 9) {
					xv_set(item, PANEL_VALUE, 9, NULL);
                  	xv_set (prop_infile, PANEL_READ_ONLY, TRUE, NULL);
					xv_set(prop_infile, PANEL_VALUE_UNDERLINED, FALSE,  NULL); 
					xv_set(prop_infile, PANEL_VALUE, defaultfilename, NULL);
					xv_set(prop_infile, PANEL_INACTIVE, TRUE, NULL);
					edflag = 1;
					lastchoice = 9;
				}
				break;

		case 2:
				if (lastchoice == 6) {
					xv_set(item, PANEL_VALUE, 6, NULL);
                	xv_set (prop_infile, PANEL_READ_ONLY, FALSE, NULL);
					xv_set(prop_infile, PANEL_VALUE_UNDERLINED, TRUE,  NULL); 
					xv_set(prop_infile, PANEL_INACTIVE, FALSE, NULL);
					edflag = 0;
					lastchoice = 6;
				}
				if (lastchoice == 10) {
					xv_set(item, PANEL_VALUE, 10, NULL);
                  	xv_set (prop_infile, PANEL_READ_ONLY, TRUE, NULL);
					xv_set(prop_infile, PANEL_VALUE_UNDERLINED, FALSE,  NULL); 
					xv_set(prop_infile, PANEL_VALUE, defaultfilename, NULL);
					xv_set(prop_infile, PANEL_INACTIVE, TRUE, NULL);
					edflag = 1;
					lastchoice = 10;
				}

				break;
	
		case 3: 
				if (lastchoice == 1) {
					xv_set(item, PANEL_VALUE, 2, NULL);
                	xv_set(george, PANEL_READ_ONLY, TRUE, NULL);
					xv_set(george, PANEL_VALUE_UNDERLINED, FALSE,  NULL); 
					xv_set(george, PANEL_VALUE, defaultcompname, NULL);
					xv_set(george, PANEL_INACTIVE, TRUE, NULL);
					edflag = 1;
					lastchoice = 2;
				}
				else if (lastchoice == 2) {
					xv_set (item, PANEL_VALUE, 1, NULL);
                	xv_set (george, PANEL_READ_ONLY, FALSE, NULL);
					xv_set(george, PANEL_VALUE_UNDERLINED, TRUE,  NULL); 
					xv_set(george, PANEL_INACTIVE, FALSE, NULL);
					lastchoice = 1;
				}
				
				break;  

		case 4:
				if (lastchoice == 5) {
					xv_set(item, PANEL_VALUE, 5, NULL);
                	xv_set (george, PANEL_READ_ONLY, FALSE, NULL);
					xv_set(george, PANEL_VALUE_UNDERLINED, TRUE,  NULL); 
					xv_set(george, PANEL_INACTIVE, FALSE, NULL);
					edflag = 0;
					lastchoice = 5;
				}
				if (lastchoice == 6) {
					xv_set(item, PANEL_VALUE, 6, NULL);
                	xv_set(george, PANEL_READ_ONLY, TRUE, NULL);
					xv_set(george, PANEL_VALUE_UNDERLINED, FALSE,  NULL); 
					xv_set(george, PANEL_VALUE, defaultcompname, NULL);
					xv_set(george, PANEL_INACTIVE, TRUE, NULL);
					lastchoice = 6;
				}

				break;
	
	
		
		case 5:
                xv_set (prop_infile, PANEL_READ_ONLY, FALSE, NULL);
				xv_set(prop_infile, PANEL_VALUE_UNDERLINED, TRUE,  NULL); 
				xv_set(prop_infile, PANEL_INACTIVE, FALSE, NULL);
				edflag = 0;
	
				
                  xv_set (george, PANEL_READ_ONLY, FALSE, NULL);
				xv_set(george, PANEL_VALUE_UNDERLINED, TRUE,  NULL); 
				xv_set(george, PANEL_INACTIVE, FALSE, NULL);
				lastchoice = 5;
				break;

		case 6:
                  xv_set (george, PANEL_READ_ONLY, TRUE, NULL);
				xv_set(george, PANEL_VALUE_UNDERLINED, FALSE,  NULL); 
				xv_set(george, PANEL_VALUE, defaultcompname, NULL);
				xv_set(george, PANEL_INACTIVE, TRUE, NULL);
				edflag = 1;

                  xv_set (prop_infile, PANEL_READ_ONLY, FALSE, NULL);
				xv_set(prop_infile, PANEL_VALUE_UNDERLINED, TRUE,  NULL); 
				xv_set(prop_infile, PANEL_INACTIVE, FALSE, NULL);
				edflag = 0;
				lastchoice = 6;
				break;
	

		case 7: 

				if (lastchoice == 5) {
					xv_set(item, PANEL_VALUE, 6, NULL);
                	xv_set(george, PANEL_READ_ONLY, TRUE, NULL);
					xv_set(george, PANEL_VALUE_UNDERLINED, FALSE,  NULL); 
					xv_set(george, PANEL_VALUE, defaultcompname, NULL);
					xv_set(george, PANEL_INACTIVE, TRUE, NULL);
					edflag = 1;
					lastchoice = 6;
				}
				else if (lastchoice == 6) {
					xv_set (item, PANEL_VALUE, 5, NULL);
                	xv_set (george, PANEL_READ_ONLY, FALSE, NULL);
					xv_set(george, PANEL_VALUE_UNDERLINED, TRUE,  NULL); 
					xv_set(george, PANEL_INACTIVE, FALSE, NULL);
					lastchoice = 5;
				}
				break;  

		case 8:
				if (lastchoice == 9) {
					xv_set(item, PANEL_VALUE, 9, NULL);
                	xv_set (george, PANEL_READ_ONLY, FALSE, NULL);
					xv_set(george, PANEL_VALUE_UNDERLINED, TRUE,  NULL); 
					xv_set(george, PANEL_INACTIVE, FALSE, NULL);
					edflag = 0;
					lastchoice = 9;
				}
				if (lastchoice == 10) {
					xv_set(item, PANEL_VALUE, 10, NULL);
                	xv_set(george, PANEL_READ_ONLY, TRUE, NULL);
					xv_set(george, PANEL_VALUE_UNDERLINED, FALSE,  NULL); 
					xv_set(george, PANEL_VALUE, defaultcompname, NULL);
					xv_set(george, PANEL_INACTIVE, TRUE, NULL);
					lastchoice = 10;
				}

				break;
	
		case 9:
                  xv_set (prop_infile, PANEL_READ_ONLY, TRUE, NULL);
				xv_set(prop_infile, PANEL_VALUE_UNDERLINED, FALSE,  NULL); 
				xv_set(prop_infile, PANEL_VALUE, defaultfilename, NULL);
				xv_set(prop_infile, PANEL_INACTIVE, TRUE, NULL);
				edflag = 1;

                  xv_set (george, PANEL_READ_ONLY, FALSE, NULL);
				xv_set(george, PANEL_VALUE_UNDERLINED, TRUE,  NULL); 
				xv_set(george, PANEL_INACTIVE, FALSE, NULL);
				lastchoice = 9;
				break;


		case 10:
                xv_set (george, PANEL_READ_ONLY, TRUE, NULL);
				xv_set(george, PANEL_VALUE_UNDERLINED, FALSE,  NULL); 
				xv_set(george, PANEL_VALUE, defaultcompname, NULL);
				xv_set(george, PANEL_INACTIVE, TRUE, NULL);
				edflag = 1;

				
                  xv_set (prop_infile, PANEL_READ_ONLY, TRUE, NULL);
				xv_set(prop_infile, PANEL_VALUE_UNDERLINED, FALSE,  NULL); 
				xv_set(prop_infile, PANEL_VALUE, defaultfilename, NULL);
				xv_set(prop_infile, PANEL_INACTIVE, TRUE, NULL);
				edflag = 1;
				lastchoice = 10;
				break;

		case 11: 
				if (lastchoice == 9) {
					xv_set(item, PANEL_VALUE, 10, NULL);
                	xv_set(george, PANEL_READ_ONLY, TRUE, NULL);
					xv_set(george, PANEL_VALUE_UNDERLINED, FALSE,  NULL); 
					xv_set(george, PANEL_VALUE, defaultcompname, NULL);
					xv_set(george, PANEL_INACTIVE, TRUE, NULL);
					edflag = 1;
					lastchoice =10;
				}
				else if (lastchoice == 10) {
					xv_set (item, PANEL_VALUE, 9, NULL);
                	xv_set (george, PANEL_READ_ONLY, FALSE, NULL);
					xv_set(george, PANEL_VALUE_UNDERLINED, TRUE,  NULL); 
					xv_set(george, PANEL_INACTIVE, FALSE, NULL);
					lastchoice = 9;
				}
				
				break;  

		case 12: 
				if (lastchoice == 4) {
					xv_set(item, PANEL_VALUE, 8, NULL);
                	xv_set(prop_infile, PANEL_READ_ONLY, TRUE, NULL);
					xv_set(prop_infile, PANEL_VALUE_UNDERLINED, FALSE,  NULL); 
					xv_set(prop_infile, PANEL_VALUE, defaultfilename, NULL);
					xv_set(prop_infile, PANEL_INACTIVE, TRUE, NULL);
					lastchoice = 8;
				}
				else if (lastchoice == 8) {
					xv_set (item, PANEL_VALUE, 4, NULL);
                	xv_set (prop_infile, PANEL_READ_ONLY, FALSE, NULL);
					xv_set(prop_infile, PANEL_VALUE_UNDERLINED, TRUE,  NULL); 
					xv_set(prop_infile, PANEL_INACTIVE, FALSE, NULL);
					lastchoice = 4;
				}
				
				break;  

		case 13: 
				if (lastchoice == 5) {
					xv_set(item, PANEL_VALUE, 9, NULL);
                	xv_set(prop_infile, PANEL_READ_ONLY, TRUE, NULL);
					xv_set(prop_infile, PANEL_VALUE_UNDERLINED, FALSE,  NULL); 
					xv_set(prop_infile, PANEL_VALUE, defaultfilename, NULL);
					xv_set(prop_infile, PANEL_INACTIVE, TRUE, NULL);
					edflag = 1;
					lastchoice =9;
				}
				else if (lastchoice == 9) {
					xv_set (item, PANEL_VALUE, 5, NULL);
                	xv_set (prop_infile, PANEL_READ_ONLY, FALSE, NULL);
					xv_set(prop_infile, PANEL_VALUE_UNDERLINED, TRUE,  NULL); 
					xv_set(prop_infile, PANEL_INACTIVE, FALSE, NULL);
					lastchoice = 5;
				}
				
				break;  

		case 14: 

				if (lastchoice == 6) {
					xv_set(item, PANEL_VALUE, 10, NULL);
                	xv_set(prop_infile, PANEL_READ_ONLY, TRUE, NULL);
					xv_set(prop_infile, PANEL_VALUE_UNDERLINED, FALSE,  NULL); 
					xv_set(prop_infile, PANEL_VALUE, defaultfilename, NULL);
					xv_set(prop_infile, PANEL_INACTIVE, TRUE, NULL);
					edflag = 1;
					lastchoice = 10;
				}
				else if (lastchoice == 10) {
					xv_set (item, PANEL_VALUE, 6, NULL);
                	xv_set (prop_infile, PANEL_READ_ONLY, FALSE, NULL);
					xv_set(prop_infile, PANEL_VALUE_UNDERLINED, TRUE,  NULL); 
					xv_set(prop_infile, PANEL_INACTIVE, FALSE, NULL);
					lastchoice = 6;
				}
				
				break;  

				/* xv_set(item, PANEL_VALUE, 8, NULL);
                  xv_set (prop_infile, PANEL_READ_ONLY, TRUE, NULL);
				xv_set(prop_infile, PANEL_VALUE_UNDERLINED, FALSE,  NULL); 
				xv_set(prop_infile, PANEL_VALUE, defaultfilename, NULL);
				xv_set(prop_infile, PANEL_INACTIVE, TRUE, NULL);
				break;  */

		default:
				xv_set(item, PANEL_VALUE, lastchoice, NULL);
      	notice_prompt (proppanel, NULL,
          NOTICE_NO_BEEPING,         TRUE,
          NOTICE_MESSAGE_STRINGS,    "You have picked an Illegal combination of buttons",
		"You may only have either one or two buttons depressed and/or ",
		"may NOT have both the \"custom - filename\" and the \"default - filename\" depressed",
          "Please choose again",
          NULL,
          NULL);
				break;
			
		}

	
}
void
findcolor_base (Panel_item item) 

{

	switch ( (int) xv_get (item, PANEL_VALUE)) {
		case SCREENCOLOR: 
			xv_set(ptred_slider, PANEL_VALUE, colors[0].red, NULL);
			xv_set(ptgreen_slider, PANEL_VALUE, colors[0].green, NULL);
			xv_set(ptblue_slider, PANEL_VALUE, colors[0].blue, NULL);
			flash_color(SCREENCOLOR);
			break;
		case DISMISSCOLOR:
			xv_set(ptred_slider, PANEL_VALUE, colors[1].red, NULL);
			xv_set(ptgreen_slider, PANEL_VALUE, colors[1].green, NULL);
			xv_set(ptblue_slider, PANEL_VALUE, colors[1].blue, NULL);
			flash_color(DISMISSCOLOR);
			break;
		case CONFIRMCOLOR: 
			xv_set(ptred_slider, PANEL_VALUE, colors[2].red, NULL);
			xv_set(ptgreen_slider, PANEL_VALUE, colors[2].green, NULL);
			xv_set(ptblue_slider, PANEL_VALUE, colors[2].blue, NULL);
			flash_color(CONFIRMCOLOR);
			break;
		case FILECOLOR:   
			xv_set(ptred_slider, PANEL_VALUE, colors[3].red, NULL);
			xv_set(ptgreen_slider, PANEL_VALUE, colors[3].green, NULL);
			xv_set(ptblue_slider, PANEL_VALUE, colors[3].blue, NULL);
			flash_color(FILECOLOR);
			break;
		case SUPPORTCOLOR: 
			xv_set(ptred_slider, PANEL_VALUE, colors[4].red, NULL);
			xv_set(ptgreen_slider, PANEL_VALUE, colors[4].green, NULL);
			xv_set(ptblue_slider, PANEL_VALUE, colors[4].blue, NULL);
			flash_color(SUPPORTCOLOR);
			break;
		case BASECOLOR:   
			xv_set(ptred_slider, PANEL_VALUE, colors[5].red, NULL);
			xv_set(ptgreen_slider, PANEL_VALUE, colors[5].green, NULL);
			xv_set(ptblue_slider, PANEL_VALUE, colors[5].blue, NULL);
			flash_color(BASECOLOR);
			break;
	}
	
}


void
alter_color (Panel_item item)
{
	switch ( (int) xv_get (color_choice, PANEL_VALUE)) {
		case SCREENCOLOR: 
			colors[0].red = (int)xv_get(ptred_slider, PANEL_VALUE);
			colors[0].green = (int)xv_get(ptgreen_slider, PANEL_VALUE);
			colors[0].blue = (int)xv_get(ptblue_slider, PANEL_VALUE);
		break;
		case DISMISSCOLOR: 
			colors[1].red = (int)xv_get(ptred_slider, PANEL_VALUE);
			colors[1].green = (int)xv_get(ptgreen_slider, PANEL_VALUE);
			colors[1].blue = (int)xv_get(ptblue_slider, PANEL_VALUE);
		break;
		case CONFIRMCOLOR: 
			colors[2].red = (int)xv_get(ptred_slider, PANEL_VALUE);
			colors[2].green = (int)xv_get(ptgreen_slider, PANEL_VALUE);
			colors[2].blue = (int)xv_get(ptblue_slider, PANEL_VALUE);
		break;
		case FILECOLOR:   
			colors[3].red = (int)xv_get(ptred_slider, PANEL_VALUE);
			colors[3].green = (int)xv_get(ptgreen_slider, PANEL_VALUE);
			colors[3].blue = (int)xv_get(ptblue_slider, PANEL_VALUE);
		break;
		case SUPPORTCOLOR:  
			colors[4].red = (int)xv_get(ptred_slider, PANEL_VALUE);
			colors[4].green = (int)xv_get(ptgreen_slider, PANEL_VALUE);
			colors[4].blue = (int)xv_get(ptblue_slider, PANEL_VALUE);
		break;
		case BASECOLOR:    
			colors[5].red = (int)xv_get(ptred_slider, PANEL_VALUE);
			colors[5].green = (int)xv_get(ptgreen_slider, PANEL_VALUE);
			colors[5].blue = (int)xv_get(ptblue_slider, PANEL_VALUE);
		break;
		default:
		break;
	}
	xv_set(phonetoolcms, CMS_COLORS, &colors, NULL);  
}
				
	
     

void
propchange_color (Panel_item item)
{

	switch ( (int) xv_get (item, PANEL_VALUE)) {

		case 0:	
	
				colorflag = 0;
				xv_set(phonetoolcms, CMS_COLORS, colors, NULL); 
				xv_set(updpanel, WIN_CMS, phonetoolcms, NULL); 
				xv_set(color_choice, PANEL_INACTIVE, colorflag, NULL);
				xv_set(ptred_slider, PANEL_INACTIVE, colorflag, NULL);
				xv_set(ptgreen_slider, PANEL_INACTIVE, colorflag, NULL);
				xv_set(ptblue_slider, PANEL_INACTIVE, colorflag, NULL);
				break;

		case 1:
				colorflag = 1;
				xv_set(phonetoolcms, CMS_COLORS, nocolors, NULL);  
				xv_set(updpanel, WIN_CMS, phonetoolcms, NULL); 
				xv_set(color_choice, PANEL_INACTIVE, colorflag, NULL);
				xv_set(ptred_slider, PANEL_INACTIVE, colorflag, NULL);
				xv_set(ptgreen_slider, PANEL_INACTIVE, colorflag, NULL);
				xv_set(ptblue_slider, PANEL_INACTIVE, colorflag, NULL);
				break;
	

		default:
				break;
			
		}
	
}


unsigned
save_textsw(Panel_item item)
{
textsw_save(updtextsw,  (int)xv_get(updtxtpanel, XV_X), (int)xv_get(updtxtpanel, XV_Y));
}

void
nullfunct(Panel_item item)
{
	Frame subframe;
	Panel panel;

	panel = (Panel)xv_get(item, PANEL_PARENT_PANEL);
	subframe = (Frame)xv_get(panel, XV_OWNER);
	if ((int)xv_get(subframe, FRAME_CMD_PIN_STATE) == FRAME_CMD_PIN_IN) {
		quitpanel(item);
		xv_set(subframe, FRAME_CMD_PIN_STATE, FRAME_CMD_PIN_IN, NULL);
	}
	else {
		quitpanel(item);
		xv_set(subframe, FRAME_CMD_PIN_STATE, FRAME_CMD_PIN_OUT, NULL);
	}
	return;

}

void
print_list(Panel_item item)
{
	char	cmd[20];
	int		result;
	Xv_notice notice;

      notice = notice_prompt (panel, NULL,
					 NOTICE_STATUS, 			&result,
                       NOTICE_NO_BEEPING,         TRUE,
                       NOTICE_MESSAGE_STRINGS,    "Print to: " ,printer , NULL,
					 NOTICE_BUTTON_YES,      "Yes",
					 NOTICE_BUTTON_NO,       "No",
                       NULL);
      
		switch(result) {
			case NOTICE_YES:
        			if (xv_get (textsw, TEXTSW_LENGTH) > 1) {
					if (strcmp(printer, "File") == 0) {
						if (strcmp(exportfile, "") != 0) {    
     				   			xv_set (mess_item, PANEL_VALUE, "Writing file to: ", NULL);
     		   					xv_set (mess_item2, PANEL_VALUE, exportfile, NULL);
							strcpy (cmd, "/bin/cp ");
							strcat (cmd, TEMPFILE);
							strcat (cmd, " ");
							strcat (cmd, exportfile);
							system(cmd);
		   		   			xv_set (mess_item3, PANEL_VALUE, "Done ", NULL);
						
						}
						else{
		   		   			xv_set (mess_item, PANEL_VALUE, "If you wish to write to a ", NULL);
		   		   			xv_set (mess_item2, PANEL_VALUE, "file, you must enter a", NULL);
		   		   			xv_set (mess_item3, PANEL_VALUE, "filename using 'properties' ", NULL);
						}	
					}
					else {
		   				xv_set (mess_item, PANEL_VALUE, "Printing file ", NULL);
				   		xv_set (mess_item2, PANEL_VALUE, " ", NULL);
			   			xv_set (mess_item3, PANEL_VALUE, " ", NULL);
						strcpy(cmd, "lpr -P");
						strcat(cmd, printer);
						strcat(cmd, " ");
						strcat(cmd, TEMPFILE); 
						system(cmd);
			   			xv_set (mess_item3, PANEL_VALUE, "Done !", NULL);
					}
				}
				else{
		   			xv_set (mess_item, PANEL_VALUE, "You must first ", NULL);
		   		   	xv_set (mess_item2, PANEL_VALUE, "search on a string...", NULL);
		   		   	xv_set (mess_item3, PANEL_VALUE, "", NULL);
				}	
			break;
			case NOTICE_NO:
     		   		xv_set (mess_item, PANEL_VALUE, "NOT printing file ", NULL);
     		   		xv_set (mess_item2, PANEL_VALUE, " ", NULL);
     		   		xv_set (mess_item3, PANEL_VALUE, " ", NULL);
				break;
			case NOTICE_FAILED:
     		   		xv_set (mess_item, PANEL_VALUE, "Unable to pop-up ", NULL);
     		   		xv_set (mess_item2, PANEL_VALUE, " ", NULL);
     		   		xv_set (mess_item3, PANEL_VALUE, " ", NULL);
				break;
			default:
     		   		xv_set (mess_item, PANEL_VALUE, "Unknown choice ", NULL);
     		   		xv_set (mess_item2, PANEL_VALUE, " ", NULL);
     		   		xv_set (mess_item3, PANEL_VALUE, " ", NULL);
				break;
      	}
}
void 
apply_funct(Panel_item item, Event *event)
{

	FILE *fp;
	char tempcomp[BUFSIZ], tempin[BUFSIZ];
	char readline[BUFSIZ];

	strcpy(tempin, (char *)xv_get(prop_infile, PANEL_VALUE));
	strcpy(tempcomp, (char *)xv_get(george, PANEL_VALUE));
	strcpy(personfilename, tempin);
	strcpy(compfilename, tempcomp);
	soundexSlide = (int)xv_get(soundex_tol_slide, PANEL_VALUE);
	soundexFlag = (int)xv_get(prop_soundex_toggle, PANEL_VALUE);
	soundexNameFlag = (int)xv_get(soundex_field_toggle, PANEL_VALUE);


	if ((fp = fopen(personfilename, "r+")) != NULL) {
              fgets(readline, MAXBUF, fp);
			if ((strstr(readline, "~|~")) != NULL){
				edflag = 1;
			}
			else
				edflag = 0;
	}

	PANEL_EACH_ITEM (proppanel, item) {
		switch ( (int) xv_get(item, PANEL_CLIENT_DATA) ) {
			case writerc: 
				writerc_file();
				break;
			case printertype:
         		    propchange_print(item);
				break;
			default:
				break;
		}
	}
	PANEL_END_EACH;

}

void
writerc_file (void)
{
	char 			path[BUFSIZ], preffile[BUFSIZ];
	FILE *fp;

	strcpy(path, getenv("HOME"));
    strcpy (preffile, path);
    strcat (preffile, "/.phonerc");

	if ((fp = fopen (preffile, "w")) == NULL) {
      	notice_prompt (panel, NULL,
          NOTICE_NO_BEEPING,         TRUE,
          NOTICE_MESSAGE_STRINGS,    "Unable to open preferance file",
          "Perferance will not be saved...",
          NULL,
          NULL);
    	}
    	else {
      	fprintf (fp, "%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%d~%s~%s~%s~%d~%d~%d~",colorflag, colors[0].red, colors[0].green, colors[0].blue,colors[1].red, colors[1].green, colors[1].blue,colors[2].red, colors[2].green, colors[2].blue,colors[3].red, colors[3].green, colors[3].blue,colors[4].red, colors[4].green, colors[4].blue,colors[5].red, colors[5].green, colors[5].blue, personfilename, compfilename, printer, soundexFlag, soundexSlide, soundexNameFlag);
         	fflush (fp);
         	fclose(fp);
    	} 
}

void
flash_color(int colornum)

{
	int i, j;

	 for (j = 1; j <= 3; j++) {
              colors[colornum].red =     255;
              colors[colornum].green =   255;
              colors[colornum].blue =    255;
              xv_set(phonetoolcms, CMS_COLORS, &colors, NULL);
			XFlush((Display *)xv_get(frame, XV_DISPLAY));
			usleep(60000);

              colors[colornum].red = (int)xv_get(ptred_slider, PANEL_VALUE);
              colors[colornum].green = (int)xv_get(ptgreen_slider, PANEL_VALUE);
              colors[colornum].blue = (int)xv_get(ptblue_slider, PANEL_VALUE);

              xv_set(phonetoolcms, CMS_COLORS, &colors, NULL);
			XFlush((Display *)xv_get(frame, XV_DISPLAY));
			usleep(60000);
       }
}

void   
getinfo(ap)
    Audio_info  *ap;
{
    if (ioctl(Audio_fd, AUDIO_GETINFO, ap) < 0) {
        FPRINTF(stderr, "%s: %s ", prog, T("Cannot access"));
        perror(Audio_ctldev);
        exit(1);
    }  
 
    /* Set the output port to a value we understand */
    ap->play.port = (ap->play.port == AUDIO_SPEAKER ? 0 : 1);
 
}

/* Open the audio control device */

void
audio_open()
{
	/* Construct the control device name by appending "ctl" */
	Audio_ctldev = (char*) malloc(strlen(Audio_device) + 4);
	SPRINTF(Audio_ctldev, "%s%s", Audio_device, "ctl");

	if ((Audio_fd = open(Audio_ctldev, O_RDWR)) < 0) {
		FPRINTF(stderr, "%s: %s ", prog, T("Cannot open"));
		perror(Audio_ctldev);
		exit(1);
	}

	/*
	 * Set the notify flag so that this program (and all others
	 * with this stream open) will be sent a SIGPOLL if changes
	 * are made to the parameters of audio device.
	 */
	 if (Audio_fd != NULL) {
        if (ioctl(Audio_fd, I_SETSIG, S_MSG) < 0) {
            FPRINTF(stderr, "%s: %s ", prog, T("Cannot initialize"));
            perror(Audio_ctldev);
            exit(1);
        }
     }    
	 AUDIO_INITINFO(&Info); 
}

void
get_prime_sel(Panel_item item)
{
	char	*temp_number;

	temp_number = get_sel_item();
	xv_set(dial_number, PANEL_VALUE, temp_number, NULL);

}

char *
convert_number (Panel_item item)

{
    int     i;
    char    *number, *cleannumber;
 	

	number = (char *) xv_get (dial_number, PANEL_VALUE);	
	cleannumber = number;

    for (i = 0; i < (strlen(number)); i++){
		if (isdigit(number[i]) != NULL) {
			cleannumber[i] = number[i];
		}
		else {
			/* if the string number is a "string" convert it to a "number" */
          switch(number[i]) {

              case 'A': case 'a': case 'B': case 'b': case 'C': case 'c':
					cleannumber[i] = '2';
					break;
			
              case 'D': case 'd': case 'E': case 'e': case 'F': case 'f':
					cleannumber[i] = '3';
					break;
			
              case 'G': case 'g': case 'H': case 'h': case 'I': case 'i':
					cleannumber[i] = '4';
					break;
			
              case 'J': case 'j': case 'K': case 'k': case 'L': case 'l':
					cleannumber[i] = '5';
					break;
			
              case 'M': case 'm': case 'N': case 'n': case 'O': case 'o':
					cleannumber[i] = '6';
					break;
			
              case 'P': case 'p': case 'R': case 'r': case 'S': case 's':
					cleannumber[i] = '7';
					break;
			
              case 'T': case 't': case 'U': case 'u': case 'V': case 'v':
					cleannumber[i] = '8';
					break;
			
              case 'W': case 'w': case 'X': case 'x': case 'Y': case 'y':
					cleannumber[i] = '9';
					break;

			  case '-': case '*': case '@':
					break;

			  default:
					cleannumber[i] = ' '; 
					break;
			
			}
		}
	xv_set(dial_number, PANEL_VALUE, cleannumber, NULL);
    }
	return(cleannumber);
}

void
dial_it (Panel_item item)
{
	Audio_info  aif;
    Audio_info  naif;
    int     i, len, volume;
	int		status;
    char    tone[BUFSIZ], num_store[BUFSIZ];
    char    *number;
	int		value;
 	
    audio_open();
    getinfo(&naif);
	volume = (int)xv_get(dial_vol_slider, PANEL_VALUE);
	value = (naif.play.port == AUDIO_SPEAKER ? 1 : 0);
    xv_set(dial_sound_output, PANEL_VALUE, value, NULL);

	(void)convert_number(item); 
	number = (char *) xv_get (dial_number, PANEL_VALUE);	
    strcpy(num_store, number);

	xv_set(frame, FRAME_BUSY, TRUE, NULL);
	xv_set(updtextframe, FRAME_BUSY, TRUE, NULL);
	xv_set(addframe, FRAME_BUSY, TRUE, NULL);
	xv_set(updframe, FRAME_BUSY, TRUE, NULL);
	xv_set(exportfnameframe, FRAME_BUSY, TRUE, NULL);
	xv_set(propframe, FRAME_BUSY, TRUE, NULL);
	xv_set(dialframe, FRAME_BUSY, TRUE, NULL);
	xv_set(helpframe, FRAME_BUSY, TRUE, NULL);
	
	switch (value) {
		case 0:
			xv_set(dial_sound_output, PANEL_CHOICE_IMAGE, 0, play_image, NULL);
            xv_set(dial_sound_output, PANEL_CHOICE_IMAGE, 1, null_image, NULL);
			break;

		case 1:
			xv_set(dial_sound_output, PANEL_CHOICE_IMAGE, 0, null_image, NULL);
            xv_set(dial_sound_output, PANEL_CHOICE_IMAGE, 1, play_image, NULL);
			break;

        default:
            break;
	}

    for (i = 0; i <= (strlen(number)); i++){
		if (isdigit(number[i]) != NULL) {
			usleep(20000);

    		/* 
    		strcpy(tone, "/local/misc/C/pt4/pta/");
			*/
			strcpy(tone, "/usr/demo/SOUND/sounds/"); 
    		strcat (tone, "touchtone.");
    		len = strlen(tone);
    		tone[len] = number[i];
    		tone[len + 1] = '\0';
    		strcat (tone, ".au");
			XFlush((Display *)xv_get(dialframe, XV_DISPLAY));
    		status = play(tone, volume);
            number[i] = '#';
			xv_set(dial_number, PANEL_VALUE, number, NULL);
		}
		else {
			if (number[i] == '-')
				sleep(1);
			if (number[i] == '*')
				sleep(10);
			if (number[i] == '@')
				sleep(60);
		}
	}
	xv_set(dial_number, PANEL_VALUE, num_store, NULL);
	xv_set(frame, FRAME_BUSY, FALSE, NULL);
	xv_set(updtextframe, FRAME_BUSY, FALSE, NULL);
	xv_set(addframe, FRAME_BUSY, FALSE, NULL);
	xv_set(updframe, FRAME_BUSY, FALSE, NULL);
	xv_set(exportfnameframe, FRAME_BUSY, FALSE, NULL);
	xv_set(propframe, FRAME_BUSY, FALSE, NULL);
	xv_set(dialframe, FRAME_BUSY, FALSE, NULL);
	xv_set(helpframe, FRAME_BUSY, FALSE, NULL);

	xv_set(dial_sound_output, PANEL_CHOICE_IMAGE, 0, speaker_image, NULL);  
    xv_set(dial_sound_output, PANEL_CHOICE_IMAGE, 1, head_phone_image, NULL);
	if (Audio_fd != NULL);
        close(Audio_fd);
    audio_open();
	return;
}

void
sound_output(Panel_item item, int value, Event event)
{
    Audio_info  aif;
	int  stat;
	extern int errno;

	value = (int) xv_get(dial_sound_output, PANEL_VALUE); 
	if (value == 0)
		xv_set(dial_vol_slider, PANEL_MAX_VALUE, 25, NULL);
	if (value == 1)
		xv_set(dial_vol_slider, PANEL_MAX_VALUE, 100, NULL);

    AUDIO_INITINFO(&aif);
    aif.play.port = (value == 0 ? AUDIO_SPEAKER : AUDIO_HEADPHONE);
    (void) ioctl(Audio_fd, AUDIO_SETINFO, &aif); 
}

char *
read_rc(void)
{


	char 			path[BUFSIZ], preffile[BUFSIZ];
	char            buff[BUFSIZ], tempbuff[BUFSIZ], rcprinter[BUFSIZ];
	char            readline[BUFSIZ];
	char			*temp;
	FILE			*pffp, *fp;
	int				i;
	char 			*found;

	strcpy(path, getenv("HOME"));
    strcpy (preffile, path);
    strcat (preffile, "/.phonerc");

	/* read in phonerc file properties    */

 
    /* try to open phonerc file */
 
    if ((pffp = fopen (preffile, "r")) != NULL) {
         fgets(buff, BUFSIZ, pffp);
 
    	/* read colors for colormap segment */
 
    	colorflag = atoi(strtok(buff, "~"));
    	for (i = 0; i < NUM_COLORS; i++){
        	colors[i].red = atoi(strtok(NULL, "~"));
        	colors[i].green = atoi(strtok(NULL, "~"));
        	colors[i].blue = atoi(strtok(NULL, "~"));
    	}
 
    	/* read in phonerc filenames properties */
        temp = strtok(NULL, "~");
 
        if (temp != NULL) {
        	if ( *temp != '\n'){
            	strcpy(personfilename, temp);
                temp = strtok(NULL, "~");
            }
            else
                strcpy(rcprinter, "");
         }
         else {
            strcpy(personfilename, defaultfilename);
         }
 
         if (temp != NULL) {
            if ( *temp != '\n'){
                strcpy(compfilename, temp);
                temp = strtok(NULL, "~");
            }
            else
                strcpy(rcprinter, "");
         }
         else {
            strcpy (compfilename, "/home/dbi0/toolset/bin/phones/phone.txt");
         }
 
         if (temp != NULL) {
            if ( *temp != '\n'){
                strcpy(rcprinter, temp);
                temp = strtok(NULL, "~");
            }
            else
                strcpy(rcprinter, "");
         }
         else
            strcpy(rcprinter, "");
 
         if (temp != NULL) {
            if ( *temp != '\n'){
				soundexFlag = atoi(temp);
                temp = strtok(NULL, "~");
            }
            else
				soundexFlag = 1;
         }
         else {
			soundexFlag = 1;
         }
		
		if (soundexFlag)
			soundexOn = FALSE;
		else
			soundexOn = TRUE;

         if (temp != NULL) {
            if ( *temp != '\n'){
				soundexSlide = atoi(temp);
                temp = strtok(NULL, "~");
            }
            else
				soundexSlide = 75;
         }
         else {
			soundexSlide = 75;
         }

         if (temp != NULL) {
            if ( *temp != '\n'){
                soundexNameFlag = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else
                soundexNameFlag = 3;
         }
         else {  
            soundexNameFlag = 3;
         }
         fclose(pffp);
 
    /* check to see if personal filname perference is the same of the default */    /* set edflag to be non default if not..     */
    if ((fp = fopen(personfilename, "r+")) != NULL) {
            fgets(readline, MAXBUF, fp);
            if ((strstr(readline, "~|~")) != NULL){
                edflag = 1;
            }
            else
                edflag = 0;
 }
 }
 
    /* no phonerc file found or unable to open, use all defaults */
    else {
         colors[0].red  = 255;
         colors[0].green = 255;
         colors[0].blue = 255;
         colors[1].red = 205;
         colors[1].green = 92;
         colors[1].blue = 92;
         colors[2].red = 34;
         colors[2].green = 139;
         colors[2].blue = 34;
         colors[3].red = 93;
         colors[3].green = 71;
         colors[3].blue = 139;
         colors[4].red = 139;
         colors[4].green = 62;
         colors[4].blue = 47;
         colors[5].red = 0;
         colors[5].green = 0;
         colors[5].blue = 0;
 
        edflag = 1;
        strcpy(personfilename, defaultfilename);
        strcpy (compfilename, "/home/dbi0/toolset/bin/phones/phone.txt");
		soundexFlag = 1;
		soundexNameFlag = 3;
		soundexFlag = 1;
		soundexSlide = 75;
		
    }	 
	fclose(pffp);
	fclose(fp);
    found = rcprinter;
	return(found);
}

void 
reset_all(void)
{
	int choice = 0;

	read_rc();

	choice = (int)xv_get(color_choice, PANEL_VALUE);

	xv_set(prop_color, PANEL_VALUE, colorflag, NULL); 

	xv_set(color_choice, PANEL_VALUE, colorflag, NULL);
    xv_set(ptred_slider, PANEL_INACTIVE, colorflag, NULL);
    xv_set(ptgreen_slider, PANEL_INACTIVE, colorflag, NULL);
    xv_set(ptblue_slider, PANEL_INACTIVE, colorflag, NULL);
	xv_set(phonetoolcms, CMS_COLORS, &colors, NULL);  

	propchange_color(color_choice);

	xv_set(ptred_slider, PANEL_VALUE, colors[choice].red, NULL);	
	xv_set(ptgreen_slider, PANEL_VALUE, colors[choice].green, NULL);	
	xv_set(ptblue_slider, PANEL_VALUE, colors[choice].blue, NULL);	

    xv_set(prop_print, PANEL_VALUE, prflag, NULL);
	/* getprint_list(rcprinter); */

 
    /* lastchoice = (int) xv_get (prop_editor, PANEL_VALUE); */

	 if ((strcmp(personfilename, defaultfilename) == 0) && (strcmp(compfilename,
defaultcompname) == 0))
        xv_set( prop_editor, PANEL_VALUE, 10, NULL);
 
    else if ((strcmp(personfilename, defaultfilename) != 0) && (strcmp(compfilename, defaultcompname) != 0)) {

        xv_set( prop_editor, PANEL_VALUE, 5, NULL);
        xv_set (george, PANEL_READ_ONLY, FALSE, NULL);
        xv_set(george, PANEL_VALUE_UNDERLINED, TRUE,  NULL);
        xv_set(george, PANEL_INACTIVE, FALSE, NULL);
		xv_set(george, PANEL_VALUE, compfilename, NULL);
 
        xv_set (prop_infile, PANEL_READ_ONLY, FALSE, NULL);
        xv_set(prop_infile, PANEL_VALUE_UNDERLINED, TRUE,  NULL);
        xv_set(prop_infile, PANEL_INACTIVE, FALSE, NULL);
		xv_set(prop_infile, PANEL_VALUE, personfilename, NULL);
    }
 
    else if ((strcmp(personfilename, defaultfilename) == 0) && (strcmp(compfilename, defaultcompname) != 0)) {
 
        xv_set( prop_editor, PANEL_VALUE, 9, NULL);
        xv_set (george, PANEL_READ_ONLY, FALSE, NULL);
        xv_set(george, PANEL_VALUE_UNDERLINED, TRUE,  NULL);
        xv_set(george, PANEL_INACTIVE, FALSE, NULL);
		xv_set(george, PANEL_VALUE, compfilename, NULL);
    }
 
    else if ((strcmp(personfilename, defaultfilename) != 0) && (strcmp(compfilename, defaultcompname) == 0)) {
        xv_set( prop_editor, PANEL_VALUE, 6, NULL);
        xv_set (prop_infile, PANEL_READ_ONLY, FALSE, NULL);
        xv_set(prop_infile, PANEL_VALUE_UNDERLINED, TRUE,  NULL);
        xv_set(prop_infile, PANEL_INACTIVE, FALSE, NULL);
		xv_set(prop_infile, PANEL_VALUE, personfilename, NULL);
 	} 

	propchange_edit(prop_editor);
}

Notify_value
sigpoll_handler(Notify_client client, int sig, Notify_signal_mode when){
    update_panels();
    return (NOTIFY_DONE);
}
 
void
update_panels()
{
    Audio_info  newinfo;
    char        buf[128];
 
    /* Only change settings that changed, to avoid flashing */
#define NEWVAL(X, Y)    {                       \
            if (newinfo.X != Info.X)            \
                xv_set(Y, PANEL_VALUE, newinfo.X, NULL);    \
            }
 
#define Set_Statuslight(item, on)   xv_set((item),          \
                        PANEL_VALUE, ((on) ? 1 : 0), NULL);
 
#define NEWSTATE(X, Y)  {                       \
            if (newinfo.X != Info.X)            \
                Set_Statuslight(Y, newinfo.X);      \
            }
 
#define NEWSTRING(X, Y) {                       \
            if (newinfo.X != Info.X) {          \
                SPRINTF(buf, "%u", newinfo.X);      \
                xv_set(Y, PANEL_LABEL_STRING, buf, NULL); \
            } }
 
    /* Get the current device state */
    getinfo(&newinfo);
 
    /* Update main panel items */
    NEWVAL(play.port, dial_sound_output);
 
 
    /*
     * Pause is tricky, since we may be holding the device open.
     * If 'resume', then release the device, if held.
     */
    /* Update status panel, if it is visible */
 
}  
void
toggle_soundex(Panel_item item)

{
    switch ( (int) xv_get (item, PANEL_VALUE)) {

        case 0:

            xv_set(soundex_tol_slide, PANEL_INACTIVE, FALSE, NULL);
            xv_set(soundex_field_toggle, PANEL_INACTIVE, FALSE, NULL);
			xv_set(frame, FRAME_LABEL, newLabel, NULL);
			soundexOn = TRUE;
            break;

        case 1:
            xv_set(soundex_tol_slide, PANEL_INACTIVE, TRUE, NULL);
            xv_set(soundex_field_toggle, PANEL_INACTIVE, TRUE, NULL);
			xv_set(frame, FRAME_LABEL, oldLabel, NULL);
			soundexOn = FALSE;
            break;


        default:
                break;

    }
}
