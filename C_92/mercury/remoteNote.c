/*
** File: remoteNote.c SCCS 1.10 - 8/4/94
** Author:   Matt Stemen
**
** Created:  7/21/93
** Edited:
**
**
** Purpose:
**
*/


#include "remoteNote.h"

#define	PERMS				0666
#define	LPERMS				0644
#define	PERMS7				0777
#define	GC_KEY   			10
#define CLEAR_CANVAS 		1
#define WRITE_CANVAS 		2
#define	LEFT 				1
#define	RIGHT 				2
#define	SEND 				1
#define	CLEAR 				2
#define	PALEYELLOW 			0
#define SKYBLUE				1
#define PALEGREEN			2
#define	PEACH				3
#define PINK				4
#define CANWIDTH			550
#define TAB					9
#define	RETURN				13
#define	ASCII_SPAN_START	33 /* '!' */
#define	ASCII_SPAN_END		119 /* 'w' */

int		repaint_com = CLEAR_CANVAS + WRITE_CANVAS;
int		mess_x = 10,	mess_y = 25;
char	message[BUFSIZ];
char	user[16];
char	home[BUFSIZ];
char	hostname[64];
char	noteQName[BUFSIZ];
Xv_font			mainfont, canvasfont;
char	fontType[BUFSIZ] = FONT_FAMILY_LUCIDA;
int		fontSize = 24;
int		colorInt = PALEYELLOW;
int		readfd;
int		noteCount = 0; 
int		totLetterCount = 0;

