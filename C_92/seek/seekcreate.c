/*
** File: seek_create.c SCCS 5.5 - 2/3/94
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
#define WHITE 	0
#define WHEAT 	1
#define RED   	2
#define PURPLE  3
#define BLACK 	4 


#include "seek_create.h" 

void
child_create(void)
{

	Rect	*rect, *tmprect;
	Xv_Window   window;
	int			win;
	int			win_no;
	Panel_item	quit_button, apply_button;
	Panel_item	fquit_button, fapply_button, freset_button;


	cms = (Cms) xv_create(NULL, CMS,
        CMS_CONTROL_CMS,       TRUE,
        CMS_COLOR_COUNT,    CMS_CONTROL_COLORS + 5,
        CMS_TYPE,           XV_STATIC_CMS,
        CMS_SIZE,           CMS_CONTROL_COLORS + 5,
        CMS_NAMED_COLORS,   "white", "wheat", "red2", "purple", "black", NULL,
        NULL);
			/* 
	xv_set((Xv_Window)xv_get(frame, XV_OWNER), XV_FONT, font, NULL);
			*/
	xv_set(frame, WIN_CMS, cms, NULL); 
	xv_set(frame, WIN_FOREGROUND_COLOR,   CMS_CONTROL_COLORS + BLACK, NULL);
	xv_set(frame, WIN_BACKGROUND_COLOR,   CMS_CONTROL_COLORS + WHITE, NULL);

    nullmenu = (Menu) xv_create (NULL, MENU, NULL);

	prime_menu = (Menu) xv_create (NULL, MENU, 
					NULL);

	pmi[0] = (Menu_item)xv_create(NULL, MENUITEM, 
					MENU_STRING,		primaryPath,
					NULL);
	
	pmi[1] = (Menu_item)xv_create(NULL, MENUITEM, 
					MENU_STRING,		"",
					NULL);
	pmi[2] = (Menu_item)xv_create(NULL, MENUITEM, 
					MENU_STRING,		"",
					NULL);
	pmi[3] = (Menu_item)xv_create(NULL, MENUITEM, 
					MENU_STRING,		"",
					NULL);
	pmi[4] = (Menu_item)xv_create(NULL, MENUITEM, 
					MENU_STRING,		"",
					NULL);
	pmi[5] = (Menu_item)xv_create(NULL, MENUITEM, 
					MENU_STRING,		"",
					NULL);
	pmi[6] = (Menu_item)xv_create(NULL, MENUITEM, 
					MENU_STRING,		"",
					NULL);
	pmi[7] = (Menu_item)xv_create(NULL, MENUITEM, 
					MENU_STRING,		"",
					NULL);
	pmi[8] = (Menu_item)xv_create(NULL, MENUITEM, 
					MENU_STRING,		"",
					NULL);
	pmi[9] = (Menu_item)xv_create(NULL, MENUITEM, 
					MENU_STRING,		"",
					NULL);


/*
	xv_set(prime_menu, MENU_APPEND_ITEM, pmi[0], NULL);
	xv_set(prime_menu, MENU_APPEND_ITEM, pmi[1], NULL);
	xv_set(prime_menu, MENU_APPEND_ITEM, pmi[2], NULL);
	xv_set(prime_menu, MENU_APPEND_ITEM, pmi[3], NULL);
	xv_set(prime_menu, MENU_APPEND_ITEM, pmi[4], NULL);
	xv_set(prime_menu, MENU_APPEND_ITEM, pmi[5], NULL);
	xv_set(prime_menu, MENU_APPEND_ITEM, pmi[6], NULL);
	xv_set(prime_menu, MENU_APPEND_ITEM, pmi[7], NULL);
	xv_set(prime_menu, MENU_APPEND_ITEM, pmi[8], NULL);
	xv_set(prime_menu, MENU_APPEND_ITEM, pmi[9], NULL);

*/
    second_menu = (Menu) xv_create (NULL, MENU, 
					NULL);
   
    smi[0] = (Menu_item)xv_create(NULL, MENUITEM,
                    MENU_STRING,        secondaryPath,
                    MENU_NOTIFY_PROC,   second_menu_proc,
                    NULL);
    smi[1] = (Menu_item)xv_create(NULL, MENUITEM,
                    MENU_STRING,        "",
                    MENU_NOTIFY_PROC,   second_menu_proc,
                    NULL);
    smi[2] = (Menu_item)xv_create(NULL, MENUITEM,
                    MENU_STRING,        "",
                    MENU_NOTIFY_PROC,   second_menu_proc,
                    NULL);
    smi[3] = (Menu_item)xv_create(NULL, MENUITEM,
                    MENU_STRING,        "",
                    MENU_NOTIFY_PROC,   second_menu_proc,
                    NULL);
    smi[4] = (Menu_item)xv_create(NULL, MENUITEM,
                    MENU_STRING,        "",
                    MENU_NOTIFY_PROC,   second_menu_proc,
                    NULL);
    smi[5] = (Menu_item)xv_create(NULL, MENUITEM,
                    MENU_STRING,        "",
                    MENU_NOTIFY_PROC,   second_menu_proc,
                    NULL);
    smi[6] = (Menu_item)xv_create(NULL, MENUITEM,
                    MENU_STRING,        "",
                    MENU_NOTIFY_PROC,   second_menu_proc,
                    NULL);
    smi[7] = (Menu_item)xv_create(NULL, MENUITEM,
                    MENU_STRING,        "",
                    MENU_NOTIFY_PROC,   second_menu_proc,
                    NULL);
    smi[8] = (Menu_item)xv_create(NULL, MENUITEM,
                    MENU_STRING,        "",
                    MENU_NOTIFY_PROC,   second_menu_proc,
                    NULL);
    smi[9] = (Menu_item)xv_create(NULL, MENUITEM,
                    MENU_STRING,        "",
                    MENU_NOTIFY_PROC,   second_menu_proc,
                    NULL);
 
