#include "headers.h"
#include "A8.h"
int substr(char *s1, char *s2)
{
    int size1 = strlen(s1);
    int size2 = strlen(s2);

    for (int i = 0; i <= size2 - size1; i++)
    {
        int j;
        for (j = 0; j < size1; j++)
            if (s2[i + j] != s1[j])
                break;

        if (j == size1)
            return i;
    }

    return -1;
}

int search(char *target, char *folder, int flage, int flagf, int flagd, int tree, char *home, char *prev)
{
    static int flagfound = 0, flagfoundd = 0, flagfoundatall = 0;
    DIR *ph = opendir(folder);
    struct dirent *dh;
    if (!ph)
    {
        printf("\033[0;31m");
        perror("opendir");
        printf("\x1b[0m");
        return 1;
    }
    static char one[1024];
    static char dir[1024];
    while (dh = readdir(ph))
    {
        // printf("%s %s %s %d\n",folder,dh->d_name,target, tree);
        if (dh->d_name[0] != '.')
        {
            if (dh->d_type == 4)
            {
                char *str2 = (char *)malloc(sizeof(char) * strlen(folder));
                int indp = 0;
                for (int i = 0; i < strlen(folder); i++)
                    str2[indp++] = folder[i];
                str2[indp] = '\0';
                // char *str = folder;
                char *str = (char *)malloc(sizeof(char) * 1024);
                strcpy(str, folder);
                strcat(str, "/");
                strcat(str, dh->d_name);
                if (chdir(str) != 0)
                {   printf("\033[0;31m");
                     perror("lsh");
                     printf("x1b[0m");
                }
                int x = search(target, str, flage, flagf, flagd, tree + 1, home, str2);

                if (chdir(str2) != 0)
                {
                    printf("\033[0;31m");
                     perror("lsh");
                     printf("\x1b[0m");
                }
            }
            char *res = strstr(dh->d_name, target);
            int y = substr(target, dh->d_name);
            //printf("** %d %s %s\n",y,target,dh->d_name);
            if (y != -1)
            {
                if (flage >= 1)
                {
                    if (flagf >= 1 && dh->d_type == 8)
                    {
                        flagfound++;
                        flagfoundatall = 1;
                        int ind = 0;
                        char cwdo[1024];
                        getcwd(cwdo, sizeof(cwdo));
                        // printf("%s ",cwdo);
                        for (int i = 0; i < strlen(cwdo); i++)
                            one[ind++] = cwdo[i];
                        one[ind++] = '/';
                        for (int i = 0; i < strlen(dh->d_name); i++)
                            one[ind++] = dh->d_name[i];
                        one[ind] = '\0';
                    }
                    if (flagd >= 1 && dh->d_type == 4)
                    {
                        flagfoundd++;
                        flagfoundatall = 1;
                        int ind = 0;
                        char cwdt[1024];
                        getcwd(cwdt, sizeof(cwdt));

                        for (int i = 0; i < strlen(dir); i++)
                            dir[i] = '\0';
                        strcpy(dir, cwdt);
                        strcat(dir, "/");
                        strcat(dir, dh->d_name);
                    }
                    else if (flagf == 0 && flagd == 0)
                    {
                        if (dh->d_type == 4)
                        {
                            flagfoundd++;
                            flagfoundatall = 1;
                            int ind = 0;
                            char cwdt[1024];
                            getcwd(cwdt, sizeof(cwdt));

                            for (int i = 0; i < strlen(dir); i++)
                                dir[i] = '\0';
                            strcpy(dir, cwdt);
                            strcat(dir, "/");
                            strcat(dir, dh->d_name);
                        }
                        if (dh->d_type == 8)
                        {
                            flagfound++;
                            flagfoundatall = 1;
                            int ind = 0;
                            char cwdo[1024];
                            getcwd(cwdo, sizeof(cwdo));
                            // printf("%s ",cwdo);
                            for (int i = 0; i < strlen(cwdo); i++)
                                one[ind++] = cwdo[i];
                            one[ind++] = '/';
                            for (int i = 0; i < strlen(dh->d_name); i++)
                                one[ind++] = dh->d_name[i];
                            one[ind] = '\0';
                        }
                    }
                }
                else if (flagf >= 1 && dh->d_type == 8)
                {
                    if (strcmp(prev, home) == 0)
                    {
                        printf("\x1b[32m ./%s\n \x1b[0m", dh->d_name);
                    }
                    else
                    {
                        int index = 0;
                        for (int cw = 0; cw < strlen(prev); cw++)
                        {
                            if (prev[cw] != home[cw])
                            {
                                index = cw + 1;
                                break;
                            }
                        }
                        char path[1024];
                        int pathind = 0;
                        for (int ind = index; ind < strlen(prev); ind++)
                        {
                            path[pathind++] = prev[ind];
                        }
                        path[pathind] = '\0';
                        printf("\x1b[32m ./%s/%s\n \x1b[0m", path, dh->d_name);
                    }
                    flagfoundatall = 1;
                    flagfound = 1;
                }
                else if (flagd >= 1 && dh->d_type == 4)
                {
                    if (strcmp(prev, home) == 0)
                    {
                        printf("\033[0;34m ./%s\n \x1b[0m", dh->d_name);
                    }
                    else
                    {
                        int index = 0;
                        for (int cw = 0; cw < strlen(prev); cw++)
                        {
                            if (prev[cw] != home[cw])
                            {
                                index = cw + 1;
                                break;
                            }
                        }
                        char path[1024];
                        int pathind = 0;
                        for (int ind = index; ind < strlen(prev); ind++)
                        {
                            path[pathind++] = prev[ind];
                        }
                        path[pathind] = '\0';
                        printf("\033[0;34m ./%s/%s\n \x1b[0m", path, dh->d_name);
                    }
                    flagfoundatall = 1;
                    flagfoundd = 1;
                }
                else if (flage == 0 && flagf == 0 && flagd == 0)
                {
                    flagfoundatall = 1;
                    flagfound = 1;
                    flagfoundd = 1;
                    if (dh->d_type == 4)
                    {
                        if (strcmp(prev, home) == 0)
                        {
                            printf("\033[0;34m ./%s\n \x1b[0m", dh->d_name);
                        }
                        else
                        {
                            int index = 0;
                            char cwdp[1024];
                            getcwd(cwdp, sizeof(cwdp));
                            for (int cw = 0; cw < strlen(cwdp); cw++)
                            {
                                if (cwdp[cw] != home[cw])
                                {
                                    index = cw + 1;
                                    break;
                                }
                            }
                            char path[1024];
                            int pathind = 0;
                            for (int ind = index; ind < strlen(cwdp); ind++)
                            {
                                path[pathind++] = cwdp[ind];
                            }
                            path[pathind] = '\0';
                            if (strcmp(path, " ") != 0 && path && strcmp(path, "") != 0)
                                printf("\033[0;34m ./%s/%s\n \x1b[0m", path, dh->d_name);
                            else
                                printf("\033[0;34m ./%s\n \x1b[0m", dh->d_name);
                        }
                    }
                    else if (dh->d_type == 8)
                    {
                        if (strcmp(prev, home) == 0)
                        {
                            printf("\x1b[32m ./%s\n \x1b[0m", dh->d_name);
                        }
                        else
                        {
                            char cwdp[1024];
                            getcwd(cwdp, sizeof(cwdp));
                            int index = 0;
                            for (int cw = 0; cw < strlen(cwdp); cw++)
                            {
                                if (cwdp[cw] != home[cw])
                                {
                                    index = cw + 1;
                                    break;
                                }
                            }
                            char path[1024];
                            int pathind = 0;
                            for (int ind = index; ind < strlen(cwdp); ind++)
                            {
                                path[pathind++] = cwdp[ind];
                            }
                            path[pathind] = '\0';
                            printf("\x1b[32m ./%s/%s\n \x1b[0m", path, dh->d_name);
                        }
                    }
                    else
                        printf("%s\n", dh->d_name);
                }
            }
        }
    }
    closedir(ph);
    // printf("%d %d %d %d %d %d\n", flagfoundatall, flagd, flagfoundd, flagf, flagfound, tree);
    if (flagfound == 1 && flage == 1 && tree == 0)
    {
        if (flage == 1 && flagf == 1 && access(one, 04) != -1)
        {
            int dif = 0;
            for (int f = 0; f < strlen(one); f++)
            {
                if (one[f] != home[f])
                {
                    dif = f;
                    break;
                }
            }
            char *one2 = (char *)malloc(sizeof(char) * strlen(one));
            int ind = 0;
            one2[0] = '.';
            for (int f = dif; f < strlen(one); f++)
                one2[ind++] = one[f];
            one2[ind] = '\0';
            printf("\x1b[32m .%s\n \x1b[0m", one2);

            char ch;
            FILE *f = fopen(one, "r");
            while (!feof(f))
            {
                ch = fgetc(f);
                printf("%c", ch);
            }
            fclose(f);
            printf("\n");
            chdir(home);
            flagfound = 0;
            flagfoundatall = 0;
            flagfoundd = 0;
            for (int i = 0; i < strlen(dir); i++)
                dir[i] = '\0';
            for (int i = 0; i < strlen(one); i++)
                one[i] = '\0';
            return 1;
        }
        else if (flage == 1 && tree == 0)
        {
            chdir(home);
            printf("Missing permissions for task!\n");
            flagfound = 0;
            flagfoundatall = 0;
            flagfoundd = 0;
            for (int i = 0; i < strlen(dir); i++)
                dir[i] = '\0';
            for (int i = 0; i < strlen(one); i++)
                one[i] = '\0';
            return 1;
        }
        else if (flage == 1 && flagf == 0 && flagd == 0)
        {
            if (flage == 1 && access(one, 04) != -1)
            {
                int dif = 0;
                for (int f = 0; f < strlen(one); f++)
                {
                    if (one[f] != home[f])
                    {
                        dif = f;
                        break;
                    }
                }
                char *one2 = (char *)malloc(sizeof(char) * strlen(one));
                int ind = 0;
                one2[0] = '.';
                for (int f = dif; f < strlen(one); f++)
                    one2[ind++] = one[f];
                one2[ind] = '\0';
                printf("\x1b[32m .%s\n \x1b[0m", one2);

                char ch;
                FILE *f = fopen(one, "r");
                while (!feof(f))
                {
                    ch = fgetc(f);
                    printf("%c", ch);
                }
                fclose(f);
                printf("\n");
                chdir(home);
                flagfound = 0;
                flagfoundatall = 0;
                flagfoundd = 0;
                for (int i = 0; i < strlen(dir); i++)
                    dir[i] = '\0';
                for (int i = 0; i < strlen(one); i++)
                    one[i] = '\0';
                return 1;
            }
            else if (flage == 1 && tree == 0 && access(one, 04) == -1)
            {
                chdir(home);
                printf("Missing permissions for task!\n");
                flagfound = 0;
                flagfoundatall = 0;
                flagfoundd = 0;
                for (int i = 0; i < strlen(dir); i++)
                    dir[i] = '\0';
                for (int i = 0; i < strlen(one); i++)
                    one[i] = '\0';
                return 1;
            }
        }
    }
    if (flagfoundd == 1 && flage == 1 && tree == 0)
    {
        // printf("**%s %s %s\n", folder, target, dir);
        if (flage == 1 && flagd == 1 && access(dir, 01) != -1 && tree == 0)
        {
            int dif = 0;
            for (int f = 0; f < strlen(dir); f++)
            {
                if (dir[f] != home[f])
                {
                    dif = f;
                    break;
                }
            }
            char *dir2 = (char *)malloc(sizeof(char) * strlen(dir));
            int ind = 0;
            dir2[0] = '.';
            for (int f = dif; f < strlen(dir); f++)
                dir2[ind++] = dir[f];
            dir2[ind] = '\0';
            printf("\033[0;34m .%s\n \x1b[0m", dir2);
            if (chdir(dir) != 0)
            {
                printf("\033[0;31m");
                 perror("lsh");
                 printf("\x1b[0m");
            }
            flagfound = 0;
            flagfoundatall = 0;
            flagfoundd = 0;
            for (int i = 0; i < strlen(dir); i++)
                dir[i] = '\0';
            for (int i = 0; i < strlen(one); i++)
                one[i] = '\0';
            return 1;
        }
        else if (flage == 1 && flagd == 1 && access(dir, 01) == -1 && tree == 0)
        {

            printf("Missing permissions for task!\n");
            flagfound = 0;
            flagfoundatall = 0;
            flagfoundd = 0;
            for (int i = 0; i < strlen(dir); i++)
                dir[i] = '\0';
            for (int i = 0; i < strlen(one); i++)
                one[i] = '\0';
            return 1;
        }
        else if (flage == 1 && flagf == 0 && flagd == 0)
        {
            if (flage == 1 && access(dir, 01) != -1 && tree == 0)
            {
                int dif = 0;
                for (int f = 0; f < strlen(dir); f++)
                {
                    if (dir[f] != home[f])
                    {
                        dif = f;
                        break;
                    }
                }
                char *dir2 = (char *)malloc(sizeof(char) * strlen(dir));
                int ind = 0;
                dir2[0] = '.';
                for (int f = dif; f < strlen(dir); f++)
                    dir2[ind++] = dir[f];
                dir2[ind] = '\0';
                printf("\033[0;34m .%s\n \x1b[0m", dir2);
                if (chdir(dir) != 0)
                {
                    printf("\033[0;31m");
                     perror("lsh");
                     printf("\x1b[0m");
                }
                flagfound = 0;
                flagfoundatall = 0;
                flagfoundd = 0;
                for (int i = 0; i < strlen(dir); i++)
                    dir[i] = '\0';
                for (int i = 0; i < strlen(one); i++)
                    one[i] = '\0';
                return 1;
            }
            else if (flage == 1 && access(dir, 01) == -1 && tree == 0)
            {

                printf("Missing permissions for task!\n");
                flagfound = 0;
                flagfoundatall = 0;
                flagfoundd = 0;
                for (int i = 0; i < strlen(dir); i++)
                    dir[i] = '\0';
                for (int i = 0; i < strlen(one); i++)
                    one[i] = '\0';
                return 1;
            }
        }
    }
    if (tree == 0 && flage >= 1 && (((flagd >= 1 && flagfoundd > 1) || (flagf >= 1 && flagfound > 1)) || ( flagf==0 && flagd==0 && (flagfoundd>1 || flagfound>1))))
    {
        // printf("*****%s %s %s %s\n ******",target,folder,home,prev);
        int x = search(target, folder, 0, flagf, flagd, 0, home, prev);
        flagfound = 0;
        flagfoundatall = 0;
        flagfoundd = 0;
        for (int i = 0; i < strlen(dir); i++)
            dir[i] = '\0';
        for (int i = 0; i < strlen(one); i++)
            one[i] = '\0';
        return 1;
    }
    // printf("%d %d %d %d %d %d\n", flagfoundatall, flagd, flagfoundd, flagf, flagfound, tree);
    if (flagfoundatall == 0 && tree == 0)
    {
        printf("\033[0;31m");
        printf("No match found!\n");
        printf("\x1b[0m");
        chdir(home);
        flagfound = 0;
        flagfoundatall = 0;
        flagfoundd = 0;
        for (int i = 0; i < strlen(dir); i++)
            dir[i] = '\0';
        for (int i = 0; i < strlen(one); i++)
            one[i] = '\0';
        return 0;
    }
    if (flagfoundatall == 1 && tree == 0 && ((flagfoundd == 0 && flagd == 1) || (flagfound == 0 && flagf == 1)))
    {
        printf("\033[0;31m");
        printf("No match found!\n");
        printf("\x1b[0m");
        chdir(home);
        flagfound = 0;
        flagfoundatall = 0;
        flagfoundd = 0;
        for (int i = 0; i < strlen(dir); i++)
            dir[i] = '\0';
        for (int i = 0; i < strlen(one); i++)
            one[i] = '\0';
        return 0;
    }
    if (tree == 0)
    {
        if (flage == 1 && flagd == 0)
            chdir(home);
        else if (flage == 0)
            chdir(home);
        flagfound = 0;
        flagfoundatall = 0;
        flagfoundd = 0;
        for (int i = 0; i < strlen(dir); i++)
            dir[i] = '\0';
        for (int i = 0; i < strlen(one); i++)
            one[i] = '\0';
        return 1;
    }
    return 1;
}

