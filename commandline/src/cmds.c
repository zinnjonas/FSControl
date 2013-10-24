/*
 * =====================================================================================
 *
 *       Filename:  cmds.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  22.10.2013 02:58:04
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
#include <string.h>
#include <stdbool.h>
#include "emalloc.h"
#include "cmds.h"

bool singlePrint;
char* to;

/* structure to describe a command */
struct cmd_entry {
    char* name;
    char* desc;
    list_t para;
    func_ptr func;
    void_func release;
    bool no_redirect;
};

struct parameter_t
{
    const char* para;
    const char* desc;
};

typedef struct parameter_t* parameter;

int anz_commands = 0;

bool useColor = true;

void can_use_color()
{
    useColor = true;
}

void can_not_use_color()
{
    useColor = false;
}

cmdEntry* create_commands()
{
    return (cmdEntry*)ecalloc(0, sizeof(cmdEntry));
}

void register_command(cmdEntry** cmds,cmdEntry entry)
{
    cmdEntry* temp = (cmdEntry*)erealloc(*cmds,sizeof(cmdEntry) * ++anz_commands);
    temp[anz_commands-1] = entry;
    *cmds = temp;
}

void register_release(cmdEntry** cmds, void_func func)
{
    (*cmds[anz_commands-1])->release = func;
}

cmdEntry create_command(char* name, func_ptr func, char* desc, bool redirect)
{
    cmdEntry temp = (cmdEntry)emalloc(sizeof(struct cmd_entry));
    temp->name = (char*)emalloc( strlen(name)+1);
    temp->desc = (char*)emalloc( strlen(desc)+1);

    strcpy(temp->name,name);
    strcpy(temp->desc,desc);
    temp->para = NULL;
    temp->func = func;
    temp->release = NULL;
    temp->no_redirect = !redirect;
    return temp;
}

cmdEntry create_command_ex(char* name, func_ptr func, bool redirect, char* desc, list_t para)
{
    cmdEntry temp = (cmdEntry)emalloc(sizeof(struct cmd_entry));
    temp->name = (char*)emalloc( strlen(name)+1);
    temp->desc = (char*)emalloc( strlen(desc)+1);

    strcpy(temp->name,name);
    strcpy(temp->desc,desc);

    temp->para = para;

    temp->func = func;

    temp->no_redirect = !redirect;
    temp->release = NULL;
    return temp;
}

int execute_command(cmdEntry* cmds, char* name, int num, char** argv, char* from)
{
    int i;
    /* search command*/
    for( i = 0; i < anz_commands; i++)
    {
        if( 0 == strcmp(cmds[i]->name, name))
        {
            if( !useColor && cmds[i]->no_redirect)
                return -1;
            cmds[i]->func(num,argv, from);
            return 0;
        }
    }
    /* no such command*/
    return 1;
}

void release_command( cmdEntry cmd)
{
    if( NULL != cmd->release)
    {
        (*cmd->release)();
        cmd->release = NULL;
    }
    free(cmd->name);
    free(cmd->desc);
    list_dispose(cmd->para);
    free(cmd);
}

void release_commands(cmdEntry* cmds)
{
    int i;
    for( i = 0; i < anz_commands; i++)
    {
        release_command(cmds[i]);
    }
    free(cmds);
}

void descripe_commands(cmdEntry* cmds, char* from)
{
    int i;
    for( i = 0; i < anz_commands; i++)
    {
			if( from == NULL)
        printf("%-12s   %s\n", cmds[i]->name, cmds[i]->desc);
			else
			{
				char temp[250];
				sprintf(temp, "%-12s   %s", cmds[i]->name, cmds[i]->desc);
				#ifdef MAIN_PROC
				send_msg(from, temp);
				#else
				send_message(from, temp);
				#endif
			}
    }
}

void descripe_command(cmdEntry* cmds, char* name, char* from)
{
    int i;
    int found = 0;
    for( i = 0; i < anz_commands; i++)
    {
        if( 0 == strcmp(cmds[i]->name, name))
        {
 						char temp[1024];
						if( from == NULL)
						{
	            printf("%s\n", cmds[i]->desc);
	            printf("%s  ",cmds[i]->name);
						}
						else
						{
							sprintf(temp, "%s\n", cmds[i]->desc);
							sprintf(temp, "%s  ", cmds[i]->name);
						}
            /* print all parameters with description of them*/
            if( cmds[i]->para != NULL)
            {
								to = from;
                singlePrint = true;
                list_print(cmds[i]->para);
                singlePrint = false;
                list_print(cmds[i]->para);
            }
            else
						{
								if( from == NULL)
	                printf("\n");
								else
									sprintf(temp, "\n");
						}

						if( from == NULL)
							send_msg(from, temp);
            found = 1;
            break;
        }
    }
    if( found == 0)
    {
				if( from == NULL)
					printf( "Don't know command \"%s\"!\ntype \"help\" to see the available commands\n", name);
				else
				{
					char temp[512];
					sprintf(temp,  "Don't know command \"%s\"!\ntype \"help\" to see the available commands\n", name);
					send_msg(from, temp);
				}
    }
}

int compare_parameter_list( void* d1, void* d2)
{

    parameter t1 = (parameter)d1;
    parameter t2 = (parameter)d2;


    return (!strcmp(t1->para,t2->para) && !strcmp(t1->desc,t2->desc));
}

void print_parameter_list(void* data)
{

    parameter temp = (parameter)data;
    if( to != NULL)
		{
			char tmp[1024];
			if( singlePrint)
	        if( data == NULL)
	         ;
	        else
             sprintf(tmp, "%s ", temp->para);
	    else
	        if( data != NULL)
	        {
	            sprintf(tmp,"%s %s", temp->para, temp->desc);
	        }

			send_msg(to, tmp);

		}
		else
		{

			if( singlePrint)
	        if( data == NULL)
	            printf("\n");
	        else
	            if( !useColor)
	                printf("%s ", temp->para);
	            else
	                printf("\033[22;36m%s \033[0m", temp->para);
	    else
	        if( data != NULL)
	        {

	            if( !useColor)
	                printf("%s %s\n", temp->para, temp->desc);
	            else
	                printf("\033[22;36m%s \033[22;32m%s\033[0m\n", temp->para, temp->desc);
	        }
			}
}

void dispose_parameter_list(void* data)
{
    free(data);
    data = NULL;
}

list_t create_parameter_list()
{
    return list_new(compare_parameter_list,print_parameter_list,dispose_parameter_list);
}

void parameter_append(list_t list, const char* para, const char* desc)
{
    parameter temp = (parameter)emalloc(sizeof(parameter));
    temp->para = para;
    temp->desc = desc;
    list_append(list, temp);
}

bool no_redirection(cmdEntry* cmds, char* name)
{
    int i;
    for( i = 0; i < anz_commands; i++)
    {
        if( 0 == strcmp(cmds[i]->name, name))
        {
            return cmds[i]->no_redirect;
        }
    }
    return false;
}
