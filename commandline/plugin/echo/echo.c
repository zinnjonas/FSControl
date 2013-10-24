/*
 * =====================================================================================
 *
 *       Filename:  echo.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22.10.2013 04:23:32
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
#include "plugin.h"

char* plugin_name = "echo";

/* function to call if echo is commanded */
void echoProc( int arg, char** argv, char* from)
{
	if( arg <= 0)
	{
		send_msg(from, "Wrong number of Arguments");		
	}
	else
	{
		char temp[1024];
		int i = 0;
		for ( ; i < arg; i++)
		{
			if( i == 0)
				sprintf(temp, "%s", argv[i]);
			else if( i > 0)
				sprintf(temp, "%s %s", temp, argv[i]);
		}
		send_message(from, temp);
	}
}

cmdEntry plugin_init()
{
	list_t list = create_parameter_list();
	parameter_append(list, "<String>", "the <String> to bee echoed");
	return create_command_ex("echo", echoProc, true, "echo a given String", list);
}

