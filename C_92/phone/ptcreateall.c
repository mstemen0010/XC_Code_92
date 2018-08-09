#include "ptcreate.h"
#include "gaintoolui.h"

void
create_children(void)
{

	Panel 	textpanel;




	nullmenu = (Menu) xv_create (NULL, MENU, NULL);

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

	dial_icon = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                                  XV_WIDTH,          64,
                                                  XV_HEIGHT,         64,
                                                  SERVER_IMAGE_BITS, dial_bits,
                                                  NULL);

    phonebook_icon =    (Server_image) xv_create (NULL, SERVER_IMAGE,
                                                  XV_WIDTH,          64,
                                                  XV_HEIGHT,         64,
                                                  SERVER_IMAGE_BITS, icon_bits,
                                                  NULL);
    phone_image =       (Server_image) xv_create (NULL, SERVER_IMAGE,
                                                  XV_WIDTH,          64,
                                                  XV_HEIGHT,         64,
                                                  SERVER_IMAGE_BITS, image_bits,
                                                  NULL);
    phword_image =      (Server_image) xv_create (NULL, SERVER_IMAGE,
                                                  XV_WIDTH,          64,
                                                  XV_HEIGHT,         64,
                                                  SERVER_IMAGE_BITS, phword_bits,
                                                  NULL);
    bkword_image =      (Server_image) xv_create (NULL, SERVER_IMAGE,
                                                  XV_WIDTH,          64,
                                                  XV_HEIGHT,         64,
                                                  SERVER_IMAGE_BITS, bkword_bits,
                                                  NULL);
    mask_icon =         (Server_image) xv_create (NULL, SERVER_IMAGE,
                                                  XV_WIDTH,          64,
                                                  XV_HEIGHT,         64,
                                                  XV_DEPTH,          1,
                                                  SERVER_IMAGE_BITS, mask_bits,
                                                  NULL);
    ff_icon = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                                  XV_WIDTH,          32, 
                                                  XV_HEIGHT,         16, 
                                                  SERVER_IMAGE_BITS, ff_bits,
                                                  NULL);

    rw_icon = (Server_image) xv_create (NULL, SERVER_IMAGE,
                                                  XV_WIDTH,          32, 
                                                  XV_HEIGHT,         16, 
                                                  SERVER_IMAGE_BITS, rw_bits,
                                                  NULL);

    panel =             (Panel) xv_create (frame, PANEL, 
               				XV_HELP_DATA,    "textsw:panel",
                            XV_HEIGHT,       340,
                            XV_WIDTH,     	 275, 
                      		PANEL_LAYOUT,    PANEL_VERTICAL,
							WIN_CMS,			phonetoolcms,
                            NULL);

    phoneimage =        xv_create (panel, PANEL_BUTTON,
               				XV_HELP_DATA,    "textsw:info",
							PANEL_NOTIFY_PROC,        help,
                            PANEL_LABEL_IMAGE,   phone_image,
                            XV_Y,                10,
                            XV_X,                10,
                            NULL);

     dial_image =        xv_create (panel, PANEL_BUTTON,
               				XV_HELP_DATA,    "textsw:autoDial",
							PANEL_NOTIFY_PROC,        dial,
                            PANEL_LABEL_IMAGE,   dial_icon,
                            XV_Y,                10,
                            XV_X,                100,
                            NULL);   
