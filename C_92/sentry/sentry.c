/*
** File: %M% SCCS %I% - %G%
**
** Author:   Matthew Stemen
**
** Major contributors: David Michel(various things) , Jason Trommetter(sound concepts);
**
** Original concept: Mike Alster 
**
** 
** 
** Created:  04 Jan 1993
**  
**
**
** Purpose: Monitors and reports any and all remote logins to the 
**          host it is run from.  This activity is reported either 
**          using Sound, Images(icons), and Tabular reports or any
**			combination thereof.
*/


/*
** include files
*/

#include "sentry.h" 
#define	 FIRST 	1
#define	 NEXT 	2
#define	 MAIL	1
#define  WHO    2

int		firstTime = TRUE;
int		nextTime = 0;
int		soundmatch = FALSE;
int		getSoundPanelExist = FALSE;

main (int argc, char *argv[])
{
  char line[BUFSIZ];
  int	i;


    icons[0].icon_xhot = 0;  /* tower */
    icons[0].icon_yhot = 0;
    icons[0].icon_fg   = 1;
    icons[0].icon_bg   = 5;

    icons[1].icon_xhot = 0;    /* boat */
    icons[1].icon_yhot = 0;
    icons[1].icon_fg   = 1;
    icons[1].icon_bg   = 7;

    icons[2].icon_xhot = 10;  /* dog */
    icons[2].icon_yhot = 0;
    icons[2].icon_fg   = 1;
    icons[2].icon_bg   = 3;

    icons[3].icon_xhot = 17;  /* trek */
    icons[3].icon_yhot = 0;
    icons[3].icon_fg   = 1;
    icons[3].icon_bg   = 0;

    icons[4].icon_xhot = 17;  /* trek next gen.*/
    icons[4].icon_yhot = 0;
    icons[4].icon_fg   = 1;
    icons[4].icon_bg   = 0;

    icons[5].icon_xhot = 0;  /* tank */
    icons[5].icon_yhot = 0;
    icons[5].icon_fg   = 1;
    icons[5].icon_bg   = 4;

    icons[6].icon_xhot = 0;  /* defcon */
    icons[6].icon_yhot = 0;
    icons[6].icon_fg   = 2;
    icons[6].icon_bg   = 6;

  xv_init(XV_INIT_ARGC_PTR_ARGV, &argc, argv, NULL);


  frame = (Frame) xv_create (XV_NULL, FRAME,
		FRAME_SHOW_FOOTER, 		TRUE,
		FRAME_INHERIT_COLORS, 	TRUE, 
       	FRAME_LABEL,       		"Sentry - V7.1",
        NULL);

  screen = (Xv_screen)xv_get(frame, XV_SCREEN); 

  sentrycms = (Cms) xv_create(screen, CMS,
		CMS_CONTROL_CMS,       TRUE,
		CMS_COLOR_COUNT,	CMS_CONTROL_COLORS + 11,
		CMS_TYPE,			XV_STATIC_CMS,
		CMS_SIZE,			CMS_CONTROL_COLORS + 11,
		CMS_NAMED_COLORS,	"seashell2", "black", "red4", "wheat1", "green3", "gray63", "yellow", "tan", "red3", "purple", NULL,
		NULL);

    



  /* gethostname(hostname, 20); */
  strcpy(authuser, getenv("USER"));
  strcpy(homepath, getenv("HOME"));  

  strcpy(defaultlog, homepath);
  strcat(defaultlog, "/.sentry.txt");   

  strcpy(RcFile, homepath);
  strcat(RcFile, "/.sentryrc"); 

  strcpy (dlogfile, homepath);
  strcat (dlogfile, "/.sentryD.txt");

  /* get .sentryrc options */
	
  if ((infp = fopen ( RcFile, "r")) == NULL){
	warn_slide_value = 30;
	mail_slide_value = 30;
	noWarnSoundFlag = 1;
	noMailSoundFlag = 1;
	norecordflag = 1;
	nosiegeflag = 0;
	volume_value = 5;
	strcpy(icons[0].warSound[0], " ");
	strcpy(icons[0].warSound[1], " ");
	strcpy(icons[0].warSound[2], " ");
	strcpy(icons[0].warSound[3], " ");
	strcpy(icons[0].warSound[4], " ");
	strcpy(icons[0].warSound[5], " ");
    strcpy(icons[1].warSound[0], " ");
    strcpy(icons[1].warSound[1], " ");
    strcpy(icons[1].warSound[2], " ");
    strcpy(icons[1].warSound[3], " ");
    strcpy(icons[1].warSound[4], " ");
    strcpy(icons[1].warSound[5], " ");
    strcpy(icons[2].warSound[0], " ");
    strcpy(icons[2].warSound[1], " ");
    strcpy(icons[2].warSound[2], " ");
    strcpy(icons[2].warSound[3], " ");
    strcpy(icons[2].warSound[4], " ");
    strcpy(icons[2].warSound[5], " ");
    strcpy(icons[3].warSound[0], " ");
    strcpy(icons[3].warSound[1], " ");
    strcpy(icons[3].warSound[2], " ");
    strcpy(icons[3].warSound[3], " ");
    strcpy(icons[3].warSound[4], " ");
    strcpy(icons[3].warSound[5], " ");
    strcpy(icons[4].warSound[0], " ");
    strcpy(icons[4].warSound[1], " ");
    strcpy(icons[4].warSound[2], " ");
    strcpy(icons[4].warSound[3], " ");
    strcpy(icons[4].warSound[4], " ");
    strcpy(icons[4].warSound[5], " ");
    strcpy(icons[5].warSound[0], " ");
    strcpy(icons[5].warSound[1], " ");
    strcpy(icons[5].warSound[2], " ");
    strcpy(icons[5].warSound[3], " ");
    strcpy(icons[5].warSound[4], " ");
    strcpy(icons[5].warSound[5], " ");
    strcpy(icons[6].warSound[0], " ");
    strcpy(icons[6].warSound[1], " ");
    strcpy(icons[6].warSound[2], " ");
    strcpy(icons[6].warSound[3], " ");
    strcpy(icons[6].warSound[4], " ");
    strcpy(icons[6].warSound[5], " ");

	strcpy(soundPath, "/usr/demo/SOUND/sounds/"); 
	strcpy(rlogfile, defaultlog);
    strcpy(authuserlist, authuser);
	logflag = 1;
	monflag = 1;
	whoFlag = FALSE;
	mailFlag = FALSE;
    strcpy(mfilename, "/usr/spool/mail/");
	strcat(mfilename, authuser);
	strcpy(MailSound, "");
  }
  else {
 	fgets(line, BUFSIZ, infp);
	warn_slide_value = atoi(strtok(line, "~"));
	noWarnSoundFlag = atoi(strtok(NULL, "~"));
	norecordflag = atoi(strtok(NULL, "~"));
	nosiegeflag = atoi(strtok(NULL, "~"));
	volume_value = atoi(strtok(NULL, "~"));
	temp = strtok(NULL, "~");

	for (i = 0; i <= 6 ; i++) {
	    if (temp != NULL) {
	        if ( *temp != '\n'){
	            strcpy(icons[i].warSound[0], temp);
	            temp = strtok(NULL, "~");
	        }
	        else                                                
	            strcpy(icons[i].warSound[0], " ");
	    }
	    else {
	        strcpy(icons[i].warSound[0], " ");
	    }
	
	    if (temp != NULL) {
	        if ( *temp != '\n'){
	            strcpy(icons[i].warSound[1], temp);
	            temp = strtok(NULL, "~");
	        }
	        else       
	            strcpy(icons[i].warSound[1], " ");
	    }
	    else {
	        strcpy(icons[i].warSound[1], " ");
	    }    
	    if (temp != NULL) {
	        if ( *temp != '\n'){
	            strcpy(icons[i].warSound[2], temp);
	            temp = strtok(NULL, "~");
	        }
	        else       
	            strcpy(icons[i].warSound[2], " ");
	    }
	    else {
	        strcpy(icons[i].warSound[2], " ");
	    }    
	    if (temp != NULL) {
	        if ( *temp != '\n'){
	            strcpy(icons[i].warSound[3], temp);
	            temp = strtok(NULL, "~");
	        }
	        else       
	            strcpy(icons[i].warSound[3], " ");
	    }
	    else {
	        strcpy(icons[i].warSound[3], " ");
	    }    
	    if (temp != NULL) {
	        if ( *temp != '\n'){
	            strcpy(icons[i].warSound[4], temp);
	            temp = strtok(NULL, "~");
	        }
	        else       
	            strcpy(icons[i].warSound[4], " ");
	    }
	    else {
	        strcpy(icons[i].warSound[4], " ");
	    }    
	    if (temp != NULL) {
	        if ( *temp != '\n'){
	            strcpy(icons[i].warSound[5], temp);
	            temp = strtok(NULL, "~");
	        }
	        else       
	            strcpy(icons[i].warSound[5], " ");
	    }
	    else {
	        strcpy(icons[i].warSound[5], " ");
	    }    
	}

    if (temp != NULL) { 
        if ( *temp != '\n'){ 
            strcpy(soundPath, temp); 
            temp = strtok(NULL, "~"); 
        } 
        else                                                 
            strcpy(soundPath, "/usr/demo/SOUND/sounds/"); 
    } 
    else { 
        strcpy(soundPath, "/usr/demo/SOUND/sounds/"); 
    } 
 
    if (temp != NULL) {
        if ( *temp != '\n'){
            strcpy(rlogfile, temp);
            temp = strtok(NULL, "~");
        }
        else
            strcpy(rlogfile, "");
    }
    else {
        strcpy(rlogfile, "");
    }
 

    if (temp != NULL) {
        if ( *temp != '\n'){
            strcpy(authuserlist, temp);
            temp = strtok(NULL, "~");
        }
        else
            strcpy(authuserlist, "");
    }
    else {
        strcpy(authuserlist, authuser);
    }

    if (temp != NULL) {
        if ( *temp != '\n')
			iconflag =  atoi(temp);
		else 
			iconflag = 0;
	}
	else
		iconflag = 0;
		
    temp = strtok(NULL, "~");

    if (temp != NULL) {
        if ( *temp != '\n') {
			strcpy(rcprinter, temp);
    		temp = strtok(NULL, "~");
		}
		else 
			strcpy(rcprinter, "");
	}
	else
		strcpy(rcprinter, "");

		
    if (temp != NULL) {  
        if ( *temp != '\n') {
			soflag =  atoi(temp);
    		temp = strtok(NULL, "~");
		}
        else 
            soflag = 0;
    }
    else 
        soflag = 0;
 
    if (temp != NULL) {
        if ( *temp != '\n'){
            monflag =  atoi(temp);
            temp = strtok(NULL, "~");
		}
        else
            monflag = 1;
    }
    else 
        monflag = 1;

    if (temp != NULL) {
        if ( *temp != '\n') {
            strcpy(mfilename, temp);
            temp = strtok(NULL, "~");
        }
        else {
            strcpy(mfilename, "/usr/spool/mail/");
			strcat(mfilename, authuser);
		}
    }
    else {
        strcpy(mfilename, "/usr/spool/mail/");
		strcat(mfilename, authuser);
	}

    if (temp != NULL) {
        if ( *temp != '\n') {
            strcpy(MailSound, temp);
            temp = strtok(NULL, "~");
        }
        else {   
            strcpy(MailSound, "");
        }
    }    
    else {
        strcpy(MailSound, "");
    }
    if (temp != NULL) {
        if ( *temp != '\n'){
            mail_slide_value =  atoi(temp);
            temp = strtok(NULL, "~");
        }
        else
            mail_slide_value = 30;
    }
    else 
        mail_slide_value = 30;

	if ((strcmp(rlogfile, defaultlog)) == 0)
		logflag = 1;
	else
		logflag = 0;

	norecordflag = 0;
  }
    if (temp != NULL) {
        if ( *temp != '\n'){
            noMailSoundFlag =  atoi(temp);
            temp = strtok(NULL, "~");
        }
        else
            noMailSoundFlag = 1;
    }
    else
        noMailSoundFlag = 1;
	
    if (temp != NULL) {  
        if ( *temp != '\n'){
            whoFlag =  atoi(temp);
            temp = strtok(NULL, "~");
        }
        else
            whoFlag = FALSE; 
    }
    else 
        whoFlag = FALSE;

    if (temp != NULL) {  
        if ( *temp != '\n'){
            mailFlag =  atoi(temp);
            temp = strtok(NULL, "~");
        }
        else
            mailFlag = FALSE; 
    }
    else 
        mailFlag = FALSE;
    if (temp != NULL) {  
        if ( *temp != '\n'){
            strcpy(subjectLine, temp);
        }
        else
            strcpy(subjectLine, "");
    }
    else 
            strcpy(subjectLine, "");

  if (noMailSoundFlag == 0 || noWarnSoundFlag == 0)
	nosoundflag = 0;

  create_all();
  getprint_list(rcprinter);
  xv_set(prop_print, PANEL_VALUE, prflag, NULL);
  set_iconset(); 

  xv_set(panel, WIN_CURSOR, generic_cursor, NULL);
  xv_set(proppanel, WIN_CURSOR, generic_cursor, NULL);
  xv_set(cmdpanel, WIN_CURSOR, generic_cursor, NULL);


  warntimer.it_value.tv_sec = 1;
  warntimer.it_interval.tv_sec = warn_slide_value;

  mailtimer.it_value.tv_sec = 1;
  mailtimer.it_interval.tv_sec = mail_slide_value;

  notify_set_itimer_func(frame, mon_toggle1, ITIMER_REAL, &warntimer, NULL); 

  notify_set_itimer_func(panel, mon_toggle2, ITIMER_REAL, &mailtimer, NULL); 

  notify_set_signal_func(frame, (Notify_func) sigpoll_handler, SIGPOLL, NOTIFY_SYNC);
  audio_open();
  update_panels();

    
  xv_main_loop(frame);
}
void
watch_mail(void) 
{ 
	static	off_t 	old_size;
	struct	stat	statbuff;
	static  char	oldFilename[BUFSIZ];
	static  int		lastMailCount;
	static	int		sameItem;
	static	time_t	lastModTime;
	static	int		firstTime;
	      	time_t	thisModTime;
			char	footerStrLeft[BUFSIZ];
			char	footerStrRight[BUFSIZ];
	        int		mailCount = 0;
	        int		mailRead = 0;
	        int		mailUnRead = 0;
			int		subjectFlag = FALSE;
			int		newSubjectFound = FALSE;
			int		statusFlag = FALSE;
			char 	buff[BUFSIZ];
			off_t	current_size;
			char	filename[BUFSIZ];
			int		volvalue, len, swvalue;
			FILE	*mailfp;
			char	cmd[BUFSIZ];
			char 	tmpFileName[BUFSIZ];
			char	subjectStr[BUFSIZ];
			char	*psubjectStr;


		strcpy(tmpFileName, "/tmp/sentryMailTmp");

		psubjectStr = (char *)xv_get(prop_subject_line, PANEL_VALUE);
		
		if (psubjectStr != NULL) 
		{
			strcpy(subjectStr, psubjectStr);
			strcpy(subjectLine, subjectStr);
		}
		else 
		{
			strcpy(subjectStr, "XXX_OOO_XXX");
		}
			
		strcpy (filename, (char *)xv_get(prop_mfilename, PANEL_VALUE));

		if (strcmp (filename, oldFilename) != 0) {
			firstTime = TRUE;
			old_size = 0;	
			lastModTime = 0;
		}

		lstat(filename, &statbuff);
        if ((statbuff.st_mode & S_IFMT) != S_IFREG)
        {
        	notice_prompt (panel, NULL,
            NOTICE_MESSAGE_STRINGS,    "Unable to find: ", filename, "check the path", NULL,
        	NULL);
			return;
        }
		current_size = statbuff.st_size;
		thisModTime = statbuff.st_mtime;
		
		if (current_size == 0) {
			old_size = 0;
		}

		if (old_size == 0){
			old_size = statbuff.st_size;
			strcpy(oldFilename, filename);
		}

		if (lastModTime != thisModTime || firstTime) {
#ifdef DEBUG
				printf("Polling... \n\n");
				fflush(stdout);
#endif
  			firstTime = FALSE; 
			strcpy (cmd, "cp ");
			strcat (cmd, filename);
			strcat (cmd, " ");
			strcat (cmd, tmpFileName);
			system(cmd);
	
	        if ((mailfp = fopen (tmpFileName, "r")) != NULL){
				while(fscanf(mailfp, "%s", buff) >= 1) {

					if (strstr (subjectStr, buff) != NULL)
					{
						subjectFlag = TRUE;
					}
					/* 
					if (strcmp(buff, "From:") == 0 ) {
						mailCount++;
						sameItem = 0;
					}
					if (strcmp(buff, ">From") == 0  && sameItem == 0) {
						mailCount--;
						sameItem = 1;
					}
					*/
					if (strcmp(buff, "Message-Id:") == 0 ) 
						mailCount++;
							
					if (strcmp(buff, "Status:") == 0)
						statusFlag = TRUE;
	
					else {
						if (statusFlag){
							if (strcmp(buff, "RO") == 0) {
								mailRead++;
								subjectFlag = FALSE;
							}
							else {
								statusFlag = FALSE;
							/* 	subjectFlag = FALSE;  */ 
							}
						}
					}
				}
						
				mailUnRead = mailCount - mailRead;
	        	fclose(mailfp);
				unlink(tmpFileName);
	        }
			else {
				sprintf(footerStrLeft, "Unable to open %s", tmpFileName);
				sprintf(footerStrRight, "");
			}
			
	
			sprintf(footerStrLeft, "Total Mail Found: %d", mailCount);
			sprintf(footerStrRight, "Read: %d          Unread: %d", mailRead, mailUnRead );
			xv_set(frame, FRAME_LEFT_FOOTER, footerStrLeft, NULL);
			xv_set(frame, FRAME_RIGHT_FOOTER, footerStrRight, NULL);
	
			volvalue = ((int) xv_get (prop_volume, PANEL_VALUE));
	    	strcpy(MailSound, (char *)xv_get(prop_soundPath, PANEL_VALUE));
	    	len = strlen(MailSound);
	    	if (MailSound[len - 1] != '/')
	    		strcat(MailSound, "/");
	    	strcat(MailSound, (char *)xv_get(prop_mailSound, PANEL_VALUE));
	
			if (mailUnRead > 0 && lastMailCount < mailCount) {
		  		if  (! noMailSoundFlag) 
	      			callplay (MailSound, volume_value, TRUE); 
				old_size = current_size;
			}
			else 
				subjectFlag = FALSE;

			swvalue = (int)xv_get(icon_swapper, PANEL_VALUE);
			if (mailUnRead > 0 ) {
				if (subjectFlag) {
  					xv_set(sentryicon, WIN_FOREGROUND_COLOR, CMS_CONTROL_COLORS + 1, NULL);
  					xv_set(sentryicon, WIN_BACKGROUND_COLOR, CMS_CONTROL_COLORS + 9, NULL);
				}
				else 
				{
  					xv_set(sentryicon, WIN_FOREGROUND_COLOR, CMS_CONTROL_COLORS + 2, NULL);
  					xv_set(sentryicon, WIN_BACKGROUND_COLOR, CMS_CONTROL_COLORS + 8, NULL);
				}
			}
			else {
  				xv_set(sentryicon, WIN_FOREGROUND_COLOR, CMS_CONTROL_COLORS + icons[swvalue].icon_fg, NULL);
  				xv_set(sentryicon, WIN_BACKGROUND_COLOR, CMS_CONTROL_COLORS + icons[swvalue].icon_bg, NULL);
			}
			
		lastMailCount = mailCount;
		}
	
		lastModTime = thisModTime;
		
}

