#include "headers.h"
#include "A4ls.h"
int compare(const void* v1,const void* v2)
{
    lsstructt p1=*(lsstructt*)v1;
    lsstructt p2=*(lsstructt*)v2;
    return strcmp(p1->name,p2->name);
}


char* permission(int mode) {
    char* perm=(char*)malloc(sizeof(char)*11);
    if(S_ISDIR(mode))
        perm[0]='d';
    else
        perm[0]='-';

    if(mode & S_IRUSR)
        perm[1]='r';
    else
        perm[1]='-';

    if(mode & S_IWUSR)
        perm[2]='w';
    else
        perm[2]='-';

    if(mode & S_IXUSR)
        perm[3]='x';
    else
        perm[3]='-';
    
    if(mode & S_IRGRP)
        perm[4]='r';
    else
        perm[4]='-';

    if(mode & S_IWGRP)
        perm[5]='w';
    else
        perm[5]='-';

    if(mode & S_IXGRP)
        perm[6]='x';
    else
        perm[6]='-';

    if(mode & S_IROTH)
        perm[7]='r';
    else
        perm[7]='-';

    if(mode & S_IWOTH)
        perm[8]='w';
    else
        perm[8]='-';

    if(mode & S_IXOTH)
        perm[9]='x';
    else
        perm[9]='-';
    perm[10]='\0';
    return perm;

}

void lsimp(const char *path) {
    struct dirent *entry;
    struct stat file_stat;
    struct passwd *user_info;
    struct group *group_info;
    lsstructt* larr=(lsstructt*)malloc(sizeof(struct structp)*100000);
    int lsind=0;
    
    //printf("%s",path);
    DIR *dir = opendir(path);
    if (dir == NULL) {
        printf("\033[0;31m");
        perror("opendir");
        printf("\x1b[0m");
        exit(EXIT_FAILURE);
    }
    int inds=0;
    long long int blocks=0;
    while ((entry = readdir(dir)) != NULL) {
        //setting elements of array of structs
        larr[lsind]=(lsstructt)malloc(sizeof(struct structp));
        larr[lsind]->userinfo=(char*)malloc(sizeof(char)*1024);
        larr[lsind]->grpinfo=(char*)malloc(sizeof(char)*1024);
        larr[lsind]->time=(char*)malloc(sizeof(char)*1024);
        larr[lsind]->name=(char*)malloc(sizeof(char)*1024);
        
        char full_path[100000];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        //lstat
        if (stat(full_path, &file_stat) == -1) {
            printf("\033[0;31m");
            perror("stat");
            printf("\x1b[0m");
            continue;
        }

        blocks+=file_stat.st_blocks;

        char* str=(char*)malloc(sizeof(char)*11);
        str=permission(file_stat.st_mode);
        strcpy(larr[lsind]->perm,str);
        larr[lsind]->nlink=file_stat.st_nlink;

        user_info = getpwuid(file_stat.st_uid);
        group_info = getgrgid(file_stat.st_gid);
        inds=0;
        for(int i=0;i<strlen(user_info->pw_name);i++)
        larr[lsind]->userinfo[inds++]=user_info->pw_name[i];
        larr[lsind]->userinfo[inds]='\0';
        inds=0;
        for(int i=0;i<strlen(group_info->gr_name);i++)
        larr[lsind]->grpinfo[inds++]=group_info->gr_name[i];
        larr[lsind]->grpinfo[inds]='\0';
        
        larr[lsind]->size=file_stat.st_size;

        struct tm *timeinfo = localtime(&file_stat.st_mtime);
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%b %d %H:%M", timeinfo);
        inds=0;
        for(int i=0;i<strlen(time_str);i++)
        larr[lsind]->time[inds++]=time_str[i];
        larr[lsind]->time[inds]='\0';
        
        inds=0;
        for(int i=0;i<strlen(entry->d_name);i++)
        larr[lsind]->name[inds++]=entry->d_name[i];
        larr[lsind]->name[inds]='\0';
        larr[lsind]->type=entry->d_type;
        
        lsind++;
        
    }
    //sorting based on names of files
    qsort(larr,lsind,sizeof(larr[0]),compare);
    char full_path[1024];
    printf("total %lld\n", (long long int)(blocks/2));
    //printing like ls
    for(int i=0;i<lsind;i++)
    {
        printf("%s",larr[i]->perm);
        printf(" %ld ",larr[i]->nlink);
        printf("%s %s ",larr[i]->userinfo,larr[i]->grpinfo);
        printf("%5ld ",larr[i]->size);
        printf("%s ",larr[i]->time);
        if(stat(full_path,&file_stat)==0 && (file_stat.st_mode & S_IXUSR))
        printf("\x1b[32m %s\n \x1b[0m",larr[i]->name);
        else if(larr[i]->type==8)
        printf("%s\n",larr[i]->name);
        else if(larr[i]->type==4)
        printf("\033[0;34m %s\n \x1b[0m",larr[i]->name);
    }

    closedir(dir);
    
}   
