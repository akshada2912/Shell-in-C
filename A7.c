#include "headers.h"
#include "A7.h"
int proc(char* buf)
{
    int pid;
    char *pid_str = (char*)malloc(sizeof(char)*strlen(buf));
    if(buf[9]=='\0')
    {
        pid_str = "self";
    }
    else{
        int ind=0;
        for(int i=9;i<strlen(buf)-1;i++)
        pid_str[ind++]=(char)buf[i];
        pid_str[ind]='\0';
    }
    
    char spath[256];
    snprintf(spath, sizeof(spath), "/proc/%s/status", pid_str);
    
    FILE *f = fopen(spath, "r");
    if (!f)
    {
        printf("\033[0;31m");
        perror("Failed to open status file");
        printf("\x1b[0m");
        return 0;
    }
    if (strcmp(pid_str, "self") != 0)
        {printf("pid: %s\n", pid_str);
         pid = atoi(pid_str); }
    else
    {
        int pid2 = getpid();
        printf("pid: %d\n", pid2);
        pid=pid2;
    }
    char line[256];
    char pstatus;
    int grp;
    unsigned long mem;
    char *epath = (char *)malloc(sizeof(char) * 1024);
    int bgflag=0;
    int status;
    int result = waitpid(pid, &status, 0x01);

    if (result == -1) 
    {
        // printf("\033[0;31m");
        // perror("waitpid");
        // printf("\x1b[0m");
       // exit(EXIT_FAILURE);
    } else if (result == 0) 
    {
        bgflag=1;
    }

    while (fgets(line, sizeof(line), f))
    {
        
        if (strncmp(line, "PPid:", 5) == 0)
        {
            sscanf(line, "PPid:\t%d", &grp);
        }
        else if (strncmp(line, "Name:", 5) == 0)
        {
            sscanf(line, "Name:\t%s", epath);
        }
        else if (strncmp(line, "State:", 6) == 0)
        {
            sscanf(line, "State:\t%c", &pstatus);
        }
        else if (strncmp(line, "VmSize:", 7) == 0)
        {
            sscanf(line, "VmSize:\t%lu", &mem);
        }
    }
    if(bgflag==0)
    printf("Process status: %c+\n", pstatus);
    else
    printf("Process status: %c\n", pstatus);
    printf("Process group: %d\n", grp);
    printf("Virtual memory: %lu KB\n", mem);
    printf("executable path: %s\n", epath);

    fclose(f);
    return 1;
    
}