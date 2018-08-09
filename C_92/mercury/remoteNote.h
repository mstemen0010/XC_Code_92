#ifndef MEMO_H     /* include only once */
#define MEMO_H

#include <sys/ioctl.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>
#include <xview/xview.h>
#include <xview/frame.h>
#include <xview/panel.h>
#include <xview/canvas.h>
#include <xview/notify.h>
#include <xview/scrollbar.h>
#include <xview/xv_xrect.h>
#include <xview/cms.h>
#include <xview/icon.h>
#include <xview/svrimage.h>
#include <xview/font.h>
#include <xview/notice.h>
#include <xview/win_event.h>
#include <xview/win_input.h>

Canvas  		canvas;
Frame   		frame, send_frame, prop_frame;
Panel			panel, send_panel, send_panel2, prop_panel;
Panel_item		noteLine1, noteLine2, noteLine3, noteLine4, noteLine5, toLine;
Panel_item		noteLine6, noteLine7, noteLine8, noteLine9, noteLine10;
Panel_item		noteLine11, noteLine12, sendNote_button, send_button;
Panel_item		propFont_choice, propColor_choice;
Panel_item		uPathLine;
Cms				memoCms;
char    		msg[BUFSIZ] = " ";
char			pathname[BUFSIZ];
char			tmppathname[BUFSIZ];
Xv_screen		screen;
Icon			memo_icon;
Server_image	memo_image, memo2_image, memo_example_image, memo_mask_image, memo2_mask_image;
Notify_client	client = (Notify_client)10101;
Display			*dpy;
GC				gc;
XGCValues		gcvalues;

unsigned short memo_bits[] = { 
#include "../icons/memo.icon" 
};

unsigned short memo2_bits[] = { 
#include "../icons/memo2.icon" 
};

unsigned short memo_example_bits[] = { 
#include "../icons/memoexample.icon" 
};

unsigned short memo_mask_bits[] = { 
#include "../icons/memomask.icon" 
};

unsigned short memo2_mask_bits[] = { 
#include "../icons/memo2mask.icon" 
};

enum handle {
			to,
			line,
			button,
};

struct	itimerval 	noteTimer;

Notify_value
read_message
(
	Notify_client client, int which
);

int
pin_note
(
char *header, char *body
);

void
write_footer
(
Frame targetFrame, char   *message, int	side
); 

void
quiteFrame
(
void
);

int
callSendFrame 
( 
Panel_item item, Event *event
);

int
callPropFrame 
( 
Panel_item item, Event *event
);

int
sendNote 
( 
Panel_item item, int value, Event *event
);

Notify_value 
clean_up
(
Notify_client client, int sig, Notify_signal_mode when
);

int
setFont
(
Panel_item item, int value, Event *event
);
int
setColor
(
Panel_item item, int value, Event *event
);
void
resetCount(void);

Notify_value
wrapAround( Panel panel, Event *event, Notify_arg arg, Notify_event_type type );

void 
my_event_proc(Xv_Window window, Event *event);

void 
my_repaint_proc(Xv_Window pw, Display *dpy, Window xwin, Xv_xrectlist *xrects);

#endif



