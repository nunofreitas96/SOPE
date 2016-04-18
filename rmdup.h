#ifndef RMDUP_H
#define RMDUP_H

#include<stdio.h>
#include<sys/wait.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include <dirent.h>

#define BUFF_LENGTH 1000
#define FILE_NAME "files.txt"

typedef struct{

char name[BUFF_LENGTH];
char name_path[BUFF_LENGTH];
char perm[BUFF_LENGTH];
char date[BUFF_LENGTH];


}File;

int cmpcont(char* file1, char* file2, char* path1, char* path2);

int cmpfiles(char* file1, char* file2, char* path1, char* path2);

int crthls(File* files, int arr_size);

int prplist();

int main();










#endif
