#include "headers.h"
#include "A5.h"
int pastev(char *buf, char **pastarray, int *countpast, char *home, char *prev, int pastind,int* exec_time,char* prompttime)
{
    int ret = 0;
    if (buf[11] == 'p')
        return 2;
    if (buf[11] == 'e')
    {

        int ind = 0;
        char com[8];
        for (int i = 11; i < 18; i++)
            com[ind++] = buf[i];
        com[7] = '\0';
        char exec[8] = "execute";
        exec[7] = '\0';
        int flageq = 1;
        for (int i = 0; i < 7; i++)
        {
            if (com[i] != exec[i])
            {
                // printf("%d %c %c", i, com[i], exec[i]);
                flageq = 0;
                break;
            }
        }
        if (flageq == 1)
        {
            if (isdigit(buf[19]))
            {
                int x = buf[19] - '0';
                if ((*countpast) == -1 || x > (*countpast) + 1 || x < 1)
                {
                    printf("\033[0;31m");
                    printf("ERROR: \'%s\' is not a valid command/n", buf);
                    printf("\x1b[0m");
                    return 0;
                }
                char *buf2 = (char *)malloc(sizeof(char) * 1024);
                int ind = 0;
                for (int q = 0; q < strlen(pastarray[(*countpast) - x + 1]); q++)
                {
                    if(pastarray[(*countpast) - x + 1][q]!='\n' && pastarray[(*countpast) - x + 1][q]!='\0')
                    buf2[ind++] = pastarray[(*countpast) - x + 1][q];
                }
                buf2[ind] = '\0';
                int flagsemi = 0, flagand = 0;
                for (int k = 0; k < strlen(buf2); k++)
                {
                    if (buf2[k] == '&')
                        flagand = 1;
                    if (buf2[k] == ';')
                        flagsemi = 1;
                }
                // printf("%d",flagand);
                int y = 0;
                if (flagsemi == 1 || flagand == 1)
                {
                    y = back(buf2, flagsemi, flagand, home, pastarray, &(*countpast), prev, pastind,&(*exec_time),prompttime);
                }
                if (y == 2 || y == 3)
                    ret = -1;

                int background = 0;
                if (flagsemi == 0 && flagand == 0)
                {
                    if (strlen(buf2) < 3)
                    {

                        int x = specsix(buf2, home,&(*exec_time),prompttime);
                        if (x == 2)
                            ret = -1;
                    }
                    char com[5];
                    for (int i = 0; i < 4; i++)
                        com[i] = buf2[i];
                    com[4] = '\0';
                    char com2[11];
                    if (strlen(buf2) >= 10)
                    {
                        for (int i = 0; i < 10; i++)
                            com2[i] = buf2[i];
                        com2[10] = '\0';
                    }
                    else
                        com2[0] = '\0';
                    char com3[9];
                    if (strlen(buf2) >= 8)
                    {
                        for (int i = 0; i < 9; i++)
                            com3[i] = buf2[i];
                    }
                    else
                        com3[0] = '\0';
                    com3[8] = '\0';
                    int iserror = 1;
                    if (strcmp(com, "warp") == 0)
                    {
                        int x = warp(buf2, home, prev);
                    }
                    else if (strcmp(com, "peek") == 0)
                    {
                        int x = peek(buf2, home, prev);
                        if (x == 0)
                            iserror = 0;
                    }
                    else if (strcmp(com, "seek") == 0)
                    {
                        int x = seek(buf2, home);
                        if (x == 0)
                            iserror = 0;
                    }
                    else if (strcmp(com3, "proclore") == 0)
                    {
                        int x = proc(buf2);
                        if (x == 0)
                            iserror = 0;
                    }
                    else
                    {
                        int x = specsix(buf2, home,&(*exec_time),prompttime);
                        if (x == 0)
                            iserror = 0;
                        if (x == 2)
                            ret = -1;
                    }
                    //if (iserror == 1)
                    //{
                        char comc[11];
                        for (int i = 0; i < 10; i++)
                            comc[i] = buf2[i];
                        comc[10] = '\0';
                        if (strcmp(comc, "pastevents") != 0)
                        {
                            int ind1 = 0;
                            int flageq = 1;
                            if ((pastind == 0 && (*countpast) == 14))
                            {
                                if ((strlen(buf2) - 1) != strlen(pastarray[14]) || strlen(buf2) - 1 != strlen(pastarray[pastind - 1]))
                                    flageq = 0;
                            }
                            else if (pastind == 0 && (*countpast) < 14)
                            {
                                flageq = 0;
                            }
                            else
                            {
                                for (int i = 0; i < strlen(buf2) - 1; i++)
                                {
                                    if (pastind == 0)
                                    {
                                        if (buf2[i] != pastarray[14][i])
                                        {
                                            flageq = 0;
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        if (buf2[i] != pastarray[pastind - 1][i])
                                        {
                                            // printf("%d %c %c", i, buf[i], pastarray[pastind - 1][i]);
                                            flageq = 0;
                                            break;
                                        }
                                    }
                                }
                            }
                            if (flageq == 0 && buf2!=NULL)
                            {
                                if (pastind >= 15)
                                    pastind = 0;
                                for (int p = 0; p < strlen(buf2); p++)
                                {
                                    if (buf2[p] != '\n')
                                        pastarray[pastind][ind1++] = buf2[p];
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
                                    int c;
                                    for (c = 0; c < countind - 1; c++)
                                    {
                                        fputs(pastarray[c], f);
                                        fputs("\n", f);
                                    }
                                    fputs(pastarray[c], f);
                                    fclose(f);
                                }
                                if (chdir(cwd5) != 0)
                                {
                                }
                            }
                        }
                    //}
                    /*if(iserror==0)
                    {
                        printf("\033[0;31m");
                        printf("ERROR: /'%s/' is not a valid command/n", buf);
                        printf("\x1b[0m");
                        if (ret == -1)
                            return 5;
                        return 0;
                    }*/
                }
                if (ret == -1)
                    return 5;
                return 1;
            }
            else
            {
                printf("\033[0;31m");
                printf("ERROR: /'%s/' is not a valid command/n", buf);
                printf("\x1b[0m");
                if (ret == -1)
                    return 5;
                return 0;
            }
        }
    }
    else
    {
        int i = 0;
        // printf("%d",(*countpast));
        while (i <= (*countpast))
        {
            printf("%s\n", pastarray[i]);
            i++;
        }
        return 1;
    }
}