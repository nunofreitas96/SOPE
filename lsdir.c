/* LISTAR FICHEIROS REGULARES E SUB-DIRECTÓRIOS DE UM DIRECTÓRIO */
/* USO: listdir2 dirname */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h> 
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
int main(int argc, char *argv[]){
 DIR *dirp;
struct dirent *direntp;
struct stat stat_buf;
char *str;
char name[200];
int fd1;

if (argc != 3){

 fprintf( stderr, "Usage: %s dir_name\n", argv[0]);

 exit(1);
 }
//open directory
if ((dirp = opendir( argv[1])) == NULL){
 perror(argv[1]);
 exit(2);
 }
fd1 = open(argv[2], O_WRONLY | O_CREAT , 0644);
//Search for regulars
while ((direntp = readdir( dirp)) != NULL){

//name now has the name of the file
 sprintf(name,"%s/%s",argv[1],direntp->d_name);
 
if (lstat(name, &stat_buf)==-1){
 perror("lstat ERROR");
 exit(3);
 }
 // printf("%10d - ",(int) stat_buf.st_ino);
sprintf(name,"%s\n", name);
//get mode
if (S_ISREG(stat_buf.st_mode)) str = "regular";
else if (S_ISDIR(stat_buf.st_mode)) str = "directory";
else str = "other";


//prints for testing purposes
 printf("%-25s - %s\n", direntp->d_name, str);

//open file for writing


if (fd1 == -1) {
 perror(argv[2]);
 close(fd1);
 return 3;
 } 

int x = strlen(name);
write(fd1, name, x);

 }

close(fd1);
 closedir(dirp);
 exit(0);
} 
