#ifndef HEADERS_H_
#define HEADERS_H_

 struct structp{
    char perm[11];
    long int nlink;
    char* userinfo;
    char* grpinfo;
    long int size;
    char* time;
    char* name;
    int type;
};
typedef struct structp lstruct;
typedef struct structp* lsstructt;

extern int bgcount;



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#include "direct.h"
#include<unistd.h>
#include<sys/types.h>
#include <sys/stat.h>
//#include<readline/readline.h>
//#include<readline/history.h>
#include "time.h"
//#include "io.h"
//#include "process.h"
//#include "Windows.h"
//#include "tchar.h"
//#include "winbase.h"
#include "sys/types.h"
#include "dirent.h"
#include "limits.h"
#include <sys/wait.h>
#include "pwd.h"
#include "grp.h"
#include <sys/time.h>



#endif