/* 
	xv_set(second_menu, MENU_APPEND_ITEM, smi[0], NULL);
	xv_set(second_menu, MENU_APPEND_ITEM, smi[1], NULL);
	xv_set(second_menu, MENU_APPEND_ITEM, smi[2], NULL);
	xv_set(second_menu, MENU_APPEND_ITEM, smi[3], NULL);
	xv_set(second_menu, MENU_APPEND_ITEM, smi[4], NULL);
	xv_set(second_menu, MENU_APPEND_ITEM, smi[5], NULL);
	xv_set(second_menu, MENU_APPEND_ITEM, smi[6], NULL);
	xv_set(second_menu, MENU_APPEND_ITEM, smi[7], NULL);
	xv_set(second_menu, MENU_APPEND_ITEM, smi[8], NULL);
	xv_set(second_menu, MENU_APPEND_ITEM, smi[9], NULL);
*/

	seek_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				64,
			XV_HEIGHT,				64,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    icon_bits,
			NULL);    	

	seek_icon2 = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				64,
			XV_HEIGHT,				64,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    icon_bits2,
			NULL);    	

	seek_icon3 = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				64,
			XV_HEIGHT,				64,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    icon_bits3,
			NULL);    	

	vi_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				64,
			XV_HEIGHT,				64,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    vi_icon_bits,
			NULL);    	

	mask_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				64,
			XV_HEIGHT,				64,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    mask_bits,
			NULL);    	

	file_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    file_bits,
			NULL);    	

	dir_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    dir_bits,
			NULL);    	

	sys_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    sys_bits,
			NULL);    	

	link_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    link_bits,
			NULL);    	

	pipe_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    pipe_bits,
			NULL);    	

	sock_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    sock_bits,
			NULL);    	

	core_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    core_bits,
			NULL);    	

	compressed_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    compressed_bits,
			NULL);    	

	csource_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    csource_bits,
			NULL);    	

	object_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    object_bits,
			NULL);    	

	header_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    header_bits,
			NULL);    	

	exe_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    exe_bits,
			NULL);    	

	aml_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    aml_bits,
			NULL);    	

	sound_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    sound_bits,
			NULL);    	

	ps_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    ps_bits,
			NULL);    	

	rast_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    rast_bits,
			NULL);    	

	mail_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    mail_bits,
			NULL);    	

	shell_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    shell_bits,
			NULL);    	

	wp_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    wp_bits,
			NULL);    	

	bm_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    bm_bits,
			NULL);    	

	gif_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    gif_bits,
			NULL);    	

	make_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    make_bits,
			NULL);    	

	info_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    info_bits,
			NULL);    	

	lib_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    lib_bits,
			NULL);    	

	gis_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    gis_bits,
			NULL);    	

	im_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    im_bits,
			NULL);    	

	gra_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    gra_bits,
			NULL);    	

	plt_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    plt_bits,
			NULL);    	

	XRs_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    XRs_bits,
			NULL);    	

	XRh_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    XRh_bits,
			NULL);    	

	XRr_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    XRr_bits,
			NULL);    	

	XRe_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    XRe_bits,
			NULL);    	

	XRd_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    XRd_bits,
			NULL);    	

	empty_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    empty_bits,
			NULL);    	

	dos_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    dos_bits,
			NULL);    	

	pkzip_icon = (Server_image)xv_create(NULL, SERVER_IMAGE,
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			XV_WIDTH,				32,
			XV_HEIGHT,				32,
			XV_DEPTH,				 1,
			SERVER_IMAGE_BITS,	    pkzip_bits,
			NULL);    	

	panel = (Panel)xv_create(frame, PANEL, 
			WIN_CMS,				cms,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			WIN_CMS,				cms,
			XV_X,					0,
			XV_Y,					0,
/* 			XV_WIDTH,				675,
			XV_HEIGHT,				100, */
 			XV_WIDTH,				(int)xv_get(frame, XV_WIDTH),
 			XV_HEIGHT,				(int)xv_get(frame, XV_HEIGHT),
			XV_HELP_DATA,			"seek_help:panel",
			NULL); 


	xv_set (panel, PANEL_LAYOUT, PANEL_HORIZONTAL, NULL);

	word_item = (Panel_item)xv_create(panel, PANEL_TEXT,
			XV_HELP_DATA,			"seek_help:wordItem",
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			XV_X,					10,
			XV_Y,					10,
			PANEL_LABEL_STRING,		"Search for: ",
			PANEL_VALUE_DISPLAY_LENGTH, 30,
			PANEL_VALUE_STORED_LENGTH,	BUFSIZ - 1,
			PANEL_NOTIFY_PROC,		look_up_all,
			PANEL_CLIENT_DATA,		prime,
			NULL);

	/* window = (Xv_Window)xv_get(panel, XV_XID); */


	rect = (Rect *)xv_get(word_item, XV_RECT);

	done_button = xv_create(panel, PANEL_BUTTON, 
			XV_HELP_DATA,			"seek_help:done",
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + RED,	
			WIN_CMS,				cms,
			XV_X,	rect_right(rect) + 100,
			XV_Y,					10,
			PANEL_LABEL_STRING,     "Done",
			PANEL_NOTIFY_PROC,		toggle_done,
			XV_SHOW,				FALSE, 
			NULL);



	rect = (Rect *)xv_get(word_item, XV_RECT);

    goto_item = (Panel_item) xv_create(panel, PANEL_TEXT,
			XV_HELP_DATA,			"seek_help:gotoItem",
			XV_X,					10,
			XV_Y,	rect_bottom(rect) + 10,
			PANEL_LABEL_STRING,     "Goto:",
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
            PANEL_VALUE_DISPLAY_LENGTH, 45,
			PANEL_VALUE_STORED_LENGTH,	BUFSIZ - 1,
            PANEL_LABEL_BOLD,       TRUE,
            PANEL_VALUE_UNDERLINED, TRUE,
            PANEL_READ_ONLY,        FALSE,
			PANEL_NOTIFY_PROC,		goto_funct,
            NULL);

	rect = (Rect *)xv_get(goto_item, XV_RECT);

	tmprect = (Rect *)xv_get(goto_item, XV_RECT);

    mess_item = (Panel_item) xv_create(panel, PANEL_TEXT,
			XV_HELP_DATA,			"seek_help:messItem",
			XV_X,					10,
			XV_Y,	rect_bottom(rect) + 10,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
            PANEL_VALUE_DISPLAY_LENGTH, 80,
            PANEL_LABEL_BOLD,       FALSE,
            PANEL_VALUE_UNDERLINED, FALSE,
            PANEL_READ_ONLY,        TRUE,
            NULL);

	rect = (Rect *)xv_get(mess_item, XV_RECT);

	tmprect = (Rect *)xv_get(mess_item, XV_RECT);

	primebutton = xv_create(panel, PANEL_BUTTON, 
			XV_HELP_DATA,			"seek_help:prime",
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			WIN_CMS,				cms,
			XV_X,					10,
			XV_Y,	rect_bottom(rect) + 20,
			PANEL_LABEL_STRING,     primaryNameVal,
			PANEL_NOTIFY_PROC,		look_up_all,
			PANEL_CLIENT_DATA,		prime,
			PANEL_ITEM_MENU,		prime_menu,
			NULL);

	rect = (Rect *)xv_get(primebutton, XV_RECT);

	secondbutton = xv_create(panel, PANEL_BUTTON, 
			XV_HELP_DATA,			"seek_help:second",
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			WIN_CMS,				cms,
			XV_X,	rect_right(rect) + 20,
			XV_Y,	rect_bottom(tmprect) + 20,
			PANEL_LABEL_STRING,     secondaryNameVal,
			PANEL_NOTIFY_PROC,		look_up_all,
			PANEL_CLIENT_DATA,		second,
			PANEL_ITEM_MENU,		second_menu,
			NULL);

	rect = (Rect *)xv_get(secondbutton, XV_RECT);

	grab_word = (Panel_item) xv_create(panel, PANEL_BUTTON, 
			XV_HELP_DATA,			"seek_help:grab",
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			XV_X,	rect_right(rect) + 20,
			XV_Y,	rect_bottom(tmprect) + 20,
			PANEL_LABEL_STRING,     "Grab highlighted",
			PANEL_NOTIFY_PROC,		get_prime_sel,
			PANEL_CLIENT_DATA,		frame,
			NULL);

	rect = (Rect *)xv_get(grab_word, XV_RECT);

    propsOn = (Panel_item) xv_create(panel, PANEL_BUTTON,
			XV_HELP_DATA,			"seek_help:props",
            PANEL_ITEM_COLOR,       CMS_CONTROL_COLORS + BLACK,
			XV_X,	rect_right(rect) + 20,
            XV_Y,   rect_bottom(tmprect) + 20,
            PANEL_LABEL_STRING,     "Props",
            PANEL_NOTIFY_PROC,      prop_OnOff,
            PANEL_CLIENT_DATA,      TRUE,
            NULL);

	rect = (Rect *)xv_get(done_button, XV_RECT);

	filter_button = xv_create(panel, PANEL_BUTTON, 
			XV_HELP_DATA,			"seek_help:done",
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			WIN_CMS,				cms,
			XV_X,	rect_right(rect) + 100,
			XV_Y,					10,
			PANEL_LABEL_STRING,     "File Filter",
			PANEL_NOTIFY_PROC,		show_filter,
			XV_SHOW,				TRUE, 
			NULL);

	rect = (Rect *)xv_get(propsOn, XV_RECT);

	quit_button = (Panel_item) xv_create(panel, PANEL_BUTTON, 
			XV_HELP_DATA,			"seek_help:quit",
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			XV_X,	rect_right(rect) + 30,
			XV_Y,	rect_bottom(tmprect) + 20,
			PANEL_LABEL_STRING,     "Quit",
			PANEL_NOTIFY_PROC,		quit,
			PANEL_CLIENT_DATA,		frame,
			NULL);
			