main(argc,argv)
int     argc;
char    *argv[];
{
	FILE			*fp;
	int				len1, len2;
	extern	int		errno;
	Rect			*rect;
	char			*token;
    /*
     * Initialize, create base frame (with footers) and create canvas.
     */
    xv_init(XV_INIT_ARGS, argc, argv, NULL);

	strcpy(pathname, "");
	strcpy(user, getenv("USER"));
	strcpy(home, getenv("HOME"));
	gethostname(hostname, 64);
	strcat(noteQName, home);
	strcat(noteQName, "/");
	strcat(noteQName, user);
	strcat(noteQName, ".noteQ");
	len1 = strlen(home);
	token = strstr(home, user);
	len2 = strlen(token);
	bcopy(home, pathname, len1 - len2);
	
	noteTimer.it_value.tv_sec = 1;
	noteTimer.it_interval.tv_sec = 10;

    frame = (Frame)xv_create(NULL,FRAME,
		XV_HEIGHT,				25,
		XV_WIDTH,				400,
        FRAME_LABEL,            "Mercury V1.10",
        FRAME_SHOW_FOOTER,      TRUE,
        NULL);

  	if ((readfd = open(noteQName, O_RDWR | O_NDELAY)) < 0) {
        if ((readfd = open(noteQName, O_RDWR | O_CREAT | PERMS)) < 0) {
            fprintf (stderr, "Mercury: Unable to open note queue: %s\n", noteQName);
            fflush (stdout);
            exit(0);
        }
        else {
            sprintf(message, "Created note queue: %s\n", noteQName);
            write_footer(frame, message, LEFT);
            chmod(noteQName, PERMS);
        }
	}
	else
	{
            sprintf(message, "Queue already present, not creating new queue");
            write_footer(frame, message, LEFT);
	}

/*
  	if ((readfd = open(noteQName, O_RDWR | O_NDELAY)) < 0) {

	
    comment this out from here 

 		if ((mkfifo(fifoName, S_IFIFO | PERMS) < 0) && (errno != EEXIST)) {
        	fflush (stderr);
        	unlink(fifoName);
        	exit(0);
    	}

	to here

  		if ((readfd = open(noteQName, O_RDWR | O_CREAT | PERMS)) < 0) {
    		fprintf (stderr, "Mercury: Unable to open note queue: %s\n", noteQName);
        	fflush (stdout);
			exit(0);
		}
		else {
    		sprintf(message, "Created note queue: %s\n", noteQName);
			write_footer(frame, message, LEFT);
			chmod(noteQName, PERMS);
		}
	}
	else {
		fprintf(stderr, "\n\n Mercury already running. \n");
		fprintf(stderr, "You may only run one instance of Mercury at a time. \n");
		fprintf(stderr, "bye... \n\n\n");
		exit(0);
	}

*/

	mainfont = (Xv_Font)xv_find(frame, FONT, 
		FONT_FAMILY,		FONT_FAMILY_LUCIDA_FIXEDWIDTH,
		FONT_STYLE,			FONT_STYLE_NORMAL,
		FONT_SIZE,			16,
		NULL);

	canvasfont = (Xv_Font)xv_find(frame, FONT, 
		FONT_FAMILY,		fontType,
		FONT_STYLE,			FONT_STYLE_BOLD,
        FONT_SIZE,          fontSize,
		NULL);

    screen = (Xv_screen)xv_get(frame, XV_SCREEN);
 
 
    memoCms = (Cms) xv_create(screen, CMS,
        CMS_CONTROL_CMS,       TRUE,
        CMS_COLOR_COUNT,    CMS_CONTROL_COLORS + 7,
        CMS_TYPE,           XV_STATIC_CMS,
        CMS_SIZE,           CMS_CONTROL_COLORS + 7,
        CMS_NAMED_COLORS,   "lightgoldenrod2", "powderblue", "palegreen1", "peachpuff1", "pink", "black", NULL,
        NULL);

	panel = (Panel)xv_create(frame, PANEL,
		XV_HEIGHT,				100,
		XV_WIDTH,				400,
        NULL);

    sendNote_button = xv_create (panel, PANEL_BUTTON,
               PANEL_LABEL_STRING,          "Send a Note",
               PANEL_CLIENT_DATA,            frame,
               PANEL_NOTIFY_PROC,            callSendFrame,
               NULL);
 
    xv_create (panel, PANEL_BUTTON,
               PANEL_LABEL_STRING,          "Properties",
               PANEL_CLIENT_DATA,            frame,
               PANEL_NOTIFY_PROC,            callPropFrame,
               NULL);
 
    xv_create (panel, PANEL_BUTTON,
               PANEL_LABEL_STRING,          "Quit",
               PANEL_CLIENT_DATA,            frame,
               PANEL_NOTIFY_PROC,            quiteFrame,
               NULL);

	rect = (Rect *)xv_get(frame, XV_RECT);

    send_frame = (Frame)xv_create(frame, FRAME_CMD,
	    XV_X,					(int)xv_get(frame, XV_X),
	    XV_Y,					(int)xv_get(frame, XV_Y),
	 	FRAME_CMD_PIN_STATE,	FRAME_CMD_PIN_IN, 
		XV_HEIGHT,				500,
		XV_WIDTH,				350,
        FRAME_LABEL,            "Send a Note",
        FRAME_SHOW_FOOTER,      TRUE,
        NULL);

	send_panel = (Panel)xv_create(send_frame, PANEL,
		XV_FONT,				mainfont,
		PANEL_LAYOUT,			PANEL_VERTICAL,
		XV_X,		0,
		XV_Y,		0,
		XV_HEIGHT,				500,
		XV_WIDTH,				350,
        NULL);

	/*
	xv_set(send_panel, WIN_EVENT_PROC, wrapAround, NULL);
	*/

	uPathLine = (Panel_item)xv_create(send_panel, PANEL_TEXT,
				PANEL_VALUE,				pathname,
				PANEL_LABEL_STRING,			"pathname:",
				PANEL_VALUE_UNDERLINED,     FALSE,
				PANEL_VALUE_DISPLAY_LENGTH, 	32,
				PANEL_VALUE_STORED_LENGTH,   	32,
				NULL);


	toLine = (Panel_item)xv_create(send_panel, PANEL_TEXT,
				PANEL_LABEL_STRING,			"To:",
				PANEL_VALUE_UNDERLINED,     FALSE,
				PANEL_VALUE_DISPLAY_LENGTH, 	8,
				PANEL_VALUE_STORED_LENGTH,   	8,
				NULL);

	xv_set(send_panel, PANEL_CARET_ITEM, toLine, NULL);

	noteLine1 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
				PANEL_VALUE_UNDERLINED,     TRUE,
				PANEL_VALUE_DISPLAY_LENGTH, 	30,
				PANEL_VALUE_STORED_LENGTH,   	30,
				NULL);

	noteLine2 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
				PANEL_VALUE_UNDERLINED,     TRUE,
				PANEL_VALUE_DISPLAY_LENGTH, 	30,
				PANEL_VALUE_STORED_LENGTH,   	30,
				NULL);

	noteLine3 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
				PANEL_VALUE_UNDERLINED,     TRUE,
				PANEL_VALUE_DISPLAY_LENGTH, 	30,
				PANEL_VALUE_STORED_LENGTH,   	30,
				NULL);

	noteLine4 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
				PANEL_VALUE_UNDERLINED,     TRUE,
				PANEL_VALUE_DISPLAY_LENGTH, 	30,
				PANEL_VALUE_STORED_LENGTH,   	30,
				NULL);

	noteLine5 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
				PANEL_VALUE_UNDERLINED,     TRUE,
				PANEL_VALUE_DISPLAY_LENGTH, 	30,
				PANEL_VALUE_STORED_LENGTH,   	30,
				NULL);

    noteLine6 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
                PANEL_VALUE_UNDERLINED,     TRUE,
                PANEL_VALUE_DISPLAY_LENGTH,     30,
                PANEL_VALUE_STORED_LENGTH,      30,
                NULL);

    noteLine7 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
                PANEL_VALUE_UNDERLINED,     TRUE,
                PANEL_VALUE_DISPLAY_LENGTH,     30,
                PANEL_VALUE_STORED_LENGTH,      30,
                NULL);

    noteLine8 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
                PANEL_VALUE_UNDERLINED,     TRUE,
                PANEL_VALUE_DISPLAY_LENGTH,     30,
                PANEL_VALUE_STORED_LENGTH,      30,
                NULL);

    noteLine9 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
                PANEL_VALUE_UNDERLINED,     TRUE,
                PANEL_VALUE_DISPLAY_LENGTH,     30,
                PANEL_VALUE_STORED_LENGTH,      30,
                NULL);

    noteLine10= (Panel_item)xv_create(send_panel, PANEL_TEXT,
                PANEL_VALUE_UNDERLINED,     TRUE,
                PANEL_VALUE_DISPLAY_LENGTH,     30,
                PANEL_VALUE_STORED_LENGTH,      30,
                NULL);

	send_button = xv_create (send_panel, PANEL_TOGGLE,
               PANEL_CHOICE_STRINGS,          "  Send it  ", "  Clear note  ", NULL,
               PANEL_CLIENT_DATA,            frame,
			   PANEL_NOTIFY_PROC,			 sendNote,
               NULL);    


    screen = (Xv_screen)xv_get(frame, XV_SCREEN);
 
 
    memo_image = (Server_image)xv_create(XV_NULL, SERVER_IMAGE,
        XV_HEIGHT,          64,
        XV_WIDTH,           64,
        SERVER_IMAGE_BITS,  memo_bits,
        NULL);
 
    memo2_image = (Server_image)xv_create(XV_NULL, SERVER_IMAGE,
        XV_HEIGHT,          64,
        XV_WIDTH,           64,
        SERVER_IMAGE_BITS,  memo2_bits,
        NULL);
 
    memo_example_image = (Server_image)xv_create(XV_NULL, SERVER_IMAGE,
        XV_HEIGHT,          64,
        XV_WIDTH,           64,
        SERVER_IMAGE_BITS,  memo_example_bits,
        NULL);
 
    memo_mask_image = (Server_image)xv_create(XV_NULL, SERVER_IMAGE,
        XV_HEIGHT,          64,
        XV_WIDTH,           64,
        SERVER_IMAGE_BITS,  memo_mask_bits,
        NULL);

    memo2_mask_image = (Server_image)xv_create(XV_NULL, SERVER_IMAGE,
        XV_HEIGHT,          64,
        XV_WIDTH,           64,
        SERVER_IMAGE_BITS,  memo2_mask_bits,
        NULL);

	memo_icon = (Icon)xv_create(frame, ICON,
        WIN_CMS,            memoCms,
        ICON_IMAGE,         memo_image,
        ICON_MASK_IMAGE,    memo_mask_image,
        ICON_TRANSPARENT,   TRUE,
        XV_HEIGHT,          64,
        XV_WIDTH,           64,
        WIN_FOREGROUND_COLOR, CMS_CONTROL_COLORS + 6,
        WIN_BACKGROUND_COLOR, CMS_CONTROL_COLORS + colorInt,
        NULL);

    prop_frame = (Frame)xv_create(frame, FRAME_CMD,
		WIN_CMS,				memoCms,
        XV_X,                   (int)xv_get(frame, XV_X),
        XV_Y,                   (int)xv_get(frame, XV_Y),
        XV_HEIGHT,              200,
        XV_WIDTH,               625,
        FRAME_LABEL,            "Properties for Mercury",
        FRAME_SHOW_FOOTER,      TRUE,
        NULL);

    prop_panel = (Panel)xv_create(prop_frame, PANEL,
        PANEL_LAYOUT,           PANEL_VERTICAL,
        XV_X,       0,
        XV_Y,       0,
        XV_HEIGHT,              200,
        XV_WIDTH,               625,
        NULL);

	propFont_choice = xv_create (prop_panel, PANEL_CHOICE,
               PANEL_LABEL_STRING,          "Note font Type:", 
			   PANEL_CHOICE_STRINGS, "Lucida", "Courier", "Rockwell", "Helvetica", "Times", "New century schoolbook",  NULL,
               PANEL_CLIENT_DATA,            frame,
			   PANEL_NOTIFY_PROC,			 setFont,
               NULL);    

	propColor_choice = xv_create (prop_panel, PANEL_CHOICE,
               PANEL_LABEL_STRING,          "Note pad Color:", 
				/*
			   PANEL_CHOICE_STRINGS, "Yellow", "Blue", "Green", "Peach","Pink", NULL,
				*/
			   PANEL_CHOICE_IMAGES, memo_example_image, memo_example_image, memo_example_image, memo_example_image, memo_example_image, NULL,
			   PANEL_CHOICE_COLOR, 0,	CMS_CONTROL_COLORS + PALEYELLOW,
			   PANEL_CHOICE_COLOR, 1,	CMS_CONTROL_COLORS + SKYBLUE,
			   PANEL_CHOICE_COLOR, 2,	CMS_CONTROL_COLORS + PALEGREEN,
			   PANEL_CHOICE_COLOR, 3,	CMS_CONTROL_COLORS + PEACH,
			   PANEL_CHOICE_COLOR, 4,	CMS_CONTROL_COLORS + PINK,
               PANEL_CLIENT_DATA,            frame,
			   PANEL_NOTIFY_PROC,			 setColor,
               NULL);    

    xv_create (prop_panel, PANEL_BUTTON,
               PANEL_LABEL_STRING,          "Reset note counter",
               PANEL_CLIENT_DATA,            frame,
               PANEL_NOTIFY_PROC,            resetCount,
               NULL);
 
    xv_create (prop_panel, PANEL_BUTTON,
               PANEL_LABEL_STRING,          "Dismiss",
               PANEL_CLIENT_DATA,            frame,
               NULL);




	xv_set(frame, WIN_CMS, memoCms, NULL);
	xv_set(frame, FRAME_ICON, memo_icon, NULL);
	xv_set(frame, WIN_FOREGROUND_COLOR, CMS_CONTROL_COLORS + 6, NULL);
	xv_set(frame, WIN_BACKGROUND_COLOR, CMS_CONTROL_COLORS + colorInt, NULL);
		

	dpy = (Display *)xv_get(frame, XV_DISPLAY);
	gcvalues.font = (Font)xv_get(canvasfont, XV_XID);
	gcvalues.foreground = BlackPixel(dpy, DefaultScreen(dpy));
	gcvalues.background = WhitePixel(dpy, DefaultScreen(dpy));
	gcvalues.graphics_exposures = FALSE; 
	gc = XCreateGC(dpy, RootWindow(dpy, DefaultScreen(dpy)), GCForeground | GCBackground | GCFont | GCGraphicsExposures, &gcvalues);

	

    (void) xv_create(canvas, SCROLLBAR,
        SCROLLBAR_DIRECTION,    SCROLLBAR_VERTICAL,
        NULL);
    (void) xv_create(canvas, SCROLLBAR,
		XV_X,					0,
        SCROLLBAR_DIRECTION,    SCROLLBAR_HORIZONTAL,
        NULL);

    /*
     *  Set input mask
     */
	notify_set_itimer_func(client, read_message, ITIMER_REAL, &noteTimer, NULL);
	notify_set_signal_func(frame, clean_up, SIGINT, NOTIFY_ASYNC);
	notify_interpose_event_func(send_panel, wrapAround, NOTIFY_SAFE);

    xv_main_loop(frame);
	unlink(noteQName);
}

