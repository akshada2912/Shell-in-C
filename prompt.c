#include "headers.h"
#include "prompt.h"

void prompt(char *home,char* bgprompt,int time)
{
    
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    int res = strcmp(home, cwd);
    char *contain = strstr(cwd, home);
    int len=strlen(home);
    char *contain2 = (char *)malloc(sizeof(char) * len);
    int res2 = 1;
    if (contain != NULL)
    {
        for (int i = 0; i < strlen(home); i++)
            contain2[i] = contain[i];
        contain2[strlen(home)] = '\0';
        res2 = strcmp(contain2, home);
    }
    char *username = getlogin();
    char hostname[1024];
    hostname[1023] = '\0';
    int size = sizeof(hostname);
    int x= gethostname(hostname, size);
    //GetComputerName(hostname, &size);
    if (res == 0)
        {   if (time<=2)
            printf("<\033[0;35m %s\x1b[0m@%s:~> ", username, hostname);
            else
            printf("<\033[0;35m %s\x1b[0m@%s:~%s: %ds> ", username, hostname,bgprompt,time);
            }
    else
    {
        if (res2 != 0)
        {
            if(time<=2)
            printf("<\033[0;35m %s\x1b[0m@%s:~%s> ", username, hostname, cwd);
            else
            printf("<\033[0;35m %s\x1b[0m@%s:~%s~%s: %ds> ", username, hostname, cwd,bgprompt,time);
            }
        else
        {
            int lastslash = 0;
            // finding the last differing character to get the current folder name
            for (int i = 0; i < strlen(cwd); i++)
            {
                if (cwd[i] !=home[i])
                    {lastslash = i;
                    break;}
            }
            char *folder = (char *)malloc(sizeof(char) * strlen(cwd));
            int ind = 0;
            for (int i = lastslash + 1; i < strlen(cwd); i++)
                folder[ind++] = cwd[i];
            folder[ind] = '\0';
           if(time<=2)
            printf("<\033[0;35m %s\x1b[0m@%s:~/%s> ", username, hostname, folder);
            else
            printf("<\033[0;35m %s \x1b[0m@%s:~/%s %s: %ds> ", username, hostname, folder,bgprompt,time);
        }
    }
   
}
