/*
** File: ptmain.c SCCS 5.6 - 5/20/94 
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

#include "ptmain.h"
#define HELPPATHNAME1 "/home/mw/usr/mgs/release/phonetool/"
#define HELPPATHNAME2 "/auto/home/mw/usr/mgs/release/phonetool/"
#define HELPPATHNAME3 "/auto/home/car1/rti/bin/"


Xv_screen	screen;

extern  Xv_singlecolor colors[7];

extern  Xv_singlecolor nocolors[7];


main(int argc, char *argv[])


{ 

FILE                *pffp, *fp;
char				*winProc;
char				*cmd;
char                searchstr[BUFSIZ], searchfile[BUFSIZ];
char                buff[BUFSIZ], tempbuff[BUFSIZ], rcprinter[BUFSIZ];
char 				readline[BUFSIZ];
char				*temp, *found_printer;
int					i, opt, errflag = 0;
extern char         *optarg;
extern  int     	optind;
char            buf[BUFSIZ];
int				soundexOn = FALSE, tol = -1, fieldVal = -1;


 
/* initialize xview       */

	cmd = "/bin/ps -aux | /bin/grep openwin | /bin/grep -v grep";

	if ((pffp = popen(cmd, "r")) != NULL) {
		fgets(readline, BUFSIZ, pffp);
		if (strlen(readline) >= 2) 
    		xv_init(XV_INIT_ARGC_PTR_ARGV, &argc, argv, NULL);
		pclose(pffp);
	}