int seek(char *buf, char *home)
{
    int flage = 0, flagf = 0, flagd = 0;
    int i = 5;
    int lastdash = 2;
    for (i = 5; i < strlen(buf) - 2; i++)
    {
        if (buf[i] == '-')
        {
            lastdash = i;
            if (buf[i + 1] == 'd' && (i+2==strlen(buf)-1 || buf[i+2]==' '))
            {
                flagd++;
            }
            else if (buf[i + 1] == 'e'  && (i+2==strlen(buf)-1 || buf[i+2]==' ') )
                flage++;
            else if (buf[i + 1] == 'f'  && (i+2==strlen(buf)-1 || buf[i+2]==' '))
                flagf++;
            else if (i + 1 == strlen(buf) - 2 || (buf[i + 1] != 'd' && buf[i+1]!='e' && buf[i+1]!='f'))
                {
                    printf("\033[0;31m");
                    printf("No such file or directory\n");
                    printf("\x1b[0m");
                    return 0;}
        }
    }
    if (flagd > 0 && flagf > 0)
    {
        printf("Invalid flags!\n");
        return 0;
    }
    i = lastdash + 3;
    char *target = (char *)malloc(sizeof(char) * strlen(buf));
    char *folder = (char *)malloc(sizeof(char) * 1024);
    char *prev = (char *)malloc(sizeof(char) * 1024);
    getcwd(prev, sizeof(prev));
    folder[0] = '-';
    folder[1] = '\0';
    int ind = 0, j, ind2 = 0;
    for (j = i; j < strlen(buf) && buf[j] != ' ' &&  buf[j]!='\n'; j++)
    {
        target[ind++] = buf[j];
    }
    target[ind] = '\0';
    i = j + 1;
    //printf("%d %d",i,strlen(buf));
    if (i < strlen(buf) )
    {
        if (buf[i] == '.' && buf[i + 1] != '/')
        {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            int indc = 0;
            for (int k = 0; k < strlen(cwd); k++)
                folder[indc++] = cwd[k];
            folder[indc] = '\0';
            // printf("%s", folder);
        }
        else if (buf[i] == '.' && buf[i + 1] == '/')
        {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            int indc = 0;
            for (int k = 0; k < strlen(cwd); k++)
                folder[indc++] = cwd[k];
            i = i + 2;
            folder[indc++] = '/';
            while (i < strlen(buf) - 1)
            {
                folder[indc++] = buf[i++];
            }
            folder[indc] = '\0';
        }
        else if (buf[i] == '~')
        {
            int indc = 0;
            for (int k = 0; k < strlen(home); k++)
                folder[indc++] = home[k];
            folder[indc] = '\0';
            // printf("%s", folder);
        }
        else if (buf[i] == '/')
        {
            int indc = 0;
            folder[indc++]='a';
            for (int k = i+1; k < strlen(buf)-1; k++)
                folder[indc++] = buf[k];
            folder[indc] = '\0';
             printf("%s", folder);
            folder[0]='/';
             printf("%s", folder);
        }
        else
        {
            //i = i + 2;
            while (i < strlen(buf))
            {
                folder[ind2++] = buf[i++];
            }
            folder[ind2] = '\0';
        }
    }
    else if (i >= strlen(buf) - 1)
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        int indc = 0;
        for (int k = 0; k < strlen(cwd); k++)
            folder[indc++] = cwd[k];
        folder[indc] = '\0';
    }
    // printf("%s**",folder);
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    int x = search(target, folder, flage, flagf, flagd, 0, cwd, folder);

    return 1;
}