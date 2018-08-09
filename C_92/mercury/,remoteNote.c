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
#define	LEFT 1
#define	RIGHT 2
#define	SEND 1
#define	CLEAR 2

int		repaint_com = CLEAR_CANVAS + WRITE_CANVAS;
int		mess_x = 10,	mess_y = 25;
char	message[BUFSIZ];
char	user[16];
char	home[BUFSIZ];
char	hostname[64];
char	fifoName[BUFSIZ];
Xv_font			mainfont, canvasfont;

main(argc,argv)
int     argc;
char    *argv[];
{
	FILE			*fp;
	int				readfd, len1, len2;
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
	strcat(fifoName, home);
	strcat(fifoName, "/");
	strcat(fifoName, user);
	strcat(fifoName, ".fifo");
	len1 = strlen(home);
	token = strstr(home, user);
	len2 = strlen(token);
	bcopy(home, pathname, len1 - len2);
	


	mainfont = (Xv_Font)xv_find(frame, FONT, 
		FONT_FAMILY,		FONT_FAMILY_LUCIDA,
		FONT_STYLE,			FONT_STYLE_NORMAL,
		FONT_SIZE,			16,
		NULL);

	canvasfont = (Xv_Font)xv_find(frame, FONT, 
		FONT_FAMILY,		FONT_FAMILY_HELVETICA,
		FONT_STYLE,			FONT_STYLE_BOLD,
		FONT_SIZE,			22,
		NULL);

    frame = (Frame)xv_create(NULL,FRAME,
		XV_HEIGHT,				25,
		XV_WIDTH,				400,
        FRAME_LABEL,            "Remote Note V1.1",
        FRAME_SHOW_FOOTER,      TRUE,
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


	noteLine1 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
				PANEL_VALUE_UNDERLINED,     TRUE,
				PANEL_VALUE_DISPLAY_LENGTH, 	25,
				PANEL_VALUE_STORED_LENGTH,   	25,
				NULL);

	noteLine2 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
				PANEL_VALUE_UNDERLINED,     TRUE,
				PANEL_VALUE_DISPLAY_LENGTH, 	25,
				PANEL_VALUE_STORED_LENGTH,   	25,
				NULL);

	noteLine3 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
				PANEL_VALUE_UNDERLINED,     TRUE,
				PANEL_VALUE_DISPLAY_LENGTH, 	25,
				PANEL_VALUE_STORED_LENGTH,   	25,
				NULL);

	noteLine4 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
				PANEL_VALUE_UNDERLINED,     TRUE,
				PANEL_VALUE_DISPLAY_LENGTH, 	25,
				PANEL_VALUE_STORED_LENGTH,   	25,
				NULL);

	noteLine5 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
				PANEL_VALUE_UNDERLINED,     TRUE,
				PANEL_VALUE_DISPLAY_LENGTH, 	25,
				PANEL_VALUE_STORED_LENGTH,   	25,
				NULL);

    noteLine6 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
                PANEL_VALUE_UNDERLINED,     TRUE,
                PANEL_VALUE_DISPLAY_LENGTH,     25,
                PANEL_VALUE_STORED_LENGTH,      25,
                NULL);

    noteLine7 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
                PANEL_VALUE_UNDERLINED,     TRUE,
                PANEL_VALUE_DISPLAY_LENGTH,     25,
                PANEL_VALUE_STORED_LENGTH,      25,
                NULL);

    noteLine8 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
                PANEL_VALUE_UNDERLINED,     TRUE,
                PANEL_VALUE_DISPLAY_LENGTH,     25,
                PANEL_VALUE_STORED_LENGTH,      25,
                NULL);

    noteLine9 = (Panel_item)xv_create(send_panel, PANEL_TEXT,
                PANEL_VALUE_UNDERLINED,     TRUE,
                PANEL_VALUE_DISPLAY_LENGTH,     25,
                PANEL_VALUE_STORED_LENGTH,      25,
                NULL);

    noteLine10= (Panel_item)xv_create(send_panel, PANEL_TEXT,
                PANEL_VALUE_UNDERLINED,     TRUE,
                PANEL_VALUE_DISPLAY_LENGTH,     25,
                PANEL_VALUE_STORED_LENGTH,      25,
                NULL);

	send_button = xv_create (send_panel, PANEL_TOGGLE,
               PANEL_CHOICE_STRINGS,          "     Send it     ", "     Clear note     ", NULL,
               PANEL_CLIENT_DATA,            frame,
			   PANEL_NOTIFY_PROC,			 sendNote,
               NULL);    


  	if ((readfd = open(fifoName, O_RDONLY | O_NDELAY)) < 0) {
	
 		if ((mknod(fifoName, S_IFIFO | PERMS, 0) < 0) && (errno != EEXIST)) {
        	fflush (stderr);
        	unlink(fifoName);
        	exit(0);
    	}

		chmod(fifoName, PERMS);

  		if ((readfd = open(fifoName, O_RDONLY | O_NDELAY)) < 0) {
    		fprintf (stderr, "Remote note: Unable to open message fifo: %s\n", fifoName);
        	fflush (stdout);
			exit(0);
		}
		else {
    		sprintf(message, "Created message fifo: %s\n", fifoName);
			write_footer(message, LEFT);
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
	notify_set_input_func(client, read_message, readfd);

    xv_main_loop(frame);
	unlink(fifoName);
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
	static	int	noteCount;
	long		bytes;
	char		readline[BUFSIZ * 5] = " ";
	Xv_Window	pw;
	char		message[BUFSIZ] = " ", header[BUFSIZ] = " ", body[BUFSIZ] = " ";
	char 		*token;

	mess_x = 10;
	mess_y = 25;

	strcpy(msg, " ");
	

	noteCount++;
	write_footer(message, LEFT);
	if (ioctl (fd, FIONREAD, &iobytes) == -1 || iobytes == 0) {
            return NOTIFY_DONE;
    }          
	else {
			read(fd, readline, BUFSIZ * 5);
			token = strtok(readline, ">");
			while (token != NULL)	 {
				strcpy(message ,token);
				strcpy(header, message);
				strcpy(body, message); 
				token = strtok(NULL, ">");
				pin_note(header, body);
			}
		/* break up the messages */
		/*
			fprintf(stdout, "read: %s\n", readline);
		*/
			
        sprintf(message, "Received a Note");
		write_footer(message, LEFT);
        sprintf(message, "Note Count:%d ", noteCount );
		write_footer(message, RIGHT);
		return NOTIFY_DONE;
	}


}
int
pin_note(char *header, char *body)
{
	Frame	note_frame;
	Canvas	note_canvas;
	Display         *dpy;
	GC              gc;
	XGCValues       gcvalues;
	Xv_Window	pw;
	char		readline[BUFSIZ] = " ";
	char		*token;
	char		label[BUFSIZ] = " ";
	static	int	frameNum = 1;


	/*  snap off the header */

	token = strtok(header, "<");
	if (token != NULL){
		strcpy(label, "A Note from " );
		strcat(label, token);
	}

	token = strchr(body, '<');
	if (token != NULL) {
		token++;
		strcpy(readline, token);
	}

	/*
	fprintf(stdout, "H: %s B: %s\n", header, readline);
	*/

	note_frame = (Frame)xv_create(frame, FRAME_CMD, 
		XV_X,					500,
		XV_Y,					300,
		WIN_CMS,			memoCms,
		XV_HEIGHT,				325,
		XV_WIDTH,				410,
		WIN_FOREGROUND_COLOR, CMS_CONTROL_COLORS + 1, 
		WIN_BACKGROUND_COLOR, CMS_CONTROL_COLORS + 0, 
		FRAME_LABEL,		    label, 	
		FRAME_CMD_PIN_STATE,	FRAME_CMD_PIN_IN,
		XV_SHOW,				TRUE,
		NULL);

    note_canvas = (Canvas)xv_create(note_frame ,CANVAS,
		XV_X,					0,
		XV_Y,					0,
		XV_HEIGHT,				325,
		XV_WIDTH,				410,
        CANVAS_X_PAINT_WINDOW,  TRUE,
        CANVAS_REPAINT_PROC,    my_repaint_proc,
        NULL);

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
        my_repaint_proc(note_canvas, pw, xv_get(note_canvas, XV_DISPLAY), xv_get(pw, XV_XID), NULL);
        token = strtok(readline, "|");
        while (token != NULL) {
        	repaint_com = WRITE_CANVAS;
            sprintf(msg, "%s", token);
			/*
            printf("Token: %s X: %d Y: %d\n", token, mess_x, mess_y);
			*/
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
write_footer(char	*message, int side)
{
	switch (side) {
		case LEFT:
			xv_set(frame, FRAME_LEFT_FOOTER, message, NULL);
			break;
		case RIGHT:
			xv_set(frame, FRAME_RIGHT_FOOTER, message, NULL);
			break;
	}
	return;
}

void
quiteFrame()
{
    xv_destroy_safe(frame);
	unlink(fifoName);
	return;
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
	char	line1[30] = "  ";
	char	line2[30] = "  ";
	char	line3[30] = "  ";
	char	line4[30] = "  ";
	char	line5[30] = "  ";
	char	line6[30] = "  ";
	char	line7[30] = "  ";
	char	line8[30] = "  ";
	char	line9[30] = "  ";
	char	line10[30] = "  ";
	char	line11[30] = "  ";
	char	line12[30] = "  ";
	char	cmd[25] = " ";
	char	*gptr = " ";
	char	message[BUFSIZ] = " ";
	char 	fifo[BUFSIZ] = " ";
	char	pathName[BUFSIZ] = " ";
	extern	int		errno;
	FILE	fp;
	int		fd, i, len;
	int		lineCount = 0;

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
		
			sprintf(fifo, "%s/%s/%s.fifo", pathName, To, To);
		
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
		
		    if ((fd = open(fifo, O_WRONLY | O_NDELAY)) < 0) {
				if (errno == EACCES) {
		        	sprintf(message, "Unable to access %s ", fifo);
					write_footer(message, LEFT);
				}
				if (errno == ENOENT) {
		        	sprintf(message, "%s is not running Remote Note", To);
					write_footer(message, LEFT);
				}
				xv_set(send_button, PANEL_VALUE, 0, NULL);
				return;
		    }
			else {
				xv_set(send_frame, FRAME_CMD_PIN_STATE,	FRAME_CMD_PIN_OUT, NULL);
				xv_set(send_button, PANEL_VALUE, 0, NULL);
				xv_set(send_button, PANEL_VALUE, 0, NULL);
				xv_set(send_frame, XV_SHOW,	FALSE, NULL);
				sprintf (message, "%s@%s<%s%s%s%s%s%s%s%s%s%s>", user, hostname, line1, line2, line3, line4, line5, line6, line7, line8, line9, line10);
				
				/*
				fprintf (stdout, "%s@%s<%s%s%s%s%s%s%s%s%s%s>\n", user, hostname, line1, line2, line3, line4, line5, line6, line7, line8, line9, line10);
				fflush(stdout);
				*/
				write(fd, message, strlen(message));
		        sprintf(message, "Sent a Note to %s", To);
				write_footer(message, LEFT);
				close(fd);
			}
			break;
		case CLEAR:
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