void
watch_who(void) 
{ 
  static				intruderArrayIndex;
  static 	struct      users intruders[100];
  time_t				t;
  char                  intruderstring[MAXSTRINGSIZE], date[BUFSIZ];    
  char					footerMessage[BUFSIZ];
  FILE					*logfp, *utmpfp;
  int					i, j, k, oldintflag = 0, stillthere = 0;
  int					siegecount = 0, newArrayIndex = 0, len = 0;
  struct    stat 		statbuff;
  int					swapval = 0;
  int					unique = TRUE;

  struct utmp ulist;


  if (firstTime) {
	sleep(1); 
	firstTime = FALSE;
  }

  if ((utmpfp = fopen("/etc/utmp", "r")) == NULL)
      notice_prompt (panel, NULL,
                     NOTICE_NO_BEEPING,         TRUE,
                     NOTICE_MESSAGE_STRINGS,  "Cannot open /etc/utmp",   
                     NULL);
			
  if (! norecordflag ) { 
        if (( logfp = fopen (rlogfile, "a+")) == NULL)   {
            notice_prompt (panel, NULL,
            NOTICE_NO_BEEPING,         TRUE,
            NOTICE_MESSAGE_STRINGS,  "Cannot open ",  
            rlogfile, "for update", NULL,
            NULL);
        }
  }

  strcpy (intruderstring,"");   

/* see whos out there */

  newArrayIndex = intruderArrayIndex; /* hold the old array size */

  if (utmpfp) {
	  while ((fread((char *)&ulist, sizeof(ulist), 1, utmpfp)) != 0) {  /* read /etc/utmp into a utmp struct */
		unique = TRUE; /* reset unique */
		if (intruderArrayIndex <= 99 ) { /* do not want to blow out our array */
			if ((strcmp(ulist.ut_name, "")) != 0) { /* utmp entry not blank */
				if ((strstr(authuserlist, ulist.ut_name) == NULL)) { /* not authorized */
					siegecount++; /* we want to see a user with multiple tty's */
					swflag = 0;  /* show we have @ least one intruder */
	
					/* build intruder string */
	            	strcat (intruderstring,ulist.ut_name);
	            	strcat (intruderstring,"@");
	            	strcat (intruderstring,ulist.ut_host);
	            	strcat (intruderstring," ");
	
#if DEGBUG
						fprintf(stdout, "string: %s int. newArrayIndex: %d\n", intruderstring, intruderArrayIndex);
						fflush(stdout);
#endif
	
					/* walk our intruder array to see if uniq and if old ones are still there*/
					for (i = 0; i <= intruderArrayIndex; i++){ 
						if (strcmp(intruders[i].name, ulist.ut_name) == 0) {
							intruders[i].found = TRUE; /* already in the array */
							unique = FALSE;
						}
					}
	
					if (unique) { /* if the intruder is not in the array */
						t = time(NULL);
						strcpy(date, ctime(&t));
						strcpy(intruders[newArrayIndex].name, ulist.ut_name);
						strcpy(intruders[newArrayIndex].host,  ulist.ut_host);
						intruders[newArrayIndex].found = TRUE;
						intruders[newArrayIndex].unauthorized = TRUE;
						if (logfp != NULL)
							fprintf (logfp, "-> User %s@%s logged into %s  %s" ,ulist.ut_name , ulist.ut_host,hostname, date);
						newArrayIndex++; /* increment array to hold the next user */
					}
				}   
				else { /* they are newly authorized */
					for (i = 0; i < intruderArrayIndex; i++) {
						if (strcmp(intruders[i].name, ulist.ut_name) == 0) {
							if (intruders[i].unauthorized == TRUE) {
								t = time(NULL);
								strcpy(date, ctime(&t));
								if (logfp != NULL)
									fprintf (logfp, "*> User %s@%s was authorized %s" ,intruders[i].name, intruders[i].host, date);
								intruders[i].found = TRUE;
								intruders[i].unauthorized = FALSE;
							}
						}
					}
				}
			} /* end of blank utmp entry test */
		} /* end of if array blow out test */  
		intruderArrayIndex = newArrayIndex;
	  } /* end of while */
	}
	fclose(utmpfp);


	for (i = 0; i < intruderArrayIndex; i++){ 
		if (intruders[i].found == FALSE) {
			if (i == intruderArrayIndex - 1) {
				/* show they left */
				t = time(NULL);
				strcpy(date, ctime(&t));
				if (intruders[i].unauthorized == TRUE )
					if (logfp != NULL)
						fprintf (logfp, "<- User %s@%s logged out of %s %s" ,intruders[i].name, intruders[i].host, hostname, date);
				if (intruders[i].unauthorized == FALSE )
					if (logfp != NULL)
						fprintf (logfp, "<* User %s@%s logged out of %s %s" ,intruders[i].name, intruders[i].host, hostname, date);
				strcpy(intruders[i].name,  "");
				strcpy(intruders[i].host,  "");
				intruders[i].unauthorized = FALSE;
    			intruderArrayIndex--;
			}
			else {
				/* remove them from the list and shuffle everybody back one */
				/* show they left */
				t = time(NULL);
				strcpy(date, ctime(&t));
				if (intruders[i].unauthorized == TRUE )
					if (logfp != NULL)
						fprintf (logfp, "<- User %s@%s logged out of %s %s" ,intruders[i].name, intruders[i].host, hostname, date);
				if (intruders[i].unauthorized == FALSE )
					if (logfp != NULL)
						fprintf (logfp, "<* User %s@%s logged out of %s %s" ,intruders[i].name, intruders[i].host, hostname, date);
				for (j = i ; j < intruderArrayIndex; j++) { 
					strcpy(intruders[j].name,  intruders[j + 1].name);
					strcpy(intruders[j].host,  intruders[j + 1].host);
					intruders[j].found = intruders[j + 1].found;
					intruders[j].unauthorized = intruders[j + 1].unauthorized;
				}
    			intruderArrayIndex--;
			}
				
		}
		else
			intruders[i].found = FALSE;
	}

			

  switch (swflag)
    {
    case 0:        
      /* toggle icon when intruders present */
	  if (! nosiegeflag){
	  	switch (siegecount)
	  	{
			case 1:
				if (siegeflag == 0) {
					siegeflag = 1;
      				xv_set (intruder,
       	     		PANEL_VALUE,          intruderstring,
       	       		NULL);
      				xv_set (sentry_state,
       	       		PANEL_LABEL_IMAGE,    gen_s1,
       	       		NULL);
      				xv_set (sentryicon,	
       	       		ICON_IMAGE,           gen_s1,
       	       		ICON_MASK_IMAGE,      genm_s1,
       	       		ICON_TRANSPARENT,	    TRUE,
       	       		NULL);
				}
				else {
					siegeflag = 0;
      				xv_set (intruder,
       	     		PANEL_VALUE,          intruderstring,
       	       		NULL);
      				xv_set (sentry_state,
       	       		PANEL_LABEL_IMAGE,    gen_s1p,
       	       		NULL);
      				xv_set (sentryicon,	
       	       		ICON_IMAGE,           gen_s1p,
       	       		ICON_MASK_IMAGE,      genm_s1p,
       	       		ICON_TRANSPARENT,	    TRUE,
       	       		NULL);
				}
				break;

			case 2:
				if (siegeflag == 0) {
					siegeflag = 1;
      				xv_set (intruder,
       	     		PANEL_VALUE,          intruderstring,
       	       		NULL);
      				xv_set (sentry_state,
       	       		PANEL_LABEL_IMAGE,    gen_s2,
       	       		NULL);
      				xv_set (sentryicon,	
       	       		ICON_IMAGE,           gen_s2,
       	       		ICON_MASK_IMAGE,      genm_s2,
       	       		ICON_TRANSPARENT,	    TRUE,
       	       		NULL);
				}
				else {
					siegeflag = 0;
      				xv_set (intruder,
       	     		PANEL_VALUE,          intruderstring,
       	       		NULL);
      				xv_set (sentry_state,
       	       		PANEL_LABEL_IMAGE,    gen_s2p,
       	       		NULL);
      				xv_set (sentryicon,	
       	       		ICON_IMAGE,           gen_s2p,
       	       		ICON_MASK_IMAGE,      genm_s2p,
       	       		ICON_TRANSPARENT,	    TRUE,
       	       		NULL);
				}
				break;

			case 3:
				if (siegeflag == 0) {
					siegeflag = 1;
      				xv_set (intruder,
       	     		PANEL_VALUE,          intruderstring,
       	       		NULL);
      				xv_set (sentry_state,
       	       		PANEL_LABEL_IMAGE,    gen_s3,
       	       		NULL);
      				xv_set (sentryicon,	
       	       		ICON_IMAGE,           gen_s3,
       	       		ICON_MASK_IMAGE,      genm_s3,
       	       		ICON_TRANSPARENT,	    TRUE,
       	       		NULL);
				}
				else {
					siegeflag = 0;
      				xv_set (intruder,
       	     		PANEL_VALUE,          intruderstring,
       	       		NULL);
      				xv_set (sentry_state,
       	       		PANEL_LABEL_IMAGE,    gen_s3p,
       	       		NULL);
      				xv_set (sentryicon,	
       	       		ICON_IMAGE,           gen_s3p,
       	       		ICON_MASK_IMAGE,      genm_s3p,
       	       		ICON_TRANSPARENT,	    TRUE,
       	       		NULL);
				}
				break;


			case 4:
				if (siegeflag == 0) {
					siegeflag = 1;
      				xv_set (intruder,
       	     		PANEL_VALUE,          intruderstring,
       	       		NULL);
      				xv_set (sentry_state,
       	       		PANEL_LABEL_IMAGE,    gen_s4,
       	       		NULL);
      				xv_set (sentryicon,	
       	       		ICON_IMAGE,           gen_s4,
       	       		ICON_MASK_IMAGE,      genm_s4,
       	       		ICON_TRANSPARENT,	    TRUE,
       	       		NULL);
				}
				else {
					siegeflag = 0;
      				xv_set (intruder,
       	     		PANEL_VALUE,          intruderstring,
       	       		NULL);
      				xv_set (sentry_state,
       	       		PANEL_LABEL_IMAGE,    gen_s4p,
       	       		NULL);
      				xv_set (sentryicon,	
       	       		ICON_IMAGE,           gen_s4p,
       	       		ICON_MASK_IMAGE,      genm_s4p,
       	       		ICON_TRANSPARENT,	    TRUE,
       	       		NULL);
				}
				break;


			case 5:
				if (siegeflag == 0) {
					siegeflag = 1;
      				xv_set (intruder,
       	     		PANEL_VALUE,          intruderstring,
       	       		NULL);
      				xv_set (sentry_state,
       	       		PANEL_LABEL_IMAGE,    gen_s5,
       	       		NULL);
      				xv_set (sentryicon,	
       	       		ICON_IMAGE,           gen_s5,
       	       		ICON_MASK_IMAGE,      genm_s5,
       	       		ICON_TRANSPARENT,	    TRUE,
       	       		NULL);
				}
				else {
					siegeflag = 0;
      				xv_set (intruder,
       	     		PANEL_VALUE,          intruderstring,
       	       		NULL);
      				xv_set (sentry_state,
       	       		PANEL_LABEL_IMAGE,    gen_s5p,
       	       		NULL);
      				xv_set (sentryicon,	
       	       		ICON_IMAGE,           gen_s5p,
       	       		ICON_MASK_IMAGE,      genm_s5p,
       	       		ICON_TRANSPARENT,	    TRUE,
       	       		NULL);
				}
				break;



			case 6:
				if (siegeflag == 0) {
					siegeflag = 1;
      				xv_set (intruder,
       	     		PANEL_VALUE,          intruderstring,
       	       		NULL);
      				xv_set (sentry_state,
       	       		PANEL_LABEL_IMAGE,    gen_s6,
       	       		NULL);
      				xv_set (sentryicon,	
       	       		ICON_IMAGE,           gen_s6,
       	       		ICON_MASK_IMAGE,      genm_s6,
       	       		ICON_TRANSPARENT,	    TRUE,
       	       		NULL);
				}
				else {
					siegeflag = 0;
      				xv_set (intruder,
       	     		PANEL_VALUE,          intruderstring,
       	       		NULL);
      				xv_set (sentry_state,
       	       		PANEL_LABEL_IMAGE,    gen_s6p,
       	       		NULL);
      				xv_set (sentryicon,	
       	       		ICON_IMAGE,           gen_s6p,
       	       		ICON_MASK_IMAGE,      genm_s6p,
       	       		ICON_TRANSPARENT,	    TRUE,
       	       		NULL);
				}
				break;


			default:
				if (siegeflag == 0) {
					siegeflag = 1;
      				xv_set (intruder,
       	     		PANEL_VALUE,          intruderstring,
       	       		NULL);
      				xv_set (sentry_state,
       	       		PANEL_LABEL_IMAGE,    gen_s6,
       	       		NULL);
      				xv_set (sentryicon,	
       	       		ICON_IMAGE,           gen_s6,
       	       		ICON_MASK_IMAGE,      genm_s6,
       	       		ICON_TRANSPARENT,	    TRUE,
       	       		NULL);
				}
				else {
					siegeflag = 0;
      				xv_set (intruder,
       	     		PANEL_VALUE,          intruderstring,
       	       		NULL);
      				xv_set (sentry_state,
       	       		PANEL_LABEL_IMAGE,    gen_s6p,
       	       		NULL);
      				xv_set (sentryicon,	
       	       		ICON_IMAGE,           gen_s6p,
       	       		ICON_MASK_IMAGE,      genm_s6p,
       	       		ICON_TRANSPARENT,	    TRUE,
       	       		NULL);
				}
				break;


	  	}
	}
	else {
				if (siegeflag == 0) {
					siegeflag = 1;
      				xv_set (intruder,
       	     		PANEL_VALUE,          intruderstring,
       	       		NULL);
      				xv_set (sentry_state,
       	       		PANEL_LABEL_IMAGE,    gen_s1,
       	       		NULL);
      				xv_set (sentryicon,	
       	       		ICON_IMAGE,           gen_s1,
       	       		ICON_MASK_IMAGE,      genm_s1,
       	       		ICON_TRANSPARENT,	    TRUE,
       	       		NULL);
				}
				else {
					siegeflag = 0;
      				xv_set (intruder,
       	     		PANEL_VALUE,          intruderstring,
       	       		NULL);
      				xv_set (sentry_state,
       	       		PANEL_LABEL_IMAGE,    gen_s1p,
       	       		NULL);
      				xv_set (sentryicon,	
       	       		ICON_IMAGE,           gen_s1p,
       	       		ICON_MASK_IMAGE,      genm_s1p,
       	       		ICON_TRANSPARENT,	    TRUE,
       	       		NULL);
				}
				break;
	}	

      swflag =1;
	  if  (! noWarnSoundFlag) {
		strcpy(WarningSound, (char *)xv_get(prop_soundPath, PANEL_VALUE));
	   	len = strlen(WarningSound);
		if (WarningSound[len - 1] != '/') 
        	strcat(WarningSound, "/");
		if (siegecount <= 6 ) 
			strcat(WarningSound, icons[(int)xv_get(icon_swapper, PANEL_VALUE)].warSound[siegecount - 1]);
		
		else
			strcat(WarningSound, icons[(int)xv_get(icon_swapper, PANEL_VALUE)].warSound[5]);
		
			
		lstat(WarningSound, &statbuff);
		
		if ((statbuff.st_mode & S_IFMT) == S_IFREG) {
            xv_set (propframe, FRAME_LEFT_FOOTER, "", NULL);
			soundmatch = TRUE;
		}
		else {
			sprintf(footerMessage, "Warning sound %s is not found...defaulting\n", WarningSound);
            xv_set(propframe, FRAME_LEFT_FOOTER, footerMessage, NULL);
			soundmatch = FALSE;
		}

      	callplay (WarningSound, volume_value, soundmatch); 
	}
      break;

    case 1:	        /* left side    */
      xv_set (intruder,
              PANEL_VALUE,          "None found",
              NULL);
      xv_set (sentry_state,
              PANEL_LABEL_IMAGE,    gen_l,
              NULL);
      xv_set (sentryicon,	
              ICON_IMAGE,	    gen_l,
              ICON_MASK_IMAGE,      genm_l,
              ICON_TRANSPARENT,	    TRUE,
              NULL);
      swflag++;
      break;
 
    case 2:	        /* center    */
      xv_set (intruder,
              PANEL_VALUE,	    "None found",
              NULL);
      xv_set (sentry_state,
              PANEL_LABEL_IMAGE,    gen_c,
              NULL);
      xv_set (sentryicon,	
              ICON_IMAGE,	    gen_c,
              ICON_MASK_IMAGE,      genm_c,
              ICON_TRANSPARENT,	    TRUE,
              NULL);
      swflag++;
      break;
 
    case 3:	        /* right side  */
      xv_set (intruder,
              PANEL_VALUE,	    "None found",
              NULL);
      xv_set (sentry_state,
              PANEL_LABEL_IMAGE,    gen_r,
              NULL);
      xv_set (sentryicon,	
              ICON_IMAGE,	    gen_r,
              ICON_MASK_IMAGE,      genm_r,
              ICON_TRANSPARENT,	    TRUE,
              NULL);
	  swapval = (int)xv_get(icon_swapper, PANEL_VALUE);
	  if (swapval == 3 || swapval == 4)
		swflag = 1;
	  else
      	swflag++;
      break;

    case 4:	      
      xv_set (intruder,
        PANEL_VALUE,	    "None found",
        NULL);
      xv_set (sentry_state,
        PANEL_LABEL_IMAGE,    gen_c,
        NULL);
      xv_set (sentryicon,	
      	ICON_IMAGE,	    gen_c,
        ICON_MASK_IMAGE,      genm_c,
        ICON_TRANSPARENT,	    TRUE,
        NULL);
      swflag = 1;
      break;
 
    default:
      swflag = 1;
      break;
    }
 
  if (! norecordflag && logfp != NULL){
  	if (fclose (logfp) != 0)
   		 printf ("Error in closing log file");
  }
  XFlush((Display *)xv_get(frame, XV_DISPLAY));
}