/* initialize variables    */  
	unlink (TEMPFILE);
    strcpy(authuser, getenv("USER"));
    strcpy(homepath, getenv("HOME"));


    sprintf(buf, "HELPPATH=/usr/lib/help:%s:%s:%s", HELPPATHNAME1, HELPPATHNAME2, HELPPATHNAME3);
    putenv(buf);

    strcpy (defaultfilename, "");
    strcat (defaultfilename,homepath); 
    strcat (defaultfilename, "/.phone.txt");
    strcpy (defaultcompname, "/home/toolset/bin/phones/phone.txt");

	found_printer = (char *)read_rc();
	strcpy(rcprinter, found_printer);


	if (argc > 1 ){
    	strcpy(searchfile, compfilename);
		if (argc <= 6 ){
        	while ((opt = getopt(argc, argv, "x:f:h")) != -1) 
			{
            	switch(opt) {
					case 'x':
						tol = atoi(optarg);
						if (argv[optind] != NULL)
							fieldVal = atoi(argv[optind]);
						else
							fieldVal = 1;
						if (tol == 0 || tol == -1 )
							tol = 75;
						if (fieldVal == 0 || fieldVal == -1)
							fieldVal = 1;
						soundexOn = TRUE;
						break;
                	case 'f':
						if ( strcmp (optarg, "p") == 0)
                    		strcpy(searchfile, personfilename);
						else if ( strcmp (optarg, "c") == 0)
                    		strcpy(searchfile, compfilename);
						else
							errflag++;

                    	break;
					case 'h':
							errflag++;
					case '?':
						/*
                		fprintf (stderr, "%s ERROR: Invalid option detected. \n", argv[0]);
						*/
        				fprintf (stderr, "\n \n Usage: %s -[options] string \n \n", argv[0]);
						fprintf (stderr, "options:\n\n");
						fprintf (stderr, "  -fc Search company file ( the default)\n");
						fprintf (stderr, "  -fp Search personal file\n");
						fprintf (stderr, "  -x (soundex match) followed by (percent) (field value)\n");
						fprintf (stderr, "    The percent is how the match found should soundlike the sting (default: 75%)\n");
						fprintf (stderr, "    The field value is which field to match against, where:\n");
						fprintf(stderr, "       field value 1 = Last Name (the default)\n");
						fprintf(stderr, "       field value 2 = First Name\n");
						fprintf(stderr, "       field value 3 = All fields\n");
						exit(0);
                    	break;
            	}
			}
    
 
            if(errflag){
                fprintf (stderr, "\n \n Usage: %s -[options] string \n \n", argv[0]);
                fprintf (stderr, "options:\n\n");
                fprintf (stderr, "  -fc Search company file ( the default)\n");                                              
                fprintf (stderr, "  -fp Search personal file\n");
                fprintf (stderr, "  -x (soundex match) followed by (percent) (field value)\n");                              
                fprintf (stderr, "    The percent is how the match found should soundlike the sting (default: 75%)\n");
                fprintf (stderr, "    The field value is which field to match against, where:\n");
                fprintf(stderr, "       field value 1 = Last Name (the default)\n");
                fprintf(stderr, "       field value 2 = First Name\n");
                fprintf(stderr, "       field value 3 = All fields\n");
                exit(0);
            }
            else {
				if (argv[argc -1] != NULL) {
					strcpy(searchstr, argv[argc - 1]);
				
					if (soundexOn) 
             			batchreadfile_soundex(searchfile, searchstr, tol, fieldVal - 1);
					else
             			batchreadfile(searchfile, searchstr);
                	exit(0);
				}
			}
		}
		else {
            fprintf (stderr, "\n \n Usage: %s -[options] string \n \n", argv[0]);
            fprintf (stderr, "options:\n\n");
            fprintf (stderr, "  -fc Search company file ( the default)\n");                                              
            fprintf (stderr, "  -fp Search personal file\n");
            fprintf (stderr, "  -x (soundex match) followed by (percent) (field value)\n");                              
            fprintf (stderr, "    The percent is how the match found should soundlike the sting (default: 75%)\n");
            fprintf (stderr, "    The field value is which field to match against, where:\n");
            fprintf(stderr, "       field value 1 = Last Name (the default) \n");
            fprintf(stderr, "       field value 2 = First Name\n");
            fprintf(stderr, "       field value 3 = All fields\n");
        	exit(0);
		}
    }

	else{


		
	/* create parent frame for all sub-frames    */

    frame = (Frame)xv_create (XV_NULL, FRAME,
		XV_HEIGHT,			350,
		XV_WIDTH,			910,
		FRAME_LABEL,       "Phone Tool - V5.6",
        NULL);
	
	/* get default screen for the frame to use for the cms */
	
	screen = (Xv_screen)xv_get(frame, XV_SCREEN);

	/* define cms */	

	phonetoolcms =   (Cms)xv_create(screen, CMS,
					 CMS_COLOR_COUNT,		CMS_CONTROL_COLORS + 6,
                     CMS_TYPE,              XV_DYNAMIC_CMS,
                     CMS_CONTROL_CMS,       TRUE,
                     CMS_SIZE,              CMS_CONTROL_COLORS + 6,
                     NULL);

 	if (! colorflag) 
		xv_set(phonetoolcms, CMS_COLORS, colors, NULL); 
	else
		xv_set(phonetoolcms, CMS_COLORS, nocolors, NULL); 
			
	/* create all panels, panel_items, textsw, cmd_frames, etc.  */

	create_children();


	/* setup flag for filename defaults */
 
	if ((strcmp(personfilename, defaultfilename) == 0) && (strcmp(compfilename, defaultcompname) == 0)) {
		xv_set( prop_editor, PANEL_VALUE, 10, NULL);   
		propeditflag = 10;
	}

	else if ((strcmp(personfilename, defaultfilename) != 0) && (strcmp(compfilename, defaultcompname) != 0)) {

		xv_set( prop_editor, PANEL_VALUE, 5, NULL);
		xv_set (george, PANEL_READ_ONLY, FALSE, NULL);
        xv_set(george, PANEL_VALUE_UNDERLINED, TRUE,  NULL);
        xv_set(george, PANEL_INACTIVE, FALSE, NULL);
		propeditflag = 5;

        xv_set (prop_infile, PANEL_READ_ONLY, FALSE, NULL);
        xv_set(prop_infile, PANEL_VALUE_UNDERLINED, TRUE,  NULL);
        xv_set(prop_infile, PANEL_INACTIVE, FALSE, NULL);
	}

	else if ((strcmp(personfilename, defaultfilename) == 0) && (strcmp(compfilename, defaultcompname) != 0)) {

		xv_set( prop_editor, PANEL_VALUE, 9, NULL);
		xv_set (george, PANEL_READ_ONLY, FALSE, NULL);
        xv_set(george, PANEL_VALUE_UNDERLINED, TRUE,  NULL);
        xv_set(george, PANEL_INACTIVE, FALSE, NULL);
		propeditflag = 9;
	}

	else if ((strcmp(personfilename, defaultfilename) != 0) && (strcmp(compfilename, defaultcompname) == 0)) {
		xv_set( prop_editor, PANEL_VALUE, 6, NULL);
        xv_set (prop_infile, PANEL_READ_ONLY, FALSE, NULL);
        xv_set(prop_infile, PANEL_VALUE_UNDERLINED, TRUE,  NULL);
        xv_set(prop_infile, PANEL_INACTIVE, FALSE, NULL);
		propeditflag = 6;
	}

		
	/* read printcap and alloctate buttons on the fly   */
 
	getprint_list(rcprinter);

	/* setup frames cms, background + foreground colors, icons etc.  */ 

	xv_set (frame, WIN_CMS, phonetoolcms, NULL);
	xv_set(frame, WIN_FOREGROUND_COLOR, CMS_CONTROL_COLORS + BASECOLOR, NULL);
	xv_set(frame, WIN_BACKGROUND_COLOR,	CMS_CONTROL_COLORS + SCREENCOLOR, NULL);
    xv_set (frame, FRAME_ICON, icon, NULL);   
    window_fit (frame);

	lastchoice = propeditflag;


    strcpy (oldLabel, (char *)xv_get(frame, FRAME_LABEL));
    strcpy (newLabel, oldLabel);
    strcat (newLabel, " - Soundex On -");

    switch ( (int) xv_get (prop_soundex_toggle, PANEL_VALUE)) {
 
        case 0:
 
            xv_set(frame, FRAME_LABEL, newLabel, NULL);
            break;
 
        case 1:
            xv_set(frame, FRAME_LABEL, oldLabel, NULL);
            break;
 
 
        default:
                break;
 
    }

	/* start notifer */

		if (strcmp(rcprinter, "") == 0) {
			notice_prompt (frame, NULL,
        	NOTICE_NO_BEEPING,         TRUE,
			NOTICE_BUTTON,	"Continue...", 0,
        	NOTICE_MESSAGE_STRINGS,    "Welcome to phonetool (pt) (pta)",
			"",
        	" In addition to the GUI interface you may also ", 
        	" Use phonetool's command line interface  ",
			" The usage is: ",
			"",
			" pt -[options] (string)",
		    "",	
			" options:",
		    "",	
			"		-fp is search your personal phone file for a match",
			"		-fc is search the company phone file for a match",
			"		-x  is a soundex match",
		    "",	
		    "Examples :",
		    "",	
			"	 \"pt John -fp\"  Would find all occurances of \"John\" or \"john\" in your personal file",	
			"",
			"Note: All searches are NOT case sensitive.",

			"To find out more about the phonetool operations",
			"Simply focus the mouse over button, text, or slider",
			"and press the \"Help\" key located on your keyboard",
        	NULL);
			writerc_file();
		}

		notify_set_signal_func(dialframe, sigpoll_handler, SIGPOLL, NOTIFY_SYNC);  
		audio_open();
  		update_panels();
    	xv_main_loop (frame);  
	}
}
