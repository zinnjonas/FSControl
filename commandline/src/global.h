/*
 * =====================================================================================
 *
 *       Filename:  global.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22.10.2013 02:55:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jonas Zinn (jsz), jonas.zinn@uni-konstanz.de
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "list.h"
#include "cmds.h"

typedef struct command_t* command;
typedef struct redirect_t* redirect;

void use_normal_sdout();

redirect splittRedirection( char* command);
FILE* openRedirection(redirect red);

list_t splittCommands(char* cmd);

int do_command(cmdEntry* cmds, command cmd, char* from);
int do_pipe_command(cmdEntry* cmds, command cmd, command cmd2, char* from);

char* get_command_name(command cmd);

void do_system_command(command cmd);

#endif // GLOBAL_H_