/* 
    bkimage =           xv_create (panel, PANEL_MESSAGE,
                                   PANEL_LABEL_IMAGE,   bkword_image,
                                   XV_Y,                10,
                                   XV_X,                145,
                                   NULL);   
    phimage =           xv_create (panel, PANEL_MESSAGE,
                                   PANEL_LABEL_IMAGE,   phword_image,
                                   XV_Y,                10,
                                   XV_X,                85,
                                   NULL);   
*/
    word_item = (Panel_item) xv_create (panel, PANEL_TEXT,
               XV_HELP_DATA,                 "textsw:wordItem",
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
               PANEL_LABEL_STRING, "Search for: ",
               PANEL_VALUE_DISPLAY_LENGTH, 15,
               PANEL_VALUE_STORED_LENGTH, BUFSIZ - 1,
               PANEL_NOTIFY_PROC, look_up_sys,
			   PANEL_CLIENT_DATA, search,
               NULL);
    xv_create (panel, PANEL_BUTTON, 
               XV_HELP_DATA,                 "textsw:system",
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
               PANEL_LABEL_STRING,           "Search system phone book",
               PANEL_NOTIFY_PROC,            look_up_sys,
			   PANEL_CLIENT_DATA,            button,
               NULL);

    xv_create (panel, PANEL_BUTTON, 
               XV_HELP_DATA,                 "textsw:personal",
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
               PANEL_LABEL_STRING,           "Search personal phone book",
               PANEL_NOTIFY_PROC,            look_personal,
			   PANEL_CLIENT_DATA,            button,
               NULL);

	xv_set (panel, PANEL_LAYOUT, PANEL_HORIZONTAL, NULL);

    xv_create (panel, PANEL_BUTTON,
               XV_HELP_DATA,                 "textsw:addper",
  			   XV_X,                         3,
               XV_Y,                         185,     
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + CONFIRMCOLOR,
               PANEL_LABEL_STRING,           "Add to",
               PANEL_NOTIFY_PROC,            add_panel,
               PANEL_VALUE_UNDERLINED,       FALSE,
			   PANEL_CLIENT_DATA,            button,
               NULL);

    editbutton = (Panel_item) xv_create (panel, PANEL_BUTTON,
               XV_HELP_DATA,                 "textsw:upper",
  			   XV_X,                         75,
               XV_Y,                         185,     
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + CONFIRMCOLOR,
               PANEL_LABEL_STRING,           "Edit",
               PANEL_NOTIFY_PROC,            editor,
			   PANEL_CLIENT_DATA,            button,
               NULL);

    xv_create (panel, PANEL_TEXT,
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + CONFIRMCOLOR,
  			   XV_X,                         125,
               XV_Y,                         190,     
               PANEL_VALUE,                  "Personal Phone Book",
               PANEL_VALUE_DISPLAY_LENGTH,   20,
               PANEL_VALUE_UNDERLINED,       FALSE,
			   PANEL_READ_ONLY, TRUE,
               NULL);

    xv_create (panel, PANEL_BUTTON, 
               XV_HELP_DATA,                 "textsw:quit",
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + DISMISSCOLOR,
               PANEL_LABEL_STRING,           "Quit",
               PANEL_NOTIFY_PROC,            quitprg,
               PANEL_CLIENT_DATA,            frame,
               NULL);

	xv_create (panel, PANEL_BUTTON,			
               XV_HELP_DATA,                 "textsw:props",
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
 /*              XV_X,                         70,  */
  /*             XV_Y,                         207,  */
		       PANEL_LABEL_STRING,			"Properties",
               PANEL_NOTIFY_PROC,            props,
			   PANEL_CLIENT_DATA,            button,
               NULL);

	xv_create (panel, PANEL_BUTTON,			
               XV_HELP_DATA,                 "textsw:print",
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
   /*            XV_X,                         160,  */
    /*           XV_Y,                         207,  */
		       PANEL_LABEL_STRING,			"Print list",
               PANEL_NOTIFY_PROC,            print_list,
			   PANEL_CLIENT_DATA,            button,
               NULL);

    mess_item = (Panel_item) xv_create (panel, PANEL_TEXT,
               XV_HELP_DATA,                 "textsw:messItem",
			   	PANEL_ITEM_COLOR,		 CMS_CONTROL_COLORS + BASECOLOR,
                                        PANEL_VALUE_UNDERLINED,     FALSE,
                                        PANEL_VALUE_DISPLAY_LENGTH, 25,
                                        PANEL_VALUE_STORED_LENGTH,  BUFSIZ - 1,
										PANEL_READ_ONLY, TRUE,
                                        NULL);

    mess_item2 = (Panel_item) xv_create (panel, PANEL_TEXT,
               XV_HELP_DATA,                 "textsw:messItem",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + BASECOLOR,
                PANEL_VALUE_UNDERLINED,     FALSE,
                PANEL_VALUE_DISPLAY_LENGTH, 25,
                PANEL_VALUE_STORED_LENGTH,  BUFSIZ - 1,
				PANEL_READ_ONLY, TRUE,
                NULL);

    mess_item3 = (Panel_item) xv_create (panel, PANEL_TEXT,
               XV_HELP_DATA,                 "textsw:messItem",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + BASECOLOR,
                PANEL_VALUE_UNDERLINED,     FALSE,
                PANEL_VALUE_DISPLAY_LENGTH, 25,
                PANEL_VALUE_STORED_LENGTH,  BUFSIZ - 1,
				PANEL_READ_ONLY, TRUE,
                NULL);


    textsw =        (Textsw) xv_create (frame, TEXTSW, 
                XV_HEIGHT,       310,
                XV_WIDTH,     	 530, 
				TEXTSW_MEMORY_MAXIMUM,  200000,
				WIN_CMS,			phonetoolcms,
				WIN_FOREGROUND_COLOR,	CMS_CONTROL_COLORS + FILECOLOR,
			  	WIN_BACKGROUND_COLOR,	CMS_CONTROL_COLORS + SCREENCOLOR ,
				WIN_MENU,             nullmenu,
				TEXTSW_BROWSING, 		TRUE,
                TEXTSW_DISABLE_CD,      TRUE,
                TEXTSW_DISABLE_LOAD,    TRUE,
                NULL); 

 	 textpanel = (Panel) xv_create (frame, PANEL,
                XV_HEIGHT,       30,
                XV_WIDTH,     	 530, 
				WIN_BELOW,		textsw,
				WIN_RIGHT_OF,	panel,
				WIN_CMS,			phonetoolcms,
                NULL);  
 
    xv_create (textpanel, PANEL_BUTTON, 
               XV_HELP_DATA,                 "textsw:cls",
			   XV_X,		100,
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + DISMISSCOLOR,
               PANEL_LABEL_STRING,           "                    Clear Screen                    ",
               PANEL_NOTIFY_PROC,            clear_screen,
               PANEL_CLIENT_DATA,            button,
               NULL);

    icon =          (Icon) xv_create (frame, ICON, 
                ICON_IMAGE,       phonebook_icon,
                ICON_MASK_IMAGE,  mask_icon,
                ICON_TRANSPARENT, TRUE,
                XV_X,             100,
                XV_Y,             100,
                NULL);

    addframe = (Frame) xv_create (frame, FRAME_CMD,
                XV_WIDTH,       300,
                XV_HEIGHT,      50,
                XV_X,           xv_get (frame, XV_X),
                XV_Y,           xv_get (frame, XV_Y),
                FRAME_LABEL,    "Add  to personal phone book",
                NULL);
    addpanel = (Panel) xv_create (addframe, PANEL, 
				XV_X,               0,
                XV_Y,               0,
				WIN_CMS,			phonetoolcms,
                WIN_ROWS,       10,
                WIN_COLUMNS,    25,  
                NULL); 
   
  	lname_add = (Panel_item) xv_create (addpanel, PANEL_TEXT,
               	XV_HELP_DATA,                 "textsw:lnadd",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
                PANEL_LABEL_STRING,         "Last Name: ",
                PANEL_VALUE_DISPLAY_LENGTH, 40,
                PANEL_VALUE_STORED_LENGTH,  BUFSIZ - 1,
                PANEL_NOTIFY_PROC,          add_line,
				PANEL_CLIENT_DATA,          lnameadd,
                NULL);

  	fname_add = (Panel_item) xv_create (addpanel, PANEL_TEXT,
               	XV_HELP_DATA,                 "textsw:fnadd",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
                PANEL_LABEL_STRING,         "First Name: ",
                PANEL_VALUE_DISPLAY_LENGTH, 40,
                PANEL_VALUE_STORED_LENGTH,  BUFSIZ - 1,
                PANEL_NOTIFY_PROC,          add_line,
				PANEL_CLIENT_DATA,   fnameadd,
                NULL);
   
  	phone_add = (Panel_item) xv_create (addpanel, PANEL_TEXT,
               	XV_HELP_DATA,                 "textsw:pnadd",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
                PANEL_LABEL_STRING,         "Phone #: ",
                PANEL_VALUE_DISPLAY_LENGTH, 20,
                PANEL_VALUE_STORED_LENGTH,  BUFSIZ - 1,
                PANEL_NOTIFY_PROC,          add_line,
				PANEL_CLIENT_DATA,   phoneadd,
                NULL);
   
  	ext_add =   (Panel_item) xv_create (addpanel, PANEL_TEXT,
               	XV_HELP_DATA,                 "textsw:exadd",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
                PANEL_LABEL_STRING,         "Ext. #: ",
                PANEL_VALUE_DISPLAY_LENGTH, 10,
                PANEL_VALUE_STORED_LENGTH,  BUFSIZ - 1,
                PANEL_NOTIFY_PROC,          add_line,
				PANEL_CLIENT_DATA,  extadd,
                NULL);

  	addr_add =  (Panel_item) xv_create (addpanel, PANEL_TEXT,
               	XV_HELP_DATA,                 "textsw:addadd",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
                PANEL_LABEL_STRING,         "Address: ",
                PANEL_VALUE_DISPLAY_LENGTH, 60,
                PANEL_VALUE_STORED_LENGTH,  BUFSIZ - 1,
                PANEL_NOTIFY_PROC,          add_line,
				PANEL_CLIENT_DATA,   addradd,
                NULL);

  	note_add = (Panel_item) xv_create (addpanel, PANEL_TEXT,
               	XV_HELP_DATA,                 "textsw:noadd",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
                PANEL_LABEL_STRING,          "Notes: ",
                PANEL_VALUE_DISPLAY_LENGTH,  80,
                PANEL_VALUE_STORED_LENGTH,   BUFSIZ  * 5 - 1,
                PANEL_NOTIFY_PROC,           add_line,
				PANEL_CLIENT_DATA,    noteadd,
                NULL);

  	addinsert_but = (Panel_item) xv_create (addpanel, PANEL_BUTTON, 
               	XV_HELP_DATA,                 "textsw:insert",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + CONFIRMCOLOR,
                PANEL_LABEL_STRING, "Insert to" 
                " personal phone"
                " book",
                PANEL_NOTIFY_PROC,  insert_add,
				PANEL_CLIENT_DATA,    button,
                NULL);

	xv_set (addpanel, PANEL_LAYOUT, PANEL_HORIZONTAL, NULL);

  	(void) xv_create (addpanel, PANEL_BUTTON, 
               XV_HELP_DATA,                 "textsw:adddismiss",
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + DISMISSCOLOR,
               PANEL_LABEL_STRING,           "Dismiss",
        	   PANEL_NOTIFY_PROC,  quitpanel,
			   PANEL_CLIENT_DATA,    button,
               NULL);


    updtextframe = (Frame) xv_create (frame, FRAME_CMD,
               XV_WIDTH,           300,
               XV_HEIGHT,          50,
               XV_X,               xv_get(frame, XV_X),
               XV_Y,               xv_get(frame, XV_Y),
               FRAME_LABEL,        "Update personal"
               " phone book",
               NULL);
   
   
     updtxtpanel = (Panel) xv_create (updtextframe, PANEL,
           XV_HELP_DATA,                 "textsw:updtext",
		   WIN_CMS,     		phonetoolcms,
           XV_X,               xv_get(updtextframe, XV_X),
           XV_Y,               xv_get(updtextframe, XV_Y),
           PANEL_LAYOUT,    PANEL_VERTICAL, 
           NULL);
   
     (Panel_item) xv_create (updtxtpanel, PANEL_BUTTON, 
		   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + DISMISSCOLOR,
           XV_X,               10,
           XV_Y,               5,
   		PANEL_LABEL_STRING,           "Dismiss",
           PANEL_NOTIFY_PROC,  quitpanel,
      		PANEL_CLIENT_DATA,    button,
      		NULL);
   
     (Panel_item) xv_create (updtxtpanel, PANEL_BUTTON, 
               XV_HELP_DATA,                 "textsw:updsave",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + CONFIRMCOLOR,
           XV_X,               75,
           XV_Y,               5,
   		PANEL_LABEL_STRING,           "Save changes",
      		PANEL_CLIENT_DATA,    button,
           PANEL_NOTIFY_PROC,          save_textsw,
      		NULL);
   
     xv_set (updtxtpanel, PANEL_LAYOUT, PANEL_HORIZONTAL, NULL);
   
   
     updtextsw = (Textsw) xv_create (updtextframe, TEXTSW, 
               XV_HELP_DATA,                 "textsw:updtext",
		   WIN_CMS,     		phonetoolcms,
		   WIN_FOREGROUND_COLOR,	CMS_CONTROL_COLORS + FILECOLOR,
		   WIN_BACKGROUND_COLOR,	CMS_CONTROL_COLORS + SCREENCOLOR, 
           XV_X,               xv_get(updtxtpanel, XV_X),
           XV_Y,               xv_get(updtxtpanel, XV_Y) + 30,
           WIN_ROWS,       40,
           WIN_COLUMNS,    80,  
           TEXTSW_DISABLE_LOAD,    TRUE,
           NULL); 
   
   
     window_fit (updtextsw); 
     window_fit (updtxtpanel);
     window_fit (updtextframe);



      updframe = (Frame) xv_create (frame, FRAME_CMD,
                                    XV_WIDTH,           300,
                                    XV_HEIGHT,          50,
                                    XV_X,               xv_get(frame, XV_X),
                                    XV_Y,               xv_get(frame, XV_Y),
                                    FRAME_LABEL,        "Update personal"
                                                        " phone book",
                                    NULL);
     
     
      updpanel = (Panel) xv_create (updframe, PANEL,
               XV_HELP_DATA,                 "textsw:panel",
				XV_X,               0,
                XV_Y,               0,
		   		WIN_CMS,     		phonetoolcms,
                WIN_ROWS,           10,
                WIN_COLUMNS,        25,
                NULL);
    
      word_upd =  (Panel_item) xv_create (updpanel, PANEL_TEXT,
               XV_HELP_DATA,                 "textsw:search",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
                PANEL_LABEL_STRING,         "Search for: ",
                PANEL_VALUE_DISPLAY_LENGTH, 20,
                PANEL_VALUE_STORED_LENGTH,  BUFSIZ - 1,
                PANEL_NOTIFY_PROC,          find_match,
    			PANEL_CLIENT_DATA, search,
                NULL);
     
      lname_upd = (Panel_item) xv_create (updpanel, PANEL_TEXT,
               XV_HELP_DATA,                 "textsw:lnup",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
                PANEL_LABEL_STRING,         "Last Name: ",
                PANEL_VALUE_DISPLAY_LENGTH, 40,
                PANEL_VALUE_STORED_LENGTH,  BUFSIZ - 1,
    			PANEL_CLIENT_DATA,   lnameupd,
                NULL);
     
      fname_upd = (Panel_item) xv_create (updpanel, PANEL_TEXT,
               XV_HELP_DATA,                 "textsw:fnup",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
                PANEL_LABEL_STRING,         "First Name: ",
                PANEL_VALUE_DISPLAY_LENGTH, 40,
                PANEL_VALUE_STORED_LENGTH,  BUFSIZ - 1,
                PANEL_NOTIFY_PROC,          add_line,
    			PANEL_CLIENT_DATA,   fnameupd,
                NULL);
    
      phone_upd = (Panel_item) xv_create (updpanel, PANEL_TEXT,
               XV_HELP_DATA,                 "textsw:pnup",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
                PANEL_LABEL_STRING,         "Phone #: ",
                PANEL_VALUE_DISPLAY_LENGTH, 20,
                PANEL_VALUE_STORED_LENGTH,  BUFSIZ - 1,
                PANEL_NOTIFY_PROC,          add_line,
    			PANEL_CLIENT_DATA,   phoneupd,
                NULL);
     
      ext_upd =   (Panel_item) xv_create (updpanel, PANEL_TEXT,
               XV_HELP_DATA,                 "textsw:exup",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
                PANEL_LABEL_STRING,         "Ext. #: ",
                PANEL_VALUE_DISPLAY_LENGTH, 10,
                PANEL_VALUE_STORED_LENGTH,  BUFSIZ - 1,
                PANEL_NOTIFY_PROC,          add_line,
    			PANEL_CLIENT_DATA,   extupd,
                NULL);
     
      addr_upd =  (Panel_item) xv_create (updpanel, PANEL_TEXT,
               XV_HELP_DATA,                 "textsw:addup",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
                PANEL_LABEL_STRING,         "Address: ",
                PANEL_VALUE_DISPLAY_LENGTH, 60,
                PANEL_VALUE_STORED_LENGTH,  BUFSIZ - 1,
                PANEL_NOTIFY_PROC,          add_line,
    			PANEL_CLIENT_DATA,   addrupd,
                NULL);
     
      note_upd =  (Panel_item) xv_create (updpanel, PANEL_TEXT,
               XV_HELP_DATA,                 "textsw:noup",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
                PANEL_LABEL_STRING,         "Notes: ",
                PANEL_VALUE_DISPLAY_LENGTH, 40,
                PANEL_VALUE_STORED_LENGTH,  BUFSIZ * 5  - 1,
                PANEL_NOTIFY_PROC,          add_line,
    			PANEL_CLIENT_DATA,   noteupd,
                NULL);
     
      updinsert_but = (Panel_item) xv_create (updpanel, PANEL_BUTTON,
               XV_HELP_DATA,                 "textsw:update",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + CONFIRMCOLOR,
                PANEL_LABEL_STRING, "Update"
                " personal"
                " phone book",
                PANEL_NOTIFY_PROC,  insert_upd,
    			PANEL_CLIENT_DATA,   button,
                NULL);
    
      xv_set (updpanel, PANEL_LAYOUT, PANEL_HORIZONTAL, NULL);
    
      findlast_but = (Panel_item) xv_create (updpanel, PANEL_BUTTON,
               XV_HELP_DATA,                 "textsw:last",
    			PANEL_INACTIVE, 	TRUE,
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
                PANEL_LABEL_IMAGE,   rw_icon,
                /* PANEL_LABEL_STRING, "Find last", */
                PANEL_NOTIFY_PROC,  find_last_match,
    			PANEL_CLIENT_DATA,   button,
                NULL);
     

      findmatch_but = (Panel_item) xv_create (updpanel, PANEL_BUTTON,
               XV_HELP_DATA,                 "textsw:first",
                PANEL_ITEM_COLOR,            CMS_CONTROL_COLORS + FILECOLOR,
                PANEL_LABEL_STRING, "First Match",
                PANEL_NOTIFY_PROC,  find_match,
                PANEL_CLIENT_DATA,   button,
                NULL);


        findnext_but = (Panel_item) xv_create (updpanel, PANEL_BUTTON,
               XV_HELP_DATA,                 "textsw:next",
    			PANEL_INACTIVE, 	TRUE,
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
                PANEL_LABEL_IMAGE,   ff_icon,
              	/*  PANEL_LABEL_STRING, "Find next match", */
                PANEL_NOTIFY_PROC,  find_next_match,
    			PANEL_CLIENT_DATA,   button,
                NULL);
     

        delete_but = (Panel_item) xv_create (updpanel, PANEL_BUTTON,
               XV_HELP_DATA,                 "textsw:delete",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + FILECOLOR,
                PANEL_LABEL_STRING, "Delete entry",
                PANEL_NOTIFY_PROC,  delete_line,
    			PANEL_CLIENT_DATA,   button,
                NULL);
     

      (void) xv_create (updpanel, PANEL_BUTTON, 
           		XV_HELP_DATA,                 "textsw:updismiss",
			   	PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + DISMISSCOLOR,
                PANEL_LABEL_STRING,           "Dismiss",
                PANEL_NOTIFY_PROC,  quitpanel,
    			PANEL_CLIENT_DATA,   button,
                NULL);
    
      window_fit (updpanel);
      window_fit (updframe);

	  exportfnameframe = (Frame)xv_create (frame, FRAME_CMD, 
									XV_WIDTH, 			300,
                                    XV_HEIGHT,          50,
                                    XV_X,               xv_get(frame, XV_X),
                                    XV_Y,               xv_get(frame, XV_Y),
                                    FRAME_LABEL,        "Export filename",
                                    NULL);
    
      exportfnamepanel = (Panel) xv_create (exportfnameframe, PANEL,
		   							WIN_CMS,     		phonetoolcms,
                                    PANEL_LAYOUT,    PANEL_VERTICAL,
                                    NULL);

	  exportfname = (Panel_item) xv_create (exportfnamepanel, PANEL_TEXT, 
			   		PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
    				PANEL_LABEL_STRING, "Filename (include full path): ",
    				PANEL_VALUE_DISPLAY_LENGTH, 40,
    				PANEL_VALUE_STORED_LENGTH, BUFSIZ, 
                    PANEL_NOTIFY_PROC,  updateexport,
    				NULL);

    
      window_fit (exportfnamepanel);
      window_fit (exportfnameframe);


      propframe = (Frame) xv_create (frame, FRAME_CMD,
                                    XV_WIDTH,           300,
                                    XV_HEIGHT,          50,
                                    XV_X,               xv_get(frame, XV_X),
                                    XV_Y,               xv_get(frame, XV_Y),
                                    FRAME_LABEL,        "Properties",
                                    NULL);
    
     
      proppanel = (Panel) xv_create (propframe, PANEL,
           		XV_HELP_DATA,                 "textsw:panel",
				XV_X,               0,
                XV_Y,               0,
		   		WIN_CMS,     		phonetoolcms,
                PANEL_LAYOUT,    PANEL_VERTICAL,
                NULL);

      prop_color = (Panel_item) xv_create (proppanel, PANEL_CHOICE,
           		XV_HELP_DATA,                 "textsw:color",
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
    			PANEL_LABEL_STRING, "Color : ",
    			PANEL_CHOICE_STRINGS, "On", "Off",NULL,
       		    PANEL_NOTIFY_PROC, 		  propchange_color,
    			PANEL_VALUE, 			  colorflag, 
    			PANEL_CLIENT_DATA,            colortype,
    			NULL);     
    
	  color_choice = (Panel_item) xv_create (proppanel, PANEL_CHOICE,
           		XV_HELP_DATA,                 "textsw:class",
				PANEL_CHOOSE_NONE,				TRUE,
				PANEL_INACTIVE,				colorflag,
			    PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
    			PANEL_LABEL_STRING, "Phonetool color buttons grouped by type : ",
    			PANEL_CHOICE_STRINGS, "Screen", "Dismiss", "Confirm","File", "Support", "Basic",   NULL,
       		    PANEL_NOTIFY_PROC, 		 	  findcolor_base,
    			NULL);     
    
	  ptred_slider  = (Panel_item) xv_create (proppanel, PANEL_SLIDER,
           		XV_HELP_DATA,                 "textsw:red",
				PANEL_SLIDER_END_BOXES,		TRUE,
				PANEL_INACTIVE,				colorflag,
			    PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
				PANEL_LABEL_STRING,			 "Red value:     ",
				PANEL_VALUE,			     0,
				PANEL_MIN_VALUE,			   0,
				PANEL_MAX_VALUE,			 255, 
				PANEL_TICKS,				   1,
       		    PANEL_NOTIFY_PROC, 		  alter_color,
				NULL);
				
	  ptgreen_slider  = (Panel_item) xv_create (proppanel, PANEL_SLIDER,
           		XV_HELP_DATA,                 "textsw:green",
				PANEL_SLIDER_END_BOXES,		TRUE,
				PANEL_INACTIVE,				colorflag,
			    PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
				PANEL_LABEL_STRING,			 "Green value: ",
				PANEL_VALUE,			     0,
				PANEL_MIN_VALUE,			   0,
				PANEL_MAX_VALUE,			 255, 
				PANEL_TICKS,				   1,
       		    PANEL_NOTIFY_PROC, 		  alter_color,
				NULL);
				
	  ptblue_slider  = (Panel_item) xv_create (proppanel, PANEL_SLIDER,
           		XV_HELP_DATA,                 "textsw:blue",
				PANEL_SLIDER_END_BOXES,		TRUE,
				PANEL_INACTIVE,				colorflag,
			    PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
				PANEL_LABEL_STRING,			 "Blue value:   ",
				PANEL_VALUE,			     0,
				PANEL_MIN_VALUE,			   0,
				PANEL_MAX_VALUE,			 255, 
				PANEL_TICKS,				   1,
       		    PANEL_NOTIFY_PROC, 		  alter_color,
				NULL);
				
      prop_print = (Panel_item) xv_create (proppanel, PANEL_CHOICE,
           		XV_HELP_DATA,                 "textsw:printer",
			    PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
    			PANEL_LABEL_STRING, 			"Print to : ",
    			PANEL_CLIENT_DATA,            printertype,
       		    PANEL_NOTIFY_PROC, 		  get_exportfile,
    			NULL);  
    
      prop_soundex_toggle = (Panel_item) xv_create (proppanel, PANEL_CHOICE,
                XV_HELP_DATA,               "textsw:color",
               	PANEL_ITEM_COLOR,           CMS_CONTROL_COLORS + SUPPORTCOLOR,
                PANEL_LABEL_STRING, 		"Soundex : ",
                PANEL_CHOICE_STRINGS, 		"On", "Off",NULL,
                PANEL_VALUE,              	soundexFlag,
                PANEL_CLIENT_DATA,          soundex,
				PANEL_NOTIFY_PROC,			toggle_soundex,
                NULL);	

      soundex_field_toggle = (Panel_item) xv_create (proppanel, PANEL_CHOICE,
				XV_X, 		(int)xv_get(prop_soundex_toggle, XV_X) + 175,
				XV_Y, 		(int)xv_get(prop_soundex_toggle, XV_Y),
                XV_HELP_DATA,               "textsw:color",
               	PANEL_ITEM_COLOR,           CMS_CONTROL_COLORS + SUPPORTCOLOR,
                PANEL_LABEL_STRING, 		"Soundex on : ",
                PANEL_CHOICE_STRINGS, 		"Last name", "First name", "All",NULL,
                PANEL_VALUE,              	soundexNameFlag,
                PANEL_CLIENT_DATA,          soundex,
                PANEL_INACTIVE,             soundexFlag,
                NULL);	

      soundex_tol_slide  = (Panel_item) xv_create (proppanel, PANEL_SLIDER,
				XV_X, 		(int)xv_get(prop_soundex_toggle, XV_X),
				XV_Y, 		(int)xv_get(prop_soundex_toggle, XV_Y) + 50,
				PANEL_SLIDER_WIDTH,    150,
                PANEL_SLIDER_END_BOXES,     TRUE,
                PANEL_INACTIVE,             soundexFlag,
                PANEL_ITEM_COLOR,            CMS_CONTROL_COLORS + SUPPORTCOLOR,
                PANEL_LABEL_STRING,          "Percent words sound alike:   ",
            	PANEL_SHOW_RANGE,       FALSE,
                PANEL_MIN_VALUE,             1,
                PANEL_MAX_VALUE,             100,
                PANEL_VALUE,              	soundexSlide,
            	PANEL_MIN_TICK_STRING,  "1",
            	PANEL_MAX_TICK_STRING,  "100",
				PANEL_TICKS,            10,
                NULL);


      prop_editor = (Panel_item) xv_create (proppanel, PANEL_TOGGLE,
           		XV_HELP_DATA,                 "textsw:filenames",
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
    			PANEL_LABEL_STRING, "File locations/names : ",
    			PANEL_CHOICE_STRINGS, "Custom - company","Default - company", "Custom - personal", "Default - personal", NULL,
       		    PANEL_NOTIFY_PROC, 		  propchange_edit,
    			PANEL_VALUE, 				propeditflag, 
    			NULL);  
    
	  george = (Panel_item) xv_create (proppanel, PANEL_TEXT,
           		XV_HELP_DATA,                 "textsw:CFN",
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
    				PANEL_LABEL_STRING, "Company filename: ",
    				PANEL_VALUE,	compfilename,
    				PANEL_INACTIVE, 	TRUE,
                    PANEL_VALUE_DISPLAY_LENGTH, 60,
                    PANEL_VALUE_STORED_LENGTH, BUFSIZ,
    			   	PANEL_READ_ONLY, TRUE,
                   	PANEL_VALUE_UNDERLINED,       FALSE,
                    NULL);

    
      prop_infile = (Panel_item) xv_create (proppanel, PANEL_TEXT,
           		XV_HELP_DATA,                 "textsw:PFN",
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
    				PANEL_LABEL_STRING, "Personal Filename: ",
    				PANEL_VALUE,	personfilename,
    				PANEL_INACTIVE, 	TRUE,
    				PANEL_VALUE_DISPLAY_LENGTH, 60,
    				PANEL_VALUE_STORED_LENGTH, BUFSIZ, 
    			   	PANEL_READ_ONLY, TRUE,
                   	PANEL_VALUE_UNDERLINED,       FALSE,
    				NULL);
    

      apply_button = (Panel_item) xv_create (proppanel, PANEL_BUTTON, 
           		XV_HELP_DATA,                 "textsw:apply",
			   		PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + CONFIRMCOLOR,
                   	PANEL_LABEL_STRING,           "Apply and Save",
       		        PANEL_NOTIFY_PROC,			  apply_funct,
    				PANEL_CLIENT_DATA,            writerc,
                   	NULL);
    
      xv_set (proppanel, PANEL_LAYOUT, PANEL_HORIZONTAL, NULL);
    
      (void) xv_create (proppanel, PANEL_BUTTON, 
           		XV_HELP_DATA,                 "textsw:reset",
			   	   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + CONFIRMCOLOR,
                   PANEL_LABEL_STRING,           "Reset all",
            	   PANEL_NOTIFY_PROC,  reset_all,
				   PANEL_CLIENT_DATA,    button,
               	   NULL);
    
      (void) xv_create (proppanel, PANEL_BUTTON, 
           		XV_HELP_DATA,                 "textsw:dismiss",
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + DISMISSCOLOR,
                   PANEL_LABEL_STRING,           "Dismiss",
            	   PANEL_NOTIFY_PROC,  quitpanel,
				   PANEL_CLIENT_DATA,    button,
               	   NULL);
    
    
      window_fit (proppanel);
      window_fit (propframe);


	dialframe = (Frame) xv_create (frame, FRAME_CMD, 
    			XV_WIDTH,           300,
                XV_HEIGHT,          50,    
                XV_X,               xv_get (frame, XV_X),
                XV_Y,               xv_get (frame, XV_Y),
                FRAME_LABEL,        "Phonetool Auto dial", 
                NULL);
    
    dialpanel = (Panel) xv_create (dialframe, PANEL, 
               	XV_HELP_DATA,    "textsw:panel",
		   		WIN_FOREGROUND_COLOR,	CMS_CONTROL_COLORS + SUPPORTCOLOR,
		   		WIN_BACKGROUND_COLOR,	CMS_CONTROL_COLORS + SCREENCOLOR,  
				WIN_CMS,			phonetoolcms,
                XV_HEIGHT,          	60,
                WIN_X,      			0,
                WIN_Y,      			0,  
                NULL);

			(Panel_item) xv_create (dialpanel, PANEL_MESSAGE, 
				PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
                WIN_X,      			10,
                WIN_Y,      			0,  
    			PANEL_READ_ONLY, TRUE,
                NULL);

			(Panel_item) xv_create (dialpanel, PANEL_MESSAGE, 
				PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
                WIN_X,      			10,
                WIN_Y,      			15,  
    			PANEL_READ_ONLY, TRUE,
                NULL);

    xv_set (dialpanel, PANEL_LAYOUT, PANEL_VERTICAL, NULL);
    
    dial_sound_output = (Panel_item) xv_create(dialpanel, PANEL_CHOICE,
			PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
            XV_HELP_DATA,                 "textsw:outPut",
        	PANEL_CHOICE_NROWS, 1,
        	PANEL_LAYOUT, PANEL_HORIZONTAL,
        	PANEL_CHOOSE_NONE, FALSE,
        	PANEL_LABEL_STRING, "Output:",
            PANEL_CHOICE_IMAGES,        speaker_image,head_phone_image, NULL,
			/*
        	PANEL_CHOICE_STRINGS,
            	"Spkr",
            	"Jack",
            	NULL,
			*/
            PANEL_NOTIFY_PROC,          sound_output,
        	NULL);

	dial_vol_slider  = (Panel_item) xv_create (dialpanel, PANEL_SLIDER,
			PANEL_ITEM_COLOR,			CMS_CONTROL_COLORS + SUPPORTCOLOR,
            XV_HELP_DATA,                 "textsw:dialVol",
			PANEL_LABEL_STRING,			"Dial tone volume:     ",
			PANEL_VALUE,			    5,
			PANEL_MIN_VALUE,			0,
			PANEL_MAX_VALUE,			25, 
			PANEL_TICKS,				1,
			NULL);

  	dial_number =	(Panel_item) xv_create (dialpanel, PANEL_TEXT,
			PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
            XV_HELP_DATA,                 "textsw:dialNumber",
            PANEL_LABEL_STRING,         "Phone Number: ",
            PANEL_VALUE_DISPLAY_LENGTH, 30,
            PANEL_VALUE_STORED_LENGTH,  BUFSIZ - 1,
            PANEL_NOTIFY_PROC,          dial_it,
            NULL);

    xv_set (dialpanel, PANEL_LAYOUT, PANEL_VERTICAL, NULL);

	(Panel_item) xv_create(dialpanel, PANEL_BUTTON,
            XV_HELP_DATA,                 "textsw:convert",
			PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
			PANEL_LABEL_STRING,			" Convert alpha number to digital number",
        	PANEL_NOTIFY_PROC,  convert_number,
            NULL);

	(Panel_item) xv_create(dialpanel, PANEL_BUTTON,
            XV_HELP_DATA,                 "textsw:grab",
			PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
			PANEL_LABEL_STRING,			" Grab current selection",
        	PANEL_NOTIFY_PROC,  get_prime_sel,
            NULL);
    
	(Panel_item) xv_create(dialpanel, PANEL_BUTTON,
            XV_HELP_DATA,                 "textsw:adNumber",
			PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
			PANEL_LABEL_STRING,			" Auto-Dial number",
        	PANEL_NOTIFY_PROC,  dial_it,
            NULL);
    
	(Panel_item) xv_create(dialpanel, PANEL_BUTTON,
           	XV_HELP_DATA,                 "textsw:dismiss",
			PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + DISMISSCOLOR,
			PANEL_LABEL_STRING,			" Dismiss ",
        	PANEL_NOTIFY_PROC,  quitpanel,
            NULL);
    
      window_fit (dialpanel);
      window_fit (dialframe);

	helpframe = (Frame) xv_create (frame, FRAME_CMD, 
    			XV_WIDTH,           450,
                XV_HEIGHT,          50,    
                XV_X,               xv_get(frame, XV_X) - 2,
                XV_Y,               xv_get(frame, XV_Y) + 96,
                FRAME_LABEL,        "- Phonetool Help -", 
    /*            FRAME_DONE_PROC,    nullfunct,   */
                NULL);
    
    	helppanel = (Panel) xv_create (helpframe, PANEL, 
		   		WIN_FOREGROUND_COLOR,	CMS_CONTROL_COLORS + FILECOLOR,
		   		WIN_BACKGROUND_COLOR,	CMS_CONTROL_COLORS + SCREENCOLOR,  
					WIN_CMS,			phonetoolcms,
                    XV_HEIGHT,          	60,
                    WIN_X,      			10,
                    WIN_Y,      			1,
                    NULL);

		(Panel_item) xv_create(helppanel, PANEL_BUTTON,
			   	  PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + DISMISSCOLOR,
				  PANEL_LABEL_STRING,			" Dismiss ",
        	      PANEL_NOTIFY_PROC,  quitpanel,
                  NULL);
    
    	helppanel1 = (Panel) xv_create (helpframe, PANEL, 
		   		WIN_FOREGROUND_COLOR,	CMS_CONTROL_COLORS + FILECOLOR,
		   		WIN_BACKGROUND_COLOR,	CMS_CONTROL_COLORS + SCREENCOLOR,  
					WIN_CMS,			phonetoolcms,
                    XV_HEIGHT,          	20,
                    WIN_X,      			10,
                    NULL);

		info_help = (Panel_item) xv_create (helppanel1, PANEL_MESSAGE,
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
                        PANEL_LABEL_BOLD,   TRUE,
                        PANEL_LABEL_STRING, "Phonetool info:",
                        NULL);

		info_helptw =	(Textsw) xv_create (helpframe, TEXTSW,
					WIN_CMS,				phonetoolcms,
		   				WIN_FOREGROUND_COLOR,	CMS_CONTROL_COLORS + FILECOLOR,
		   				WIN_BACKGROUND_COLOR,	CMS_CONTROL_COLORS + SCREENCOLOR, 
						WIN_X,      			10,
						WIN_BELOW,  helppanel1,
						TEXTSW_READ_ONLY,		TRUE,
            			TEXTSW_DISABLE_LOAD,    TRUE,
    					TEXTSW_BROWSING,		TRUE,
    					WIN_MENU,				nullmenu,
						WIN_ROWS, 				5,
						WIN_COLUMNS,   			60,
						TEXTSW_CONTENTS, "Phonetool allows you to query a company phonelist, or a personal one. In addition to this it also allows you to edit your personal phone list, and allows you to get customized phone list which you can re format in your favorite word processor via a flat file.",
						NULL);

        helppanel2 = (Panel) xv_create (helpframe, PANEL,
		   		WIN_FOREGROUND_COLOR,	CMS_CONTROL_COLORS + FILECOLOR,
		   		WIN_BACKGROUND_COLOR,	CMS_CONTROL_COLORS + SCREENCOLOR,  
					WIN_CMS,			phonetoolcms,
                    XV_HEIGHT,          20,
                    WIN_BELOW,  info_helptw,
                    WIN_X,      10,
                    NULL);

        search_help = (Panel_item) xv_create (helppanel2, PANEL_MESSAGE,
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
                        PANEL_LABEL_BOLD,   TRUE,
                        PANEL_LABEL_STRING, "Search Info:",
                        NULL);

		search_helptw = (Textsw) xv_create (helpframe, TEXTSW,
					WIN_CMS,				phonetoolcms,
		   		WIN_FOREGROUND_COLOR,	CMS_CONTROL_COLORS + FILECOLOR,
		   		WIN_BACKGROUND_COLOR,	CMS_CONTROL_COLORS + SCREENCOLOR, 
						WIN_X,      			10,
                        WIN_BELOW,  			helppanel2,
						TEXTSW_READ_ONLY,		TRUE,
            			TEXTSW_DISABLE_LOAD,    TRUE,
    					TEXTSW_BROWSING,		TRUE,
    					WIN_MENU,				nullmenu,
						WIN_ROWS, 				5,
						WIN_COLUMNS,   			60,
						TEXTSW_CONTENTS, "Searches are conducted based on a string, which an exact match is looked for. The search is not case sensitive. If you which to find all entries in your personal list, If using the default format, enter '~' on the 'search for:' line. When editing your personal phone list, while using the default file format, Enter a unique string to search for. The search on the edit panel, only finds the grabs the first match it finds, based on the last name. If you have several same last names in your personal list, you may want to put a unique string in the 'Notes' entry ",
						NULL);

       helppanel3 = (Panel) xv_create (helpframe, PANEL,
		   		WIN_FOREGROUND_COLOR,	CMS_CONTROL_COLORS + FILECOLOR,
		   		WIN_BACKGROUND_COLOR,	CMS_CONTROL_COLORS + SCREENCOLOR,  
					WIN_CMS,			phonetoolcms,
                    XV_HEIGHT,          	20,
                    WIN_BELOW,  			search_helptw,
                    WIN_X,      			5,
                    NULL);
 
        color_help = (Panel_item) xv_create (helppanel3, PANEL_MESSAGE,
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
						PANEL_LABEL_STRING, "Color info:                    ",
                        PANEL_LABEL_BOLD,   TRUE,
                        NULL);

		color_helptw = (Textsw) xv_create (helpframe, TEXTSW,
					WIN_CMS,				phonetoolcms,
		   		WIN_FOREGROUND_COLOR,	CMS_CONTROL_COLORS + FILECOLOR,
		   		WIN_BACKGROUND_COLOR,	CMS_CONTROL_COLORS + SCREENCOLOR, 
                    	WIN_X,      10,
                        WIN_BELOW,  helppanel3,
						TEXTSW_READ_ONLY,	TRUE,
            			TEXTSW_DISABLE_LOAD,    TRUE,
    					TEXTSW_BROWSING,	TRUE,
    					WIN_MENU,		nullmenu,
                        WIN_ROWS, 5,
                        WIN_COLUMNS,   60,
						TEXTSW_CONTENTS, "The colors are changable because you will not always have the same root window, and panel colors in your environment. This feature allows you to set these as you wish. The 'groups' refer to the way certain items are grouped together. This is because these items have a relation to one another. Remember, once you have your colors set to your liking, hit 'Apply' to save them permanently.",
					NULL);

        helppanel4 = (Panel) xv_create (helpframe, PANEL,
		   		WIN_FOREGROUND_COLOR,	CMS_CONTROL_COLORS + FILECOLOR,
		   		WIN_BACKGROUND_COLOR,	CMS_CONTROL_COLORS + SCREENCOLOR,  
					WIN_CMS,			phonetoolcms,
                    XV_HEIGHT,          20,
                    WIN_BELOW,  color_helptw,
                    WIN_X,      10,
                    NULL);

        print_help = (Panel_item) xv_create (helppanel4, PANEL_MESSAGE,
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
                        PANEL_LABEL_BOLD,   TRUE,
						PANEL_LABEL_STRING, "Printer info:                 ",
                        NULL);

		print_helptw = (Textsw) xv_create (helpframe, TEXTSW,
					WIN_CMS,				phonetoolcms,
		   		WIN_FOREGROUND_COLOR,	CMS_CONTROL_COLORS + FILECOLOR,
		   		WIN_BACKGROUND_COLOR,	CMS_CONTROL_COLORS + SCREENCOLOR, 
						WIN_X,      10,
                        WIN_BELOW,  helppanel4,
						TEXTSW_READ_ONLY,	TRUE,
            			TEXTSW_DISABLE_LOAD,    TRUE,
    					TEXTSW_BROWSING,	TRUE,
    					WIN_MENU,		nullmenu,
                        WIN_ROWS, 5,
                        WIN_COLUMNS,   60, 
						TEXTSW_CONTENTS, "Your printcap is read to determine printers available to you. This is done only once in the program, so if your printcap has changed since you started phonetool, quit and restart the program." ,
						NULL);

        helppanel5 = (Panel) xv_create (helpframe, PANEL,
		   		WIN_FOREGROUND_COLOR,	CMS_CONTROL_COLORS + FILECOLOR,
		   		WIN_BACKGROUND_COLOR,	CMS_CONTROL_COLORS + SCREENCOLOR,  
					WIN_CMS,			phonetoolcms,
                    XV_HEIGHT,          20,
                    WIN_BELOW,  print_helptw,
                    WIN_X,      10,
                    NULL);
 
        person_help = (Panel_item) xv_create (helppanel5, PANEL_MESSAGE,
			   PANEL_ITEM_COLOR,			 CMS_CONTROL_COLORS + SUPPORTCOLOR,
                        PANEL_LABEL_BOLD,   TRUE,
						PANEL_LABEL_STRING, "Personal file info:       ",
                        NULL); 

		person_helptw = (Textsw) xv_create (helpframe, TEXTSW,
					WIN_CMS,				phonetoolcms,
		   		WIN_FOREGROUND_COLOR,	CMS_CONTROL_COLORS + FILECOLOR,
		   		WIN_BACKGROUND_COLOR,	CMS_CONTROL_COLORS + SCREENCOLOR, 
						WIN_X,      10,
                        WIN_BELOW,  helppanel5,
						TEXTSW_READ_ONLY,	TRUE,
            			TEXTSW_DISABLE_LOAD,    TRUE,
    					TEXTSW_BROWSING,	TRUE,
    					WIN_MENU,		nullmenu,
                        WIN_ROWS, 5,
                        WIN_COLUMNS,   60,
						TEXTSW_CONTENTS, "Your personal phone file may be one of two types: personal or default. The personal type is used if you wish to use an existing phone file, (i.e. one you used to perform greps on). If you choose this type from the properites panel, you must tell phonetool where to find your file. All edits and additions performed to your file will be handled via a text editor window. If you do not have a preivous file, then you can use the default type.  This will allow to uses the edit and add panels to amend your phone file.  ",
						NULL);

        	helppanel6 = (Panel) xv_create (helpframe, PANEL,
                    XV_HEIGHT,          	60,
                    WIN_BELOW,  person_helptw,
                    WIN_X,      10,
                    NULL);


      window_fit(helpframe);

}