int
props ( Panel_item item, Event *event)
{
    Audio_info  naif;
	int			value;

 /* xv_set(view_log, PANEL_INACTIVE, TRUE, NULL);  */
   	  xv_set (propframe, XV_X, xv_get(frame, XV_X) + 5, NULL);
      xv_set (propframe, XV_Y, xv_get(frame, XV_Y) + 96, NULL);
      xv_set(propframe, XV_SHOW, TRUE, NULL);
}

void 
sound_toggle (Panel_item item, Event *event)
{

	switch ( (int) xv_get (wprop_sound, PANEL_VALUE)) {
		case 0: 
				noWarnSoundFlag = 0;
				nosoundflag = 0;
				xv_set(prop_volume, PANEL_INACTIVE, nosoundflag, NULL);
				xv_set(prop_warnSound, PANEL_INACTIVE, noWarnSoundFlag, NULL);
				xv_set(prop_soundPath, PANEL_INACTIVE, nosoundflag, NULL);
				xv_set(prop_setSoundwarn, PANEL_INACTIVE, noWarnSoundFlag, NULL);
				xv_set(prop_setSoundphase, PANEL_INACTIVE, noWarnSoundFlag, NULL);
				xv_set(prop_sound_output, PANEL_INACTIVE, nosoundflag, NULL);
				break;
		case 1: 
				xv_set(propframe, FRAME_LEFT_FOOTER, "", NULL);
				noWarnSoundFlag = 1;
				if (noMailSoundFlag == 1) 
					nosoundflag = 1;
				xv_set(prop_volume, PANEL_INACTIVE, nosoundflag, NULL);
				xv_set(prop_warnSound, PANEL_INACTIVE, noWarnSoundFlag, NULL);
				xv_set(prop_soundPath, PANEL_INACTIVE, nosoundflag, NULL);
				xv_set(prop_setSoundwarn, PANEL_INACTIVE, noWarnSoundFlag, NULL);
				xv_set(prop_setSoundphase, PANEL_INACTIVE, noWarnSoundFlag, NULL);
				xv_set(prop_sound_output, PANEL_INACTIVE, nosoundflag, NULL);
				break;
		default:
				break;
	}
    switch ( (int) xv_get (mprop_sound, PANEL_VALUE)) {
        case 0:  
                noMailSoundFlag = 0;
				nosoundflag = 0;
                xv_set(prop_volume, PANEL_INACTIVE, nosoundflag, NULL);
                xv_set(prop_mailSound, PANEL_INACTIVE, noMailSoundFlag, NULL);
                xv_set(prop_soundPath, PANEL_INACTIVE, nosoundflag, NULL);
                xv_set(prop_setSoundmail, PANEL_INACTIVE, noMailSoundFlag, NULL);
                xv_set(prop_sound_output, PANEL_INACTIVE, nosoundflag, NULL);
                break;
        case 1: 
                noMailSoundFlag = 1;
				if (noWarnSoundFlag == 1)
					nosoundflag = 1;
                xv_set(prop_volume, PANEL_INACTIVE, nosoundflag, NULL);
                xv_set(prop_mailSound, PANEL_INACTIVE, noMailSoundFlag, NULL);
                xv_set(prop_soundPath, PANEL_INACTIVE, nosoundflag, NULL);
                xv_set(prop_setSoundmail, PANEL_INACTIVE, noMailSoundFlag, NULL);
                xv_set(prop_sound_output, PANEL_INACTIVE, nosoundflag, NULL);
                break;
        default:
                break;   
    }
}

void 
log_toggle (Panel_item item, Event *event)
{
	switch ( (int) xv_get (prop_log_toggle, PANEL_VALUE)) {
		case 2: 
				logflag = 0;
				xv_set(prop_rlogname, PANEL_INACTIVE, TRUE, NULL);
				xv_set(prop_rlogname, PANEL_VALUE, defaultlog, NULL);
				break;
		case 0: 
				logflag = 0;
				xv_set(prop_rlogname, PANEL_INACTIVE, logflag, NULL);
				break;
		case 1: 
				logflag = 1;
				xv_set(prop_rlogname, PANEL_INACTIVE, logflag, NULL);
				break;
		default:
				break;
	}


}


