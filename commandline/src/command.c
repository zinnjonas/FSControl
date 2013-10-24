/*
 * =====================================================================================
 *
 *       Filename:  command.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  21.10.2013 16:14:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jonas Zinn (jsz), jonas.zinn@uni-konstanz.de
 *   Organization:
 *
 * =====================================================================================
 */

#define _GNU_SOURCE

#include "command.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>
#include "emalloc.h"
#include "cmds.h"
#include "global.h"
#ifdef MAIN_PROC
/*  init commands */
void init_commands()
{
	anz_commands = 0;
	cmds = create_commands();

	register_function();

	read_plugins();
}

/*  function to call the help files */
void helpProc(int arg, char** argv, char* from)
{
	if( arg == 0)
		descripe_commands(cmds, from);
	else
		descripe_command(cmds, argv[0], from);
}

/*  register the help command */
void register_help()
{
	list_t list = create_parameter_list();
	parameter_append(list, "[command]", "prints the help for the [command]");
	register_command( &cmds, create_command_ex("help", helpProc, true, "Prints the avaidable functions or the help for a command", list));
}


void reloadProc(int argc, char** argv, char* from)
{
	release_commands(cmds);
	cmds = NULL;
	init_commands();
	send_msg(from, "reloaded");
}

void register_reload()
{
	 register_command(&cmds, create_command_ex("reload", reloadProc, true, "Reloads all plugins", NULL));
}

void register_function()
{
	register_help();
	printf("load plugin: help\n");
	register_reload();
	printf("load plugin: reload\n");
}

void read_plugins()
{
	/*  search for plugins */
	struct dirent *dp;
	const char* dir_path = "./plugins/";
	DIR* dir = opendir(dir_path);
	int i;

	/*  open all plugins */
	while((dp = readdir(dir)) != NULL)
	{
		if( strcmp(dp->d_name, ".") != 0 && strcmp( dp->d_name, "..") != 0)
		{
			char* temp = NULL;
			if( !strcmp( &dp->d_name[strlen(dp->d_name)-3], ".so"))
			{
				temp = (char*) emalloc(strlen(dir_path)+strlen(dp->d_name)+1);
				strcpy(temp, dir_path);
				strcat(temp, dp->d_name);

				void* hplugin = dlopen(temp, RTLD_NOW);
				if( hplugin != NULL)
				{

					*(void**)&init = dlsym(hplugin, "init");
					*(void**)&init_ex = dlsym(hplugin, "init_ex");
					*(void**)&reg = dlsym( hplugin, "register_send_file");
					*(void**)&rel = dlsym(hplugin, "release_plugin");

					/*  call the init function  */
					if( init != NULL)
					{
						p_send_msg ptr_send = send_msg;
						register_command(&cmds, init(ptr_send));
					}
					else if( init_ex != NULL)
					{
						cmdEntry* initEntry = init_ex();
						i = 0;
						while(initEntry[i] != NULL)
						{
							register_command(&cmds, initEntry[i++]);
						}
					}
					else
					{
						printf("\"%s\": Can not find init in plugin!\n", dp->d_name);
					}
					if( reg != NULL)
					{
						p_send_msg ptr_send_file = send_file;
						reg(ptr_send_file);
					}
					if( rel != NULL)
                    {
                        register_release(&cmds, rel);
                    }
				}
				else
				{
					printf("Can not open plugin!\n");
					perror(dlerror());
				}
			}
			free(temp);
		}
	}
}

char* toLowerStr(char* msg)
{
	char* temp = (char*)emalloc(strlen(msg)+1);
	int i = 0;
	while(msg[i] != '\0')
	{
		temp[i] = tolower(msg[i]);
		i++;
	}
	temp[i] = '\0';

	return temp;
}

void execute( char* command, char* para, char* from)
{
	char* cmd = toLowerStr(command);

	if( !strcmp(cmd, "echo"))
	{
		send_msg( from, para);
	}
	else if( !strcmp(cmd, "led"))
	{
//		led_parameter(para);
	}
}

void parse_msg(char* msg, char* from)
{

	list_t executeList = splittCommands(msg);
  list_node_t it;
	for( it = list_head(executeList); it != NULL; it = node_next(it))
	{
		int result;
		command tempCommand = (command) node_get_data(it);
		if( !node_has_next(it))
		{
			result = do_command( cmds, tempCommand, from);
		}
	}

	list_dispose(executeList);

/* 	char* cmd = get_next_part(msg);

	if( cmd != NULL  && strlen(cmd) != 0)
	  execute( cmd, msg, from);*/
//	else
	//	eliza(msg, from);

}

char* get_next_part(char* msg)
{
  char temp[1024];
	strcpy( temp, msg);

	char* ptr = strtok( temp, " ");

	if( ptr!= NULL)
	{
		int size = strlen(ptr);
		if( size != strlen(msg))
			memmove( msg, msg+size+1, strlen(msg) - size);
		else
		{
			memcpy(msg, "\0", 0);
		}
	}

	return ptr;
}

#endif // MAIN_PROC
