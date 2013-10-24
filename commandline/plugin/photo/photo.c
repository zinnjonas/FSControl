/*
 * =====================================================================================
 *
 *       Filename:  photo.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  23.10.2013 02:35:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jonas Zinn (jsz), jonas.zinn@uni-konstanz.de
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/highgui/highgui_c.h>
#include "plugin.h"

char* plugin_name="camera";

CvCapture* capture = NULL;

void init_camera()
{
	if( capture == NULL)
	{
		capture = cvCreateCameraCapture(0);
		if( capture == NULL)
			printf("ERROR ERROR\n");
	}
}

void make_photo(char* from)
{
	if( capture == NULL)
  {
		send_message( from, "can not make picture no capture!");
		if( capture == NULL)
			return;
	}

	IplImage* frame = cvQueryFrame(capture);
	if(!frame)
	{
		send_message(from, "can note take picture from frame!");
		return;
	}
	cvSaveImage("test.png", frame, 0);
	send_message(from, "photo gespeichert!");
	(*send_file)(from, "test.png");
}

void release_camera()
{
	if(NULL != capture)
	{
		cvReleaseCapture(&capture);
		capture = NULL;
	}
}

void photoProc( int argc, char** argv, char* from)
{
	make_photo(from);
}

cmdEntry plugin_init()
{
	init_camera();
	return create_command_ex("photo", photoProc, true, "takes a photo", NULL);
}

void plugin_release()
{
	release_camera();
}

void register_send_file(p_send_msg s_file)
{
	send_file = s_file;
}

