/*
 * =====================================================================================
 *
 *       Filename:  cmds.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  22.10.2013 02:56:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jonas Zinn (jsz), jonas.zinn@uni-konstanz.de
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef CMDS_H_
#define CMDS_H_

#include <stdbool.h>
#include "list.h"
#ifdef MAIN_PROC
extern void send_msg(char*,char*);
extern void send_file(char*, char*);
#endif
/* structure for a single command*/
typedef struct cmd_entry* cmdEntry;

/* call function definition*/
typedef void (*func_ptr)(int arg, char** argv, char* from);

typedef void (*p_send_msg)(char*,char*);

typedef void (*void_func)();

/* create the command array*/
cmdEntry* create_commands();
/* executes a given command in the field*/
int execute_command(cmdEntry* cmds, char* name, int num, char** argv, char* from);
int execute_pipe_command(cmdEntry* cmds, char* name, int num, char** argv);
/* releases all commands*/
void release_commands(cmdEntry* cmds);
/* prepare all for a new command, returns the new command array*/
void register_command(cmdEntry** cmds, cmdEntry entry);
/* register a release function for this plugin*/
void register_release(cmdEntry** cmds, void_func func);
/* crate an new command entry, returns the new command to register */
cmdEntry create_command( char* name, func_ptr func, char* desc, bool redirect);
/* crate an new command entry, with single parameter description, returns the new command to register */
cmdEntry create_command_ex( char* name, func_ptr func, bool redirect, char* desc, list_t para);
/* describes all commands in the command array*/
void descripe_commands(cmdEntry* cmds, char* from);
/* describes all commands in the command array */
void descripe_command(cmdEntry* cmds, char* name, char* from);

void can_use_color();
void can_not_use_color();

list_t create_parameter_list();
void parameter_append(list_t list, const char* para, const char* desc);

bool no_redirection(cmdEntry* cmds, char* name);

#endif // CMDS_H_