void
apply_props (Panel panel, Panel_item item) 
{
	int 		mtimevalue, wtimevalue;
	int 		volvalue;
	char        cmd[20];
	char		propStr[BUFSIZ];
	FILE        *fp, *rcfp, *tfp;

	logview = 0;
	viewpanel = 0;
	PANEL_EACH_ITEM (proppanel, item)
		switch ( (int) xv_get (item, PANEL_CLIENT_DATA)) {
			case authlist:
				strcpy(authuserlist, (char *)xv_get(prop_authlist, PANEL_VALUE));
				break;
				
			case wtimeslide:
				wtimevalue = ((int) xv_get (item, PANEL_VALUE));
  				warntimer.it_value.tv_sec = 1;
				warntimer.it_interval.tv_sec = wtimevalue;
  				notify_set_itimer_func(frame, mon_toggle1, ITIMER_REAL, &warntimer, NULL); 

  				warn_slide_value = wtimevalue; 
				break;

            case mtimeslide:
                mtimevalue = ((int) xv_get (item, PANEL_VALUE));
                mailtimer.it_value.tv_sec = 1;
                mailtimer.it_interval.tv_sec = mtimevalue;
  				notify_set_itimer_func(panel, mon_toggle2, ITIMER_REAL, &mailtimer, NULL); 
                mail_slide_value = mtimevalue;
                break;

            case printertype:
                propchange_print(item);
                break;

			case outputtype:
				switch ((int) xv_get (item, PANEL_VALUE)) {
                    case 0:
                        soflag = 0;
                        break;
                    case 1:
                        soflag = 1;
                        break;
                    default:
                        break;
                }
            break;

				
			case wsoundtype:
				switch ( (int) xv_get (item, PANEL_VALUE)) {
					case 0: 

						noWarnSoundFlag = 0;
						break;
					case 1: 
						noWarnSoundFlag = 1;
						break;
					default:
						break;
				}
			break;

            case msoundtype:
                switch ( (int) xv_get (item, PANEL_VALUE)) {
                    case 0:
 
                        noMailSoundFlag = 0;
                        break;
                    case 1:
                        noMailSoundFlag = 1;
                        break;
                    default:
                        break;
                }
            break;
			case file:
				switch ( (int) xv_get (prop_recfile, PANEL_VALUE)) {
					case 0: 
						norecordflag = 0;
						xv_set (clear_file, PANEL_INACTIVE, FALSE, NULL);
						xv_set (view_log, PANEL_INACTIVE, FALSE, NULL);
						break;
					case 1: 
						norecordflag = 1;
						xv_set (clear_file, PANEL_INACTIVE, TRUE, NULL);
						xv_set (view_log, PANEL_INACTIVE, TRUE, NULL);
						break;
					default:
						break;
				}
			break;
			case rlogname:
				strcpy(rlogfile, (char *)xv_get(prop_rlogname, PANEL_VALUE));
				xv_set(cmdframe, FRAME_LABEL, rlogfile, NULL);
				break;

			case volume:
				volvalue = ((int) xv_get (item, PANEL_VALUE));
  				volume_value = volvalue; 
				break;

			case clear:
				switch ( (int) xv_get (clear_file, PANEL_VALUE)) {
					case 1:
  						if ((fp = fopen (rlogfile, "r")) != NULL){
							fclose(fp);
							strcpy(cmd, "/bin/rm ");
							strcat(cmd, rlogfile);
							system(cmd);
						}
						break;

					default:
						break;
				}
				clearflag = 0;
				xv_set(clear_file, PANEL_VALUE, clearflag, NULL);
				break;


			case soundpath:
				strcpy(soundPath, (char *)xv_get(prop_soundPath, PANEL_VALUE));
				break;



			case seticon:
				iconflag = (int)xv_get(icon_swapper, PANEL_VALUE);
				set_iconset();
				break;

			case soundwar:
					break;

			case montype:
					monflag = (int)xv_get(prop_monitor_toggle, PANEL_VALUE);
					break;
					
			case soundmai:
					strcpy(MailSound, (char *)xv_get(prop_mailSound, PANEL_VALUE));				
					break;
			case mailtype:
        			strcpy(subjectLine, (char *)xv_get(prop_subject_line, PANEL_VALUE));
					strcpy(mfilename, (char *)xv_get(prop_mfilename, PANEL_VALUE));
					break;
			default:
				break;

		}
	PANEL_END_EACH
  	if ((rcfp = fopen(RcFile, "w+")) == NULL)
      notice_prompt (proppanel, NULL,
                     NOTICE_NO_BEEPING,         TRUE,
                     NOTICE_MESSAGE_STRINGS,  "Cannot open file: ", RcFile,   NULL,
                     NULL);
	else {
		fprintf (rcfp, "%d~%d~%d~%d~%d~%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~", wtimevalue, noWarnSoundFlag, norecordflag, nosiegeflag, volvalue, icons[0].warSound[0],icons[0].warSound[1], icons[0].warSound[2], icons[0].warSound[3], icons[0].warSound[4],icons[0].warSound[5], icons[1].warSound[0],icons[1].warSound[1], icons[1].warSound[2], icons[1].warSound[3], icons[1].warSound[4],icons[1].warSound[5], icons[2].warSound[0],icons[2].warSound[1], icons[2].warSound[2], icons[2].warSound[3], icons[2].warSound[4],icons[2].warSound[5]);

		fprintf (rcfp, "%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~%s~", icons[3].warSound[0],icons[3].warSound[1], icons[3].warSound[2], icons[3].warSound[3], icons[3].warSound[4], icons[3].warSound[5], icons[4].warSound[0], icons[4].warSound[1], icons[4].warSound[2], icons[4].warSound[3], icons[4].warSound[4], icons[4].warSound[5], icons[5].warSound[0], icons[5].warSound[1], icons[5].warSound[2], icons[5].warSound[3], icons[5].warSound[4], icons[5].warSound[5]);  

		fprintf (rcfp, "%s~%s~%s~%s~%s~%s~%s~%s~%s~%d~%s~%d~%d~%s~%s~%d~%d~%d~%d~%s~", icons[6].warSound[0],icons[6].warSound[1], icons[6].warSound[2], icons[6].warSound[3], icons[6].warSound[4],icons[6].warSound[5], soundPath, rlogfile, authuserlist, iconflag, rcprinter, soflag, monflag, mfilename, MailSound, mtimevalue, noMailSoundFlag, whoFlag, mailFlag, subjectLine );
	    fclose(rcfp);	
	}
	
}

int
clearlog(Panel_item item, Event *event)
{
	clearflag = 1;	
}

void
viewlog(Panel_item item, Event *event)
{
/* 	xv_set(props_button, PANEL_INACTIVE, TRUE, NULL);   */
	xv_set(textsw, TEXTSW_FILE,  rlogfile, NULL);
	xv_set (cmdframe, XV_X, xv_get(frame, XV_X) - 2, NULL);
    xv_set (cmdframe, XV_Y, xv_get(frame, XV_Y) + 96, NULL);
    xv_set(cmdframe, XV_SHOW, TRUE, NULL); 
}

void
nullfunct(Panel_item item)
{
    Frame tmpframe;
    Panel panel;

    panel = (Panel)xv_get(item, PANEL_PARENT_PANEL);
    tmpframe = (Frame)xv_get(panel, XV_OWNER);
    if ((int)xv_get(tmpframe, FRAME_CMD_PIN_STATE) == FRAME_CMD_PIN_IN) {
        quitpanel(item);
        xv_set(tmpframe, XV_SHOW, FALSE, NULL);
    }
    else {
        quitpanel(item);
        xv_set(tmpframe, XV_SHOW, TRUE, NULL);
    }
    return;


}

int
quitpanel (Panel_item item)        
{
	xv_destroy_safe(frame);
	if (Audio_fd != NULL)
		close(Audio_fd);
}

int
view (Panel_item item)
{
	Frame frame;
    Panel panel;
 

/* 	xv_set(props_button, PANEL_INACTIVE, FALSE, NULL);  */
/*xv_set(view_log, PANEL_INACTIVE, FALSE, NULL);    */
    panel = (Panel)xv_get(item, PANEL_PARENT_PANEL);
    frame = (Frame)xv_get(panel, XV_OWNER);
    xv_set(frame, XV_SHOW, FALSE, NULL);
	  
	 
}
void 
help(Panel_item item, Event *event)
{
/*  xv_set(props_button, PANEL_INACTIVE, TRUE, NULL);  
	xv_set(view_log, PANEL_INACTIVE, TRUE, NULL); */
	xv_set (helpframe, XV_X, xv_get(frame, XV_X) - 2, NULL);
    xv_set (helpframe, XV_Y, xv_get(frame, XV_Y) + 96, NULL);
    xv_set(helpframe, XV_SHOW, TRUE, NULL); 
}

void
which_warn_choice(Panel_item item, int value)
{
	switch(value) {
		case 1:
			get_list(item, WHO);
			xv_set(prop_setSoundwarn, PANEL_VALUE, 0, NULL);
			break;
		case 2:
			test_sound(WHO);
			xv_set(prop_setSoundwarn, PANEL_VALUE, 0, NULL);
			break;
		default:
			fprintf(stdout, "Value: %d\n", value);
			fflush(stdout);
			break;
	}
}

void
which_mail_choice(Panel_item item, int value)
{
    switch(value) {
        case 1:
            get_list(item, MAIL);
            xv_set(prop_setSoundmail, PANEL_VALUE, 0, NULL);
            break;
        case 2:
            test_sound(MAIL);
            xv_set(prop_setSoundmail, PANEL_VALUE, 0, NULL);
            break;
        default:
            fprintf(stdout, "Value: %d\n", value);
            fflush(stdout);
            break;
    }
}

void
test_sound(int whichsound) {

  struct    stat 		statbuff;
  int		len, volvalue;
 

	switch(whichsound) {
		case MAIL:
			volvalue = ((int) xv_get (prop_volume, PANEL_VALUE));
			strcpy(MailSound, (char *)xv_get(prop_soundPath, PANEL_VALUE));
		   	len = strlen(MailSound);
		    if (MailSound[len - 1] != '/')
		    	strcat(MailSound, "/");
		    strcat(MailSound, (char *)xv_get(prop_mailSound, PANEL_VALUE));
		    lstat(MailSound, &statbuff);
		        
		    if ((statbuff.st_mode & S_IFMT) == S_IFREG)
		    	soundmatch = TRUE;
		    else {
				if (strlen((char *)xv_get(prop_mailSound, PANEL_VALUE)) > 2) {
		        	notice_prompt (panel, NULL,
		        	NOTICE_MESSAGE_STRINGS,    "Unable to test sound ", WarningSound, "check the path", NULL,
		        	NULL);
				}
				else {
		        	notice_prompt (panel, NULL,
		        	NOTICE_MESSAGE_STRINGS,    "You must first select a mail sound ", NULL,
		        	NULL);
				}
				
		        soundmatch = FALSE;
			}
		 
		    callplay (MailSound, volvalue, soundmatch);
		break;
        case WHO: 
            volvalue = ((int) xv_get (prop_volume, PANEL_VALUE));
            strcpy(WarningSound, (char *)xv_get(prop_soundPath, PANEL_VALUE));
            len = strlen(WarningSound);
            if (WarningSound[len - 1] != '/')
                strcat(WarningSound, "/");
            strcat(WarningSound, (char *)xv_get(prop_warnSound, PANEL_VALUE));
            lstat(WarningSound, &statbuff);
             
            if ((statbuff.st_mode & S_IFMT) == S_IFREG)
                soundmatch = TRUE;
            else {
				if (strlen((char *)xv_get(prop_warnSound, PANEL_VALUE)) > 2) {
                	notice_prompt (panel, NULL,
                	NOTICE_MESSAGE_STRINGS,    "Unable to test sound ", WarningSound, "check the path", NULL,
                	NULL);
				}
				else {   
                    notice_prompt (panel, NULL,
                    NOTICE_MESSAGE_STRINGS,    "You must first select a warning sound ", NULL,
                    NULL);
                } 
                soundmatch = FALSE;
            }
         
            callplay (WarningSound, volvalue, soundmatch);
        break; 
	}

	return;
}

void
callplay (char *sound, unsigned vol, int sv)
{
	Audio_info  aif;
    Audio_info  naif;
	int		value, stat, errno;

	audio_open();
	getinfo(&naif);
    value = (naif.play.port == AUDIO_SPEAKER ? 1 : 0);
	xv_set(prop_sound_output, PANEL_VALUE, value, NULL); 

	switch(sv){
		case TRUE:
    		if (value == 0) {
        		xv_set(prop_sound_output, PANEL_CHOICE_IMAGE, 0, play_image, NULL);
        		xv_set(prop_sound_output, PANEL_CHOICE_IMAGE, 1, null_image, NULL);
    		}
    		else
    		{   
        		xv_set(prop_sound_output, PANEL_CHOICE_IMAGE, 0, null_image, NULL);
        		xv_set(prop_sound_output, PANEL_CHOICE_IMAGE, 1, play_image, NULL);
    		}
  			XFlush((Display *)xv_get(propframe, XV_DISPLAY));
			play(sound, vol);
			break;
		case FALSE:
			printf("\007");
			fflush(stdout);
			break;
		default:
			break;
	}
	xv_set(prop_sound_output, PANEL_CHOICE_IMAGE, 0, speaker_image, NULL); 
	xv_set(prop_sound_output, PANEL_CHOICE_IMAGE, 1, head_phone_image, NULL); 
	if (Audio_fd != NULL);
		close(Audio_fd);
	audio_open();
	return;
}

void
getprint_list(char *rcprinter)
{
    FILE    *fp;
    char    plist[BUFSIZ];
    char    token[BUFSIZ];
    int     i;

    if ((fp = fopen("/etc/printcap", "r")) == NULL)
        printf("Unable to open printcap");
    else {
        while(fgets (printer, BUFSIZ, fp) != NULL && printer[0] != '\n'){
            if (isdigit(printer[0])){
                strcpy(token, strtok(printer, "|"));
                strcat(printlist[prcount], token);
				if (strcmp (rcprinter, printer) == 0){
                    prflag = prcount;
                }
                prcount ++;
            }
		}
    }
    fclose(fp);
	if (prcount > 0) {
    	for (i = 0; i < prcount ; i++) 
        	xv_set(prop_print,
            	PANEL_CHOICE_STRING, i, printlist[i],
            	NULL);
    		strcpy (printer, printlist[0]);
	}
	else 
		xv_set(prop_print, PANEL_INACTIVE, TRUE, NULL);

    window_fit (proppanel);
    window_fit (propframe);

}    

void
propchange_print (Panel_item item)
{
    int i;

    for (i = 0; i <= prcount; i++)
        if (((int)xv_get(item, PANEL_VALUE)) == i){
            strcpy (printer, printlist[i]);
            strcpy (rcprinter, printlist[i]);
            prflag = i;
        }

}  

void
print_list(Panel_item item)
{
    char    cmd[BUFSIZ];
    int     result;
    Xv_notice notice;
 
    notice = notice_prompt (panel, NULL,
                     NOTICE_STATUS,             &result,
                     NOTICE_NO_BEEPING,         TRUE,
                     NOTICE_MESSAGE_STRINGS,    "Print to: " ,printer , NULL,
                     NOTICE_BUTTON_YES,      "Yes",
                     NOTICE_BUTTON_NO,       "No",
                     NULL);

        switch(result) { 
            case NOTICE_YES:
                strcpy(cmd, "echo ");
                strcat(cmd, "\"");
                strcat(cmd, "Sentry Log File");
                strcat(cmd, "\" | ");
                strcat(cmd, "cat ");
                strcat(cmd, rlogfile);
                strcat(cmd, " | ");
                strcat(cmd, "mp -lo |");
                strcat(cmd, " lpr -P");
                strcat(cmd, printer);
                strcat(cmd, " ");
                system(cmd);
                xv_set (cmdframe, FRAME_LEFT_FOOTER, "Done !", NULL);
                break;
            case NOTICE_NO:
                break;
            case NOTICE_FAILED:
                break;
            default:
                break;
        }
/*	xv_set(props_button, PANEL_INACTIVE, FALSE, NULL);  */
}    

 
void
set_iconset(void)
{

	int 	value;
	Panel_item item;

	value = (int)xv_get(icon_swapper, PANEL_VALUE);

	xv_set(gen_cursor_svrimage, SERVER_IMAGE_BITS, icons[value].cursorm_bits, NULL);
	xv_set(gen_cursorsi_mask, SERVER_IMAGE_BITS, icons[value].cursorm_bits, NULL);

  	xv_set(generic_cursor, CURSOR_IMAGE, gen_cursor_svrimage, NULL);
  	xv_set(generic_cursor, CURSOR_XHOT, icons[value].icon_xhot, NULL);
  	xv_set(generic_cursor, CURSOR_YHOT, icons[value].icon_yhot, NULL);
  	xv_set(sentryicon, WIN_FOREGROUND_COLOR, CMS_CONTROL_COLORS + icons[value].icon_fg, NULL);
  	xv_set(sentryicon, WIN_BACKGROUND_COLOR, CMS_CONTROL_COLORS + icons[value].icon_bg, NULL);
  	xv_set(panel, WIN_CURSOR, generic_cursor, NULL);
  	xv_set(proppanel, WIN_CURSOR, generic_cursor, NULL);
  	xv_set(cmdpanel, WIN_CURSOR, generic_cursor, NULL);

 	xv_set(gen_l, SERVER_IMAGE_BITS, icons[value].l_bits, NULL);
 	xv_set(gen_r, SERVER_IMAGE_BITS, icons[value].r_bits, NULL);
 	xv_set(gen_c, SERVER_IMAGE_BITS, icons[value].c_bits, NULL);
	xv_set(gen_s1, SERVER_IMAGE_BITS, icons[value].s1_bits, NULL);
 	xv_set(gen_s2, SERVER_IMAGE_BITS, icons[value].s2_bits, NULL);
 	xv_set(gen_s3, SERVER_IMAGE_BITS, icons[value].s3_bits, NULL);
 	xv_set(gen_s4, SERVER_IMAGE_BITS, icons[value].s4_bits, NULL);
 	xv_set(gen_s5, SERVER_IMAGE_BITS, icons[value].s5_bits, NULL);
 	xv_set(gen_s6, SERVER_IMAGE_BITS, icons[value].s6_bits, NULL);

 	xv_set(gen_s1p, SERVER_IMAGE_BITS, icons[value].s1p_bits, NULL);
 	xv_set(gen_s2p, SERVER_IMAGE_BITS, icons[value].s2p_bits, NULL);
 	xv_set(gen_s3p, SERVER_IMAGE_BITS, icons[value].s3p_bits, NULL);
 	xv_set(gen_s4p, SERVER_IMAGE_BITS, icons[value].s4p_bits, NULL);
 	xv_set(gen_s5p, SERVER_IMAGE_BITS, icons[value].s5p_bits, NULL);
 	xv_set(gen_s6p, SERVER_IMAGE_BITS, icons[value].s6p_bits, NULL);

 	xv_set(genm_l, SERVER_IMAGE_BITS, icons[value].lm_bits, NULL);
 	xv_set(genm_r, SERVER_IMAGE_BITS, icons[value].rm_bits, NULL);
 	xv_set(genm_c, SERVER_IMAGE_BITS, icons[value].cm_bits, NULL);

 	xv_set(genm_s1, SERVER_IMAGE_BITS, icons[value].s1m_bits, NULL);
 	xv_set(genm_s2, SERVER_IMAGE_BITS, icons[value].s2m_bits, NULL);
 	xv_set(genm_s3, SERVER_IMAGE_BITS, icons[value].s3m_bits, NULL);
 	xv_set(genm_s4, SERVER_IMAGE_BITS, icons[value].s4m_bits, NULL);
 	xv_set(genm_s5, SERVER_IMAGE_BITS, icons[value].s5m_bits, NULL);
 	xv_set(genm_s6, SERVER_IMAGE_BITS, icons[value].s6m_bits, NULL);

 	xv_set(genm_s1p, SERVER_IMAGE_BITS, icons[value].s1mp_bits, NULL);
 	xv_set(genm_s2p, SERVER_IMAGE_BITS, icons[value].s2mp_bits, NULL);
 	xv_set(genm_s3p, SERVER_IMAGE_BITS, icons[value].s3mp_bits, NULL);
 	xv_set(genm_s4p, SERVER_IMAGE_BITS, icons[value].s4mp_bits, NULL);
 	xv_set(genm_s5p, SERVER_IMAGE_BITS, icons[value].s5mp_bits, NULL);
 	xv_set(genm_s6p, SERVER_IMAGE_BITS, icons[value].s6mp_bits, NULL);
	
  	XFlush((Display *)xv_get(frame, XV_DISPLAY));
  	XFlush((Display *)xv_get(helpframe, XV_DISPLAY));
  	XFlush((Display *)xv_get(helppanel6, XV_DISPLAY));
  	XFlush((Display *)xv_get(propframe, XV_DISPLAY));
}

