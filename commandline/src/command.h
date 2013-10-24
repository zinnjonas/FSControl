/*
 * =====================================================================================
 *
 *       Filename:  command.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  21.10.2013 16:14:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jonas Zinn (jsz), jonas.zinn@uni-konstanz.de
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef COMMANDS_H_
#define COMMANDS_H_
#ifdef MAIN_PROC

#include "cmds.h"

extern int anz_commands;

typedef cmdEntry (*init_f)(p_send_msg);
typedef cmdEntry* (*init_ex_f)();
typedef void (*reg_func) (p_send_msg);
init_f    init;
init_ex_f init_ex;
cmdEntry* cmds;
reg_func  reg;
void_func rel;

/* init commands */
void init_commands();

/*  function to call the help files */
void helpProc(int arg, char** argv, char* from);

/*  register the help command */
void register_help();

/*  read all existing plugins */
void read_plugins();

/* function to parse and execute a command */
void parse_msg(char* msg, char* from);
/*  seperate a string by \" \"  */
char* get_next_part(char* msg);

void register_function();
#endif // MAIN_PROC
#endif // COMMANDS_H_