/*
 * when a viewport is split, this routine is called.
 */

void
init_split(splitview, newview, pos)
Xv_Window splitview, newview;
int pos;
{
    Xv_Window   view;
    int         i = 0;

    /*
     * Determine view # from the new view and set its scrollbar to 0,0
     */
    OPENWIN_EACH_VIEW(canvas, view)
        if (view == splitview) {
            /* identify the view # of the view the user just split. */
            sprintf(msg, "Split view #%d", i+1);
            xv_set(frame, FRAME_LEFT_FOOTER, msg, NULL);
        } else if (view == newview) {
            xv_set(xv_get(canvas, OPENWIN_VERTICAL_SCROLLBAR, view),
                SCROLLBAR_VIEW_START, 0,
                NULL);
            xv_set(xv_get(canvas, OPENWIN_HORIZONTAL_SCROLLBAR, view),
                SCROLLBAR_VIEW_START, 0,
                NULL);
        }
        i++;
    OPENWIN_END_EACH
    sprintf(msg, "Total views: %d", i);
    xv_set(frame, FRAME_RIGHT_FOOTER, msg, NULL);
}

/*
 * Called when an event is received in an arbitrary paint window.
 */
void
my_event_proc(window, event)
Xv_Window       window;
Event           *event;
{
    register char *p = msg;
	Frame		  tmpFrame;
	Canvas		  tmpCanvas;
	Window		  tmpWindow; 

    *p = 0;

	tmpWindow = (Window)xv_get(window, XV_OWNER);
	tmpCanvas = (Canvas)xv_get(tmpWindow, XV_OWNER);
	tmpFrame = (Frame)xv_get(tmpCanvas, XV_OWNER);
	switch (event_action(event)) {
		case WIN_RESIZE :
        case WIN_REPAINT :
            return;
		case ACTION_SELECT:
			xv_destroy_safe(tmpFrame);
			break;

        default :
            /* There are too many ACTION events to trap -- ignore the
             * ones we're not interested in.
             */
            return;
    }

}