/* 	xv_set(frame, XV_X, (int)xv_get(panel, XV_X), NULL);
	xv_set(frame, XV_Y, (int)xv_get(panel, XV_Y), NULL); */

	xv_set(panel, XV_WIDTH, (int)xv_get(quit_button, XV_WIDTH) + 20, NULL);
	xv_set(panel, XV_HEIGHT, rect_bottom(tmprect) + 50, NULL);


	/*
	canvas = (Canvas)xv_create(frame, CANVAS,    
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + WHEAT,	
 			XV_WIDTH,			    20,	
 			XV_HEIGHT,				(int)xv_get(frame, XV_HEIGHT),
			XV_X,					0,
			XV_Y,					rect_bottom(tmprect) + 51,
			NULL); 
	*/

	textsw = (Textsw)xv_create(frame, TEXTSW, 
			XV_FONT,				font,
			TEXTSW_LINE_BREAK_ACTION,	TEXTSW_WRAP_AT_CHAR,
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + WHEAT,	
			XV_X,					0,
			XV_Y,					rect_bottom(tmprect) + 51,
 			XV_WIDTH,				(int)xv_get(panel, XV_WIDTH),
 			XV_HEIGHT,				(int)xv_get(frame, XV_HEIGHT),
			TEXTSW_DISABLE_LOAD, 	TRUE,
			TEXTSW_MEMORY_MAXIMUM,  2000000,
			NULL); 

	default_textsw = (Menu)xv_get(textsw, WIN_MENU);

	if (editFlag == FALSE)	{
		xv_set(textsw, 
			WIN_MENU, nullmenu, 
			TEXTSW_BROWSING,        TRUE,
		NULL);
	}
	
	window_fit(textsw);
	window_fit(frame);
	window_fit(panel);


	icon = (Icon)xv_create(frame, ICON, 
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			ICON_IMAGE,				seek_icon,
			ICON_MASK_IMAGE,		mask_icon,
			ICON_TRANSPARENT,		TRUE,
			XV_X,					100,
			XV_Y,					100,
			NULL);

	icon2 = (Icon)xv_create(frame, ICON, 
			WIN_FOREGROUND_COLOR, 	CMS_CONTROL_COLORS + BLACK,	
			WIN_BACKGROUND_COLOR, 	CMS_CONTROL_COLORS + WHITE,	
			ICON_IMAGE,				seek_icon2,
			ICON_MASK_IMAGE,		mask_icon,
			ICON_TRANSPARENT,		TRUE,
			XV_X,					100,
			XV_Y,					100,
			NULL);

   subframe = (Frame)xv_create(frame, FRAME_CMD,
			FRAME_SHOW_RESIZE_CORNER, TRUE,
			WIN_CMS,				cms,
            FRAME_DONE_PROC,      	done_proc,
            FRAME_LABEL,            "",
            XV_SHOW,                FALSE,
            WIN_COLUMNS,            20,
            WIN_ROWS,               20,
            XV_X,                   (int)xv_get(frame, XV_X) + 150,
            XV_Y,                   (int)xv_get(frame, XV_Y) + 135,
            NULL);

   subframe2 = (Frame)xv_create(frame, FRAME_CMD,
			FRAME_SHOW_RESIZE_CORNER, FALSE,
			WIN_CMS,				cms,
            FRAME_LABEL,            "File Filter",
            XV_SHOW,                FALSE,
            WIN_COLUMNS,            80,
            WIN_ROWS,               60,
            XV_X,                   (int)xv_get(filter_button, XV_X) + 50,
            XV_Y,                   (int)xv_get(filter_button, XV_Y),
            NULL);

    panel2 = (Panel)xv_create(subframe, PANEL,
			WIN_CMS,				cms,
            XV_SHOW,                FALSE,
            XV_X,                   0,
            XV_Y,                   0,
            WIN_COLUMNS,            20,
            WIN_ROWS,               20,
            PANEL_LAYOUT,           PANEL_VERTICAL,
            FRAME_CMD_PUSHPIN_IN,   TRUE,
            NULL);

    panel3 = (Panel)xv_create(subframe2, PANEL,
			WIN_CMS,				cms,
            XV_SHOW,                FALSE,
            XV_X,                   0,
            XV_Y,                   0,
            WIN_COLUMNS,            80,
            WIN_ROWS,               60,
            PANEL_LAYOUT,           PANEL_VERTICAL,
            NULL);

	  ffdir_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    dir_icon,
			NULL);
			
	  ffdir_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffdir_image, XV_X) + 50,
            XV_Y,                   xv_get(ffdir_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_dir,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  fflnk_image = (Panel_item) xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    link_icon,
			NULL);
			
	  fflnk_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(fflnk_image, XV_X) + 50,
            XV_Y,                   xv_get(fflnk_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_lnk,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffsock_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    sock_icon,
			NULL);
			
	  ffsock_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffsock_image, XV_X) + 50,
            XV_Y,                   xv_get(ffsock_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_sock,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  fffifo_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    pipe_icon,
			NULL);
			
	  fffifo_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(fffifo_image, XV_X) + 50,
            XV_Y,                   xv_get(fffifo_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_fifo,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffchr_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    sys_icon,
			NULL);
			
	  ffchr_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffchr_image, XV_X) + 50,
            XV_Y,                   xv_get(ffchr_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_chr,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffempty_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    empty_icon,
			NULL);
			
	  ffempty_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffempty_image, XV_X) + 50,
            XV_Y,                   xv_get(ffempty_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_empty,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffcore_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    core_icon,
			NULL);
			
	  ffcore_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffcore_image, XV_X) + 50,
            XV_Y,                   xv_get(ffcore_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_core,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffcompressed_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    compressed_icon,
			NULL);
			
	  ffcompressed_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffcompressed_image, XV_X) + 50,
            XV_Y,                   xv_get(ffcompressed_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_compressed,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  fffile_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    file_icon,
			NULL);
			
	  fffile_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(fffile_image, XV_X) + 50,
            XV_Y,                   xv_get(fffile_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_file,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffcsource_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    csource_icon,
			NULL);
			
	  ffcsource_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffcsource_image, XV_X) + 50,
            XV_Y,                   xv_get(ffcsource_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_csource,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffobject_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    object_icon,
			NULL);
			
	  ffobject_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffobject_image, XV_X) + 50,
            XV_Y,                   xv_get(ffobject_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_object,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffheader_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    header_icon,
			NULL);
			
	  ffheader_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffheader_image, XV_X) + 50,
            XV_Y,                   xv_get(ffheader_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_header,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffexe_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    exe_icon,
			NULL);
			
	  ffexe_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffexe_image, XV_X) + 50,
            XV_Y,                   xv_get(ffexe_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_exe,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffaml_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    aml_icon,
			NULL);
			
	  ffaml_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffaml_image, XV_X) + 50,
            XV_Y,                   xv_get(ffaml_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_aml,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffXRh_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    XRh_icon,
			NULL);
			
	  ffXRh_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffXRh_image, XV_X) + 50,
            XV_Y,                   xv_get(ffXRh_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_XRh,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffXRd_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    XRd_icon,
			NULL);
			
	  ffXRd_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffXRd_image, XV_X) + 50,
            XV_Y,                   xv_get(ffXRd_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_XRd,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffXRr_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    XRr_icon,
			NULL);
			
	  ffXRr_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffXRr_image, XV_X) + 50,
            XV_Y,                   xv_get(ffXRr_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_XRr,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffdos_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    dos_icon,
			NULL);
			
	  ffdos_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffdos_image, XV_X) + 50,
            XV_Y,                   xv_get(ffdos_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_dos,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffsound_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(ffdir_image, XV_X) + 270,
            XV_Y,                   xv_get(ffdir_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    sound_icon,
			NULL);
			
	  ffsound_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffsound_image, XV_X) + 50,
            XV_Y,                   xv_get(ffsound_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_sound,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffps_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(fflnk_image, XV_X) + 270,
            XV_Y,                   xv_get(fflnk_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    ps_icon,
			NULL);
			
	  ffps_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffps_image, XV_X) + 50,
            XV_Y,                   xv_get(ffps_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_ps,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffrast_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(ffsock_image, XV_X) + 270,
            XV_Y,                   xv_get(ffsock_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    rast_icon,
			NULL);
			
	  ffrast_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffrast_image, XV_X) + 50,
            XV_Y,                   xv_get(ffrast_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_im,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffmail_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(fffifo_image, XV_X) + 270,
            XV_Y,                   xv_get(fffifo_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    mail_icon,
			NULL);
			
	  ffmail_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffmail_image, XV_X) + 50,
            XV_Y,                   xv_get(ffmail_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_mail,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffshell_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(ffchr_image, XV_X) + 270,
            XV_Y,                   xv_get(ffchr_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    shell_icon,
			NULL);
			
	  ffshell_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffshell_image, XV_X) + 50,
            XV_Y,                   xv_get(ffshell_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_shell,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffwp_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(ffempty_image, XV_X) + 270,
            XV_Y,                   xv_get(ffempty_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    wp_icon,
			NULL);
			
	  ffwp_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffwp_image, XV_X) + 50,
            XV_Y,                   xv_get(ffwp_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_wp,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffbm_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(ffcore_image, XV_X) + 270,
            XV_Y,                   xv_get(ffcore_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    bm_icon,
			NULL);
			
	  ffbm_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffbm_image, XV_X) + 50,
            XV_Y,                   xv_get(ffbm_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_bm,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffgif_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(ffcompressed_image, XV_X) + 270,
            XV_Y,                   xv_get(ffcompressed_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    gif_icon,
			NULL);
			
	  ffgif_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffgif_image, XV_X) + 50,
            XV_Y,                   xv_get(ffgif_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_gif,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffmake_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(fffile_image, XV_X) + 270,
            XV_Y,                   xv_get(fffile_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    make_icon,
			NULL);
			
	  ffmake_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffmake_image, XV_X) + 50,
            XV_Y,                   xv_get(ffmake_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_make,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffinfo_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(ffcsource_image, XV_X) + 270,
            XV_Y,                   xv_get(ffcsource_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    info_icon,
			NULL);
			
	  ffinfo_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffinfo_image, XV_X) + 50,
            XV_Y,                   xv_get(ffinfo_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_info,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  fflib_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(ffobject_image, XV_X) + 270,
            XV_Y,                   xv_get(ffobject_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    lib_icon,
			NULL);
			
	  fflib_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(fflib_image, XV_X) + 50,
            XV_Y,                   xv_get(fflib_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
            PANEL_VALUE,              ff_lib,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            NULL);

	  ffgis_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(ffheader_image, XV_X) + 270,
            XV_Y,                   xv_get(ffheader_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    gis_icon,
			NULL);
			
	  ffgis_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffgis_image, XV_X) + 50,
            XV_Y,                   xv_get(ffgis_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            PANEL_VALUE,              ff_gis,
            NULL);

	  ffim_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(ffexe_image, XV_X) + 270,
            XV_Y,                   xv_get(ffexe_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    im_icon,
			NULL);
			
	  ffim_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffim_image, XV_X) + 50,
            XV_Y,                   xv_get(ffim_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            PANEL_VALUE,              ff_im,
            NULL);

	  ffgra_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(ffaml_image, XV_X) + 270,
            XV_Y,                   xv_get(ffaml_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    gra_icon,
			NULL);
			
	  ffgra_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffgra_image, XV_X) + 50,
            XV_Y,                   xv_get(ffgra_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            PANEL_VALUE,              ff_gra,
            NULL);

	  ffplt_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(ffXRh_image, XV_X) + 270,
            XV_Y,                   xv_get(ffXRh_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    plt_icon,
			NULL);
			
	  ffplt_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffplt_image, XV_X) + 50,
            XV_Y,                   xv_get(ffplt_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            PANEL_VALUE,              ff_plt,
            NULL);

	  ffXRe_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(ffXRd_image, XV_X) + 270,
            XV_Y,                   xv_get(ffXRd_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    XRe_icon,
			NULL);
			
	  ffXRe_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffXRe_image, XV_X) + 50,
            XV_Y,                   xv_get(ffXRe_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            PANEL_VALUE,              ff_XRe,
            NULL);

	  ffXRs_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(ffXRr_image, XV_X) + 270,
            XV_Y,                   xv_get(ffXRr_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    XRs_icon,
			NULL);
			
	  ffXRs_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffXRs_image, XV_X) + 50,
            XV_Y,                   xv_get(ffXRs_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            PANEL_VALUE,              ff_XRs,
            NULL);

	  ffpkzip_image = (Panel_item)xv_create(panel3, PANEL_MESSAGE,
            XV_X,                   xv_get(ffdos_image, XV_X) + 270,
            XV_Y,                   xv_get(ffdos_image, XV_Y),
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_IMAGE,    pkzip_icon,
			NULL);
			
	  ffpkzip_choice = (Panel_item) xv_create(panel3, PANEL_CHOICE,
            XV_X,                   xv_get(ffpkzip_image, XV_X) + 50,
            XV_Y,                   xv_get(ffpkzip_image, XV_Y),
            PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
            PANEL_LABEL_STRING,   "Filtered: ",
            PANEL_CHOICE_STRINGS, "Yes", "No", "All but",NULL,
			PANEL_NOTIFY_PROC,		toggle_filter,
			PANEL_CLIENT_DATA,		choice,
            PANEL_VALUE,              ff_pkzip,
            NULL);

      xv_set (panel3, PANEL_LAYOUT, PANEL_HORIZONTAL, NULL);

      freset_button = (Panel_item) xv_create (panel3, PANEL_BUTTON,
					XV_X,						10,
					XV_Y,						(int)xv_get(ffpkzip_image, XV_Y) + 50,
                    PANEL_ITEM_COLOR,            CMS_CONTROL_COLORS + BLACK,
                    PANEL_LABEL_STRING,           "Show all files",
					PANEL_NOTIFY_PROC,		toggle_filter,
					PANEL_CLIENT_DATA,		button,
                    NULL);

      fapply_button = (Panel_item) xv_create (panel3, PANEL_BUTTON,
					XV_X,						210,
					XV_Y,						(int)xv_get(ffpkzip_image, XV_Y) + 50,
                    PANEL_ITEM_COLOR,            CMS_CONTROL_COLORS + BLACK,
                    PANEL_LABEL_STRING,           "Apply and Save",
					PANEL_NOTIFY_PROC,		apply_funct,
                    NULL);

	  fquit_button = (Panel_item) xv_create(panel3, PANEL_BUTTON, 
					XV_X,						410,
					XV_Y,						(int)xv_get(ffpkzip_image, XV_Y) + 50,
					PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
					PANEL_LABEL_STRING,     "Dismiss",
					PANEL_CLIENT_DATA,		FALSE,
					NULL);

    window_fit(panel3);
    window_fit(subframe2);


    test_choice = (Panel_item)xv_create(panel2, PANEL_LIST,
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LIST_INSERT_DUPLICATE,	FALSE,
			PANEL_READ_ONLY,				TRUE,
			PANEL_LIST_MODE,				PANEL_LIST_READ,
			PANEL_LIST_DISPLAY_ROWS,		10,
            PANEL_LIST_ROW_HEIGHT,   		35,
            PANEL_LIST_WIDTH,           	-1,
            PANEL_LIST_TITLE,           	"		Directory list",
            PANEL_NOTIFY_PROC,      		list_notify_proc,
            NULL);


    window_fit(panel2);
    window_fit(subframe);

      propframe = (Frame) xv_create (frame, FRAME_CMD,
                                    XV_WIDTH,           300,
                                    XV_HEIGHT,          50,
                                    XV_X,               xv_get(frame, XV_X),
                                    XV_Y,               xv_get(frame, XV_Y),
                                    FRAME_LABEL,        "Properties",
                                    NULL);


      proppanel = (Panel) xv_create (propframe, PANEL,
                                    XV_X,               0,
                                    XV_Y,               0,
                                    WIN_CMS,            cms,
                                    PANEL_LAYOUT,    PANEL_VERTICAL,
                                    NULL);

      primarySearchPath = (Panel_item) xv_create (proppanel, PANEL_TEXT,
               PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
                    PANEL_LABEL_STRING, "Primary Search Path",
                    PANEL_VALUE,    primaryPath,
                    PANEL_VALUE_DISPLAY_LENGTH, 40,
                    PANEL_VALUE_STORED_LENGTH, BUFSIZ,
                    PANEL_READ_ONLY, FALSE,
                    PANEL_VALUE_UNDERLINED,       TRUE,
                    NULL);
    
      xv_set (proppanel, PANEL_LAYOUT, PANEL_HORIZONTAL, NULL);

	  prime_toCurr = (Panel_item) xv_create(proppanel, PANEL_BUTTON, 
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_STRING,     "Set Primary to Current",
			PANEL_NOTIFY_PROC,		set_current_loc,
			NULL);

      xv_set (proppanel, PANEL_LAYOUT, PANEL_VERTICAL, NULL);

      secondarySearchPath = (Panel_item) xv_create (proppanel, PANEL_TEXT,
               PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
                    PANEL_LABEL_STRING, "Secondary Search Path",
                    PANEL_VALUE,    secondaryPath,
                    PANEL_VALUE_DISPLAY_LENGTH, 40,
                    PANEL_VALUE_STORED_LENGTH, BUFSIZ,
                    PANEL_READ_ONLY, FALSE,
                    PANEL_VALUE_UNDERLINED,       TRUE,
                    NULL);
    
      xv_set (proppanel, PANEL_LAYOUT, PANEL_HORIZONTAL, NULL);

	  second_toCurr = (Panel_item) xv_create(proppanel, PANEL_BUTTON, 
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_STRING,     "Set Secondary to Current",
			PANEL_NOTIFY_PROC,		set_current_loc,
			NULL);

      xv_set (proppanel, PANEL_LAYOUT, PANEL_VERTICAL, NULL);

      primaryName = (Panel_item) xv_create (proppanel, PANEL_TEXT,
               PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
                    PANEL_LABEL_STRING, "Primary Search Button Name",
                    PANEL_VALUE,    primaryNameVal,
                    PANEL_VALUE_DISPLAY_LENGTH, 40,
                    PANEL_VALUE_STORED_LENGTH, BUFSIZ,
                    PANEL_READ_ONLY, FALSE,
                    PANEL_VALUE_UNDERLINED,       TRUE,
                    NULL);
    

      secondaryName = (Panel_item) xv_create (proppanel, PANEL_TEXT,
               PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
                    PANEL_LABEL_STRING, "Secondary Search Button Name",
                    PANEL_VALUE,    secondaryNameVal,
                    PANEL_VALUE_DISPLAY_LENGTH, 40,
                    PANEL_VALUE_STORED_LENGTH, BUFSIZ,
                    PANEL_READ_ONLY, FALSE,
                    PANEL_VALUE_UNDERLINED,       TRUE,
                    NULL);
    
	  targetChoice = (Panel_item) xv_create(proppanel, PANEL_CHOICE,
               		PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
                	PANEL_LABEL_STRING, "Target Type: ",
                	PANEL_CHOICE_STRINGS, "Directory", "File",NULL,
                	PANEL_NOTIFY_PROC,        target_toggle,
                	PANEL_VALUE,              targetFlag,
                    NULL);
			

	 if ((int)xv_get(targetChoice, PANEL_VALUE) == 0)
		xv_set(goto_item, XV_SHOW, FALSE, NULL);

      tagName = (Panel_item) xv_create (proppanel, PANEL_TEXT,
               PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
                    PANEL_LABEL_STRING, "Tag on Value",
                    PANEL_VALUE,    tag,
                    PANEL_VALUE_DISPLAY_LENGTH, 40,
                    PANEL_VALUE_STORED_LENGTH, BUFSIZ,
                    PANEL_READ_ONLY, FALSE,
                    PANEL_VALUE_UNDERLINED,       TRUE,
					PANEL_INACTIVE,				  targetFlag,
                    NULL);
    
      view_choice = (Panel_item) xv_create(proppanel, PANEL_TOGGLE,
                    PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
                    PANEL_LABEL_STRING, "Show : ",
                    PANEL_CHOICE_STRINGS, "File type", "File size", "File name" ,NULL,
                    PANEL_VALUE,              viewFlag,
                	PANEL_NOTIFY_PROC,        control_toggle,
                    NULL);
         
      emaxName = (Panel_item) xv_create (proppanel, PANEL_TEXT,
               PANEL_ITEM_COLOR,             CMS_CONTROL_COLORS + BLACK,
                    PANEL_LABEL_STRING, "Emacs line",
                    PANEL_VALUE,    emaxed,
                    PANEL_VALUE_DISPLAY_LENGTH, 40,
                    PANEL_VALUE_STORED_LENGTH, BUFSIZ,
                    PANEL_READ_ONLY, FALSE,
                    PANEL_VALUE_UNDERLINED,       TRUE,
                    NULL);
    

      xv_set (proppanel, PANEL_LAYOUT, PANEL_HORIZONTAL, NULL);

	  quit_button = (Panel_item) xv_create(proppanel, PANEL_BUTTON, 
			PANEL_ITEM_COLOR,		CMS_CONTROL_COLORS + BLACK,	
			PANEL_LABEL_STRING,     "Dismiss",
			PANEL_CLIENT_DATA,		FALSE,
			NULL);


      apply_button = (Panel_item) xv_create (proppanel, PANEL_BUTTON,
                    PANEL_ITEM_COLOR,            CMS_CONTROL_COLORS + BLACK,
                    PANEL_LABEL_STRING,           "Apply and Save",
					PANEL_NOTIFY_PROC,		apply_funct,
                    NULL);

      window_fit (proppanel);
      window_fit (propframe);
}
