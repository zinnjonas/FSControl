/*
 * =====================================================================================
 *
 *       Filename:  plugin.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22.10.2013 05:04:12
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

void send_message(char* from, char* msg)
{
	(*send_msg)(from, msg);
}

cmdEntry init(p_send_msg s_message)
{
	printf("load of plugin: %s \n", plugin_name);
	send_msg = s_message;
	return plugin_init();
}