void
create_all(void)
{

  Rect 	*rect;

  nullmenu = (Menu) xv_create (NULL, MENU, NULL);

  panel = (Panel) xv_create (frame, PANEL, 
				PANEL_LAYOUT, PANEL_VERTICAL,
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

  tower_demo = (Server_image) xv_create (XV_NULL, SERVER_IMAGE,
                                          XV_WIDTH,             64,
                                          XV_HEIGHT,            64,
                                          SERVER_IMAGE_BITS,    icons[0].c_bits,
                                          NULL);

  defcon_demo = (Server_image) xv_create (XV_NULL, SERVER_IMAGE,
                                          XV_WIDTH,             64,
                                          XV_HEIGHT,            64,
                                          SERVER_IMAGE_BITS,    icons[6].c_bits,
                                          NULL);

  dog_demo = (Server_image) xv_create (XV_NULL, SERVER_IMAGE,
                                          XV_WIDTH,             64,
                                          XV_HEIGHT,            64,
                                          SERVER_IMAGE_BITS,    icons[2].l_bits,
                                          NULL);

  boat_demo = (Server_image) xv_create (XV_NULL, SERVER_IMAGE,
                                          XV_WIDTH,             64,
                                          XV_HEIGHT,            64,
                                          SERVER_IMAGE_BITS,    icons[1].l_bits,
                                          NULL);

  trek_demo = (Server_image) xv_create (XV_NULL, SERVER_IMAGE,
                                          XV_WIDTH,             64,
                                          XV_HEIGHT,            64,
                                          SERVER_IMAGE_BITS,    icons[3].c_bits,
                                          NULL);

  tank_demo = (Server_image) xv_create (XV_NULL, SERVER_IMAGE,
                                          XV_WIDTH,             64,
                                          XV_HEIGHT,            64,
                                          SERVER_IMAGE_BITS,    icons[5].c_bits,
                                          NULL);

  ngtrek_demo = (Server_image) xv_create (XV_NULL, SERVER_IMAGE,
                                          XV_WIDTH,             64,
                                          XV_HEIGHT,            64,
                                          SERVER_IMAGE_BITS,    icons[4].c_bits,
                                          NULL);

  gen_cursor_svrimage = (Server_image) xv_create (XV_NULL, SERVER_IMAGE,
                                          XV_WIDTH,             32,
                                          XV_HEIGHT,            32,
                                          SERVER_IMAGE_BITS,    icons[0].cursor_bits,
                                          NULL);

  gen_cursorsi_mask = (Server_image) xv_create (XV_NULL, SERVER_IMAGE,
                                          XV_WIDTH,             32,
                                          XV_HEIGHT,            32,
                                          SERVER_IMAGE_BITS,    icons[0].cursor_bits,
                                          NULL);



  generic_cursor = (Xv_Cursor)xv_create(XV_NULL, CURSOR, 
				CURSOR_IMAGE,		gen_cursor_svrimage,
				CURSOR_XHOT,		0,
				CURSOR_YHOT,		0,
				NULL);



/*

  gen_icon = (Server_image) xv_create (frame, ICON,
										  WIN_CMS,				sentrycms,
                                          XV_WIDTH,             64,
                                          XV_HEIGHT,            64,
										  WIN_FOREGROUND_COLOR, CMS_CONTROL_COLORS + 0;
										  WIN_BACKGROUND_COLOR, CMS_CONTROL_COLORS + 1;
                                          SERVER_IMAGE_BITS,    icon_bits,
                                          NULL);
*/
  logo_image = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                64,
                                       XV_HEIGHT,               64,
                                       SERVER_IMAGE_BITS,       logo_bits,
                                       NULL);

  logo_image_mask = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                64,
                                       XV_HEIGHT,               64,
                                       SERVER_IMAGE_BITS,       logo_mbits,
                                       NULL);


  play_image = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                16,
                                       XV_HEIGHT,               16,
                                       SERVER_IMAGE_BITS,       play_bits,
                                       NULL);

  null_image = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                16,
                                       XV_HEIGHT,               16,
                                       SERVER_IMAGE_BITS,       null_bits,
                                       NULL);

  head_phone_image = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                16,
                                       XV_HEIGHT,               16,
                                       SERVER_IMAGE_BITS,       head_phone_bits,
                                       NULL);

  speaker_image = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                16,
                                       XV_HEIGHT,               16,
                                       SERVER_IMAGE_BITS,       speaker_bits,
                                       NULL);

  gen_l = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                64,
                                       XV_HEIGHT,               64,
                                       SERVER_IMAGE_BITS,       icons[0].l_bits,
                                       NULL);

  gen_r = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                64,
                                       XV_HEIGHT,               64,
                                       SERVER_IMAGE_BITS,       icons[0].r_bits,
                                       NULL);

  gen_c = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                64,
                                       XV_HEIGHT,               64,
                                       SERVER_IMAGE_BITS,       icons[0].c_bits,
                                       NULL);

  gen_s1 = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                64,
                                       XV_HEIGHT,               64,
                                       SERVER_IMAGE_BITS,       icons[0].s1_bits,
                                       NULL);

  gen_s2 = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                64,
                                       XV_HEIGHT,               64,
                                       SERVER_IMAGE_BITS,       icons[0].s2_bits,
                                       NULL);

  gen_s3 = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                64,
                                       XV_HEIGHT,               64,
                                       SERVER_IMAGE_BITS,       icons[0].s3_bits,
                                       NULL);

  gen_s4 = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                64,
                                       XV_HEIGHT,               64,
                                       SERVER_IMAGE_BITS,       icons[0].s4_bits,
                                       NULL);

  gen_s5 = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                64,
                                       XV_HEIGHT,               64,
                                       SERVER_IMAGE_BITS,       icons[0].s5_bits,
                                       NULL);

  gen_s6 = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                64,
                                       XV_HEIGHT,               64,
                                       SERVER_IMAGE_BITS,       icons[0].s6_bits,
                                       NULL);

  gen_s1p = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                64,
                                       XV_HEIGHT,               64,
                                       SERVER_IMAGE_BITS,       icons[0].s1p_bits,                                       NULL);

  gen_s2p = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                64,
                                       XV_HEIGHT,               64,
                                       SERVER_IMAGE_BITS,       icons[0].s2p_bits,                                       NULL);
 
  gen_s3p = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                64,
                                       XV_HEIGHT,               64,
                                       SERVER_IMAGE_BITS,       icons[0].s3p_bits,                                       NULL);
 
  gen_s4p = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                64,
                                       XV_HEIGHT,               64,
                                       SERVER_IMAGE_BITS,       icons[0].s4p_bits,                                       NULL);
 
  gen_s5p = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                64,
                                       XV_HEIGHT,               64,
                                       SERVER_IMAGE_BITS,       icons[0].s5p_bits,                                       NULL);
 
  gen_s6p = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                       XV_WIDTH,                64,
                                       XV_HEIGHT,               64,
                                       SERVER_IMAGE_BITS,       icons[0].s6p_bits,                                       NULL);
  genm_l = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                     XV_WIDTH,                  64,
                                     XV_HEIGHT,                 64,
                                     XV_DEPTH,                  1, 
                                     SERVER_IMAGE_BITS,         icons[0].lm_bits,
                                     NULL);

  genm_r = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                     XV_WIDTH,                  64,
                                     XV_HEIGHT,                 64,
                                     XV_DEPTH,                  1, 
                                     SERVER_IMAGE_BITS,         icons[0].rm_bits,
                                     NULL);

  genm_c = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                     XV_WIDTH,                  64,
                                     XV_HEIGHT,                 64,
                                     XV_DEPTH,                  1, 
                                     SERVER_IMAGE_BITS,	        icons[0].cm_bits,
                                     NULL);

  genm_s1 = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                     XV_WIDTH,                  64,
                                     XV_HEIGHT,                 64,
                                     XV_DEPTH,                  1, 
                                     SERVER_IMAGE_BITS,         icons[0].s1m_bits,
                                     NULL);

  genm_s2 = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                     XV_WIDTH,                  64,
                                     XV_HEIGHT,                 64,
                                     XV_DEPTH,                  1, 
                                     SERVER_IMAGE_BITS,         icons[0].s2m_bits,
                                     NULL);

  genm_s3 = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                     XV_WIDTH,                  64,
                                     XV_HEIGHT,                 64,
                                     XV_DEPTH,                  1, 
                                     SERVER_IMAGE_BITS,         icons[0].s3m_bits,
                                     NULL);

  genm_s4 = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                     XV_WIDTH,                  64,
                                     XV_HEIGHT,                 64,
                                     XV_DEPTH,                  1, 
                                     SERVER_IMAGE_BITS,         icons[0].s4m_bits,
                                     NULL);

  genm_s5 = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                     XV_WIDTH,                  64,
                                     XV_HEIGHT,                 64,
                                     XV_DEPTH,                  1, 
                                     SERVER_IMAGE_BITS,         icons[0].s5m_bits,
                                     NULL);

  genm_s6 = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                     XV_WIDTH,                  64,
                                     XV_HEIGHT,                 64,
                                     XV_DEPTH,                  1, 
                                     SERVER_IMAGE_BITS,         icons[0].s6m_bits,
                                     NULL);

  genm_s1p = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                     XV_WIDTH,                  64,
                                     XV_HEIGHT,                 64,
                                     XV_DEPTH,                  1,
                                     SERVER_IMAGE_BITS,         icons[0].s1mp_bits,                                     NULL);
 
  genm_s2p = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                     XV_WIDTH,                  64,
                                     XV_HEIGHT,                 64,
                                     XV_DEPTH,                  1,
                                     SERVER_IMAGE_BITS,         icons[0].s2mp_bits,                                     NULL);
 
  genm_s3p = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                     XV_WIDTH,                  64,
                                     XV_HEIGHT,                 64,
                                     XV_DEPTH,                  1,
                                     SERVER_IMAGE_BITS,         icons[0].s3mp_bits,                                     NULL);
 
  genm_s4p = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                     XV_WIDTH,                  64,
                                     XV_HEIGHT,                 64,
                                     XV_DEPTH,                  1,
                                     SERVER_IMAGE_BITS,         icons[0].s4mp_bits,                                     NULL);
 
  genm_s5p = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                     XV_WIDTH,                  64,
                                     XV_HEIGHT,                 64,
                                     XV_DEPTH,                  1,
                                     SERVER_IMAGE_BITS,         icons[0].s5mp_bits,                                     NULL);
 
  genm_s6p = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                     XV_WIDTH,                  64,
                                     XV_HEIGHT,                 64,
                                     XV_DEPTH,                  1,
                                     SERVER_IMAGE_BITS,         icons[0].s6mp_bits,                                     NULL);

  sentry_state = xv_create (panel, PANEL_MESSAGE,
                  PANEL_LABEL_IMAGE,        logo_image,	
                  NULL);

  intruder = xv_create (panel, PANEL_TEXT,
						PANEL_READ_ONLY, TRUE,
                        PANEL_ITEM_X,                   80,
                        PANEL_ITEM_Y,                   15,
                        PANEL_VALUE_DISPLAY_LENGTH,     25,
                        PANEL_VALUE_STORED_LENGTH,	MAXSTRINGSIZE - 1,
			PANEL_LABEL_STRING,		"Intruders:", 
                        PANEL_VALUE,			"None found",
                        NULL);
 
   sentryicon = (Icon) xv_create (frame, ICON,
						   XV_WIDTH,					64,
						   XV_HEIGHT,					64,
						   WIN_CMS,						sentrycms,
							/*
						   WIN_FOREGROUND_COLOR,		CMS_CONTROL_COLORS + 0,
						   WIN_BACKGROUND_COLOR,		CMS_CONTROL_COLORS + 1,
							*/
                           ICON_IMAGE,                  logo_image,
                           ICON_MASK_IMAGE,     		logo_image_mask,
                           ICON_TRANSPARENT,            TRUE,
                           XV_X,			100,
                           XV_Y,			100,
                           NULL);

 xv_set (panel, PANEL_LAYOUT, PANEL_HORIZONTAL, NULL);

 xv_create (panel, PANEL_BUTTON,
               PANEL_ITEM_X,                   80,
               PANEL_ITEM_Y,                   60,
               PANEL_LABEL_STRING,          "Help",
               PANEL_NOTIFY_PROC,            help,
			   PANEL_CLIENT_DATA,            button,
               NULL);

 xv_create (panel, PANEL_BUTTON,
               PANEL_ITEM_X,                   315,
               PANEL_ITEM_Y,                   60,
               PANEL_LABEL_STRING,          "Quit",
               PANEL_NOTIFY_PROC,            quitpanel,
			   PANEL_CLIENT_DATA,            frame,
               NULL);

  view_log = (Panel_item) xv_create (panel, PANEL_BUTTON,
               PANEL_ITEM_X,                   140,
               PANEL_ITEM_Y,                   60,
               PANEL_LABEL_STRING,          "View log",
			   PANEL_INACTIVE,               norecordflag,
               PANEL_NOTIFY_PROC,            viewlog,
			   PANEL_CLIENT_DATA,            button,
               NULL);


 props_button = xv_create (panel, PANEL_BUTTON,
               PANEL_ITEM_X,                   220,
               PANEL_ITEM_Y,                   60,
               PANEL_LABEL_STRING,          "Properties",
               PANEL_NOTIFY_PROC,            props,
			   PANEL_CLIENT_DATA,            button,
               NULL);

  xv_set(frame, FRAME_ICON, sentryicon, NULL);

 
  window_fit(panel);
  window_fit(frame);

	propframe = (Frame) xv_create (frame, FRAME_CMD,
		FRAME_SHOW_FOOTER, 		TRUE,
        XV_WIDTH,           320,
        XV_HEIGHT,          50,
        XV_X,               xv_get(frame, XV_X) + 5,
        XV_Y,               xv_get(frame, XV_Y) + 96,
        FRAME_LABEL,        "Properties",
		/*	FRAME_DONE_PROC,	nullfunct,  */
        NULL);
    
    
      proppanel = (Panel) xv_create (propframe, PANEL,
                                    XV_X,               0,
                                    XV_Y,               0,
                                    PANEL_LAYOUT,    PANEL_VERTICAL,
                                    NULL);

      prop_monitor_toggle = (Panel_item) xv_create (proppanel, PANEL_TOGGLE,
            PANEL_LABEL_STRING, "Monitor :                ",
            PANEL_CHOICE_STRINGS, "Who's in", "Mail", NULL,
            PANEL_VALUE,              monflag,
            PANEL_CLIENT_DATA,        montype,
            PANEL_NOTIFY_PROC,        sound_flag_toggle,
            NULL);
 
      rect = (Rect *)xv_get(prop_monitor_toggle, XV_RECT);
 

	  prop_authlist = (Panel_item) xv_create (proppanel, PANEL_TEXT,
            XV_Y,   rect_bottom(rect) + 10,
    		PANEL_INACTIVE, 				whoFlag,
            PANEL_VALUE_DISPLAY_LENGTH,     40,
            PANEL_LABEL_STRING, "Authorized user list : ",
            PANEL_VALUE,              authuserlist,
            PANEL_CLIENT_DATA,        authlist,
            NULL);

	  rect = (Rect *)xv_get(prop_authlist, XV_RECT);

	  prop_log_toggle = (Panel_item) xv_create (proppanel, PANEL_CHOICE,
			XV_Y,	rect_bottom(rect) + 10,
    		PANEL_INACTIVE, 				whoFlag,
            PANEL_LABEL_STRING, "Personal log file : ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "Default", NULL,
            PANEL_VALUE,              logflag,
            PANEL_CLIENT_DATA,        logtype,
            PANEL_NOTIFY_PROC, 	      log_toggle,
            NULL);

	  rect = (Rect *)xv_get(prop_log_toggle, XV_RECT);


	  prop_rlogname = (Panel_item) xv_create(proppanel, PANEL_TEXT,
			XV_Y,	rect_bottom(rect) + 10,
    		PANEL_INACTIVE, 				whoFlag,
            PANEL_VALUE_DISPLAY_LENGTH,     40,
			PANEL_LABEL_STRING,		"Log file name:  ",
			PANEL_VALUE,			rlogfile,
			PANEL_CLIENT_DATA,		rlogname,
            NULL);

	  rect = (Rect *)xv_get(prop_rlogname, XV_RECT);

	  prop_mfilename = (Panel_item) xv_create(proppanel, PANEL_TEXT,
			XV_Y,	rect_bottom(rect) + 15,
    		PANEL_INACTIVE, 				mailFlag,
            PANEL_VALUE_DISPLAY_LENGTH,     40,
			PANEL_LABEL_STRING,		"Mail file name: ",
			PANEL_VALUE,			mfilename,
			PANEL_CLIENT_DATA,		mailtype,
            NULL);

	  rect = (Rect *)xv_get(prop_mfilename, XV_RECT);

      prop_print = (Panel_item) xv_create (proppanel, PANEL_CHOICE,
			XV_Y,	rect_bottom(rect) + 15,
            PANEL_LABEL_STRING, "Select printer:       ",
            PANEL_VALUE, prflag,
            PANEL_CLIENT_DATA,            printertype,
            NULL);

	  rect = (Rect *)xv_get(prop_print, XV_RECT);

      prop_warn_slide = (Panel_item) xv_create (proppanel, PANEL_SLIDER,
			XV_Y,	rect_bottom(rect) + 25,
    		PANEL_INACTIVE, 				whoFlag,
            PANEL_LABEL_STRING,        "Check who's in every(seconds): ",
            PANEL_VALUE,		warn_slide_value,
            PANEL_MIN_VALUE,		1,
            PANEL_MAX_VALUE,		120,
            PANEL_SLIDER_WIDTH,	200,
            PANEL_TICKS,               0,
    		PANEL_CLIENT_DATA,         wtimeslide,
            PANEL_NOTIFY_PROC, 	      mon_toggle1,
            NULL);

	  rect = (Rect *)xv_get(prop_warn_slide, XV_RECT);

    

      prop_mail_slide = (Panel_item) xv_create (proppanel, PANEL_SLIDER,
			XV_Y,	rect_bottom(rect) + 10,
    		PANEL_INACTIVE, 				mailFlag,
            PANEL_LABEL_STRING,        "Check mail every(seconds):       ",
            PANEL_VALUE,       mail_slide_value,
            PANEL_MIN_VALUE,       1,
            PANEL_MAX_VALUE,       120,
            PANEL_SLIDER_WIDTH,    200,
            PANEL_TICKS,               0,
            PANEL_CLIENT_DATA,         mtimeslide,
            PANEL_NOTIFY_PROC, 	      mon_toggle2,
            NULL);

	  rect = (Rect *)xv_get(prop_mail_slide, XV_RECT);

	  prop_subject_line = (Panel_item) xv_create(proppanel, PANEL_TEXT,
			XV_Y,	rect_bottom(rect) + 10,
    		PANEL_INACTIVE, 				mailFlag,
            PANEL_VALUE_DISPLAY_LENGTH,     40,
			PANEL_LABEL_STRING,		"Subject(s) item to look for: ",
			PANEL_VALUE,			subjectLine,
			PANEL_CLIENT_DATA,		mailtype,
            NULL);

	  rect = (Rect *)xv_get(prop_subject_line, XV_RECT);


      prop_recfile = (Panel_item) xv_create (proppanel, PANEL_CHOICE,
			XV_Y,	rect_bottom(rect) + 10,
    		PANEL_INACTIVE, 				whoFlag,
            PANEL_LABEL_STRING, "Record to log file:  ",
            PANEL_CHOICE_STRINGS, "On", "Off",NULL,
            PANEL_VALUE, norecordflag,
    		PANEL_CLIENT_DATA,         file,
            NULL);

	  rect = (Rect *)xv_get(prop_recfile, XV_RECT);

    
     clear_file = (Panel_item)  xv_create (proppanel, PANEL_CHOICE,
			XV_X,	rect_right(rect) + 50,
			XV_Y,	rect_bottom((Rect *)xv_get(prop_subject_line, XV_RECT)) + 10,
    		PANEL_INACTIVE,          norecordflag,
    		PANEL_INACTIVE, 				whoFlag,
            PANEL_LABEL_STRING,      "Clear log file:        ",
            PANEL_CHOICE_STRINGS, 	"No", "Yes",NULL,
    		PANEL_CLIENT_DATA,       clear,
            PANEL_VALUE,			 	clearflag,
            NULL);

	  rect = (Rect *)xv_get(clear_file, XV_RECT);

    
    
      wprop_sound = (Panel_item) xv_create (proppanel, PANEL_CHOICE,
			XV_Y,	rect_bottom(rect) + 15,
    		PANEL_INACTIVE,          whoFlag,
            PANEL_LABEL_STRING, "Warning sound:     ",
            PANEL_CHOICE_STRINGS, "On", "Off",NULL,
            PANEL_NOTIFY_PROC, sound_toggle,
            PANEL_VALUE, noWarnSoundFlag,
    		PANEL_CLIENT_DATA,         wsoundtype,
            NULL);

	  rect = (Rect *)xv_get(wprop_sound, XV_RECT);


      mprop_sound = (Panel_item) xv_create (proppanel, PANEL_CHOICE,
			XV_Y,	rect_bottom((Rect *)xv_get(clear_file, XV_RECT)) + 15,
			XV_X,	rect_right(rect) + 50,
    		PANEL_INACTIVE,          mailFlag,
            PANEL_LABEL_STRING, "Mail sound:           ",
            PANEL_CHOICE_STRINGS, "On", "Off",NULL,
            PANEL_NOTIFY_PROC, sound_toggle,
            PANEL_VALUE, noMailSoundFlag,
            PANEL_CLIENT_DATA,         msoundtype,
            NULL);

	  rect = (Rect *)xv_get(mprop_sound, XV_RECT);

    
      prop_volume = (Panel_item) xv_create (proppanel, PANEL_SLIDER,
			XV_Y,	rect_bottom(rect) + 15,
    		PANEL_INACTIVE, nosoundflag,
            PANEL_LABEL_STRING,        "Volume level: ",
            PANEL_VALUE,		volume_value,
            PANEL_MIN_VALUE,		0,
            PANEL_MAX_VALUE,		50,	 
            PANEL_SLIDER_WIDTH,	100,
            PANEL_TICKS,               1,
    		PANEL_CLIENT_DATA,         volume,
            NULL);

	  rect = (Rect *)xv_get(prop_volume, XV_RECT);


     xv_set (proppanel, PANEL_LAYOUT, PANEL_HORIZONTAL, NULL);

	prop_soundPath = (Panel_item) xv_create(proppanel, PANEL_TEXT,
		    XV_X,	(int)xv_get(prop_volume, XV_X),
			XV_Y,	rect_bottom(rect) + 10,
    		PANEL_INACTIVE, 		nosoundflag,
            PANEL_VALUE_DISPLAY_LENGTH,     40,
			PANEL_LABEL_STRING,		"Sound path name: ",
			PANEL_VALUE,			soundPath,
    		PANEL_CLIENT_DATA,         soundpath,
            NULL);

	  rect = (Rect *)xv_get(prop_soundPath, XV_RECT);

	prop_warnSound = (Panel_item) xv_create(proppanel, PANEL_TEXT,
			XV_Y,	rect_bottom(rect) + 25,
			PANEL_VALUE_UNDERLINED,		FALSE,
			PANEL_READ_ONLY, 		TRUE,
    		PANEL_INACTIVE, 		noWarnSoundFlag,
            PANEL_VALUE_DISPLAY_LENGTH,     15,
			PANEL_LABEL_STRING,		"Siege phase 1 sound:",
			PANEL_VALUE,			icons[iconflag].warSound[0],
    		PANEL_CLIENT_DATA,         	soundwar,
            NULL);

	  rect = (Rect *)xv_get(prop_warnSound, XV_RECT);

 	prop_setSoundphase = (Panel_item) xv_create (proppanel, PANEL_CHOICE,            
			XV_X,   rect_right(rect) + 5,
            PANEL_INACTIVE,         noWarnSoundFlag,
            PANEL_CHOICE_STRINGS,    "1","2","3","4","5","6", NULL, 
            PANEL_NOTIFY_PROC,      show_phase_choice,
            PANEL_CLIENT_DATA,         button,
            NULL);

	  rect = (Rect *)xv_get(prop_setSoundphase, XV_RECT);

    prop_setSoundwarn = (Panel_item) xv_create (proppanel, PANEL_TOGGLE,
            XV_X,   rect_right(rect) + 5,
			XV_Y,	(int)xv_get(prop_setSoundphase, XV_Y),
            PANEL_INACTIVE,         noWarnSoundFlag,
            PANEL_CHOICE_STRINGS,    "Set sound...", "Test sound...", NULL,
            PANEL_NOTIFY_PROC,      which_warn_choice,
            PANEL_CLIENT_DATA,         button,
            NULL);
 
	  rect = (Rect *)xv_get(prop_warnSound, XV_RECT);

	prop_mailSound = (Panel_item) xv_create(proppanel, PANEL_TEXT,
		    XV_X,	(int)xv_get(prop_warnSound, XV_X) + 65,
			XV_Y,	rect_bottom(rect) + 20,
			PANEL_VALUE_UNDERLINED,		FALSE,
			PANEL_READ_ONLY, 		TRUE,
    		PANEL_INACTIVE, 		nosoundflag,
            PANEL_VALUE_DISPLAY_LENGTH,     15,
			PANEL_LABEL_STRING,		"Mail sound:",
			PANEL_VALUE,			MailSound,
    		PANEL_CLIENT_DATA,         	soundmai,
            NULL);

	  rect = (Rect *)xv_get(prop_mailSound, XV_RECT);


     prop_setSoundmail = (Panel_item) xv_create (proppanel, PANEL_TOGGLE,
            XV_X,   rect_right(rect) + 75,
			XV_X,	(int)xv_get(prop_setSoundwarn, XV_X),
    		PANEL_INACTIVE, 		noMailSoundFlag,
            PANEL_CHOICE_STRINGS,    "Set sound...", "Test sound...", NULL,
    		PANEL_NOTIFY_PROC,		which_mail_choice,
            PANEL_CLIENT_DATA,         button,
            NULL);

	  rect = (Rect *)xv_get(prop_setSoundmail, XV_RECT);


	 prop_sound_output = (Panel_item) xv_create (proppanel, PANEL_CHOICE,
			XV_Y,	rect_bottom(rect) + 10,
    		PANEL_INACTIVE, 				nosoundflag,
            PANEL_LABEL_STRING, "Sound output : ",
            /* PANEL_CHOICE_STRINGS, "Spkr", "Jack", NULL, */
			PANEL_CHOICE_IMAGES, 	    speaker_image,head_phone_image, NULL,
            PANEL_NOTIFY_PROC, 	      sound_output,
			PANEL_VALUE,				soflag,
    		PANEL_CLIENT_DATA,         outputtype,
            NULL);

	  rect = (Rect *)xv_get(prop_sound_output, XV_RECT);


	icon_swapper = (Panel_item) xv_create(proppanel, PANEL_CHOICE,
		    XV_X,	(int)xv_get(prop_sound_output, XV_X),
			XV_Y,	rect_bottom(rect) + 10,
    		PANEL_INACTIVE, 				whoFlag,
            PANEL_LABEL_STRING,        "Icon set: ",
			PANEL_CHOICE_IMAGES, 	    tower_demo, boat_demo, dog_demo, trek_demo, ngtrek_demo, tank_demo, defcon_demo, NULL,
			PANEL_CLIENT_DATA,         	seticon,
			PANEL_VALUE,				iconflag,
            PANEL_NOTIFY_PROC,      show_phase_choice,
			NULL);

	  rect = (Rect *)xv_get(icon_swapper, XV_RECT);

    
     xv_create (proppanel, PANEL_BUTTON,
            PANEL_LABEL_STRING,          "Dismiss",
    		PANEL_CLIENT_DATA,         button,
    		PANEL_NOTIFY_PROC,		view,
            NULL);
    
     xv_create (proppanel, PANEL_BUTTON,
            PANEL_LABEL_STRING,          "Apply",
    		PANEL_CLIENT_DATA,         button,
    		PANEL_NOTIFY_PROC,		apply_props,
            NULL);
    
    
     
      window_fit (proppanel);
      window_fit (propframe);


    	cmdframe = (Frame) xv_create (frame, FRAME_CMD, 
				FRAME_SHOW_FOOTER, 		TRUE,
    			XV_WIDTH,           300,
                XV_HEIGHT,          50,    
                XV_X,               xv_get(frame, XV_X) - 2,
                XV_Y,               xv_get(frame, XV_Y) + 96,
                FRAME_LABEL,        "View log - " ,
                FRAME_LABEL,        rlogfile, 
/*				FRAME_DONE_PROC,	nullfunct, */
                NULL);
    
    	cmdpanel = (Panel) xv_create (cmdframe, PANEL, 
            		XV_X,               xv_get(cmdframe, XV_X) + 2,
            		XV_Y,               xv_get(cmdframe, XV_Y) - 96 ,
                    PANEL_LAYOUT,    PANEL_VERTICAL,
                    NULL);
    
    			 (Panel_item) xv_create (cmdpanel, PANEL_BUTTON,
                   	PANEL_LABEL_STRING,          "Dismiss",
               		PANEL_NOTIFY_PROC,            view,
    				XV_X,						  10,
     				XV_Y,						  5,
                   	NULL);
    		
				(Panel_item) xv_create (cmdpanel, PANEL_BUTTON,
               		XV_X,                         80,
		            XV_Y,                         5,
       		        PANEL_LABEL_STRING,          "Print log",
           		    PANEL_NOTIFY_PROC,            print_list,
               		PANEL_CLIENT_DATA,            button,
		            NULL);


    
    	textsw = (Textsw) xv_create (cmdframe,  TEXTSW,
     
            XV_X,               xv_get(cmdframe, XV_X) + 2,
            XV_Y,               xv_get(cmdframe, XV_Y) - 66 ,
            WIN_ROWS,       20,
            WIN_COLUMNS,    70,
            TEXTSW_DISABLE_LOAD,    TRUE,
    		TEXTSW_BROWSING,	TRUE,
    		WIN_MENU,		nullmenu,
            NULL);
    	
      window_fit(textsw);
      window_fit(cmdpanel);
      window_fit(cmdframe);

	helpframe = (Frame) xv_create (frame, FRAME_CMD, 
    			XV_WIDTH,           450,
                XV_HEIGHT,          50,     
                XV_X,               xv_get(frame, XV_X) - 2,
                XV_Y,               xv_get(frame, XV_Y) + 96,
                FRAME_LABEL,        "- Sentry Help -", 
/*				FRAME_DONE_PROC,	nullfunct,  */
                NULL);
    
    
    	helppanel1 = (Panel) xv_create (helpframe, PANEL, 
                	XV_HEIGHT,          20,     
					WIN_X,		10,
					WIN_Y,		0,
                    NULL);

		info_help =	(Panel_item) xv_create (helppanel1, PANEL_MESSAGE,
						PANEL_LABEL_BOLD,	TRUE,
						PANEL_LABEL_STRING, "Sentry info:",
						NULL);

		info_helptw =	(Textsw) xv_create (helpframe, TEXTSW,
					WIN_BELOW,	helppanel1,
						WIN_X,		10,
						TEXTSW_READ_ONLY,	TRUE,
            			TEXTSW_DISABLE_LOAD,    TRUE,
    					TEXTSW_BROWSING,	TRUE,
    					WIN_MENU,		nullmenu,
						WIN_ROWS, 5,
            			WIN_COLUMNS,    40,
						TEXTSW_CONTENTS, "Sentry allows you to monitor logins to your machine. Notification is through any combination of sound, graphics, or flat file. Intruders are considered to be anyone not contained in the 'Authorized user list', and are currently remotely logged into the host where sentry is running. The 'Authorized user list' may be updated via properties and may contain up to 1024 characters, the user names may be kept in any order, and be separated by any punctuation, spaces, or run together into one long string. This is because sentry evaluates intruders by comparing strings via strstr().",
						NULL);

    	helppanel2 = (Panel) xv_create (helpframe, PANEL, 
                	XV_HEIGHT,          20,     
					WIN_BELOW,	info_helptw,
					WIN_X,		10,
                    NULL);

		time_help = (Panel_item) xv_create (helppanel2, PANEL_MESSAGE,
						PANEL_LABEL_BOLD,	TRUE,
						PANEL_LABEL_STRING, "Search time delay:   ",
						NULL);

		time_helptw = (Textsw) xv_create (helpframe, TEXTSW,
					WIN_X,		10,
						WIN_BELOW,	helppanel2,
						TEXTSW_READ_ONLY,	TRUE,
            			TEXTSW_DISABLE_LOAD,    TRUE,
    					TEXTSW_BROWSING,	TRUE,
    					WIN_MENU,		nullmenu,
						WIN_ROWS, 5,
						WIN_COLUMNS,   40,
						TEXTSW_CONTENTS, "Time in seconds between a check to monitor login activity. The default (30 secs) is highly recommended.",
						NULL);

    	helppanel3 = (Panel) xv_create (helpframe, PANEL, 
                	XV_HEIGHT,          20,     
					WIN_BELOW,	time_helptw,
					WIN_X,		10,
                    NULL);

		file_help = (Panel_item) xv_create (helppanel3, PANEL_MESSAGE,
						PANEL_LABEL_BOLD,	TRUE,
						PANEL_LABEL_STRING, "Record to file:           ",
						NULL);

		file_helptw = (Textsw) xv_create (helpframe, TEXTSW,
					WIN_X,		10,
						WIN_BELOW,	helppanel3,
						TEXTSW_READ_ONLY,	TRUE,
            			TEXTSW_DISABLE_LOAD,    TRUE,
    					TEXTSW_BROWSING,	TRUE,
    					WIN_MENU,		nullmenu,
						WIN_ROWS, 5,
						WIN_COLUMNS,   40,
						TEXTSW_CONTENTS, "Allows you to monitor login activity , via a file kept under your  home directory called '.sentry.txt'.The record to file option is meant to be used while you are away from your machine. A user is logged when they come in (->), and when they leave (<-). 'Clear file' allows you to reset your log file, NOTE: if you reset while someone is logged into your machine, you will not see them in the log again",
						NULL);

    	helppanel4 = (Panel) xv_create (helpframe, PANEL, 
                	XV_HEIGHT,          20,     
					WIN_BELOW,	file_helptw,
					WIN_X,		10,
                    NULL);
		sound_help = (Panel_item) xv_create (helppanel4, PANEL_MESSAGE,
						PANEL_LABEL_BOLD,	TRUE,
						PANEL_LABEL_STRING, "Warning sound:        ",
						NULL);


		sound_helptw = (Textsw) xv_create (helpframe, TEXTSW,
					WIN_X,		10,
						WIN_BELOW,	helppanel4,
						TEXTSW_READ_ONLY,	TRUE,
            			TEXTSW_DISABLE_LOAD,    TRUE,
    					TEXTSW_BROWSING,	TRUE,
    					WIN_MENU,		nullmenu,
						WIN_ROWS, 5,
						WIN_COLUMNS,   40,
						TEXTSW_CONTENTS, "Audiable warning sound to notify you  When a user logs onto your machine  Note: If you do not have the sound files  Found under /usr/demo/SOUNDS, this option will not work. The volume level is in relation to 100% of the allowed volume, the max is 20%, this is so you do not annoy those around you." ,
						NULL);

    	helppanel5 = (Panel) xv_create (helpframe, PANEL, 
                	XV_HEIGHT,          20,     
					WIN_BELOW,	sound_helptw,
					WIN_X,		10,
                    NULL);

		siege_help = (Panel_item) xv_create (helppanel5, PANEL_MESSAGE,
						PANEL_LABEL_BOLD,	TRUE,
						PANEL_LABEL_STRING, "Phases of siege:       ",
						NULL);

		siege_helptw = (Textsw) xv_create (helpframe, TEXTSW,
					WIN_X,		10,
						WIN_BELOW,	helppanel5,
						TEXTSW_READ_ONLY,	TRUE,
            			TEXTSW_DISABLE_LOAD,    TRUE,
    					TEXTSW_BROWSING,	TRUE,
    					WIN_MENU,		nullmenu,
						WIN_ROWS, 5,
						WIN_COLUMNS,   40,
						TEXTSW_CONTENTS, "The 'phases' indicate the number of users currently logged in, or if one user is using on several different ttys (windows). If this option is used the tower icon will start to crumble after more than one user is logged in, this will continue until there are more than five users logged in. The phases are shown below...", 
					NULL);


    	helppanel6 = (Panel) xv_create (helpframe, PANEL, 
					WIN_BELOW,	siege_helptw,
					WIN_X,		10,
                    NULL);

  					(Panel_item)  xv_create (helppanel6, PANEL_MESSAGE,
                  PANEL_LABEL_IMAGE,        gen_s1,	
                  NULL);

  					(Panel_item)  xv_create (helppanel6, PANEL_MESSAGE,
                  PANEL_LABEL_IMAGE,        gen_s2,	
                  NULL);

  					(Panel_item)  xv_create (helppanel6, PANEL_MESSAGE,
                  PANEL_LABEL_IMAGE,        gen_s3,	
                  NULL);

  					(Panel_item)  xv_create (helppanel6, PANEL_MESSAGE,
                  PANEL_LABEL_IMAGE,        gen_s4,	
                  NULL);

  					(Panel_item)  xv_create (helppanel6, PANEL_MESSAGE,
                  PANEL_LABEL_IMAGE,        gen_s5,	
                  NULL);

  					(Panel_item)  xv_create (helppanel6, PANEL_MESSAGE,
                  PANEL_LABEL_IMAGE,        gen_s6,	
                  NULL);


  					(Panel_item)  xv_create (helppanel6, PANEL_MESSAGE,
                  PANEL_LABEL_IMAGE,        gen_s1p,	
                  NULL);

  					(Panel_item)  xv_create (helppanel6, PANEL_MESSAGE,
                  PANEL_LABEL_IMAGE,        gen_s2p,	
                  NULL);

  					(Panel_item)  xv_create (helppanel6, PANEL_MESSAGE,
                  PANEL_LABEL_IMAGE,        gen_s3p,	
                  NULL);

  					(Panel_item)  xv_create (helppanel6, PANEL_MESSAGE,
                  PANEL_LABEL_IMAGE,        gen_s4p,	
                  NULL);

  					(Panel_item)  xv_create (helppanel6, PANEL_MESSAGE,
                  PANEL_LABEL_IMAGE,        gen_s5p,	
                  NULL);

  					(Panel_item)  xv_create (helppanel6, PANEL_MESSAGE,
                  PANEL_LABEL_IMAGE,        gen_s6p,	
                  NULL);


					(Panel_item) xv_create (helppanel6, PANEL_MESSAGE,
						PANEL_LABEL_STRING, "   1 user         2 users       3 users       4 users       5 users       +5 users",
					NULL);

				 xv_set(helppanel6, PANEL_LAYOUT, PANEL_VERTICAL, NULL);

					(Panel_item) xv_create(helppanel6, PANEL_BUTTON,
				  PANEL_LABEL_STRING,			"                                                 Dismiss                                                    ",
               	  PANEL_NOTIFY_PROC,            view,
                  NULL);
