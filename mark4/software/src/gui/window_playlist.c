/*
Copyright 2022, dettus@dettus.net

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this 
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "controller.h"
#include "gui_helpers.h"
#include "window_playlist.h"
#include "theme_manager.h"
#include "datastructures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MIN_PLAYLIST_ROWS	2	// each row has a height of 29 pixels. titlebar has 20, bottom 38. 30+38+2*9=116 pixel (size of the other windows)
#define	MIN_PLAYLIST_COLS	11	// each column has a width of 25 pixel. 11*25=275 pixel. (width of the other windows)

#define	COL_WIDTH 		ELEMENT_WIDTH(PLEDIT_TOP_FILLERS_ACTIVE)
#define	COL_MARGIN_LEFT 	ELEMENT_WIDTH(PLEDIT_LEFT_SIDE_FILLERS)
#define	COL_MARGIN_RIGHT 	(ELEMENT_WIDTH(PLEDIT_RIGHT_SIDE_FILLERS_LEFT_BAR)+ELEMENT_WIDTH(PLEDIT_RIGHT_SIDE_FILLERS_SCROLL_GROOVE)+ELEMENT_WIDTH(PLEDIT_RIGHT_SIDE_FILLERS_RIGHT_BAR))
#define	ROW_HEIGHT 		ELEMENT_HEIGHT(PLEDIT_LEFT_SIDE_FILLERS)
#define	ROW_MARGIN_TOP 		ELEMENT_HEIGHT(PLEDIT_PLAYLIST_TITLEBAR_ACTIVE)
#define ROW_MARGIN_BOTTOM 	ELEMENT_HEIGHT(PLEDIT_BOTTOM_LEFT_CONTROL_BAR)



// function headers for the gtk events. the implementation is at the end of this file
static void window_playlist_event_pressed(GtkGestureClick *gesture, int n_press, double x, double y, GtkWidget *window);
static void window_playlist_event_released(GtkGestureClick *gesture, int n_press, double x, double y, GtkWidget *window);
static void window_playlist_event_drag_begin(GtkGestureDrag *gesture, double x, double y, GtkWidget *window);
static void window_playlist_event_drag_update(GtkGestureDrag *gesture, double x, double y, GtkWidget *window);
static void window_playlist_event_drag_end(GtkGestureDrag *gesture, double x, double y, GtkWidget *window);

	

int window_playlist_resize(tHandleWindowPlaylist* pThis,int rows,int columns)
{
	int retval;
	int winheight;
	int winwidth;

	int rightmargin;
	GdkPixbuf *newPixbufBackground;
	GdkPixbuf *newPixbuf;
	GtkWidget *newPicture;
	
	GdkPixbuf *ptr1;
	GdkPixbuf *ptr2;
//	GtkWidget *ptr3;

	retval=RETVAL_OK;

	if (rows<MIN_PLAYLIST_ROWS)
	{
		rows=MIN_PLAYLIST_ROWS;
	}
	if (columns<MIN_PLAYLIST_COLS)
	{
		columns=MIN_PLAYLIST_COLS;
	}
	pThis->rows=rows;
	pThis->columns=columns;

	pThis->window_height=winheight=ELEMENT_HEIGHT(PLEDIT_UPPER_LEFT_CORNERPIECE_ACTIVE)+rows*ELEMENT_HEIGHT(PLEDIT_LEFT_SIDE_FILLERS)+ELEMENT_HEIGHT(PLEDIT_BOTTOM_LEFT_CONTROL_BAR);
	pThis->window_width=winwidth=columns*ELEMENT_WIDTH(PLEDIT_TOP_FILLERS_ACTIVE);

	newPixbufBackground=gdk_pixbuf_new(GDK_COLORSPACE_RGB,TRUE,8,winwidth,winheight);
	newPixbuf=gdk_pixbuf_new(GDK_COLORSPACE_RGB,TRUE,8,winwidth,winheight);
	newPicture=gtk_picture_new_for_pixbuf(newPixbuf);

//	ptr3=pThis->picture;
	pThis->picture=newPicture;
	gtk_window_set_child(GTK_WINDOW(pThis->window),pThis->picture);
	gtk_window_set_default_size(GTK_WINDOW(pThis->window),winwidth,winheight);


	ptr2=pThis->pixbuf;
	pThis->pixbuf=newPixbuf;
	ptr1=pThis->pixbufBackground;
	pThis->pixbufBackground=newPixbufBackground;

	// at this point, the new references have been set.
	// the old ones are still "dangling".
//	if (ptr3!=NULL)	// actually, the picture may have been unreferenced due to the set_child function
//	{
//		g_object_unref(ptr3);
//	}
	if (ptr2!=NULL)
	{
		g_object_unref(ptr2);
	}
	if (ptr1!=NULL)
	{
		g_object_unref(ptr1);
	}
	// not anymore. all cleaned up!


	// since the window has been resized, the pressables might have moved
	gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[16],ePRESSED_WINDOW_PLAYLIST_ADD,		PLEDIT_ADD_BUTTON);
	gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[17],ePRESSED_WINDOW_PLAYLIST_REMOVE,		PLEDIT_REMOVE_BUTTON);
	gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[18],ePRESSED_WINDOW_PLAYLIST_SELECTION,		PLEDIT_SELECTION_BUTTON);
	gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[19],ePRESSED_WINDOW_PLAYLIST_MISCELLANEOUS,	PLEDIT_MISCELLANEOUS_BUTTON);
	gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[20],ePRESSED_WINDOW_PLAYLIST_LIST,		PLEDIT_LIST_BUTTON);
	gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[21],ePRESSED_WINDOW_PLAYLIST_RESIZE,		PLEDIT_RESIZE_CONTROL);

	gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[22],ePRESSED_WINDOW_PLAYLIST_PREVIOUS,		PLEDIT_PREVIOUS_CONTROL);
	gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[23],ePRESSED_WINDOW_PLAYLIST_PLAY,		PLEDIT_PLAY_CONTROL);
	gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[24],ePRESSED_WINDOW_PLAYLIST_PAUSE,		PLEDIT_PAUSE_CONTROL);
	gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[25],ePRESSED_WINDOW_PLAYLIST_STOP,		PLEDIT_STOP_CONTROL);
	gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[26],ePRESSED_WINDOW_PLAYLIST_NEXT,		PLEDIT_NEXT_CONTROL);
	gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[27],ePRESSED_WINDOW_PLAYLIST_OPEN,		PLEDIT_OPEN_CONTROL);

	gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[28],ePRESSED_WINDOW_PLAYLIST_PAGEUP,		PLEDIT_PAGE_UP_BUTTON);
	gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[29],ePRESSED_WINDOW_PLAYLIST_PAGEDOWN,		PLEDIT_PAGE_DOWN_BUTTON);


	rightmargin=ELEMENT_WIDTH(PLEDIT_RIGHT_SIDE_FILLERS_LEFT_BAR)-ELEMENT_WIDTH(PLEDIT_RIGHT_SIDE_FILLERS_SCROLL_GROOVE)-ELEMENT_WIDTH(PLEDIT_RIGHT_SIDE_FILLERS_RIGHT_BAR);
	pThis->list_posx=ELEMENT_WIDTH(PLEDIT_RIGHT_SIDE_FILLERS_LEFT_BAR);
	pThis->list_posy=ELEMENT_HEIGHT(PLEDIT_TOP_FILLERS_ACTIVE);
	pThis->list_dimx=pThis->window_width-pThis->list_posx-rightmargin;
	pThis->list_dimy=pThis->window_height-ELEMENT_HEIGHT(PLEDIT_PLAYLIST_TITLEBAR_ACTIVE)-ELEMENT_HEIGHT(PLEDIT_BOTTOM_FILLERS);
	
	
	gui_helpers_define_pressable_by_dimensions(&pThis->boundingBoxes[30],ePRESSED_WINDOW_PLAYLIST_SCROLLBAR,pThis->window_width-rightmargin,pThis->list_posy,rightmargin,pThis->list_dimy);
	gui_helpers_define_pressable_by_dimensions(&pThis->boundingBoxes[31],ePRESSED_WINDOW_PLAYLIST_MAIN,pThis->list_posx,pThis->list_posy,pThis->list_dimx,pThis->list_dimy);


	return retval;
}

int window_playlist_init(tHandleWindowPlaylist* pThis,void* pControllerContext,tHandleThemeManager *pHandleThemeManager,GtkApplication* app)
{
	int retval;
	retval=RETVAL_OK;
		
	memset(pThis,0,sizeof(tHandleWindowPlaylist));
	pThis->app=app;
	pThis->pControllerContext=pControllerContext;
	pThis->pHandleThemeManager=pHandleThemeManager;
	pThis->window=gtk_application_window_new(pThis->app);
	gtk_window_set_title(GTK_WINDOW(pThis->window),"d11amp playlist");

	pThis->pixbuf=NULL;
	pThis->picture=NULL;
	retval|=window_playlist_resize(pThis,MIN_PLAYLIST_ROWS,MIN_PLAYLIST_COLS);

	pThis->lastPressed=ePRESSED_NONE;
	pThis->gesture_click=gtk_gesture_click_new();
	g_object_set_data(G_OBJECT(pThis->gesture_click),"pThis",pThis);	// add a pointer to the handle to the widget. this way it is available in the gesture callbacks
	g_signal_connect(pThis->gesture_click,"pressed", G_CALLBACK(window_playlist_event_pressed) ,(pThis->window));
	g_signal_connect(pThis->gesture_click,"released",G_CALLBACK(window_playlist_event_released),(pThis->window));
	gtk_widget_add_controller(pThis->window,GTK_EVENT_CONTROLLER(pThis->gesture_click));

	pThis->gesture_drag=gtk_gesture_drag_new();
	g_object_set_data(G_OBJECT(pThis->gesture_drag),"pThis",pThis);	// add a pointer to the handle to the widget. this way it is available in the gesture callbacks
	g_signal_connect (pThis->gesture_drag,"drag-begin", G_CALLBACK (window_playlist_event_drag_begin), (pThis->window));
	g_signal_connect (pThis->gesture_drag,"drag-update",G_CALLBACK (window_playlist_event_drag_update),(pThis->window));
	g_signal_connect (pThis->gesture_drag,"drag-end",   G_CALLBACK (window_playlist_event_drag_end),   (pThis->window));

	gtk_widget_add_controller(pThis->window,GTK_EVENT_CONTROLLER(pThis->gesture_drag));

	return retval;
}

// background: the default picture
int window_playlist_refresh_background(tHandleWindowPlaylist* pThis)
{
	int i;
	int retval;
	int winwidth;
	int winheight;
	int x;
	int y;

	winheight=ROW_MARGIN_TOP+pThis->rows*ROW_HEIGHT+ROW_MARGIN_BOTTOM;
	winwidth=pThis->columns*COL_WIDTH;

	


	retval=RETVAL_OK;

	// first: draw the top frame         ------------------------
	x=0;
	retval|=theme_manager_draw_element_at(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_UPPER_LEFT_CORNERPIECE_ACTIVE,0,0);x+=ELEMENT_WIDTH(PLEDIT_UPPER_LEFT_CORNERPIECE_ACTIVE);
	while (x<pThis->window_width-ELEMENT_WIDTH(PLEDIT_UPPER_RIGHT_CORNERPIECE_ACTIVE))
	{
		retval|=theme_manager_draw_element_at(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_TOP_FILLERS_ACTIVE,x,0);x+=ELEMENT_WIDTH(PLEDIT_TOP_FILLERS_ACTIVE);
	}
	retval|=theme_manager_draw_element_at(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_UPPER_RIGHT_CORNERPIECE_ACTIVE,x,0);
	// then: add the title in the center ---------[title]--------
	retval|=theme_manager_draw_element_at(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_PLAYLIST_TITLEBAR_ACTIVE,winwidth/2-ELEMENT_WIDTH(PLEDIT_PLAYLIST_TITLEBAR_ACTIVE)/2,0);

	// add the borders on the left and on the right side |              |||	
	y=ROW_MARGIN_TOP;
	for (i=0;i<pThis->rows;i++)
	{
		retval|=theme_manager_draw_element_at(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_LEFT_SIDE_FILLERS,0,y);
	
		x=winwidth-COL_MARGIN_RIGHT;	
		retval|=theme_manager_draw_element_at(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_RIGHT_SIDE_FILLERS_LEFT_BAR,x,y);x+=ELEMENT_WIDTH(PLEDIT_RIGHT_SIDE_FILLERS_LEFT_BAR);
		retval|=theme_manager_draw_element_at(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_RIGHT_SIDE_FILLERS_SCROLL_GROOVE,x,y);x+=ELEMENT_WIDTH(PLEDIT_RIGHT_SIDE_FILLERS_SCROLL_GROOVE);
		retval|=theme_manager_draw_element_at(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_RIGHT_SIDE_FILLERS_RIGHT_BAR,x,y);x+=ELEMENT_WIDTH(PLEDIT_RIGHT_SIDE_FILLERS_RIGHT_BAR);
		y+=ROW_HEIGHT;
	}	
	// add the bottom menu
	x=0;
	y=winheight-ROW_MARGIN_BOTTOM;
	retval|=theme_manager_draw_element_at(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_BOTTOM_LEFT_CONTROL_BAR,x,y);x+=ELEMENT_WIDTH(PLEDIT_BOTTOM_LEFT_CONTROL_BAR);
	while (x<(winwidth-ELEMENT_WIDTH(PLEDIT_BOTTOM_RIGHT_CONTROL_BAR)))	// when the window is at its minimum width, the bottom left controlbar + bottom right controlbar are as wide as the window. otherwise, it might need some filling
	{
		retval|=theme_manager_draw_element_at(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_BOTTOM_FILLERS,x,y);x+=ELEMENT_WIDTH(PLEDIT_BOTTOM_FILLERS);
	}
	retval|=theme_manager_draw_element_at(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_BOTTOM_RIGHT_CONTROL_BAR,x,y);

	theme_manager_draw_element(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_PREVIOUS_CONTROL);
	theme_manager_draw_element(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_PLAY_CONTROL);
	theme_manager_draw_element(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_PAUSE_CONTROL);
	theme_manager_draw_element(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_STOP_CONTROL);
	theme_manager_draw_element(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_NEXT_CONTROL);
	theme_manager_draw_element(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_OPEN_CONTROL);

	theme_manager_draw_element(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_PAGE_UP_BUTTON);
	theme_manager_draw_element(pThis->pHandleThemeManager,pThis->pixbufBackground,PLEDIT_PAGE_DOWN_BUTTON);


	
	return retval;
}
int window_playlist_draw_status(tHandleWindowPlaylist *pThis,GdkPixbuf *destBuf)
{
	int retval;

	retval=RETVAL_OK;
	if (pThis->status.menu_add)
	{
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_DECORATION_BAR_ADD);
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_ADD_FILE_BUTTON_UNPRESSED);
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_ADD_DIR_BUTTON_UNPRESSED);
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_ADD_URL_BUTTON_UNPRESSED);
		retval|=gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[ 0],ePRESSED_WINDOW_PLAYLIST_ADD_FILE,PLEDIT_ADD_FILE_BUTTON_UNPRESSED);
		retval|=gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[ 1],ePRESSED_WINDOW_PLAYLIST_ADD_DIR,PLEDIT_ADD_DIR_BUTTON_UNPRESSED);
		retval|=gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[ 2],ePRESSED_WINDOW_PLAYLIST_ADD_URL,PLEDIT_ADD_URL_BUTTON_UNPRESSED);
	} else {
		retval|=gui_helpers_undefine_pressable(&pThis->boundingBoxes[ 0],ePRESSED_WINDOW_PLAYLIST_ADD_FILE);
		retval|=gui_helpers_undefine_pressable(&pThis->boundingBoxes[ 1],ePRESSED_WINDOW_PLAYLIST_ADD_DIR);
		retval|=gui_helpers_undefine_pressable(&pThis->boundingBoxes[ 2],ePRESSED_WINDOW_PLAYLIST_ADD_URL);
	}
	if (pThis->status.menu_remove)
	{
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_DECORATION_BAR_REMOVE);
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_MISC_REMOVE_BUTTON_UNPRESSED);
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_CROP_BUTTON_UNPRESSED);
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_REMOVE_FILE_BUTTON_UNPRESSED);
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_REMOVE_ALL_BUTTON_UNPRESSED);

		retval|=gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[ 3],ePRESSED_WINDOW_PLAYLIST_MISC_REMOVE_BUTTON,PLEDIT_MISC_REMOVE_BUTTON_UNPRESSED);
		retval|=gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[ 4],ePRESSED_WINDOW_PLAYLIST_CROP_BUTTON,PLEDIT_CROP_BUTTON_UNPRESSED);
		retval|=gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[ 5],ePRESSED_WINDOW_PLAYLIST_REMOVE_FILE,PLEDIT_REMOVE_FILE_BUTTON_UNPRESSED);
		retval|=gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[ 6],ePRESSED_WINDOW_PLAYLIST_REMOVE_ALL,PLEDIT_REMOVE_ALL_BUTTON_UNPRESSED);
	} else {
		retval|=gui_helpers_undefine_pressable(&pThis->boundingBoxes[ 3],ePRESSED_WINDOW_PLAYLIST_MISC_REMOVE_BUTTON);
		retval|=gui_helpers_undefine_pressable(&pThis->boundingBoxes[ 4],ePRESSED_WINDOW_PLAYLIST_CROP_BUTTON);
		retval|=gui_helpers_undefine_pressable(&pThis->boundingBoxes[ 5],ePRESSED_WINDOW_PLAYLIST_REMOVE_FILE);
		retval|=gui_helpers_undefine_pressable(&pThis->boundingBoxes[ 6],ePRESSED_WINDOW_PLAYLIST_REMOVE_ALL);
	}
	if (pThis->status.menu_select)
	{
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_DECORATION_BAR_SELECTION);
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_INVERT_SELECTION_BUTTON_UNPRESSED);
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_SELECT_NONE_BUTTON_UNPRESSED);
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_SELECT_ALL_BUTTON_UNPRESSED);

		retval|=gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[ 7],ePRESSED_WINDOW_PLAYLIST_INVERT_SELECTION,PLEDIT_INVERT_SELECTION_BUTTON_UNPRESSED);
		retval|=gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[ 8],ePRESSED_WINDOW_PLAYLIST_SELECT_NONE,PLEDIT_SELECT_NONE_BUTTON_UNPRESSED);
		retval|=gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[ 9],ePRESSED_WINDOW_PLAYLIST_SELECT_ALL,PLEDIT_SELECT_ALL_BUTTON_UNPRESSED);
	} else {
		retval|=gui_helpers_undefine_pressable(&pThis->boundingBoxes[ 7],ePRESSED_WINDOW_PLAYLIST_INVERT_SELECTION);
		retval|=gui_helpers_undefine_pressable(&pThis->boundingBoxes[ 8],ePRESSED_WINDOW_PLAYLIST_SELECT_NONE);
		retval|=gui_helpers_undefine_pressable(&pThis->boundingBoxes[ 9],ePRESSED_WINDOW_PLAYLIST_SELECT_ALL);
	}
	if (pThis->status.menu_misc)
	{
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_DECORATION_BAR_MISC);
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_SORT_LIST_BUTTON_UNPRESSED);
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_FILE_INFO_BUTTON_UNPRESSED);
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_MISC_OPTIONS_BUTTON_UNPRESSED);
		retval|=gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[10],ePRESSED_WINDOW_PLAYLIST_SORT_LIST,PLEDIT_SORT_LIST_BUTTON_UNPRESSED);
		retval|=gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[11],ePRESSED_WINDOW_PLAYLIST_FILE_INFO,PLEDIT_FILE_INFO_BUTTON_UNPRESSED);
		retval|=gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[12],ePRESSED_WINDOW_PLAYLIST_MISC_OPTIONS,PLEDIT_MISC_OPTIONS_BUTTON_UNPRESSED);
	} else {
		retval|=gui_helpers_undefine_pressable(&pThis->boundingBoxes[10],ePRESSED_WINDOW_PLAYLIST_SORT_LIST);
		retval|=gui_helpers_undefine_pressable(&pThis->boundingBoxes[11],ePRESSED_WINDOW_PLAYLIST_FILE_INFO);
		retval|=gui_helpers_undefine_pressable(&pThis->boundingBoxes[12],ePRESSED_WINDOW_PLAYLIST_MISC_OPTIONS);
	}
	if (pThis->status.menu_list)
	{
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_DECORATION_BAR_LIST);
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_NEW_LIST_BUTTON_UNPRESSED);
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_SAVE_LIST_BUTTON_UNPRESSED);
		retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,PLEDIT_LOAD_LIST_BUTTON_UNPRESSED);
		retval|=gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[13],ePRESSED_WINDOW_PLAYLIST_NEW_LIST,PLEDIT_NEW_LIST_BUTTON_UNPRESSED);
		retval|=gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[14],ePRESSED_WINDOW_PLAYLIST_SAVE_LIST,PLEDIT_SAVE_LIST_BUTTON_UNPRESSED);
		retval|=gui_helpers_define_pressable_by_element(pThis->window_width,pThis->window_height,&pThis->boundingBoxes[15],ePRESSED_WINDOW_PLAYLIST_LOAD_LIST,PLEDIT_LOAD_LIST_BUTTON_UNPRESSED);
	} else {
		retval|=gui_helpers_undefine_pressable(&pThis->boundingBoxes[13],ePRESSED_WINDOW_PLAYLIST_NEW_LIST);
		retval|=gui_helpers_undefine_pressable(&pThis->boundingBoxes[14],ePRESSED_WINDOW_PLAYLIST_SAVE_LIST);
		retval|=gui_helpers_undefine_pressable(&pThis->boundingBoxes[15],ePRESSED_WINDOW_PLAYLIST_LOAD_LIST);
	}

	return retval;
}
int window_playlist_draw_pressable(tHandleWindowPlaylist *pThis,GdkPixbuf *destBuf)
{
	#define	CASEBLOCK(pressableid,elementid)	\
		case (pressableid):	\
			retval|=theme_manager_draw_element(pThis->pHandleThemeManager,destBuf,(elementid));	\
			break;		


	int retval;

	retval=RETVAL_OK;
	switch (pThis->lastPressed)
	{
		CASEBLOCK(ePRESSED_WINDOW_PLAYLIST_ADD_FILE,PLEDIT_ADD_FILE_BUTTON_PRESSED);
		CASEBLOCK(ePRESSED_WINDOW_PLAYLIST_ADD_DIR,PLEDIT_ADD_DIR_BUTTON_PRESSED);
		CASEBLOCK(ePRESSED_WINDOW_PLAYLIST_ADD_URL,PLEDIT_ADD_URL_BUTTON_PRESSED);
		CASEBLOCK(ePRESSED_WINDOW_PLAYLIST_MISC_REMOVE_BUTTON,PLEDIT_MISC_REMOVE_BUTTON_PRESSED);
		CASEBLOCK(ePRESSED_WINDOW_PLAYLIST_CROP_BUTTON,PLEDIT_CROP_BUTTON_PRESSED);
		CASEBLOCK(ePRESSED_WINDOW_PLAYLIST_REMOVE_FILE,PLEDIT_REMOVE_FILE_BUTTON_PRESSED);
		CASEBLOCK(ePRESSED_WINDOW_PLAYLIST_REMOVE_ALL,PLEDIT_REMOVE_ALL_BUTTON_PRESSED);
		CASEBLOCK(ePRESSED_WINDOW_PLAYLIST_INVERT_SELECTION,PLEDIT_INVERT_SELECTION_BUTTON_PRESSED);
		CASEBLOCK(ePRESSED_WINDOW_PLAYLIST_SELECT_NONE,PLEDIT_SELECT_NONE_BUTTON_PRESSED);
		CASEBLOCK(ePRESSED_WINDOW_PLAYLIST_SELECT_ALL,PLEDIT_SELECT_ALL_BUTTON_PRESSED);
		CASEBLOCK(ePRESSED_WINDOW_PLAYLIST_SORT_LIST,PLEDIT_SORT_LIST_BUTTON_PRESSED);
		CASEBLOCK(ePRESSED_WINDOW_PLAYLIST_FILE_INFO,PLEDIT_FILE_INFO_BUTTON_PRESSED);
		CASEBLOCK(ePRESSED_WINDOW_PLAYLIST_MISC_OPTIONS,PLEDIT_MISC_OPTIONS_BUTTON_PRESSED);
		CASEBLOCK(ePRESSED_WINDOW_PLAYLIST_NEW_LIST,PLEDIT_NEW_LIST_BUTTON_PRESSED);
		CASEBLOCK(ePRESSED_WINDOW_PLAYLIST_SAVE_LIST,PLEDIT_SAVE_LIST_BUTTON_PRESSED);
		CASEBLOCK(ePRESSED_WINDOW_PLAYLIST_LOAD_LIST,PLEDIT_LOAD_LIST_BUTTON_PRESSED);
		default:
			break;
	}

	return retval;
}

int window_playlist_draw(tHandleWindowPlaylist *pThis,GdkPixbuf *destBuf)
{
	int retval;
	retval=RETVAL_OK;
	gdk_pixbuf_copy_area(pThis->pixbufBackground,0,0,pThis->window_width,pThis->window_height,destBuf,0,0);
	retval|=window_playlist_draw_status(pThis,destBuf);
	retval|=window_playlist_draw_pressable(pThis,destBuf);

	return retval;
}


int window_playlist_refresh(tHandleWindowPlaylist* pThis)
{
	int retval;
	retval=RETVAL_OK;
	retval|=window_playlist_draw(pThis,pThis->pixbuf);
        gtk_picture_set_pixbuf(GTK_PICTURE(pThis->picture),pThis->pixbuf);
	gtk_widget_queue_draw(pThis->window);

	return retval;	
}
int window_playlist_signal_new_theme(tHandleWindowPlaylist* pThis)
{
	int retval;

	retval=RETVAL_OK;
	retval|=window_playlist_refresh_background(pThis);
	retval|=window_playlist_refresh(pThis);

	return retval;
}
int window_playlist_show(tHandleWindowPlaylist* pThis)
{
	gtk_widget_show(pThis->window);
	return RETVAL_OK;
}
int window_playlist_hide(tHandleWindowPlaylist* pThis)
{
	gtk_widget_hide(pThis->window);
	return RETVAL_OK;
}






/// event handler implementation
static void window_playlist_event_pressed(GtkGestureClick *gesture, int n_press, double x, double y, GtkWidget *window)
{
	ePressable pressed;
	tHandleWindowPlaylist* pThis=(tHandleWindowPlaylist*)g_object_get_data(G_OBJECT(gesture),"pThis");
	pressed=gui_helpers_find_pressable(pThis->boundingBoxes,PRESSABLE_PLAYLIST_NUM,x,y,window,pThis->window_width,pThis->window_height);
	pThis->lastPressed=pressed;
	pThis->pressedX=x;
	pThis->pressedY=y;
	pThis->resizeCols=pThis->columns;
	pThis->resizeRows=pThis->rows;
	pThis->resizeWidth=gtk_widget_get_width(window);
	pThis->resizeHeight=gtk_widget_get_height(window);
	window_playlist_refresh(pThis);
}
static void window_playlist_event_released(GtkGestureClick *gesture, int n_press, double x, double y, GtkWidget *window)
{
	ePressable released;
	tHandleWindowPlaylist* pThis=(tHandleWindowPlaylist*)g_object_get_data(G_OBJECT(gesture),"pThis");
	released=gui_helpers_find_pressable(pThis->boundingBoxes,PRESSABLE_PLAYLIST_NUM,x,y,window,pThis->window_width,pThis->window_height);

	if (released==pThis->lastPressed && released!=ePRESSED_NONE)
	{
		switch(released)
		{
			case ePRESSED_WINDOW_PLAYLIST_ADD:
				pThis->status.menu_add=1-pThis->status.menu_add;
			break;
			case ePRESSED_WINDOW_PLAYLIST_REMOVE:
				pThis->status.menu_remove=1-pThis->status.menu_remove;
			break;
			case ePRESSED_WINDOW_PLAYLIST_SELECTION:
				pThis->status.menu_select=1-pThis->status.menu_select;
			break;
			case ePRESSED_WINDOW_PLAYLIST_MISCELLANEOUS:
				pThis->status.menu_misc=1-pThis->status.menu_misc;
			break;
			case ePRESSED_WINDOW_PLAYLIST_LIST:
				pThis->status.menu_list=1-pThis->status.menu_list;
			break;

			case ePRESSED_WINDOW_PLAYLIST_PLAY:
				controller_event(pThis->pControllerContext,eEVENT_PLAY,NULL);
				break;
			case ePRESSED_WINDOW_PLAYLIST_PAUSE:
				controller_event(pThis->pControllerContext,eEVENT_PAUSE,NULL);
				break;
			case ePRESSED_WINDOW_PLAYLIST_STOP:
				controller_event(pThis->pControllerContext,eEVENT_STOP,NULL);
				break;
			default:
			break;
		}
	}


	pThis->lastPressed=ePRESSED_NONE;
	window_playlist_refresh(pThis);
}
static void window_playlist_event_drag_begin(GtkGestureDrag *gesture, double x, double y, GtkWidget *window)
{
	tHandleWindowPlaylist* pThis=(tHandleWindowPlaylist*)g_object_get_data(G_OBJECT(gesture),"pThis");
}
static void window_playlist_event_drag_end(GtkGestureDrag *gesture, double x, double y, GtkWidget *window)
{
	tHandleWindowPlaylist* pThis=(tHandleWindowPlaylist*)g_object_get_data(G_OBJECT(gesture),"pThis");
	if (pThis->lastPressed==ePRESSED_WINDOW_PLAYLIST_RESIZE)
	{
		double width;
		double height;
		double scaleX;
		double scaleY;
		int newcols,newrows;


		width=gtk_widget_get_width(window);
		height=gtk_widget_get_height(window);
		scaleX=width/pThis->window_width;
		scaleY=height/pThis->window_height;

		

		newrows=(int)(y/(PLAYLIST_ROW_HEIGHT*scaleY))+pThis->resizeRows;
		newcols=(int)(x/(PLAYLIST_COL_WIDTH*scaleX))+pThis->resizeCols;;

		if (newrows!=pThis->rows || newcols!=pThis->columns)
		{
			window_playlist_resize(pThis,newrows,newcols);
		}
		window_playlist_refresh_background(pThis);
		window_playlist_refresh(pThis);
		gtk_window_set_title(GTK_WINDOW(pThis->window),"d11amp playlist");
	}
}

static void window_playlist_event_drag_update(GtkGestureDrag *gesture, double x, double y, GtkWidget *window)
{
	tHandleWindowPlaylist* pThis=(tHandleWindowPlaylist*)g_object_get_data(G_OBJECT(gesture),"pThis");
	if (pThis->lastPressed==ePRESSED_WINDOW_PLAYLIST_RESIZE)
	{
		int width;
		int height;
		char title[64];
		width=pThis->resizeWidth+x;
		height=pThis->resizeHeight+y;
		if (width<275)
		{
			width=275;
		} 
		if (height<116)
		{
			height=116;
		}
// FIXME: THIS CRASHES THE APPLICATION
//		gtk_window_set_default_size(GTK_WINDOW(pThis->window),width,height);
		snprintf(title,64,"%dx%d",width,height);
		gtk_window_set_title(GTK_WINDOW(pThis->window),title);
	}	
}

