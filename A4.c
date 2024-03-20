#include "headers.h"
#include "A4_print.c"
#include "A4_ls.c"
int compare1(const void *str1, const void *str2)
{
    char *const *pp1 = str1;
    char *const *pp2 = str2;
    return strcmp(*pp1, *pp2);
}

int peek(char *buf, char *home, char *prev)
{
    int i = 5;
    int untilletter = i;
    int flag = 0;
    int k;
    //finding first non space/tabspace character
    for (k = untilletter; k < strlen(buf); k++)
    {
        if (buf[k] != ' ' && (int)buf[k] != 9)
        {
            flag = 1;
            untilletter = k;
            break;
        }
    }
    i = untilletter;

    if (flag == 1 && untilletter == i)
        i = k;
    if (i >= strlen(buf) - 2)
    {
        if (buf[i] != '-')
        {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            lsimp(cwd);
        }
        else if (buf[i] == '-' && (i + 1 == strlen(buf) - 1 || buf[i + 1] == ' '))
        {
            printf("\033[0;31m");
            printf("No such file or directory\n");
            printf("\x1b[0m");
            return 0;
        }
        else
            return 0;
    }
    int flaga = 0, flagl = 0, flagal = 0, flagla = 0;
    char first = 'z';
    for (int j = i; j < strlen(buf) - 2; j++)
    {
        if (buf[j] == '-')
        {
            if (buf[j + 1] == ' ' || j + 1 == strlen(buf) - 1)
            {
                printf("\033[0;31m");
                printf("lsh: No such file or directory\n");
                printf("\x1b[0m");
                return 0;
            }
            if (first == 'z')
                first = buf[j + 1];

            if (buf[j + 1] == 'a' && buf[j + 2] == 'l' &&(buf[j+3]=='\0' || buf[j+3]=='\n' || buf[j+3]==' '))
            {
                flagal = 1;
            }
            else if (buf[j + 1] == 'l' && buf[j + 2] == 'a' &&(buf[j+3]=='\0' || buf[j+3]=='\n' || buf[j+3]==' '))
                flagla = 1;
            else if (buf[j + 1] == 'a' && (buf[j + 2] == ' ' || buf[j+2]=='\n' || buf[j+2]=='\0' || j + 2 == strlen(buf) - 1))
                flaga = 1;
            else if (buf[j + 1] == 'l' && (buf[j + 2] == ' '  | buf[j+2]=='\n' || buf[j+2]=='\0'|| j + 2 == strlen(buf) - 1))
                flagl = 1;
            else
            {
                printf("\033[0;31m");
                printf("lsh: No such file or directory\n");
                printf("\x1b[0m");
                return 0;
            }
        }
    }
    
    int lastdash = 0;
    for (int j = 0; j < strlen(buf); j++)
    {
        if (buf[j] == '-')
            lastdash = j;
    }
    
    char *dir = (char *)malloc(sizeof(char) *1024);
    int ind = 0;
    
    if (buf[lastdash + 3] == '~' && buf[lastdash+4]=='/')
    {
        char cwdc[1024];
        getcwd(cwdc,sizeof(cwdc));

        for (int i = lastdash + 3; i < strlen(buf) ; i++)
            dir[ind++] = buf[i];
        dir[ind] = '\0';
        if(chdir(dir)!=0)
        {

        }
        char cwdc2[1024];
        getcwd(cwdc2,sizeof(cwdc2));
        for(int i=0;i<strlen(dir);i++)
        dir[i]='\0';
        for (int i =0; i < strlen(cwdc2) ; i++)
            dir[ind++] = buf[i];
        dir[ind] = '\0';
        if(chdir(cwdc)!=0)
        {

        }
    }
    else if(buf[lastdash+3]=='.'&&lastdash+5<strlen(buf)-1&&buf[lastdash+4]=='/'&&buf[lastdash+5]<='z'&&buf[lastdash+5]>='a')
    {
        for (int i = lastdash + 5; i < strlen(buf) ; i++)
            dir[ind++] = buf[i];
        dir[ind] = '\0';
    }
    else
    {
        for (int i = lastdash + 3; i < strlen(buf) ; i++)
            dir[ind++] = buf[i];
        dir[ind] = '\0';
    }
    int flagcwd = 0, flaghome = 0, flagprev = 0, flagout = 0;
    if (lastdash == 0)
    {
        for (int j = 0; j < strlen(buf) ; j++)
        {
            if (buf[j] == '~' && j + 1 < strlen(buf) && buf[j + 1] == '/')
                flaghome = 1;
        }
        if (buf[i] == '.' && i + 1 < strlen(buf)  && buf[i + 1] != '.')
            flagcwd = 1;
        if (buf[i] == '.' && i + 1 < strlen(buf) && buf[i + 1] == '.')
            flagout = 1;
    }
    else
    {
        if (buf[lastdash + 3] == '~' && buf[lastdash + 4] != '/')
        {
            flaghome = 1;
        }
        if (buf[lastdash + 3] == '.' && buf[lastdash + 4] != '.' && buf[lastdash+4]!='/')
            flagcwd = 1;
        if (buf[lastdash + 3] == '.' && buf[lastdash + 4] == '.')
            flagout = 1;
        else if (lastdash + 1 == strlen(buf) - 2)
            flagcwd = 1;
        else if (lastdash + 1 == strlen(buf) - 3 && ((buf[lastdash + 1] == 'l' || buf[lastdash + 1] == 'a') || (buf[lastdash + 1] == 'a' || buf[lastdash + 1] == 'l')))
            flagcwd = 1;
    }
    char **array = (char **)malloc(sizeof(char *) * 10000);
    for (int i = 0; i < 10000; i++)
        array[i] = (char *)malloc(sizeof(char) * 1024);
    int arrind = 0;
    if (flaga == 1 && flagl == 0)
        first = 'z';
    if (flaga == 0 && flagl == 1)
        first = 'z';

    if (flagcwd == 1)
    {
        char cwd2[1024];
        getcwd(cwd2, sizeof(cwd2));
        int lastslash = 0;
        // getting index of last backslash
        for (int j = 0; j < strlen(cwd2) ; j++)
        {
            if (cwd2[j] == '/')
                lastslash = j;
        }
        ind = 0;
        
        for (int j = 0; j < lastslash; j++)
        {
            dir[ind++] = cwd2[j];
        }

        dir[ind] = '\0';
    }
    if(lastdash==0 && buf[5]!='~')
    {
        int ind=0;
        for (int j = 5; j < strlen(buf-1); j++)
        {
            dir[ind++] = buf[j];
        }
        dir[ind]='\0';

    }
    if(lastdash==0 && buf[5]=='~' && buf[6]=='/')
    {
        char cwdc[1024];
        getcwd(cwdc,sizeof(cwdc));
        
        for (int i = 7; i < strlen(buf) ; i++)
            dir[ind++] = buf[i];
        dir[ind] = '\0';
        char* res=(char*)malloc(sizeof(char)*1024);
        char* result=realpath(dir,res);
        if(chdir(dir)!=0)
        {

        }
        char cwdc2[1024];
        getcwd(cwdc2,sizeof(cwdc2));
        for(int i=0;i<strlen(dir);i++)
        dir[i]='\0';
        for (int i =0; i < strlen(cwdc2) ; i++)
            dir[ind++] = buf[i];
        dir[ind] = '\0';
        if(chdir(cwdc)!=0)
        {

        }

    }
    else if(lastdash==0&&buf[5]=='.'&&7<strlen(buf)-1&&buf[6]=='/'&&buf[7]<='z'&&buf[7]>='a')
    {
        for (int i = 7; i < strlen(buf) ; i++)
            dir[ind++] = buf[i];
        dir[ind] = '\0';
    }
    if ((first == 'a' && flaga == 1 && flagl == 1))
    {
        DIR *p = opendir(dir);
        struct dirent *d;
        if (p == NULL || flagcwd == 1)
        {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            DIR *p3 = opendir(cwd);
            struct dirent *d3;
            while (d3 = readdir(p3))
            {
                strcpy(array[arrind], d3->d_name);
                arrind++;
            }
        }
        else if (flaghome == 1)
        {
            DIR *ph = opendir(home);
            struct dirent *dh;
            while (dh = readdir(ph))
            {
                strcpy(array[arrind], dh->d_name);
                arrind++;
            }
        }
        else if (flagprev == 1)
        {
            DIR *ph = opendir(prev);
            struct dirent *dh;
            while (dh = readdir(ph))
            {
                strcpy(array[arrind], dh->d_name);
                arrind++;
            }
        }
        else if (flagout == 1)
        {
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

            DIR *po = opendir(dir);
            struct dirent *du;
            while (du = readdir(po))
            {
                strcpy(array[arrind], du->d_name);
                arrind++;
            }
        }
        else
        {
            while (d = readdir(p))
            {
                strcpy(array[arrind], d->d_name);
                arrind++;
            }
        }

        qsort(array, arrind, sizeof(array), compare1);
        printa(array, arrind, first, flaga, flagl, flagal, flagla);
        printf("\n");
        if (flagcwd == 1)
        {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            lsimp(cwd);
        }
        else if (flaghome == 1)
        {
            lsimp(home);
        }
        else if (flagprev == 1)
        {
            lsimp(prev);
        }
        else if (flagout == 1)
        {
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

            lsimp(dir);
        }
        else
        {
            lsimp(dir);
        }
    }
    else if (flagal == 1)
    {
        int ind = 0;
        for (int k = lastdash + 4; k < strlen(buf) ; k++)
        {
            dir[ind++] = buf[k];
        }
        dir[ind] = '\0';
        DIR *p = opendir(dir);
        struct dirent *d;
        if (p == NULL || flagcwd == 1)
        {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            DIR *p3 = opendir(cwd);
            struct dirent *d3;
            while (d3 = readdir(p3))
            {
                strcpy(array[arrind], d3->d_name);
                arrind++;
            }
        }
        else if (flaghome == 1)
        {
            DIR *ph = opendir(home);
            struct dirent *dh;
            while (dh = readdir(ph))
            {
                strcpy(array[arrind], dh->d_name);
                arrind++;
            }
        }
        else if (flagprev == 1)
        {
            DIR *ph = opendir(prev);
            struct dirent *dh;
            while (dh = readdir(ph))
            {
                strcpy(array[arrind], dh->d_name);
                arrind++;
            }
        }
        else if (flagout == 1)
        {
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

            DIR *po = opendir(dir);
            struct dirent *du;
            while (du = readdir(po))
            {
                strcpy(array[arrind], du->d_name);
                arrind++;
            }
        }
        else
        {
            while (d = readdir(p))
            {
                strcpy(array[arrind], d->d_name);
                arrind++;
            }
        }

        qsort(array, arrind, sizeof(array), compare1);
        printa(array, arrind, first, flaga, flagl, flagal, flagla);
        printf("\n");

        if (flagcwd == 1)
        {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            lsimp(cwd);
        }
        else if (flaghome == 1)
        {
            lsimp(home);
        }
        else if (flagprev == 1)
        {
            lsimp(prev);
        }
        else if (flagout == 1)
        {
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

            lsimp(dir);
        }
        else
        {
            lsimp(dir);
        }
    }
    else if ((first == 'l' && flaga == 1 && flagl == 1))
    {

        if (flagcwd == 1)
        {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            lsimp(cwd);
        }
        else if (flaghome == 1)
        {
            lsimp(home);
        }
        else if (flagout == 1)
        {
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

            lsimp(dir);
        }
        else if (flagprev == 1)
        {
            lsimp(prev);
        }
        else
        {
            lsimp(dir);
        }

        int ind = 0;
        for (int k = lastdash + 4; k < strlen(buf) ; k++)
        {
            dir[ind++] = buf[k];
        }
        dir[ind] = '\0';
        DIR *p = opendir(dir);
        struct dirent *d;
        if (p == NULL || flagcwd == 1)
        {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            DIR *p3 = opendir(cwd);
            struct dirent *d3;
            while (d3 = readdir(p3))
            {
                strcpy(array[arrind], d3->d_name);
                arrind++;
            }
        }
        else if (flaghome == 1)
        {
            DIR *ph = opendir(home);
            struct dirent *dh;
            while (dh = readdir(ph))
            {
                strcpy(array[arrind], dh->d_name);
                arrind++;
            }
        }
        else if (flagprev == 1)
        {
            DIR *ph = opendir(prev);
            struct dirent *dh;
            while (dh = readdir(ph))
            {
                strcpy(array[arrind], dh->d_name);
                arrind++;
            }
        }
        else if (flagout == 1)
        {
            char cwd2[1024];
            getcwd(cwd2, sizeof(cwd2));
            int lastslash = 0;
            for (int j = 0; j < strlen(cwd2) ; j++)
            {
                if (cwd2[j] == '/')
                    lastslash = j;
            }
            int ind = 0;
            for (int j = 0; j < lastslash; j++)
                dir[ind++] = cwd2[j];
            dir[ind] = '\0';

            DIR *po = opendir(dir);
            struct dirent *du;
            while (du = readdir(po))
            {
                strcpy(array[arrind], du->d_name);
                arrind++;
            }
            // printf("%s\n", du->d_name);
        }
        else
        {
            while (d = readdir(p))
            {
                strcpy(array[arrind], d->d_name);
                arrind++;
            }
        }

        qsort(array, arrind, sizeof(array), compare1);
        printa(array, arrind, first, flaga, flagl, flagal, flagla);
    }
    else if (flagla == 1)
    {
        int ind = 0;
        for (int k = lastdash + 4; k < strlen(buf) ; k++)
        {
            dir[ind++] = buf[k];
        }
        dir[ind] = '\0';

        if (flagcwd == 1)
        {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            lsimp(cwd);
        }
        else if (flagprev == 1)
        {
            lsimp(prev);
        }
        else if (flagout == 1)
        {
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

            lsimp(dir);
        }
        else if (flaghome == 1)
        {
            lsimp(home);
        }
        else
        {
            lsimp(dir);
        }
        printf("\n");
        DIR *p2 = opendir(dir);
        struct dirent *d2;
        if (p2 == NULL || flagcwd == 1)
        {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            DIR *p3 = opendir(cwd);
            struct dirent *d3;
            while (d3 = readdir(p3))
            {
                strcpy(array[arrind], d3->d_name);
                arrind++;
            }
        }
        else if (flaghome == 1)
        {
            DIR *ph = opendir(home);
            struct dirent *dh;
            while (dh = readdir(ph))
            {
                strcpy(array[arrind], dh->d_name);
                arrind++;
            }
        }
        else if (flagout == 1)
        {
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

            DIR *po = opendir(dir);
            struct dirent *du;
            while (du = readdir(po))
            {
                strcpy(array[arrind], du->d_name);
                arrind++;
            }
        }
        else if (flagprev == 1)
        {
            DIR *ph = opendir(prev);
            struct dirent *dh;
            while (dh = readdir(ph))
            {
                strcpy(array[arrind], dh->d_name);
                arrind++;
            } // printf("%s\n", dh->d_name);
        }
        else
        {
            while (d2 = readdir(p2))
            {
                strcpy(array[arrind], d2->d_name);
                arrind++;
            } // printf("%s\n", d2->d_name);
        }

        qsort(array, arrind, sizeof(array), compare1);
        printa(array, arrind, first, flaga, flagl, flagal, flagla);
    }
    else if (flaga == 1 && flagl == 0)
    {
        DIR *p = opendir(dir);
        struct dirent *d;
        if (p == NULL || flagcwd == 1)
        {
            // printf("hi");
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            DIR *p3 = opendir(cwd);
            struct dirent *d3;
            while (d3 = readdir(p3))
            {
                strcpy(array[arrind], d3->d_name);
                arrind++;
            }
            // printf("%s\n", d3->d_name);
        }
        else if (flaghome == 1)
        {
            DIR *ph = opendir(home);
            struct dirent *dh;
            while (dh = readdir(ph))
            {
                strcpy(array[arrind], dh->d_name);
                arrind++;
            } // printf("%s\n", dh->d_name);
        }
        else if (flagout == 1)
        {
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

            DIR *po = opendir(dir);
            struct dirent *du;
            while (du = readdir(po))
            {
                strcpy(array[arrind], du->d_name);
                arrind++;
            } // printf("%s\n", du->d_name);
        }
        else if (flagprev == 1)
        {
            DIR *ph = opendir(prev);
            struct dirent *dh;
            while (dh = readdir(ph))
            {
                strcpy(array[arrind], dh->d_name);
                arrind++;
            } // printf("%s\n", dh->d_name);
        }
        else
        {
            while (d = readdir(p))
            {
                strcpy(array[arrind], d->d_name);
                arrind++;
            } // printf("%s\n", d->d_name);
        }

        qsort(array, arrind, sizeof(array), compare1);
        printa(array, arrind, first, flaga, flagl, flagal, flagla);
    }
    else if (flagl == 1 && flaga == 0)
    {

        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        if (flagcwd == 1)
            lsimp(cwd);
        else if (flaghome == 1)
        {
            lsimp(home);
        }
        else if (flagout == 1)
        {
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

            lsimp(dir);
        }
        else if (flagprev == 1)
        {
            lsimp(prev);
        }
        else
        {
            lsimp(dir);
        }
    }
    else if (flaga == 0 && flagl == 0)
    {
        //printf("** %d %d %d %d",flaghome,flagcwd,flagout,flagprev);
        int ind = 0;
        for (int k = untilletter; k < strlen(buf) ; k++)
            dir[ind++] = buf[k];
        dir[ind] = '\0';
        if (flagcwd == 1)
        {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            lsimp(cwd);
        }
        else if (flaghome == 1)
        {
            // printf("hi");
            lsimp(home);
        }
        else if (flagout == 1)
        {
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

            lsimp(dir);
        }
        else if (flagprev == 1)
        {
            lsimp(prev);
        }
        else
        {
            lsimp(dir);
        }
    }
    return 1;
}