/*
 * my_repaint_proc()
 *      Called to repaint the canvas in response to damage events
 *      and the initial painting of the canvas window.
 *      Displays the keyboard, pointer and button message strings
 *      after erasing the previous messages.
 */
void
my_repaint_proc(Xv_Window pw, Display *dpy, Window xwin, Xv_xrectlist *xrects)
{
    Xv_Window   w;
    int         i = 0;

    /*
     * Determine which paint window we're writing in.
     */

	switch (repaint_com) {
		case CLEAR_CANVAS:
    		XClearWindow(dpy, xwin);
			break;

		case WRITE_CANVAS:
    		XDrawString(dpy, xwin, gc, mess_x, mess_y, msg, strlen(msg));
			break;

		case CLEAR_CANVAS +  WRITE_CANVAS:
    		XClearWindow(dpy, xwin);
    		XDrawString(dpy, xwin, gc, mess_x, mess_y, msg, strlen(msg));
			break;
	}
}
Notify_value
read_message(Notify_client client, int which)
{
	time_t			thisTime = 0; 
	static	time_t	lastTime;
	long			iobytes; 	
	static	int		oldSize;
	int				currSize = 0;
	long			bytes;
	char			readline[BUFSIZ * 5] = " ";
	Xv_Window		pw;
	char			messages[20][BUFSIZ] = {" "};
	char			message[BUFSIZ] = " ", header[BUFSIZ] = " ", body[BUFSIZ] = " ";
	char 			*token;
	extern	int		errno;
	int				fd, i = 0, j = 0;
	FILE			*fp;
	struct	stat	statbuff;

	mess_x = 10;
	mess_y = 25;

	strcpy(msg, "Called read_message");
	write_footer(frame, message, LEFT);

	lstat(noteQName, &statbuff);
	
	thisTime = statbuff.st_mtime;

	currSize = statbuff.st_size;
	/*
	if (currSize >=  oldSize && currSize != 0) {
	*/
	if (thisTime > lastTime  && currSize != 0) {
		oldSize = currSize;
		lastTime = thisTime;
			strcpy(message, "Checking note queue... ");
			write_footer(frame, message, LEFT);
  			if ((fd = open(noteQName, O_RDONLY | O_NDELAY)) < 0) {
                sprintf(message, "Unable to open note queue for read. Errno is: %d ", errno);
                write_footer(frame, message, LEFT);
                return;
            }
            else {
				read(fd,  readline, BUFSIZ * 4);
				/*
				printf("read: %s\n" , readline);
				fflush(stdout);
				*/

				/* break up the messages */
				token = strtok(readline, ">");
				while (token != NULL)	 {
					strcpy(messages[i], token);
					/*
					printf("token: %s\n" , messages[i]);
					fflush(stdout);
					*/
					token = strtok(NULL, ">");
					i++;
					noteCount++;
				}
				for (j = 0; j < i; j++) {
					strcpy(message ,messages[j]);
					strcpy(header, message);
					strcpy(body, message); 
					pin_note(header, body);
				}
			}
		/*
			fprintf(stdout, "read: %s\n", readline);
		*/
			
        sprintf(message, "Received a Note");
		write_footer(frame, message, LEFT);
        sprintf(message, "Note Count:%d ", noteCount );
		write_footer(frame, message, RIGHT);
		close(fd);
  		if ((fd = open(noteQName, O_WRONLY | O_TRUNC)) < 0) {
        	sprintf(message, "Unable to clear messages Errno is: %d ", errno);
            write_footer(frame, message, LEFT);
            return;
        }
		else
			close(fd);
	}
	lastTime = thisTime;
	return NOTIFY_DONE;

}
int
pin_note(char *header, char *body)
{
	Frame	note_frame;
	Canvas	note_canvas;
	Icon 	memo2_icon;
	Display         *dpy;
	GC              gc;
	XGCValues       gcvalues;
	Xv_Window	pw;
	char		readline[BUFSIZ] = " ";
	char		*token;
	char		label[BUFSIZ] = " ";
	char		from[BUFSIZ];
	static	int	frameNum = 1;

	mess_x = 10;	
	mess_y = 25;

	/*  snap off the header */

	token = strtok(header, "<");
	if (token != NULL){
		strcpy(label, "A Note from " );
		strcat(label, token);
		strcpy(from, token);
	}

	token = strchr(body, '<');
	if (token != NULL) {
		token++;
		strcpy(readline, token);
	}

	/*
	fprintf(stdout, "H: %s B: %s\n", header, readline);
	*/

	note_frame = (Frame)xv_create(frame, FRAME, 
		XV_X,					375,
		XV_Y,					300,
		WIN_CMS,			memoCms,
		XV_HEIGHT,				325,
		XV_WIDTH,				CANWIDTH,
		WIN_FOREGROUND_COLOR, CMS_CONTROL_COLORS + 6, 
		WIN_BACKGROUND_COLOR, CMS_CONTROL_COLORS + colorInt, 
		FRAME_LABEL,		    label, 	
	/*	FRAME_CMD_PIN_STATE,	FRAME_CMD_PIN_IN, */
		XV_SHOW,				TRUE,
		NULL);

    note_canvas = (Canvas)xv_create(note_frame ,CANVAS,
		XV_X,					0,
		XV_Y,					0,
		XV_HEIGHT,				325,
		XV_WIDTH,				CANWIDTH,
        CANVAS_X_PAINT_WINDOW,  TRUE,
        CANVAS_REPAINT_PROC,    my_repaint_proc,
        NULL);

	token = strtok(from, "@");
	memo2_icon = (Icon)xv_create(note_frame, ICON,
        WIN_CMS,            memoCms,
        ICON_IMAGE,         memo2_image,
        ICON_MASK_IMAGE,    memo2_mask_image,
        ICON_TRANSPARENT,   TRUE,
        XV_HEIGHT,          64,
        XV_WIDTH,           64,
		XV_LABEL,			token,
        WIN_FOREGROUND_COLOR, CMS_CONTROL_COLORS + 6,
        WIN_BACKGROUND_COLOR, CMS_CONTROL_COLORS + colorInt,
        NULL);

	xv_set(note_frame, FRAME_ICON, memo2_icon, NULL);

	pw = canvas_paint_window(note_canvas);
	dpy = (Display *)xv_get(note_frame, XV_DISPLAY);
	gcvalues.font = (Font)xv_get(canvasfont, XV_XID);
	gcvalues.foreground = BlackPixel(dpy, DefaultScreen(dpy));
	gcvalues.background = WhitePixel(dpy, DefaultScreen(dpy));
	gcvalues.graphics_exposures = FALSE; 
	gc = XCreateGC(dpy, RootWindow(dpy, DefaultScreen(dpy)), GCForeground | GCBackground | GCFont | GCGraphicsExposures, &gcvalues);
    xv_set(canvas_paint_window(note_canvas),
    	WIN_CONSUME_EVENTS,
        WIN_NO_EVENTS,
        WIN_ASCII_EVENTS, KBD_USE, KBD_DONE,
        LOC_DRAG, LOC_WINENTER, LOC_WINEXIT, WIN_MOUSE_BUTTONS,
        NULL,
    WIN_EVENT_PROC, my_event_proc,
    NULL);
	xv_set(note_canvas, XV_KEY_DATA, GC_KEY, gc, NULL);

	
    if (strstr(readline, "|")){
    	repaint_com = CLEAR_CANVAS;
        sprintf(msg, " ");  
        my_repaint_proc(pw, (Display *) xv_get(note_canvas, XV_DISPLAY), xv_get(pw, XV_XID), NULL);
        token = strtok(readline, "|");
        while (token != NULL) {
        	repaint_com = WRITE_CANVAS;
            sprintf(msg, "%s", token);
			/*
            printf("Token: %s X: %d Y: %d\n", token, mess_x, mess_y);
			*/
            my_repaint_proc(pw, (Display *)xv_get(note_canvas, XV_DISPLAY), xv_get(pw, XV_XID), NULL);
            token = strtok(NULL, "|");
            mess_y += 30;   
        }
    }
    else {
    	repaint_com = CLEAR_CANVAS + WRITE_CANVAS;
        sprintf(msg, "%s", readline);
        my_repaint_proc(pw, (Display *)xv_get(note_canvas, XV_DISPLAY), xv_get(pw, XV_XID), NULL);
    }

}
	