/*
	  window_fit(helppanel1);
      window_fit(info_helptw);
      window_fit(helppanel2);
      window_fit(time_helptw);
      window_fit(helppanel3);
      window_fit(file_helptw);
      window_fit(helppanel4);
      window_fit(sound_helptw);
      window_fit(helppanel5);
      window_fit(siege_helptw);
*/

      window_fit(helppanel6);
      window_fit(helpframe); 

}
void
get_list (Panel_item item, int soundType)
{
	int		numfound;
	char 	path[BUFSIZ];

	ff_sound = 1;

		if (getSoundPanelExist)
			xv_destroy(subframe);

		strcpy(path, (char *)xv_get(prop_soundPath, PANEL_VALUE));
		numfound = read_dir(".au", path, soundType);
		if (numfound <= 0)  {
   		     notice_prompt (panel, NULL,
   		     NOTICE_MESSAGE_STRINGS,    "No audio files found at: ", path, NULL,
   		     NULL);
			getSoundPanelExist = FALSE;	
		}
		else
			getSoundPanelExist = TRUE;	
}
int
read_dir(char *word, char *pathptr, int soundType)
{
	Server_image		gen_icon;

	char				sortfile[BUFSIZ];
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

	strcpy (mypathname, pathptr);
	
	       
	strcpy(child, ".");
	strcpy(parent, "..");
	strcpy(sortfile, "/usr/tmp/temp");
	
    if ((outfp = fopen (sortfile, "w")) == NULL) {
        notice_prompt (subpanel, NULL,
          NOTICE_NO_BEEPING,         TRUE,
          NOTICE_MESSAGE_STRINGS,    "Unable to open sort file",
          NULL,  
          NULL);
		  return 0;
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
	if (matchcount > 0) {

    subframe = (Frame)xv_create(frame, FRAME_CMD,
		FRAME_SHOW_RESIZE_CORNER, TRUE,
		XV_SHOW,				FALSE,
        FRAME_LABEL,            "",
        WIN_COLUMNS,            20,
        WIN_ROWS,               25,
        NULL);


  	subpanel = (Panel)xv_create(subframe, PANEL,
		XV_X,					0,
		XV_Y,					0,
		XV_SHOW,				FALSE,
        WIN_COLUMNS,            50,
        WIN_ROWS,               25,
        PANEL_LAYOUT,           PANEL_VERTICAL,
        FRAME_CMD_PUSHPIN_IN,   TRUE,
        NULL);

	if (soundType == WHO) {
		list_warn_choice = (Panel_item)xv_create(subpanel, PANEL_LIST,
			PANEL_LIST_INSERT_DUPLICATE,	FALSE,
			PANEL_READ_ONLY,				TRUE,
			PANEL_LIST_MODE,				PANEL_LIST_READ,
			PANEL_LIST_DISPLAY_ROWS,		10,
        	PANEL_LIST_ROW_HEIGHT,   		35,
        	PANEL_LIST_WIDTH,           	-1,
        	PANEL_LIST_TITLE,           	"Warning Sound choice list",
        	PANEL_NOTIFY_PROC,      		list_notify_proc,
        	NULL);

     	xv_create (subpanel, PANEL_BUTTON,
                   PANEL_LABEL_STRING,          "Dismiss",
                   NULL);
    
	}
    if (soundType == MAIL) { 
        list_mail_choice = (Panel_item)xv_create(subpanel, PANEL_LIST,
            PANEL_LIST_INSERT_DUPLICATE,    FALSE,
            PANEL_READ_ONLY,                TRUE,
            PANEL_LIST_MODE,                PANEL_LIST_READ,
            PANEL_LIST_DISPLAY_ROWS,        10,
            PANEL_LIST_ROW_HEIGHT,          35,
            PANEL_LIST_WIDTH,               -1,   
            PANEL_LIST_TITLE,               "Mail Sound choice list",
            PANEL_NOTIFY_PROC,              list_notify_proc,
            NULL);

     	xv_create (subpanel, PANEL_BUTTON,
                   PANEL_LABEL_STRING,          "Dismiss",
                   NULL);
    } 
	

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
				if (soundType == WHO) {
			    	xv_set(list_warn_choice, 
			    		PANEL_LIST_DELETE, i,
			    		PANEL_LIST_INSERT, i, 
						PANEL_LIST_GLYPH, i, gen_icon,
			    		PANEL_LIST_STRING, i, buffname,
			    		NULL);
				}
				if (soundType == MAIL) {
			    	xv_set(list_mail_choice, 
			    		PANEL_LIST_DELETE, i,
			    		PANEL_LIST_INSERT, i, 
						PANEL_LIST_GLYPH, i, gen_icon,
			    		PANEL_LIST_STRING, i, buffname,
			    		NULL);
				}
		    	i++;
			}
	
	
		} /* end of while fgets */
	
		fclose(fp);
		unlink(sortfile);
			if (soundType == WHO) {
				xv_set(subpanel, XV_WIDTH, (int)xv_get(list_warn_choice, PANEL_LIST_WIDTH) + 50, NULL);
				xv_set(subframe, XV_WIDTH, (int)xv_get(list_warn_choice, PANEL_LIST_WIDTH) + 50, NULL);
			}
			if (soundType == MAIL) {
				xv_set(subpanel, XV_WIDTH, (int)xv_get(list_mail_choice, PANEL_LIST_WIDTH) + 50, NULL);
				xv_set(subframe, XV_WIDTH, (int)xv_get(list_mail_choice, PANEL_LIST_WIDTH) + 50, NULL);
			}
			xv_set(subframe, XV_SHOW, TRUE, NULL);
			xv_set(subpanel, XV_SHOW, TRUE, NULL);
			window_fit(subpanel);
			window_fit(subframe);
	}
	return(matchcount);
} /* end of function */

