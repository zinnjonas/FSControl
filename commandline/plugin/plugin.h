/*
 * =====================================================================================
 *
 *       Filename:  plugin.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  22.10.2013 04:55:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jonas Zinn (jsz), jonas.zinn@uni-konstanz.de
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef PLUGIN_H_
#define PLUGIN_H_

#undef MAIN_PROC

#include <stdbool.h>

#include "cmds.h"
#include <list.h>

typedef void (*p_send_msg)(char*,char*);

p_send_msg  send_msg;
p_send_msg send_file;

void send_message(char* from, char* msg);

typedef struct cmd_entry* cmdEntry;

extern cmdEntry plugin_init();
extern char* plugin_name;

cmdEntry init(p_send_msg s_message);

#endif