void
write_footer(Frame targetFrame, char	*message, int side)
{
	switch (side) {
		case LEFT:
			xv_set(targetFrame, FRAME_LEFT_FOOTER, message, NULL);
			break;
		case RIGHT:
			xv_set(targetFrame, FRAME_RIGHT_FOOTER, message, NULL);
			break;
	}
	return;
}

void
quiteFrame()
{
    xv_destroy_safe(frame);
	unlink(noteQName);
	return;
}

Notify_value
clean_up(Notify_client client, int sig, Notify_signal_mode when)
{
	unlink(noteQName);
    xv_destroy_safe(frame);
	return NOTIFY_DONE;
}


int
callPropFrame ( Panel_item item, Event *event)
{
    xv_set(prop_frame, XV_SHOW, TRUE, NULL);
}


int
callSendFrame ( Panel_item item, Event *event)
{
	xv_set(send_frame, FRAME_CMD_PIN_STATE,	FRAME_CMD_PIN_IN, NULL);
	/*
	xv_set(send_frame, XV_X, (int)xv_get(frame, XV_X), NULL);
	xv_set(send_frame, XV_Y, (int)xv_get(frame, XV_Y), NULL);
	*/
	xv_set(send_frame, XV_SHOW, TRUE, NULL);
}
int
sendNote ( Panel_item item, int value, Event *event)
{

	char	To[8] = "";
	char	line1[35] = "  ";
	char	line2[35] = "  ";
	char	line3[35] = "  ";
	char	line4[35] = "  ";
	char	line5[35] = "  ";
	char	line6[35] = "  ";
	char	line7[35] = "  ";
	char	line8[35] = "  ";
	char	line9[35] = "  ";
	char	line10[35] = "  ";
	char	line11[35] = "  ";
	char	line12[35] = "  ";
	char	cmd[25] = " ";
	char	*gptr = " ";
	char	message[BUFSIZ] = " ";
	char 	noteQ[BUFSIZ] = " ";
	char	pathName[BUFSIZ] = " ";
	extern	int		errno;
	FILE	*fp;
	int		fd, i, len, numBytes;
	int		lineCount = 0;
	int		updateStatus = 0;

	strcpy(To, "");
	strcpy(pathName, "");
	switch (value){
		case SEND:
			gptr = (char *)xv_get(uPathLine, PANEL_VALUE);
			len = strlen(gptr);
			if (strlen(gptr) > 0 && gptr != NULL){
				for (i = 0; i <= len; i++){
					*gptr = tolower(*gptr);
					pathName[i] =  *gptr;
					gptr++;
				}
				xv_set(uPathLine, PANEL_VALUE, pathName, NULL);
			}

			gptr = (char *)xv_get(toLine, PANEL_VALUE);
			len = strlen(gptr);
			if (strlen(gptr) > 0 && gptr != NULL){
				for (i = 0; i <= len; i++){
					*gptr = tolower(*gptr);
					To[i] =  *gptr;
					gptr++;
				}
				xv_set(toLine, PANEL_VALUE, To, NULL);
			}
		
			sprintf(noteQ, "%s/%s/%s.noteQ", pathName, To, To);
		
			gptr = (char *)xv_get(noteLine1, PANEL_VALUE);
			if (/* strlen(gptr) > 0 && */ gptr != NULL){
				strcpy(line1, gptr);
				strcat(line1, " |");
				if (strlen(line1) > 2) 
					lineCount++;
		
			}
			gptr = (char *)xv_get(noteLine2, PANEL_VALUE);
			if (/* strlen(gptr) > 0 && */ gptr != NULL){
				strcpy(line2, gptr);
				strcat(line2, " |");
				if (strlen(line2) > 2) 
					lineCount++;
		
			}
			gptr = (char *)xv_get(noteLine3, PANEL_VALUE);
			if (/* strlen(gptr) > 0 && */ gptr != NULL){
				strcpy(line3, gptr);
				strcat(line3, " |");
				if (strlen(line3) > 2) 
					lineCount++;
		
			}
			gptr = (char *)xv_get(noteLine4, PANEL_VALUE);
			if (/* strlen(gptr) > 0 && */ gptr != NULL){
				strcpy(line4, gptr);
				strcat(line4, " |");
				if (strlen(line4) > 2) 
					lineCount++;
		
			}
			gptr = (char *)xv_get(noteLine5, PANEL_VALUE);
			if (/* strlen(gptr) > 0 && */ gptr != NULL){
				strcpy(line5, gptr);
				strcat(line5, " |");
				if (strlen(line5) > 2) 
					lineCount++;
				
			}
		
		    gptr = (char *)xv_get(noteLine6, PANEL_VALUE);
		    if (/* strlen(gptr) > 0 && */ gptr != NULL){
		        strcpy(line6, gptr);
		        strcat(line6, " |");
				if (strlen(line6) > 2) 
		        	lineCount++;
		         
		    }
		    gptr = (char *)xv_get(noteLine7, PANEL_VALUE);
		    if (/* strlen(gptr) > 0 && */ gptr != NULL){
		        strcpy(line7, gptr);
		        strcat(line7, " |");
				if (strlen(line7) > 2) 
		        	lineCount++;
		         
		    }
		    gptr = (char *)xv_get(noteLine8, PANEL_VALUE);
		    if (/* strlen(gptr) > 0 && */ gptr != NULL){
		        strcpy(line8, gptr);
		        strcat(line8, " |");
				if (strlen(line8) > 2) 
		        	lineCount++;
		         
		    }
		    gptr = (char *)xv_get(noteLine9, PANEL_VALUE);
		    if (/* strlen(gptr) > 0 && */ gptr != NULL){
		        strcpy(line9, gptr);
		        strcat(line9, " |");
				if (strlen(line9) > 2) 
		        	lineCount++;
		         
		    }
		    gptr = (char *)xv_get(noteLine10, PANEL_VALUE);
		    if (/* strlen(gptr) > 0 && */ gptr != NULL){
		        strcpy(line10, gptr);
		        strcat(line10, " |");
				if (strlen(line10) > 2) 
		        	lineCount++;
		         
		    }
		
			if (strlen(To) <= 1) {
				notice_prompt (send_panel, NULL,
		        	NOTICE_NO_BEEPING,         TRUE,
		            NOTICE_MESSAGE_STRINGS,  "You must fill in the To:", NULL,
		            NULL);
				xv_set(send_button, PANEL_VALUE, 0, NULL);
				return;
			}
		
		    if (lineCount == 0) {
		        notice_prompt (send_panel, NULL,
		            NOTICE_NO_BEEPING,         TRUE,
		            NOTICE_MESSAGE_STRINGS,  "You cannot send a blank note",NULL,
		            NULL);
				xv_set(send_button, PANEL_VALUE, 0, NULL);
		        return;
		    }
            if ((fd = open(noteQ, O_WRONLY | O_APPEND | O_NDELAY)) < 0) {
				if (errno == EACCES) {
		        	sprintf(message, "Unable to send Note to %s. They were busy ", To);
					write_footer(frame, message, LEFT);
				}
				else if (errno == ENOENT) {
		        	sprintf(message, "%s is not running Mercury", To);
					write_footer(frame, message, LEFT);
				}
				else {
		        	sprintf(message, "Unable to access. Errno is: %d ", errno);
					write_footer(frame, message, LEFT);
				}
				xv_set(send_button, PANEL_VALUE, 0, NULL);
				return;
		    }
			else {
					chmod(noteQ, LPERMS); 
					xv_set(send_frame, FRAME_CMD_PIN_STATE,	FRAME_CMD_PIN_OUT, NULL);
					xv_set(send_button, PANEL_VALUE, 0, NULL);
					xv_set(send_button, PANEL_VALUE, 0, NULL);
					xv_set(send_frame, XV_SHOW,	FALSE, NULL);
					sprintf (message, "%s@%s<%s%s%s%s%s%s%s%s%s%s>", user, hostname, line1, line2, line3, line4, line5, line6, line7, line8, line9, line10);
					numBytes = write(fd, message, strlen(message));
					close(fd);
					chmod(noteQ, PERMS); 
					updateStatus = utimes(noteQ, NULL);
					if (numBytes < strlen(message) || updateStatus == -1)
		        		sprintf(message, "Unable to send Note to %s. Numbytes:%d", To, numBytes);
					else
		        		sprintf(message, "Sent a Note to %s", To);
					write_footer(frame, message, LEFT);
					
			}
			break;
		case CLEAR:
			totLetterCount = 0;
			sprintf(message, "Line Character Count: 0 ");
	    	write_footer(send_frame, message, LEFT);
			sprintf(message, "Note Character Count: %d ", totLetterCount);
	    	write_footer(send_frame, message, RIGHT);
		    xv_set(noteLine1, PANEL_VALUE, "", NULL);
		    xv_set(noteLine2, PANEL_VALUE, "", NULL);
		    xv_set(noteLine3, PANEL_VALUE, "", NULL);
		    xv_set(noteLine4, PANEL_VALUE, "", NULL);
		    xv_set(noteLine5, PANEL_VALUE, "", NULL);
		    xv_set(noteLine6, PANEL_VALUE, "", NULL);
		    xv_set(noteLine7, PANEL_VALUE, "", NULL);
		    xv_set(noteLine8, PANEL_VALUE, "", NULL);
		    xv_set(noteLine9, PANEL_VALUE, "", NULL);
		    xv_set(noteLine10, PANEL_VALUE, "", NULL);
			xv_set(send_button, PANEL_VALUE, 0, NULL);
			break;
	}
	
}