int
list_notify_proc (Panel_item item, char *string, Xv_opaque client_data, Panel_list_op op, Event *event, int row )
{
       
static	int		interation;
	Frame 		tmpframe;
    Panel 		tmppanel;
    int       	i, value1, value2;
    char  		choice[BUFSIZ];
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
				if (item == list_warn_choice)
	       			choiceptr = (char *)xv_get(list_warn_choice, PANEL_LIST_STRING, row);
				if (item == list_mail_choice)
	       			choiceptr = (char *)xv_get(list_mail_choice, PANEL_LIST_STRING, row);
				token = strtok(choiceptr, " ");
	       		if (token != NULL) {
	       				strl = strlen(token);
	       				bcopy (token, choice, strl);
	       		}
	       		else
						return(op);
	
				if (strcmp(choice, "..") != 0) {
					if (item == list_warn_choice) {
							value1 = (int)xv_get(icon_swapper, PANEL_VALUE);
							value2 = (int)xv_get(prop_setSoundphase, PANEL_VALUE);

	       					xv_set(prop_warnSound, PANEL_VALUE, choice, NULL);  
							strcpy(icons[value1].warSound[value2], (char *)xv_get(prop_warnSound, PANEL_VALUE));  
						
						}
					if (item == list_mail_choice)
	       				xv_set(prop_mailSound, PANEL_VALUE, choice, NULL);  
				}
				else {
					if (item == list_warn_choice) 
	       				xv_set(prop_warnSound, PANEL_VALUE, choice, NULL);  
					if (item == list_mail_choice)
	       				xv_set(prop_mailSound, PANEL_VALUE, choice, NULL);  
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
void
sound_output(Panel_item item, int value, Event event)
{
    Audio_info  aif;
	int  stat;
	extern int errno;

    AUDIO_INITINFO(&aif);
    aif.play.port = (value == 0 ? AUDIO_SPEAKER : AUDIO_HEADPHONE);
    (void) ioctl(Audio_fd, AUDIO_SETINFO, &aif); 
}
void
audio_open()
{
	/* Construct the control device name by appending "ctl" */

	Audio_ctldev = (char*) malloc(strlen(Audio_device) + 4);
	SPRINTF(Audio_ctldev, "%s%s", Audio_device, "ctl");

	if ((Audio_fd = open(Audio_ctldev, O_RDWR)) < 0) {
		fprintf(stderr, "%s: %s ", prog, "Cannot open");
		perror(Audio_ctldev);
	}

	/*
	 * Set the notify flag so that this program (and all others
	 * with this stream open) will be sent a SIGPOLL if changes
	 * are made to the parameters of audio device.
	 */
	if (Audio_fd != NULL) {
		if (ioctl(Audio_fd, I_SETSIG, S_MSG) < 0) {
			fprintf(stderr, "%s: %s ", prog, "Cannot initialize");
			perror(Audio_ctldev);
			exit(1);
		}
	}

	/* Init the state structure so update_panels() will set everything */

	 AUDIO_INITINFO(&Info); 
}
void   
getinfo(ap)
    Audio_info  *ap;
{
	if (Audio_fd != NULL) {
    	if (ioctl(Audio_fd, AUDIO_GETINFO, ap) < 0) {
        	fprintf(stderr, "%s: %s ", prog, "Cannot access");
        	perror(Audio_ctldev);
        	exit(1);
		}
    }  
 
    /* Set the output port to a value we understand */
    ap->play.port = (ap->play.port == AUDIO_SPEAKER ? 0 : 1);
	ap->play.gain = unscale_gain(ap->play.gain);

 
}

Notify_func
sigpoll_handler(Notify_client client, int sig, Notify_signal_mode when)
{
	update_panels();
	return (NOTIFY_DONE);
}    

void
update_panels()
{
	Audio_info	newinfo;
	char		buf[128];

	/* Only change settings that changed, to avoid flashing */
#define	NEWVAL(X, Y)	{						\
			if (newinfo.X != Info.X)			\
			    xv_set(Y, PANEL_VALUE, newinfo.X, NULL);	\
			}

#define	Set_Statuslight(item, on)	xv_set((item),			\
					    PANEL_VALUE, ((on) ? 1 : 0), NULL);

#define	NEWSTATE(X, Y)	{						\
			if (newinfo.X != Info.X)			\
				Set_Statuslight(Y, newinfo.X);		\
			}

