#include "headers.h"
#include "A6.h"

struct BackgroundProcess
{
    pid_t pid;
    char name[1024];
    time_t time;
};

struct BackgroundProcess bgprocesses[100000];


void add_background_process(int pid, const char *name)
{
    int firstspace = strlen(name);
    for (int i = 0; i < strlen(name); i++)
    {
        if (name[i] == ' ')
        {
            firstspace = i;
            break;
        }
    }
    char *cmd = (char *)malloc(sizeof(char) * strlen(name));
    int ind = 0;
    for (int i = 0; i < firstspace; i++)
        cmd[ind++] = name[i];
    cmd[ind] = '\0';
    if (bgcount < 100000)
    {
        // printf("++%d ",pid);
        bgprocesses[bgcount].pid = pid;
        strcpy(bgprocesses[bgcount].name, cmd);
        bgprocesses[bgcount].time = time(NULL);
        bgcount++;
    }
}

int check_bgprocesses(int isfgflag, char *home)
{
    int status;
    int printflag = 0;
    int x=bgcount;
    for (int i = 0; i < bgcount; i++)
    {
        int pid = waitpid(bgprocesses[i].pid, &status, WNOHANG);
        //printf("%d",pid);
        // int pid = bgprocesses[i].pid;
        if (pid > 0)
        {
            if (isfgflag != 1)
            {
                printflag = 1;
                printf("%s ", bgprocesses[i].name);
                if (WIFEXITED(status))
                {
                    printf("exited normally (%d)\n", pid);
                }
                else
                {
                    printf("exited abnormally (%d)\n", pid);
                }
            }

            x--;
            bgprocesses[i] = bgprocesses[x];
        }
    }
    if (printflag == 1)
        return 1;
    return 0;
}

int specsix(char *command, char *home, int* execution_time,char* prompttime)
{
    command[strcspn(command, "\n")] = '\0';

    if (strcmp(command, "exit") == 0)
    {
        return 1;
    }
    else if (strstr(command, "&") != NULL)
    {
        // background process
        command[strlen(command) - 1] = '\0'; // Remove the "&"
                                             // int pid = fork();
        
        int spacecount = 0;
        for (int i = 0; i < strlen(command) - 1; i++)
        {
            if (command[i] == ' ')
                spacecount++;
        }
        spacecount += 2;
        char **const argv = (char **)malloc(sizeof(char *) * spacecount);
        for (int i = 0; i < spacecount; i++)
            argv[i] = (char *)malloc(sizeof(char) * 1024);
        int i = 0;
        char *first = (char *)malloc(sizeof(char) * strlen(command));
        char *cur = (char *)malloc(sizeof(char) * strlen(command));
        char *cmd = (char *)malloc(sizeof(char) * strlen(command));
        int argcount = 0, flagfirst = 1;
        while (i < strlen(command) - 1)
        {
            if (i != 0)
            {
                for (int j = 0; j < strlen(cur); j++)
                    cur[j] = '\0';
                for (int j = 0; j < strlen(first); j++)
                    first[j] = '\0';
            }
            int ind = 0;
            for (; i < strlen(command) - 1 && command[i] != ' '; i++)
            {
                first[ind++] = command[i];
            }
            i++;
            first[ind] = '\0';
            int indc = 0;
            for (int j = 0; j < strlen(first); j++)
                argv[argcount][indc++] = first[j];
            argv[argcount][indc] = '\0';
            if (flagfirst == 1)
            {
                int ind = 0;
                for (int j = 0; j < strlen(first); j++)
                    cmd[ind++] = first[j];
                cmd[ind] = '\0';
                flagfirst = 0;
            }
            argcount++;
        }
        

        argv[argcount] = NULL;
        int pid = fork();
        if (pid == 0)
        {
            
             if (dup2(STDOUT_FILENO, STDOUT_FILENO) == -1) // restore stdout to terminal
            {
                printf("\033[0;31m");
                perror("dup2");
                printf("\x1b[0m");
                exit(EXIT_FAILURE);
            }
            execvp(cmd, argv);
            printf("\033[0;31m");
            printf("ERROR : \'%s\' is not a valid command\n",cmd);
            printf("\x1b[0m");
            //perror("execvp");
            return 0;
        }
        else if(pid>0)
        {
            add_background_process(pid, command);
            printf("%d\n", pid);
            if (dup2(STDOUT_FILENO, STDOUT_FILENO) == -1) // restore stdout to terminal
            {
                printf("\033[0;31m");
                perror("dup2");
                printf("\x1b[0m");
                exit(EXIT_FAILURE);
            }
            return 1;
        }
        return 1;
    }
    else
    {
        //printf("%s",command);
        //foreground process
        int spacecount = 0;
        for (int i = 0; i < strlen(command) - 1; i++)
        {
            if (command[i] == ' ')
                spacecount++;
        }
        spacecount += 2;
        char **const argv = (char **)malloc(sizeof(char *) * spacecount);
        for (int i = 0; i < spacecount; i++)
            argv[i] = (char *)malloc(sizeof(char) * 1024);
        int i = 0;
        char *first = (char *)malloc(sizeof(char) * strlen(command));
        char *cur = (char *)malloc(sizeof(char) * strlen(command));
        char *cmd = (char *)malloc(sizeof(char) * strlen(command));
        int argcount = 0, flagfirst = 1;
        while (i < strlen(command))
        {
            if (i != 0)
            {
                for (int j = 0; j < strlen(cur); j++)
                    cur[j] = '\0';
                for (int j = 0; j < strlen(first); j++)
                    first[j] = '\0';
            }
            int ind = 0;
            for (; i < strlen(command) && command[i] != ' '; i++)
            {
                first[ind++] = command[i];
            }
            i++;
            first[ind] = '\0';
            int indc = 0;
            for (int j = 0; j < strlen(first); j++)
                argv[argcount][indc++] = first[j];
            argv[argcount][indc] = '\0';
            if (flagfirst == 1)
            {
                int ind = 0;
                for (int j = 0; j < strlen(first); j++)
                    prompttime[ind++] = first[j];
                prompttime[ind] = '\0';
                ind = 0;
                for (int j = 0; j < strlen(first); j++)
                    cmd[ind++] = first[j];
                cmd[ind] = '\0';
                flagfirst = 0;
            }
            argcount++;
        }
        
        argv[argcount] = NULL;
        int pid = fork();
        if (pid == -1)
        {
            printf("\033[0;31m");
            perror("Fork failed");
            printf("\x1b[0m");
            return -1;
        }

        else if (pid == 0)
        {
            
            execvp(cmd, argv);
            printf("\033[0;31m");
            printf("ERROR : \'%s\' is not a valid command\n",cmd);
            printf("\x1b[0m");
            //perror("execvp");
            return 0;
            exit(0);
        }
        
        if (dup2(STDOUT_FILENO, STDOUT_FILENO) == -1) // restore stdout to terminal
        {
            printf("\033[0;31m");
            perror("dup2");
            printf("\x1b[0m");
            exit(EXIT_FAILURE);
        }
        time_t starttime = time(NULL);
        waitpid(pid, NULL, 0);
        time_t end_time = time(NULL);
        *execution_time = (int)(end_time - starttime);
        if (*execution_time > 2)
        {
            int firstspace = strlen(command);
            for (int i = 0; i < strlen(command); i++)
            {
                if (command[i] == ' ')
                {
                    firstspace = i;
                    break;
                }
            }
            
            //printf("%s\n", command);
            //prompt(home, cmd, execution_time);
            return 2;
        }
        return 1;
        
    }

    return 1;
}