int
setFont(Panel_item item, int value, Event *event)
{
	

	xv_set(prop_frame, FRAME_BUSY, TRUE, NULL);
	switch (value){
		case 0: 			/* Lucida */
			strcpy(fontType, FONT_FAMILY_LUCIDA);
			fontSize = 24;
			break;
		case 1: 			/* Courier */
			strcpy(fontType, FONT_FAMILY_COUR);
			fontSize = 26;
			break;
		case 2: 			/* Gallant */
			strcpy(fontType, "rockwell");
			fontSize = 23;
			break;
		case 3: 			/* Helvetica */
			strcpy(fontType, FONT_FAMILY_HELVETICA);
			fontSize = 24;
			break;
		case 4: 			/* Serif */
			strcpy(fontType, "times");
			fontSize = 24;
			break;
		case 5:
			strcpy(fontType, "new century schoolbook");
			fontSize = 22;
			break;
			
	}

    canvasfont = (Xv_Font)xv_find(frame, FONT,
        FONT_FAMILY,        fontType,
        FONT_STYLE,         FONT_STYLE_BOLD,
        FONT_SIZE,          fontSize,
        NULL);
    dpy = (Display *)xv_get(frame, XV_DISPLAY);
    gcvalues.font = (Font)xv_get(canvasfont, XV_XID);
    gcvalues.foreground = BlackPixel(dpy, DefaultScreen(dpy));
    gcvalues.background = WhitePixel(dpy, DefaultScreen(dpy));
    gcvalues.graphics_exposures = FALSE;
    gc = XCreateGC(dpy, RootWindow(dpy, DefaultScreen(dpy)), GCForeground | GCBackground | GCFont | GCGraphicsExposures, &gcvalues);
	xv_set(prop_frame, FRAME_BUSY, FALSE, NULL);
	return;
} 
int
setColor(Panel_item item, int value, Event *event)
{
   

    xv_set(prop_frame, FRAME_BUSY, TRUE, NULL);
    switch (value){
        case PALEYELLOW:    
            colorInt = value;
            break;
        case SKYBLUE:       
            colorInt = value;
            break;
        case PALEGREEN:      
            colorInt = value;
            break;
        case PEACH:           
            colorInt = value;
            break;
        case PINK:             
            colorInt = value;
            break;
    }
	xv_set(memo_icon, WIN_BACKGROUND_COLOR, CMS_CONTROL_COLORS + colorInt, NULL);
    xv_set(prop_frame, FRAME_BUSY, FALSE, NULL);
    return;
}
void
resetCount(void)
{
	noteCount = 0;
    sprintf(message, "Note Count:%d ", noteCount );
	write_footer(frame, message, RIGHT);
	return;
}	
Notify_value
wrapAround( Panel panel, Event *event, Notify_arg arg, Notify_event_type type )
{
	static	int			letterCount, navCount;
			int			count = 0;
			Panel_item  currItem;
			char        *tmpp;
			char		p[BUFSIZ];

	currItem = (Panel_item)xv_get(send_panel, PANEL_CARET_ITEM);
	tmpp = (char *)xv_get(currItem, PANEL_VALUE);
	if (tmpp != NULL) {
		strcpy(p, tmpp);
		count = strlen(p);
	}

	if (currItem != toLine && currItem != uPathLine ) {
		if (event_is_down(event)){
			if (event_is_ascii(event) ) {

			#ifdef DEBUG
				printf("Panel event ID is: %d\n", event_action(event));
				fflush(stdout);
			#endif

				switch(event_action(event)) {
	
					case TAB:
						break;

					case RETURN:	
						break;

					default:
						break;
				} /* end switch */

			} /* end of if ascii event */

            #ifdef DEBUG
                printf("Panel event ID is: %d\n", event_action(event));
                fflush(stdout);
            #endif
            if (event_action(event) == ACTION_ERASE_CHAR_BACKWARD) {
                letterCount--;
                navCount--;
                totLetterCount--;
                if (navCount <= -1){
                    panel_backup_caret(send_panel);
                    currItem = (Panel_item)xv_get(send_panel, PANEL_CARET_ITEM);        
    				tmpp = (char *)xv_get(currItem, PANEL_VALUE);
    				if (tmpp != NULL) {
        				strcpy(p, tmpp);
        				count = strlen(p);
    				}
                    letterCount = count;
                    navCount = count;
                }
				#ifdef DEBUG
					printf("Count is :%d  Pos is : %d \n", letterCount, event_y(event));
					printf("NavCount is :%d  Pos is : %d \n", navCount, event_y(event));
					fflush(stdout);
				#endif
            }
            if (event_action(event) == ACTION_ERASE_LINE_BACKWARD) {
                    letterCount = count;
                    navCount = count;
            }
               
            if (event_action(event) == ACTION_GO_LINE_END) {
                    letterCount = count;
                    navCount = count;
            }
               
            if (event_action(event) == ACTION_GO_LINE_BACKWARD) {
                    letterCount = count;
                    navCount = 0;
            }
               
            if (event_action(event) == ACTION_GO_CHAR_BACKWARD) {
                navCount--;
                if (navCount <= 0){
                    panel_backup_caret(send_panel);
                    currItem = (Panel_item)xv_get(send_panel, PANEL_CARET_ITEM);        
					tmpp = (char *)xv_get(currItem, PANEL_VALUE);
                    if (tmpp != NULL) { 
                        strcpy(p, tmpp); 
                        count = strlen(p); 
                    } 
                    letterCount = count;
                    navCount = count;
                }
            }
            if (event_action(event) == ACTION_GO_CHAR_FORWARD) {
                navCount++;
                if (navCount >= 30){
                    panel_advance_caret(send_panel);
                    currItem = (Panel_item)xv_get(send_panel, PANEL_CARET_ITEM);        
					tmpp = (char *)xv_get(currItem, PANEL_VALUE);
                    if (tmpp != NULL) { 
                        strcpy(p, tmpp); 
                        count = strlen(p); 
                    } 
					count = strlen(p);
                    letterCount = count;
                    navCount = count;
                }
				#ifdef DEBUG
					printf("Count is :%d  Pos is : %d \n", letterCount, event_y(event));
					printf("NavCount is :%d  Pos is : %d \n", navCount, event_y(event));
					fflush(stdout);
				#endif
            }
            if (event_action(event) == ACTION_SELECT) {
                    letterCount = count;
                    navCount = count;
            }
            if (event_action(event) == ACTION_PASTE) {
                    letterCount = count;
                    navCount = count;
            }
			
	} /* end of if down event */
	if (event_is_up(event)) {
			if (event_is_ascii(event) ) {
				switch(event_action(event)) {

                    case TAB:
                        letterCount = strlen( (char *)xv_get((Panel_item)xv_get(send_panel, PANEL_CARET_ITEM), PANEL_VALUE));
                        navCount = strlen( (char *)xv_get((Panel_item)xv_get(send_panel, PANEL_CARET_ITEM), PANEL_VALUE));
                        break;

					case RETURN:	
                        letterCount = strlen( (char *)xv_get((Panel_item)xv_get(send_panel, PANEL_CARET_ITEM), PANEL_VALUE));
                        navCount = strlen( (char *)xv_get((Panel_item)xv_get(send_panel, PANEL_CARET_ITEM), PANEL_VALUE));
						break;
					default:
                        if (isprint(event_action(event))) {
                            letterCount++;
                            navCount++;
                            totLetterCount++;
                            if (navCount >= 30){
                                panel_advance_caret(send_panel);
                    			currItem = (Panel_item)xv_get(send_panel, PANEL_CARET_ITEM);        
                    			tmpp = (char *)xv_get(currItem, PANEL_VALUE);
                    			if (tmpp != NULL) {  
                        			strcpy(p, tmpp);  
                        			count = strlen(p);  
                    			}  
                                letterCount = count;
                                navCount = count;
                            }
                        }
                        break;
				}
				#ifdef DEBUG
					printf("Count is :%d  Pos is : %d \n", letterCount, event_y(event));
					printf("NavCount is :%d  Pos is : %d \n", navCount, event_y(event));
					fflush(stdout);
				#endif
			}
	} /* end of is up event */
	
		totLetterCount = 0; 
		totLetterCount += strlen ((char *)xv_get(noteLine1, PANEL_VALUE));
		totLetterCount += strlen ((char *)xv_get(noteLine2, PANEL_VALUE));
		totLetterCount += strlen ((char *)xv_get(noteLine3, PANEL_VALUE));
		totLetterCount += strlen ((char *)xv_get(noteLine4, PANEL_VALUE));
		totLetterCount += strlen ((char *)xv_get(noteLine5, PANEL_VALUE));
		totLetterCount += strlen ((char *)xv_get(noteLine6, PANEL_VALUE));
		totLetterCount += strlen ((char *)xv_get(noteLine7, PANEL_VALUE));
		totLetterCount += strlen ((char *)xv_get(noteLine8, PANEL_VALUE));
		totLetterCount += strlen ((char *)xv_get(noteLine9, PANEL_VALUE));
		totLetterCount += strlen ((char *)xv_get(noteLine10, PANEL_VALUE));

		sprintf(message, "Line Character Count: %d ", letterCount);
	    write_footer(send_frame, message, LEFT);
		sprintf(message, "Note Character Count: %d ", totLetterCount);
	    write_footer(send_frame, message, RIGHT);
	}
	notify_next_event_func(send_panel, (Notify_event) event, arg, type);
	return;
}
			 

