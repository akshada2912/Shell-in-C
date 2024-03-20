#include "headers.h"
#include "A2.h"
int back(char *buf, int flagsemi, int flagand, char *home, char **pastarray, int(*countpast), char *prev, int pastind, int *exec_time, char *prompttime)
{
    int flagpast = 0;
    int flagprompt = 0;
    if (strstr(buf, "pastevents") != NULL)
        flagpast = 0;
    else
        flagpast = 1;
    int i = 0;
    char *dir = (char *)malloc(sizeof(char) * strlen(buf) + 1);
    int untilletter = 0;
    char com[5];
    int ind = 0;
    while (i < strlen(buf))
    {
        // printf("***%d",i);
        // printf("**%d %c %ld***",i,buf[i],strlen(buf));
        untilletter = 0;
        for (int j = i; j < strlen(buf); j++)
        {
            if (buf[j] >= 'a' && buf[j] <= 'z')
            {
                untilletter = j;
                break;
            }
        }
        // printf("%d",untilletter);
        int k;
        int flagbg = 0, flagsem = 0;
        for (k = untilletter; k < strlen(buf) && buf[k] != '\n' && (buf[k] != '&' && buf[k] != ';'); k++)
        {
        }
        if (k < strlen(buf) && buf[k] == '&')
            flagbg = 1;
        if (buf[k] == '\n')
            flagsem = 1;
        ind = 0;
        int j;
        if (k == strlen(buf))
            k = strlen(buf) - 2;
        for (j = untilletter; j <= k; j++)
        {
            dir[ind++] = buf[j];
        }
        dir[ind] = '\0';
        // printf("%d %d",k,strlen(buf));
        // printf("***%s***\n",dir);
        // return 0;
        // if it's a background process
        if (dir[strlen(dir) - 1] == '&')
        {
            int x = specsix(dir, home, exec_time, prompttime);
            if (x == 2)
                flagprompt = 2;
        }
        // if there's a semicolon
        else if (dir[strlen(dir) - 1] == ';' || k == strlen(buf) - 2 || k == strlen(buf) - 1 || k == strlen(buf))
        {
            printf("%s\n", dir);
            if (dir[strlen(dir) - 1] == ';')
            {
                // removing the ; from the string
                char *dir2 = (char *)malloc(sizeof(char) * strlen(dir));
                int ind = 0;
                if (dir[strlen(dir) - 2] == ' ')
                {
                    for (int q = 0; q < strlen(dir) - 2; q++)
                        dir2[ind++] = dir[q];
                }
                else
                {
                    for (int q = 0; q < strlen(dir); q++)
                        dir2[ind++] = dir[q];
                }
                dir2[ind] = '\0';
                for (int q = 0; q < strlen(dir); q++)
                    dir[q] = '\0';
                ind = 0;
                for (int q = 0; q < strlen(dir2); q++)
                    dir[ind++] = dir2[q];
                dir[ind] = '\0';
                if (dir[strlen(dir) - 1] == ';')
                {
                    ind = 0;
                    for (int q = 0; q < strlen(dir2)-1; q++)
                        dir[ind++] = dir2[q];
                    dir[ind] = '\0';
                }
            }
            // printf("**%s\n",dir);
            if (strlen(dir) < 3)
            {
                int x = specsix(dir, home, exec_time, prompttime);
                if (x == 2)
                    flagprompt = 2;
            }
            char com[5];
            for (int i = 0; i < 4; i++)
                com[i] = dir[i];
            com[4] = '\0';
            char com2[11];
            if (strlen(dir) >= 10)
            {
                for (int i = 0; i < 10; i++)
                    com2[i] = dir[i];
                com2[10] = '\0';
            }
            else
                com2[0] = '\0';
            char com3[9];
            if (strlen(dir) >= 9)
            {
                for (int i = 0; i < 9; i++)
                    com3[i] = dir[i];
            }
            else
                com3[0] = '\0';
            com3[8] = '\0';
            int iserror = 1;
            if (strcmp(com, "warp") == 0)
            {

                int x = warp(dir, home, prev);
            }
            else if (strcmp(com, "peek") == 0)
            {
                int x = peek(dir, home, prev);
                if (x == 0)
                    iserror = 0;
            }
            else if (strcmp(com, "seek") == 0)
            {
                int x = seek(dir, home);
                if (x == 0)
                    iserror = 0;
            }
            else if (strcmp(com2, "pastevents") == 0)
            {
                int x = pastev(dir, pastarray, (*countpast), home, prev, pastind, exec_time, prompttime);
                char com3[6];
                int indc = 0;
                if (x == 2)
                {
                    for (int c = 11; c < 16; c++)
                        com3[indc++] = dir[c];
                    com3[5] = '\0';
                    char pur[6] = "purge";
                    pur[5] = '\0';
                    int flageq = 1;
                    for (int i = 0; i < 5; i++)
                    {
                        if (pur[i] != com3[i])
                        {
                            flageq = 0;
                            break;
                        }
                    }
                    if (flageq == 1)
                    {
                        (*countpast) = -1;
                        pastind = 0;
                        char cwd5[1024];
                        getcwd(cwd5, sizeof(cwd5));
                        if (chdir(home) != 0)
                        {
                        }
                        FILE *f = fopen("past.txt", "w");
                        if (f != NULL)
                            fputs("", f);
                        fclose(f);
                        if (chdir(cwd5) != 0)
                        {
                        }
                    }
                }
            }
            else if (strcmp(com3, "proclore") == 0)
            {
                int x = proc(dir);
                if (x == 0)
                    iserror = 0;
            }
            else
            {
                int x = specsix(dir, home, exec_time, prompttime);
                if (x == 0)
                {
                    iserror = 0;
                }
                if (x == 2)
                    flagprompt = 2;
            }
            // if (iserror == 1)
            // {
            // printf("%s %d",dir,strlen(dir));
            // return 0;
            char comc[11];
            if (strlen(dir) >= 10)
            {
                char comc[11];
                for (int i = 0; i < 10; i++)
                    comc[i] = dir[i];
                comc[10] = '\0';
            }
            else
                comc[0] = '\0';
            if (strcmp(comc, "pastevents") != 0 && strstr(buf, "pastevents") == NULL)
            {

                int ind1 = 0;
                int flageq = 1;
                if (pastind == 0 && (*countpast) == 14)
                {
                    if ((strlen(dir) - 1) != strlen(pastarray[14]) || (strlen(dir) - 1 != strlen(pastarray[pastind - 1])))
                        flageq = 0;
                }
                else if (pastind == 0 && (*countpast) < 14)
                    flageq = 0;
                else
                {
                    for (int i = 0; i < strlen(dir); i++)
                    {
                        if (pastind == 0)
                        {
                            if (dir[i] != pastarray[14][i])
                            {
                                flageq = 0;
                                break;
                            }
                        }
                        else
                        {
                            if (dir[i] != pastarray[pastind - 1][i])
                            {
                                // printf("%d %c %c", i, dir[i], pastarray[pastind - 1][i]);
                                flageq = 0;
                                break;
                            }
                        }
                    }
                }
                if (flageq == 0 && flagpast == 0)
                {
                    if (pastind >= 15)
                        pastind = 0;

                    for (int p = 0; p < strlen(dir); p++)
                    {
                        pastarray[pastind][ind1++] = dir[p];
                    }
                    pastarray[pastind][ind1] = '\0';
                    pastind++;
                    (*countpast)++;
                    if ((*countpast) >= 14)
                        (*countpast) = 14;
                    char cwd5[1024];
                    getcwd(cwd5, sizeof(cwd5));
                    if (chdir(home) != 0)
                    {
                    }
                    FILE *f = fopen("past.txt", "w");
                    if (f != NULL)
                    {
                        int countind = 0;
                        if ((*countpast) < 14)
                            countind = pastind;
                        else
                            countind = 15;
                        for (int c = 0; c < countind; c++)
                        {
                            fputs(pastarray[c], f);
                            fputs("\n", f);
                        }
                    }
                    fclose(f);
                    if (chdir(cwd5) != 0)
                    {
                    }
                }
                //}
            }
            else
            {
            }
        }
        else
        {
        }
        if (buf[j + 1] == ' ' || buf[j + 1] == '\n' || j == strlen(buf) - 1)
            i = j + 2;
        else
            i = j;
    }

    if (flagprompt == 2)
        return 2;
    return 1;
}
