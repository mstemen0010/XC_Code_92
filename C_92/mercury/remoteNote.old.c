/*
 * canvas_input.c --
 * Display a canvas whose views may be split repeatedly.  The event
 * handler is installed for each view, so events are displayed in
 * each paint window.
 */
#include "remoteNote.h"

#define	FIFO1 	"/home/mw/usr/mgs/memofifo.1"
#define	PERMS	0666
#define	GC_KEY   10
#define CLEAR_CANVAS 1
#define WRITE_CANVAS 2

int		repaint_com = CLEAR_CANVAS + WRITE_CANVAS;
int		mess_x = 10,	mess_y = 25;
char	message[BUFSIZ];
main(argc,argv)
int     argc;
char    *argv[];
{
	FILE			*fp;
	int				readfd;
	extern	int		errno;
	Xv_font			font;
    /*
     * Initialize, create base frame (with footers) and create canvas.
     */
    xv_init(XV_INIT_ARGS, argc, argv, NULL);

    frame = (Frame)xv_create(NULL,FRAME,
		XV_HEIGHT,				25,
		XV_WIDTH,				350,
        FRAME_LABEL,            "Remote Note V1.1",
        FRAME_SHOW_FOOTER,      TRUE,
        NULL);


	panel = (Panel)xv_create(frame, PANEL,
		XV_HEIGHT,				100,
		XV_WIDTH,				350,
        NULL);

	xv_create (panel, PANEL_BUTTON,
               PANEL_LABEL_STRING,          "Send Note",
               PANEL_CLIENT_DATA,            frame,
               NULL);    

	xv_create (panel, PANEL_BUTTON,
               PANEL_LABEL_STRING,          "Properties",
               PANEL_CLIENT_DATA,            frame,
               NULL);    

	xv_create (panel, PANEL_BUTTON,
               PANEL_LABEL_STRING,          "Quit",
               PANEL_CLIENT_DATA,            frame,
			   PANEL_NOTIFY_PROC,			 quiteFrame,
               NULL);    

  	if ((readfd = open(FIFO1, O_RDONLY | O_NDELAY)) < 0) {
	
 		if ((mknod(FIFO1, S_IFIFO | PERMS, 0) < 0) && (errno != EEXIST)) {
        	fflush (stderr);
        	unlink(FIFO1);
        	exit(0);
    	}

  		if ((readfd = open(FIFO1, O_RDONLY | O_NDELAY)) < 0) {
    		fprintf (stderr, "Remote note: Unable to open message fifo: %s\n", FIFO1);
        	fflush (stdout);
			exit(0);
		}
		else {
        	sprintf(message, "Created and opened message fifo: %s\n", FIFO1);
			write_footer(message);
		}
	}
	else {
		fprintf(stderr, "\n\nRemote Note already running. \n");
		fprintf(stderr, "You may only run one Remote Note at a time. \n");
		fprintf(stderr, "bye... \n\n\n");
		exit(0);
	}


    screen = (Xv_screen)xv_get(frame, XV_SCREEN); 


  	memoCms = (Cms) xv_create(screen, CMS,
		CMS_TYPE,			XV_STATIC_CMS,
		CMS_CONTROL_CMS,       TRUE,
		CMS_COLOR_COUNT,	CMS_CONTROL_COLORS + 2,
		CMS_SIZE,			CMS_CONTROL_COLORS + 2,
		CMS_NAMED_COLORS,	"lightgoldenrod2", "black", "red3", NULL,
		NULL);


	memo_image = (Server_image)xv_create(XV_NULL, SERVER_IMAGE, 
		XV_HEIGHT,			64,
		XV_WIDTH,			64,
		SERVER_IMAGE_BITS,	memo_bits,
		NULL);

	memo_mask_image = (Server_image)xv_create(XV_NULL, SERVER_IMAGE, 
		XV_HEIGHT,			64,
		XV_WIDTH,			64,
		SERVER_IMAGE_BITS,	memo_mask_bits,
		NULL);


	memo_icon = (Icon)xv_create(frame, ICON, 
		WIN_CMS,			memoCms,
		ICON_IMAGE,			memo_image,
		ICON_MASK_IMAGE,	memo_mask_image,
		ICON_TRANSPARENT,	TRUE,
		XV_HEIGHT,			64,
		XV_WIDTH,			64,
		WIN_FOREGROUND_COLOR, CMS_CONTROL_COLORS + 1,
		WIN_BACKGROUND_COLOR, CMS_CONTROL_COLORS + 0,
		NULL);


	xv_set(frame, WIN_CMS, memoCms, NULL);
	xv_set(frame, FRAME_ICON, memo_icon, NULL);
	xv_set(frame, WIN_FOREGROUND_COLOR, CMS_CONTROL_COLORS + 1, NULL);
	xv_set(frame, WIN_BACKGROUND_COLOR, CMS_CONTROL_COLORS + 0, NULL);
		

	font = (Xv_Font)xv_find(canvas, FONT, FONT_NAME, "r24", NULL);
	dpy = (Display *)xv_get(frame, XV_DISPLAY);
	gcvalues.font = (Font)xv_get(font, XV_XID);
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
	notify_set_input_func(client, read_message, readfd);

    xv_main_loop(frame);
	unlink(FIFO1);
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
my_event_proc(window, event, arg)
Xv_Window       window;
Event           *event;
Notify_arg      arg;
{
    register char *p = msg;

    *p = 0;

	switch (event_action(event)) {
		case WIN_RESIZE :
        case WIN_REPAINT :
            return;
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
my_repaint_proc(canvas, pw, dpy, xwin, xrects)
Canvas          canvas;
Xv_Window       pw;
Display         *dpy;
Window          xwin;
Xv_xrectlist    *xrects;
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
read_message(Notify_client client, int fd)
{
	int			iobytes;
	long		bytes;
	char		readline[BUFSIZ] = " ";
	Xv_Window	pw;
	char		*token;

	mess_x = 10;
	mess_y = 25;

	strcpy(msg, " ");
	

	if (ioctl (fd, FIONREAD, &iobytes) == -1 || iobytes == 0) {
            return NOTIFY_DONE;
    }          
	else {
		bytes = read(fd, readline, BUFSIZ);
		/*
		fprintf(stdout, "read: %s\n", readline);
		*/
		pin_note(readline);
			
		return NOTIFY_DONE;
	}


}
int
pin_note(char *readline)
{
	Frame	note_frame;
	Canvas	note_canvas;
	Xv_font			font;
	Display         *dpy;
	GC              gc;
	XGCValues       gcvalues;
	Xv_Window	pw;
	char		*token;
	static	int	 frameNum = 1;

	note_frame = (Frame)xv_create(XV_NULL, FRAME_CMD,
		WIN_CMS,			memoCms,
		XV_HEIGHT,				350,
		XV_WIDTH,				350,
		WIN_FOREGROUND_COLOR, CMS_CONTROL_COLORS + 1, 
		WIN_BACKGROUND_COLOR, CMS_CONTROL_COLORS + 0, 
		FRAME_LABEL,				"Remote Note",
		FRAME_CMD_PIN_STATE,	FRAME_CMD_PIN_IN,
		XV_SHOW,				TRUE,
		NULL);

    note_canvas = (Canvas)xv_create(note_frame ,CANVAS,
		XV_X,					0,
		XV_Y,					0,
		XV_HEIGHT,				350,
		XV_WIDTH,				350,
        CANVAS_X_PAINT_WINDOW,  TRUE,
        CANVAS_REPAINT_PROC,    my_repaint_proc,
        NULL);

	pw = canvas_paint_window(note_canvas);
	font = (Xv_Font)xv_find(note_canvas, FONT, FONT_NAME, "r24", NULL);
	dpy = (Display *)xv_get(note_frame, XV_DISPLAY);
	gcvalues.font = (Font)xv_get(font, XV_XID);
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
        my_repaint_proc(note_canvas, pw, xv_get(note_canvas, XV_DISPLAY), xv_get(pw, XV_XID), NULL);
        token = strtok(readline, "|");
        while (token != NULL) {
        	repaint_com = WRITE_CANVAS;
            sprintf(msg, "%s", token);
            my_repaint_proc(note_canvas, pw, xv_get(note_canvas, XV_DISPLAY), xv_get(pw, XV_XID), NULL);
            token = strtok(NULL, "|");
            mess_y += 30;   
        }
    }
    else {
    	repaint_com = CLEAR_CANVAS + WRITE_CANVAS;
        sprintf(msg, "%s", readline);
        my_repaint_proc(note_canvas, pw, xv_get(note_canvas, XV_DISPLAY), xv_get(pw, XV_XID), NULL);
    }

}
	
void
write_footer(char	*message)
{
	xv_set(frame, FRAME_LEFT_FOOTER, message, NULL);
	return;
}

void
quiteFrame()
{
    xv_destroy_safe(frame);
	unlink(FIFO1);
	return;
}
