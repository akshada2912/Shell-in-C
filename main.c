#include "headers.h"
#include "prompt.h"
#include "A2.h"
#include "A3.h"
#include "A4.h"
#include "A5.h"
#include "A6.h"
#include "A7.h"
#include "A8.h"

int bgcount=0;

int main()
{
    int exec_time = 0;
    char *prompttime = (char *)malloc(sizeof(char));
    int promptbgornot = 0;
    char **pastarray = (char **)malloc(sizeof(char *) * 15);
    for (int i = 0; i < 15; i++)
    {
        pastarray[i] = (char *)malloc(sizeof(char) * 10000);
    }
    FILE *f = fopen("past.txt", "r");
    int read;
    int p = 0;
    if (f != NULL)
    {
        char buffer1[100000];
        while (fgets(buffer1, 10000, f))
        {
            // Remove trailing newline
            buffer1[strcspn(buffer1, "\n")] = 0;
            // pastarray[p++]=buffer;
            int indp = 0;
            for (int pp = 0; pp < strlen(buffer1); pp++)
                pastarray[p][indp++] = buffer1[pp];
            pastarray[p][indp] = '\0';
            p++;
        }
        fclose(f);
    }
    int countpast;
    if (p != 0)
        countpast = p - 1;
    else
        countpast = -1;
    char home[1024];
    getcwd(home, sizeof(home));
    char prev[1024] = "OLDPWD not set";
    int isprev = 0;
    prev[14] = '\0';
    char *buf = (char *)malloc(sizeof(char) * 1024);
    buf[0] = '\0';
    char *str = (char *)malloc(sizeof(char) * 1024);
    int pastind = p;
    while (1)
    {
        buf[0] = '\0';

        //  prompt normally unless specsix return 2, signifying fg process took >2s so will be printed in prompt
        if (promptbgornot == 0)
        {
            promptbgornot = 0;
            prompt(home, home, 0);
            fgets(buf, 1024, stdin);
            if ((int)buf[0] == 10)
                continue;
            else if (buf[0]=='\n')
            {
                continue;
            }
            if (strlen(buf) != 0)
            {
                strcpy(str, buf);
            }
        }
        else if (promptbgornot == 1)
        {
            fgets(buf, 1024, stdin);
            if ((int)buf[0] == 10)
                continue;
            else if(buf[0]=='\n')
            {
                continue;
            }
            
            if (strlen(buf) != 0)
            {
                strcpy(str, buf);
            }
            promptbgornot = 0;
            // continue;
        }
        
        promptbgornot = 0;
        int x = check_bgprocesses(0, home);
        if (x == 1)
        { // bg process has been printed
            //continue;
        }

        int flagsemi = 0, flagand = 0;
        for (int k = 0; k < strlen(buf); k++)
        {
            if (buf[k] == '&')
                flagand = 1;
            if (buf[k] == ';')
                flagsemi = 1;
        }
        int y = 0;
        if (flagsemi == 1 || flagand == 1)
        {
            y = back(buf, flagsemi, flagand, home, pastarray, &countpast, prev, pastind, &exec_time, prompttime);
        }

        if (y == 2 || y == 3)
        {
            prompt(home, prompttime, exec_time);
            promptbgornot = 1;
        }
        else
        {
            exec_time = 0;
            prompttime[0] = '\0';
        }

        int background = 0;
        if (flagsemi == 0 && flagand == 0)
        {
            if (strlen(buf) < 3)
            {
                // strings like ls
                int x = specsix(buf, home, &exec_time, prompttime);
                char cmd[1024];
                int ind = 0;
                if (x == 2)
                {
                    prompt(home, prompttime, exec_time);
                    promptbgornot = 1;
                }
                else
                {
                    exec_time = 0;
                    prompttime[0] = '\0';
                    if (x == 1)
                        return 0;
                }
            }
            char com[5];
            for (int i = 0; i < 4; i++)
                com[i] = buf[i];
            com[4] = '\0';
            char com2[11];
            if (strlen(buf) >= 10)
            {
                for (int i = 0; i < 10; i++)
                    com2[i] = buf[i];
                com2[10] = '\0';
            }
            else
                com2[0] = '\0';
            char com3[9];
            if (strlen(buf) >= 9)
            {
                for (int i = 0; i < 9; i++)
                    com3[i] = buf[i];
            }
            else
                com3[0] = '\0';
            com3[8] = '\0';
            int iserror = 1;
            if (strcmp(com, "warp") == 0)
            {
                //printf("HIHI");
                char cwd2[1024];
                getcwd(cwd2, sizeof(cwd2));
                if (buf[5] != '-')
                {
                    // setting previous dir
                    int ind = 0;
                    for (int i = 0; i < strlen(cwd2); i++)
                        prev[ind++] = cwd2[i];
                    prev[ind] = '\0';
                }
                int x = warp(buf, home, prev);
            }
            else if (strcmp(com, "peek") == 0)
            {
                int x = peek(buf, home, prev);
                if (x == 0)
                    iserror = 0;
            }
            else if (strcmp(com, "seek") == 0)
            {
                int x = seek(buf, home);
                if (x == 0)
                    iserror = 0;
            }
            else if (strcmp(com2, "pastevents") == 0)
            {
                int x = pastev(buf, pastarray, &countpast, home, prev, pastind, &exec_time, prompttime);
                // specsix returned 2 ie prompt was printed
                if (x == 5)
                {
                    prompt(home, prompttime, exec_time);
                    promptbgornot = 1;
                }
                else
                {
                    exec_time = 0;
                    prompttime[0] = '\0';
                }
                char com3[6];
                int indc = 0;
                if (x == 2)
                {
                    for (int c = 11; c < 16; c++)
                        com3[indc++] = buf[c];
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
                    // if command is not equal to last command in pastarray
                    if (flageq == 1)
                    {
                        countpast = -1;
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
                int x = proc(buf);
                if (x == 0)
                    iserror = 0;
            }
            else
            {

                int x = specsix(buf, home, &exec_time, prompttime);
                char cmd[1024];
                int ind = 0;
                if (x == 2)
                {
                    prompt(home, prompttime, exec_time);
                    promptbgornot = 1;
                }
                else
                {
                    exec_time = 0;
                    prompttime[0] = '\0';
                    if (x == 0)
                        iserror = 0;
                    if (x == -1)
                        return 0;
                }
            }
           // if (iserror == 1)
            //{
                char comc[11];
                for (int i = 0; i < 10; i++)
                    comc[i] = buf[i];
                comc[10] = '\0';
                if (strcmp(comc, "pastevents") != 0)
                {
                    int ind1 = 0;
                    int flageq = 1;

                    if ((pastind == 0 && countpast == 14))
                    {
                        if ((strlen(buf) - 1) != strlen(pastarray[14]) || strlen(buf) - 1 != strlen(pastarray[pastind - 1]))
                            flageq = 0;
                    }
                    else if (pastind == 0 && countpast < 14)
                    {
                        flageq = 0;
                    }
                    else
                    {
                        for (int i = 0; i < strlen(buf) - 1; i++)
                        {
                            if (pastind == 0)
                            {
                                if (buf[i] != pastarray[14][i])
                                {
                                    flageq = 0;
                                    break;
                                }
                            }
                            else
                            {
                                if (buf[i] != pastarray[pastind - 1][i])
                                {
                                    flageq = 0;
                                    break;
                                }
                            }
                        }
                    }
                    // if command is not equal to last command in pastarray
                    if (flageq == 0)
                    {
                        if (pastind >= 15)
                            pastind = 0;

                        for (int p = 0; p < strlen(buf); p++)
                        {
                            if (buf[p] != '\n')
                                pastarray[pastind][ind1++] = buf[p];
                        }
                        pastarray[pastind][ind1] = '\0';
                        pastind++;
                        countpast++;
                        if (countpast >= 14)
                            countpast = 14;
                        char cwd5[1024];
                        getcwd(cwd5, sizeof(cwd5));
                        if (chdir(home) != 0)
                        {
                        }
                        FILE *f = fopen("past.txt", "w");
                        if (f != NULL)
                        {
                            int countind = 0;
                            if (countpast < 14)
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
            else
            {
            }
        }
        buf[0] = '\0';
    }
    return 0;
}
