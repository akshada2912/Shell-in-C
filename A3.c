#include "headers.h"
#include "A3.h"
int warp(char *buf, char *home, char *prev)
{
    if (strcmp("warp\n", buf) == 0 || strcmp("warp", buf) == 0)
    {
        if (chdir(home) != 0)
        {
            printf("\033[0;31m");
            perror("lsh");
            printf("\x1b[0m");
            return 0;
        }
        char cwd2[1024];
        getcwd(cwd2, sizeof(cwd2));
        printf("%s\n", cwd2);
        return 1;
    }
    int i = 5;
    char dir[1024];
    dir[0] = '\0';
    while (i < strlen(buf) )
    {

        int untilletter = i;
        int flag = 0;
        int k;
        // finding the first non space/tabspace
        for (k = untilletter; k < strlen(buf) ; k++)
        {
            if (buf[k] != ' ' && (int)buf[k] != 9 && buf[k] != '\n')
            {
                flag = 1;
                untilletter = k;
                break;
            }
        }

        i = untilletter;
        if (flag == 1 && untilletter == i && k == strlen(buf) )
        {
            i = k;
            continue;
        }
        if (i >= strlen(buf) )
            break;

        /*if (buf[i] != '-')
        {
            // setting previous dir
            char cwd2[1024];
            getcwd(cwd2, sizeof(cwd2));
            int ind = 0;
            for (int i = 0; i < strlen(cwd2); i++)
                prev[ind++] = cwd2[i];
            prev[ind] = '\0';
        }*/

        if ((buf[i] == '~' && buf[i + 1] == ' ') || (buf[i] == '~' && buf[i + 1] == '\n') || (buf[i] == '~' && i + 1 == strlen(buf) ) || strcmp(buf, "warp\n") == 0 || strcmp("warp", buf) == 0)
        {
            // home dir
            int ind = 0;
            for (int j = 0; j < strlen(home); j++)
                dir[ind++] = home[j];
            dir[ind] = '\0';
            // printf("***%s",dir);
            int untilletter = i + 2;
            for (int k = untilletter; k < strlen(buf) ; k++)
            {
                if (buf[k] != ' ' && (int)buf[k] != 9 && buf[k] != '\n')
                {
                    untilletter = k;
                    break;
                }
            }
            i = untilletter;
            if (chdir(dir) != 0)
            {
                printf("\033[0;31m");
                perror("lsh");
                printf("\x1b[0m");
                return 0;
                continue;
            }
            char cwd2[1024];
            getcwd(cwd2, sizeof(cwd2));
            printf("%s\n", cwd2);
            continue;
        }

        else if (buf[i] == '~' && buf[i + 1] == '/')
        {
            // relative to home
            int ind = 0;
            int j;
            for (j = i + 2; buf[j] != ' ' && j < strlen(buf) && buf[j] != '\n'; j++)
            {
                dir[ind++] = buf[j];
            }
            i = j;
            int untilletter = i + 2;
            for (int k = untilletter; k < strlen(buf) ; k++)
            {
                if (buf[k] != ' ' && (int)buf[k] != 9 && buf[k] != '\n')
                {
                    untilletter = k;
                    break;
                }
            }
            i = untilletter;
            dir[ind] = '\0';
            if (strcmp(dir, "") == 0)
            {
                printf("\033[0;31m");
                fprintf(stderr, "lsh: expected argument to \"cd\"\n");
                printf("\x1b[0m");
                continue;
            }
            else
            {
                chdir(home);
                if (chdir(dir) != 0)
                {
                    printf("\033[0;31m");
                    perror("lsh");
                    printf("\x1b[0m");
                    return 0;
                    continue;
                }
                char cwd2[1024];
                getcwd(cwd2, sizeof(cwd2));
                printf("%s\n", cwd2);
            }
            continue;
        }

        else if (buf[i] == '.' && buf[i + 1] == '.')
        {
            // cd ..
            char cwd2[1024];
            getcwd(cwd2, sizeof(cwd2));
            int lastslash = 0;
            // getting index of last backslash
            for (int j = 0; j < strlen(cwd2) ; j++)
            {
                if (cwd2[j] == '/')
                    lastslash = j;
            }
            int ind = 0;
            for (int j = 0; j < lastslash; j++)
                dir[ind++] = cwd2[j];
            dir[ind] = '\0';
            int untilletter = i + 3;
            for (int k = untilletter; k < strlen(buf) ; k++)
            {
                if (buf[k] != ' ' && (int)buf[k] != 9 && buf[k] != '\n')
                {
                    untilletter = k;
                    break;
                }
            }
            i = untilletter;
        }

        else if (buf[i] == '.' && buf[i + 1] == ' ' || buf[i] == '.' && buf[i + 1] == '\n' || buf[i] == '.' && (int)buf[i + 1] == 9 || buf[i] == '.' && i + 1 == strlen(buf) )
        {
            // current cwd
            int untilletter = i + 2;
            for (int k = untilletter; k < strlen(buf) ; k++)
            {
                if (buf[k] != ' ' && (int)buf[k] != 9 && buf[k] != '\n')
                {
                    untilletter = k;
                    break;
                }
            }
            i = untilletter;
            char cwd2[1024];
            getcwd(cwd2, sizeof(cwd2));
            printf("%s\n", cwd2);
            continue;
        }

        else if (buf[i] == '-')
        {
            // prev dir
            int ind = 0;
            for (int j = 0; j < strlen(prev); j++)
                dir[ind++] = prev[j];
            dir[ind] = '\0';
            // printf("***%s",dir);
            int untilletter = i + 2;
            for (int k = untilletter; k < strlen(buf) ; k++)
            {
                if (buf[k] != ' ' && (int)buf[k] != 9 && buf[k] != '\n')
                {
                    untilletter = k;
                    break;
                }
            }
            i = untilletter;
            char prev2[1024] = "OLDPWD not set";
            prev2[14] = '\0';
            if (strcmp(prev, prev2) == 0)
            {
                printf("\033[0;31m OLDPWD not set \x1b[0m \n");
                continue;
            }
        }
        else if (buf[i] == '/')
        {
            int ind = 0;
            int j;
            for (j = i; j < strlen(buf) ; j++)
            {
                if (buf[j + 1] == '\n' || buf[j] == ' ' || buf[j] == '\t' || buf[j] == '\0')
                    break;
                dir[ind++] = buf[j];
            }
            dir[ind] = '\0';
            // printf("%s",dir);
            i = j + 1;
        }
        else
        {
            int ind = 0;
            int j;
            for (j = i; buf[j] != ' ' && buf[j] != '\n' && ((j < strlen(buf) && buf[j] > 'z' || buf[j] < 'a') || j < strlen(buf)); j++)
                dir[ind++] = buf[j];
            dir[ind] = '\0';

            int untilletter = j + 1;
            for (int k = untilletter; k < strlen(buf) ; k++)
            {
                if (buf[k] != ' ' && (int)buf[k] != 9 && buf[k] != '\n')
                {
                    untilletter = k;
                    break;
                }
            }
            i = untilletter;
        }
         //printf("***%s***\n++",dir);
        if (chdir(dir) == -1)
        {
            perror("\033[0;31m lsh \x1b[0m");
            return 0;
        }
        char cwd2[1024];
        getcwd(cwd2, sizeof(cwd2));
        printf("%s\n", cwd2);
    }
    return 1;
}