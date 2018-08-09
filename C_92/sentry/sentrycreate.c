/*
** File: sentry.c SCCS 6.12 - 4/20/94
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


#include "sentry_create.h"

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
			XV_Y,	rect_bottom((Rect *)xv_get(prop_mail_slide, XV_RECT)) + 10,
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
