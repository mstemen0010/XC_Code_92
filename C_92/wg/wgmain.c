/*
** File: %M% SCCS %I% - %G%
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

#include "wgmain.h" 




main(argc, argv)
int						argc;
char					*argv[];
{ 
	extern char *optarg;
	extern int	optind;
	int		opt = 0, errFlag = 0;

	xv_init(XV_INIT_ARGC_PTR_ARGV, &argc, argv, NULL);

	unlink(TEMPSORT);
	unlink(TEMPFILE);
	while ((opt = getopt(argc, argv, "f:")) != -1) {
       switch(opt) {

            case 'f':
                    strcpy(wgFontName, optarg);
                    break;
            case '?':
                    break;
        }
	}
	if (strcmp(wgFontName, "") == 0)
        strcpy(wgFontName, "newcenturyschlbk-bold");

    
	if(errFlag){
        fprintf (stderr, "%s ERROR: Invalid option detected. \n", argv[0]);
        exit(0);
    }

    font = (Xv_Font)xv_find(frame, FONT, FONT_NAME, wgFontName, NULL);
	strcpy(authuser, getenv("USER"));
	strcpy(homepath, getenv("HOME"));
	frame = (Frame)xv_create(XV_NULL, FRAME,
			FRAME_LABEL,			"Word Guide   V%I%",
			XV_FONT,				font,
			NULL);

	child_create();

	xv_set(frame, FRAME_ICON, icon, NULL);   
	window_fit(frame);
	xv_main_loop(frame);  
}




