/*
 * =====================================================================================
 *
 *       Filename:  global.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22.10.2013 02:51:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jonas Zinn (jsz), jonas.zinn@uni-konstanz.de
 *   Organization:  
 *
 * =====================================================================================
 */

#include "global.h"

#include "emalloc.h"
#include "commands.h"

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

struct command_t
{
    char*  name;
    char** argv;
    int    argc;
};

struct redirect_t
{
    char* filename;
    bool  append;
};

const char delimiter[] = "> \t\n";

void use_normal_stdout()
{
    stdout = freopen("/dev/tty", "w", stdout);
    can_use_color();
}

redirect splittRedirection( char* command)
{
    redirect temp = NULL;

    char* directed = strpbrk(command, ">");
    if( NULL != directed)
    {
        temp = (redirect)emalloc(sizeof(struct redirect_t));
        if( directed[strlen(directed)-1] == '\n')
            directed[strlen(directed)-1] = '\0';
        temp->append = false;
        if( directed[1] == '>')
            temp->append = true;
        directed = strtok(directed, "> ");
        can_not_use_color();
        temp->filename = (char*) emalloc((strlen(directed) + 1)*sizeof(char));
        strcpy(temp->filename, directed);
        command[strlen(command) - strlen(temp->filename)] = '\0';
    }

    return temp;
}

FILE* openRedirection(redirect red)
{
    if( red != NULL)
    {
        return freopen(red->filename, (red->append ? "a":"w"), stdout);
    }
    use_normal_stdout();
    return NULL;
}

void dispose_command_list(void* data)
{
    free(((command)data)->name);
    free(((command)data)->argv);
    free(data);
    data = NULL;
}

command readCommand(char* line)
{
    command tempCommand = NULL;
    /* find the command and the parameters*/
    char * ptr = strtok(line, delimiter);
    if( ptr != NULL)
    {

        tempCommand = (command) emalloc(sizeof(struct command_t));
        tempCommand->name = (char*) emalloc((strlen(ptr)+1)*sizeof(char));
        strcpy(tempCommand->name, ptr);
        tempCommand->argc = 0;
        tempCommand->argv = (char**)ecalloc(tempCommand->argc, sizeof(char*));

        while((ptr = strtok(NULL, delimiter)) != NULL)
        {
            tempCommand->argv = (char**)erealloc(tempCommand->argv, sizeof(char**) * ++tempCommand->argc);
            tempCommand->argv[tempCommand->argc-1] = ptr;
        }
    }
    return tempCommand;
}

list_t splittCommands(char* cmd)
{
    if( cmd == NULL || strlen(cmd) == 0)
        return NULL;
    list_t temp = list_new(NULL, NULL, dispose_command_list);

    char* line = (char*) emalloc((strlen(cmd)+1)*sizeof(char));
    strcpy(line, cmd);
    char* nextCommand;
    do
    {
        nextCommand= strpbrk(line, "|");
        if( nextCommand != NULL)
        {
            line[ strlen(line) - strlen(nextCommand)] = '\0';
            cmd += strlen(line);
        }
        command tempCommand = readCommand(line);
        if( tempCommand != NULL)
            list_append(temp, tempCommand);
        line = cmd+1;
    }while(nextCommand != NULL);

    return temp;
}

int do_command(cmdEntry* cmds, command cmd, char* from)
{
    int result =  execute_command(cmds, cmd->name, cmd->argc, cmd->argv, from);
    if( result == 1)
        do_system_command(cmd);
    return result;
}

int do_pipe_command(cmdEntry* cmds, command cmd, command cmd2, char* from)
{
    int pipefd[2];
    pid_t cpid;

    if( pipe(pipefd) == -1)
    {
        perror("pipe");
        return -2;
    }
    cpid = fork();
    if( cpid == -1)
    {
        perror("fork");
        return -3;
    }

    if( cpid == 0)
    {
        close(pipefd[1]);
        dup2(pipefd[0],0);
        can_use_color();
        int r2 = execute_command(cmds, cmd2->name, cmd2->argc, cmd2->argv, from);
        if(r2 == 1)
            do_system_command(cmd2);
        else if(r2 == -1)
            return -1;
        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        can_not_use_color();
        close(pipefd[0]);
        dup2(pipefd[1],1);
        int r1 =  execute_command(cmds, cmd->name, cmd->argc, cmd->argv, from);
        if( r1 == 1)
            do_system_command(cmd);
        else if(r1 == -1)
            exit(-1);
        close(pipefd[1]);
        use_normal_stdout();
        wait(NULL);
    }

    return 1;
}

char* get_command_name( command cmd)
{
    return cmd->name;
}

void do_system_command(command cmd)
{
     /*  size_t size = strlen(cmd->name);
    int i;
    for(i = 0; i < cmd->argc; i++)
        size += strlen(cmd->argv[i]);
    size+=cmd->argc + 1;
    char* puffer = (char*)emalloc(size*sizeof(char));
    strcpy(puffer, cmd->name);
    for(i = 0; i < cmd->argc; i++)
    {
        strcat(puffer, " ");
        strcat(puffer, cmd->argv[i]);
    }

    if( system(puffer) == -1)
        printf( "Don't know command \"%s\"!\nrly ?type \"help\" to see the available commands\n", cmd->name);

    free(puffer);*/
}



