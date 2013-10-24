/*
 * =====================================================================================
 *
 *       Filename:  ledPlug.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22.10.2013 12:04:12
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
#include "led.h"
#include "plugin.h"

char* plugin_name = "led";

/* function to call if echo is commanded */
void ledProc( int argc, char** argv, char* from)
{

	if( argc <= 0)
	{
		send_msg(from, "Wrong number of Arguments");
	}
	else
	{
		char temp[1024];
		sprintf(temp, "LED: ");
		int counter_arg = argc;
		while (counter_arg > 0)
		{		
			if( !strcmp(argv[0], "on"))
			{
				set_led_on();
				sprintf(temp, "%son ", temp);
			}
			else if( !strcmp(argv[0], "off"))
			{
				set_led_off();
				sprintf(temp, "%soff ", temp);
			}
			else if( !strcmp(argv[0], "rgb"))
			{
				if( counter_arg-1 > 0)
				{
					unsigned int color = convertHexString(argv[1]);
					int r = ((color >> 16) & 0xFF);
					int g = ((color >> 8) & 0xFF) ;
					int b = (color & 0xFF);
					set_led_color(r,g,b);
					sprintf(temp, "%s(%d,%d,%d) ", temp, r,g,b);
					++argv;
					--counter_arg;
				}
				else
				{
					send_message(from, "Flasche anzahl parameter");
				}
			}
			else if( !strcmp(argv[0], "status"))
			{

				int r, g,b;
				sprintf(temp, "status: %s (%d,%d,%d) ", (get_led_status(&r,&g,&b) == true ? "on": "off"), r, g, b);
			}
			
			++argv;
			--counter_arg;
		}
		send_message( from, temp);
	}
}

cmdEntry plugin_init()
{
	list_t list = create_parameter_list();
	parameter_append(list, "[ON | OFF]", "switch the light on or off");
	parameter_append(list, "rgb <HEX>", "set the lights color");
	init_led_controler();
	return create_command_ex("led", ledProc, true, "controls the light", list);
}

