/*
** File: seek_main.c SCCS 8.7 - 7/8/94
** Author:   Matt Stemen
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

#include "seek_main.h" 

#define PRIMEPATH 			"/home/mw2/lc2/XR/systests/utils"
#define SECONDPATH 			"/home/mw2/lc2/XR/systest3/utils"
#define	PRIMENAMEVAL		"Search LC2 Utilites"
#define	SECONDARYNAMEVAL	"Search LC3 Utilites"
#define	ALTPRIMENAMEVAL		"Home"
#define	ALTSECONDARYNAMEVAL	"Local"

#define	TAGVALUE			"/script"
#define	HELPPATHNAME1 "/home/mw/usr/mgs/release/seek/"
#define	HELPPATHNAME2 "/auto/home/mw/usr/mgs/release/seek/"
#define	HELPPATHNAME3 "/auto/home/car1/rti/bin/"




main(argc, argv)
int						argc;
char					*argv[];
{ 
	extern char *optarg;
	extern int	optind;
	extern Panel	panel;
	extern Panel	panel2;
	extern Textsw   textsw;
	extern	char filename[BUFSIZ];
	int		opt = 0, errFlag = 0, i;
    char            path[BUFSIZ], preffile[BUFSIZ], home[BUFSIZ], user[BUFSIZ];
    char            buff[BUFSIZ], tempbuff[BUFSIZ];
	char 			*temp;
	FILE			*pffp;
	char			buf[BUFSIZ];
	Xv_Window		window;

	xv_init(XV_INIT_ARGC_PTR_ARGV, &argc, argv, NULL);

		

    strcpy(path, getenv("HELPPATH"));
    strcpy(home, getenv("HOME"));
    strcpy(user, getenv("USER"));

	sprintf(buf, "HELPPATH=/usr/lib/help:%s:%s:%s", HELPPATHNAME1, HELPPATHNAME2, HELPPATHNAME3);
	putenv(buf);
	editFlag = FALSE;
    strcpy(path, getenv("HOME"));
    strcpy (preffile, path);
    strcat (preffile, "/.seekrc");

	if ((pffp = fopen (preffile, "r")) != NULL) {
    	fgets(buff, BUFSIZ, pffp);
        targetFlag = atoi(strtok(buff, "~"));
		temp = strtok(NULL, "~");

			if (temp != NULL) {
        		if ( *temp != '\n'){
        			strcpy(primaryPath, temp);
            		temp = strtok(NULL, "~");
        		}
        		else
        			strcpy(primaryPath, PRIMEPATH);
        	}
        	else 
            	strcpy(primaryPath, PRIMEPATH);

        	if (temp != NULL) {
           		if ( *temp != '\n'){
                	strcpy(secondaryPath, temp);
                	temp = strtok(NULL, "~");
            	}
            	else
                	strcpy(secondaryPath, SECONDPATH);
        	}
        	else 
            	strcpy (secondaryPath, SECONDPATH);

        if (temp != NULL) { 
            if ( *temp != '\n'){
                strcpy(primaryNameVal, temp);
                temp = strtok(NULL, "~");
            }
            else
                strcpy(primaryNameVal, PRIMENAMEVAL);
        }  
        else   
            strcpy (primaryNameVal, PRIMENAMEVAL);
 
        if (temp != NULL) { 
            if ( *temp != '\n'){ 
                strcpy(secondaryNameVal, temp); 
                temp = strtok(NULL, "~"); 
            } 
            else 
                strcpy(secondaryNameVal, SECONDARYNAMEVAL); 
        } 
        else   
            strcpy (secondaryNameVal, SECONDARYNAMEVAL); 

        if (temp != NULL) { 
            if ( *temp != '\n'){ 
                strcpy(tag, temp); 
                temp = strtok(NULL, "~"); 
            } 
            else 
                strcpy(tag, TAGVALUE); 
        } 
        else   
            strcpy (tag, TAGVALUE); 

        if (temp != NULL) { 
            if ( *temp != '\n'){ 
        		viewFlag = atoi(temp);
				lastView = viewFlag;
                temp = strtok(NULL, "~"); 
            } 
            else  {
        		viewFlag = 7;
        		lastView = 7;
			}
        } 
        else   {
        	viewFlag = 7;
        	lastView = 7;
		}
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_dir = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_dir = 1;
                ff_dir = 1;
            }   
        }   
        else   { 
            ff_dir = 1;
            ff_dir = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_file = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_file = 1;
                ff_file = 1;
            }   
        }   
        else   { 
            ff_file = 1;
            ff_file = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_lnk = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_lnk = 1;
                ff_lnk = 1;
            }   
        }   
        else   { 
            ff_lnk = 1;
            ff_lnk = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_chr = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_chr = 1;
                ff_chr = 1;
            }   
        }   
        else   { 
            ff_chr = 1;
            ff_chr = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_sock = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_sock = 1;
                ff_sock = 1;
            }   
        }   
        else   { 
            ff_sock = 1;
            ff_sock = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_fifo = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_fifo = 1;
                ff_fifo = 1;
            }   
        }   
        else   { 
            ff_fifo = 1;
            ff_fifo = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_empty = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_empty = 1;
                ff_empty = 1;
            }   
        }   
        else   { 
            ff_empty = 1;
            ff_empty = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_core = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_core = 1;
                ff_core = 1;
            }   
        }   
        else   { 
            ff_core = 1;
            ff_core = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_compressed = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_compressed = 1;
                ff_compressed = 1;
            }   
        }   
        else   { 
            ff_compressed = 1;
            ff_compressed = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_csource = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_csource = 1;
                ff_csource = 1;
            }   
        }   
        else   { 
            ff_csource = 1;
            ff_csource = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_object = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_object = 1;
                ff_object = 1;
            }   
        }   
        else   { 
            ff_object = 1;
            ff_object = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_header = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_header = 1;
                ff_header = 1;
            }   
        }   
        else   { 
            ff_header = 1;
            ff_header = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_exe = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_exe = 1;
                ff_exe = 1;
            }   
        }   
        else   { 
            ff_exe = 1;
            ff_exe = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_aml = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_aml = 1;
                ff_aml = 1;
            }   
        }   
        else   { 
            ff_aml = 1;
            ff_aml = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_sound = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_sound = 1;
                ff_sound = 1;
            }   
        }   
        else   { 
            ff_sound = 1;
            ff_sound = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_ps = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_ps = 1;
                ff_ps = 1;
            }   
        }   
        else   { 
            ff_ps = 1;
            ff_ps = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_rast = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_rast = 1;
                ff_rast = 1;
            }   
        }   
        else   { 
            ff_rast = 1;
            ff_rast = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_mail = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_mail = 1;
                ff_mail = 1;
            }   
        }   
        else   { 
            ff_mail = 1;
            ff_mail = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_shell = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_shell = 1;
                ff_shell = 1;
            }   
        }   
        else   { 
            ff_shell = 1;
            ff_shell = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_wp = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_wp = 1;
                ff_wp = 1;
            }   
        }   
        else   { 
            ff_wp = 1;
            ff_wp = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_bm = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_bm = 1;
                ff_bm = 1;
            }   
        }   
        else   { 
            ff_bm = 1;
            ff_bm = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_gif = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_gif = 1;
                ff_gif = 1;
            }   
        }   
        else   { 
            ff_gif = 1;
            ff_gif = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_make = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_make = 1;
                ff_make = 1;
            }   
        }   
        else   { 
            ff_make = 1;
            ff_make = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_info = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_info = 1;
                ff_info = 1;
            }   
        }   
        else   { 
            ff_info = 1;
            ff_info = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_lib = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_lib = 1;
                ff_lib = 1;
            }   
        }   
        else   { 
            ff_lib = 1;
            ff_lib = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_gis = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_gis = 1;
                ff_gis = 1;
            }   
        }   
        else   { 
            ff_gis = 1;
            ff_gis = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_im = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_im = 1;
                ff_im = 1;
            }   
        }   
        else   { 
            ff_im = 1;
            ff_im = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_gra = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_gra = 1;
                ff_gra = 1;
            }   
        }   
        else   { 
            ff_gra = 1;
            ff_gra = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_plt = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_plt = 1;
                ff_plt = 1;
            }   
        }   
        else   { 
            ff_plt = 1;
            ff_plt = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_XRe = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_XRe = 1;
                ff_XRe = 1;
            }   
        }   
        else   { 
            ff_XRe = 1;
            ff_XRe = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_XRs = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_XRs = 1;
                ff_XRs = 1;
            }   
        }   
        else   { 
            ff_XRs = 1;
            ff_XRs = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_XRh = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_XRh = 1;
                ff_XRh = 1;
            }   
        }   
        else   { 
            ff_XRh = 1;
            ff_XRh = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_XRd = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_XRd = 1;
                ff_XRd = 1;
            }   
        }   
        else   { 
            ff_XRd = 1;
            ff_XRd = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
				ff_XRr = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_XRr = 1;
                ff_XRr = 1;
            }   
        }   
        else   { 
            ff_XRr = 1;
            ff_XRr = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
                ff_dos = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_dos = 1;
                ff_dos = 1;
            }   
        }   
        else   { 
            ff_dos = 1;
            ff_dos = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
                ff_pkzip = atoi(temp);
                temp = strtok(NULL, "~");
            }   
            else  {
                ff_pkzip = 1;
                ff_pkzip = 1;
            }   
        }   
        else   { 
            ff_pkzip = 1;
            ff_pkzip = 1;
        }
        if (temp != NULL) {
            if ( *temp != '\n'){
                strcpy(emaxed, temp);
            } 
            else 
                strcpy(emaxed, "epoch");
        }
        else   
            strcpy (emaxed, "epoch");
	}

	else {
		if (strstr(home, "mw") != NULL) {
			strcpy(primaryPath, PRIMEPATH);
			strcpy(secondaryPath, SECONDPATH);
			strcpy(primaryNameVal, PRIMENAMEVAL);
			strcpy(secondaryNameVal, SECONDARYNAMEVAL);
			strcpy(tag, TAGVALUE);
        	viewFlag = 7;
			ff_dir = 1;
			ff_file = 1;
			ff_lnk = 1;
			ff_chr = 1;
			ff_sock = 1;
			ff_fifo = 1;
			ff_empty = 1;
			ff_core = 1;
			ff_compressed = 1;
			ff_icon = 1;
			ff_csource = 1;
			ff_object = 1;
			ff_header = 1;
			ff_exe = 1;
			ff_aml = 1;
			ff_sound = 1;
			ff_ps = 1;
			ff_rast = 1;
			ff_mail = 1;
			ff_shell = 1;
			ff_wp = 1;
			ff_bm = 1;
			ff_gif = 1;
			ff_make = 1;
			ff_info = 1;
			ff_lib = 1;
			ff_gis = 1;
			ff_im = 1;
			ff_gra = 1;
			ff_plt = 1;
			ff_XRe = 1;
			ff_XRs = 1;
			ff_XRh = 1;
			ff_XRd = 1;
			ff_XRr = 1;
            strcpy (emaxed, "epoch");
		}
		else {
			strcpy(primaryPath, home);
			strcpy(secondaryPath, "/local/");
			strcpy(primaryNameVal, user);
			strcpy(secondaryNameVal, ALTSECONDARYNAMEVAL);
			strcpy(tag, TAGVALUE);
        	targetFlag = 1;
        	viewFlag = 7;
	        ff_dir = 1;
            ff_file = 1;
            ff_lnk = 1;
            ff_chr = 1; 
            ff_sock = 1;    
            ff_fifo = 1;    
            ff_empty = 1;   
            ff_core = 1;    
            ff_compressed = 1;  
            ff_icon = 1;    
            ff_csource = 1; 
            ff_object = 1;
            ff_header = 1;    
            ff_exe = 1;
            ff_aml = 1;
            ff_sound = 1;   
            ff_ps = 1;
            ff_rast = 1;    
            ff_mail = 1;    
            ff_shell = 1;   
            ff_wp = 1;
            ff_bm = 1;
            ff_gif = 1;   
            ff_make = 1;    
            ff_info = 1;    
            ff_lib = 1;
            ff_gis = 1;
            ff_im = 1;
            ff_gra = 1;
            ff_plt = 1;
            ff_XRe = 1;
            ff_XRs = 1;
            ff_XRh = 1;
            ff_XRd = 1;
            ff_XRr = 1;
            strcpy (emaxed, "epoch");
		}
			
	}


	unlink(TEMPSORT);
	unlink(TEMPFILE);
	while ((opt = getopt(argc, argv, "f:e")) != -1) {
       switch(opt) {

            case 'f':
                    strcpy(wgFontName, optarg);
                    break;
            case 'e':
					fprintf (stdout, "Editing on \n"); 
					fflush(stdout);
					editFlag = TRUE; 
                    break;
            case '?':
                    break;
        }
	}
	if (strcmp(wgFontName, "") == 0)
        /* strcpy(wgFontName, "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"); */
        strcpy(wgFontName, "r14");

    
	if(errFlag){
        fprintf (stderr, "%s ERROR: Invalid option detected. \n", argv[0]);
        exit(0);
    }

	
    font = (Xv_Font)xv_find(frame, FONT, FONT_NAME, wgFontName, NULL);
	strcpy(authuser, getenv("USER"));
	strcpy(homepath, getenv("HOME"));
	
	frame = (Frame)xv_create(NULL, FRAME,
			FRAME_SHOW_FOOTER,			TRUE,
			XV_FONT,				font,
			FRAME_LABEL,			"Seek - V8.7",
			XV_WIDTH,				585,
			XV_HEIGHT,				600,
			NULL);


	child_create();

	notify_interpose_event_func(panel, seek_event_hand, NOTIFY_SAFE);
	xv_set(frame, FRAME_ICON, icon, NULL);   
	i = strlen(primaryPath);
	/*
	if (primaryPath[i - 1] != '/')
		strcat(primaryPath, "/");
	i = strlen(secondaryPath);
	if (secondaryPath[i - 1] != '/')
		strcat(secondaryPath, "/");
	*/
	window_fit(frame);
	strcpy(filename, primaryPath);
	xv_main_loop(frame);  
}