#define	NEWSTRING(X, Y) {						\
			if (newinfo.X != Info.X) {			\
				SPRINTF(buf, "%u", newinfo.X);		\
				xv_set(Y, PANEL_LABEL_STRING, buf, NULL); \
			} }

	/* Get the current device state */
	getinfo(&newinfo);

	/* Update main panel items */
	NEWVAL(play.port, prop_sound_output);


	/*
	 * Pause is tricky, since we may be holding the device open.
	 * If 'resume', then release the device, if held.
	 */

	/* Update status panel, if it is visible */

}
void
play_volume_proc(item, value, event)
	Panel_item 	item;
	int		value;
	Event		*event;
{
	Audio_info	aif;

	AUDIO_INITINFO(&aif);
	aif.play.gain = scale_gain(value);
	if (Audio_fd != NULL);
		(void) ioctl(Audio_fd, AUDIO_SETINFO, &aif);

	/* Since the return value is quantized, always update the display */
	Info.play.gain = ~0;
}
unsigned
scale_gain(g)
	unsigned	g;
{
	return (AUDIO_MIN_GAIN + (unsigned)
	    irint(((double) (AUDIO_MAX_GAIN - AUDIO_MIN_GAIN)) *
	    ((double)g / (double)MAX_GAIN)));
}
unsigned
unscale_gain(g)
	unsigned	g;
{
	return ((unsigned) irint((double)MAX_GAIN *
	    (((double)(g - AUDIO_MIN_GAIN)) /
	    (double)(AUDIO_MAX_GAIN - AUDIO_MIN_GAIN))));
}
Notify_value
mon_toggle1(void)
{
	int value;
	int	return_done = FALSE;

	value = (int)xv_get(prop_monitor_toggle, PANEL_VALUE);

	switch(value) {
		case 0:	
			break;
		case 1:
			watch_who();
            return_done = TRUE;
			break;
		case 2:
			break;
		case 3:
			watch_who();
            return_done = TRUE;
			break;
		default:
			printf("Monitor switch value is: %d", value);
			fflush(stdout);
			break;
	}
		if (return_done)
            return NOTIFY_DONE;
}
Notify_value
mon_toggle2(void)
{
    int value;
	int	return_done = FALSE;
 
    value = (int)xv_get(prop_monitor_toggle, PANEL_VALUE);
 
    switch(value) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            watch_mail();
            return_done = TRUE;
            break;
        case 3:
            watch_mail();
            return_done = TRUE;
            break;
        default:                                                
            printf("Monitor switch value is: %d", value);
            fflush(stdout);
            break;
    }
		if (return_done)
            return NOTIFY_DONE;
}

void
sound_flag_toggle(Panel_item item, Event *event)
{

	int value;
 
    value = (int)xv_get(prop_monitor_toggle, PANEL_VALUE);
 
    switch(value) {
        case 0:
			whoFlag = TRUE;
			mailFlag = TRUE;
			xv_set(wprop_sound, PANEL_VALUE, 1, NULL); 
			xv_set(mprop_sound, PANEL_VALUE, 1, NULL); 
			xv_set(wprop_sound, PANEL_INACTIVE, TRUE, NULL); 
			xv_set(mprop_sound, PANEL_INACTIVE, TRUE, NULL); 
            break;
        case 1:
			whoFlag = FALSE;
			mailFlag = TRUE;
			xv_set(frame, FRAME_LEFT_FOOTER, "", NULL);
			xv_set(frame, FRAME_RIGHT_FOOTER, "", NULL);
			/*
			xv_set(wprop_sound, PANEL_VALUE, 0, NULL); 
			xv_set(mprop_sound, PANEL_VALUE, 1, NULL); 
			*/
			xv_set(wprop_sound, PANEL_INACTIVE, FALSE, NULL); 
			xv_set(mprop_sound, PANEL_INACTIVE, TRUE, NULL); 
            break;
        case 2:
			whoFlag = TRUE; 
			mailFlag = FALSE;
			/*
			xv_set(wprop_sound, PANEL_VALUE, 1, NULL);  
			xv_set(mprop_sound, PANEL_VALUE, 0, NULL); 
			*/
			xv_set(mprop_sound, PANEL_INACTIVE, FALSE, NULL); 
			xv_set(wprop_sound, PANEL_INACTIVE, TRUE, NULL); 
            break;
        case 3:
			whoFlag = FALSE;
			mailFlag = FALSE;
			whoFlag = 0;
			mailFlag = 0;
			xv_set(wprop_sound, PANEL_VALUE, 0, NULL); 
			xv_set(mprop_sound, PANEL_VALUE, 0, NULL); 
			xv_set(wprop_sound, PANEL_INACTIVE, FALSE, NULL); 
			xv_set(mprop_sound, PANEL_INACTIVE, FALSE, NULL); 
            break;
        default:
            printf("Monitor switch value is: %d", value);
            fflush(stdout);
            break;
    }
	sound_toggle(item, event);
	xv_set(prop_authlist, PANEL_INACTIVE, whoFlag, NULL);
	xv_set(prop_log_toggle, PANEL_INACTIVE, whoFlag, NULL);
	xv_set(prop_rlogname, PANEL_INACTIVE, whoFlag, NULL);
	xv_set(prop_mfilename, PANEL_INACTIVE, mailFlag, NULL);
	xv_set(prop_warn_slide, PANEL_INACTIVE, whoFlag, NULL);
	xv_set(prop_mail_slide, PANEL_INACTIVE, mailFlag, NULL);
	xv_set(prop_subject_line, PANEL_INACTIVE, mailFlag, NULL);
	xv_set(prop_recfile, PANEL_INACTIVE, whoFlag, NULL);
	xv_set(clear_file, PANEL_INACTIVE, whoFlag, NULL);
	xv_set(icon_swapper, PANEL_INACTIVE, whoFlag, NULL);
}
void
show_phase_choice(Panel_item item, Event *event, int value)
{
	int value1, value2;
	value1 = (int)xv_get(icon_swapper, PANEL_VALUE);
	value2 = (int)xv_get(prop_setSoundphase, PANEL_VALUE);

	switch(value2) {
		case 0:
			xv_set(prop_warnSound, PANEL_LABEL_STRING, "Siege phase 1 Sound: ", NULL);
			xv_set(prop_warnSound, PANEL_VALUE, icons[value1].warSound[value2], NULL);
			break;
		case 1:
			xv_set(prop_warnSound, PANEL_LABEL_STRING, "Siege phase 2 Sound: ", NULL);
			xv_set(prop_warnSound, PANEL_VALUE, icons[value1].warSound[value2], NULL);
			break;
		case 2:
			xv_set(prop_warnSound, PANEL_LABEL_STRING, "Siege phase 3 Sound: ", NULL);
			xv_set(prop_warnSound, PANEL_VALUE, icons[value1].warSound[value2], NULL);
			break;
		case 3:
			xv_set(prop_warnSound, PANEL_LABEL_STRING, "Siege phase 4 Sound: ", NULL);
			xv_set(prop_warnSound, PANEL_VALUE, icons[value1].warSound[value2], NULL);
			break;
		case 4:
			xv_set(prop_warnSound, PANEL_LABEL_STRING, "Siege phase 5 Sound: ", NULL);
			xv_set(prop_warnSound, PANEL_VALUE, icons[value1].warSound[value2], NULL);
			break;
		case 5:
			xv_set(prop_warnSound, PANEL_LABEL_STRING, "Siege phase 6 Sound: ", NULL);
			xv_set(prop_warnSound, PANEL_VALUE, icons[value1].warSound[value2], NULL);
			break;
	}
}
 
