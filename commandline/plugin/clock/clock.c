/*
 * =====================================================================================
 *
 *       Filename:  clock.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  23.10.2013 01:44:33
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
//#include <stdbool.h>
#include "plugin.h"

char* plugin_name = "clock";

/* function to call if echo is commanded */
void clockProc( int arg, char** argv, char* from)
{
	if( arg > 0)
	{
		send_message(from, "Wrong number of Arguments");
	}
	else
	{
		FILE* fp = popen("date", "r");
		char* temp = NULL;
		size_t len = 0;

		while( getline( &temp, &len, fp) != -1)
			send_message(from, temp);
		free(temp);
		pclose(fp);
	}
}

cmdEntry plugin_init()
{
	return create_command_ex("clock", clockProc, true, "gives the current time", NULL);
}

