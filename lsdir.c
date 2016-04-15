/* LISTAR FICHEIROS REGULARES E SUB-DIRECTÓRIOS DE UM DIRECTÓRIO */
/* USO: listdir2 dirname */
#include "lsdir.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h> 
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
int listdir(char *direc, char *file){
 DIR *dirp;
struct dirent *direntp;
struct stat stat_buf;
char *str;
char name[200];
//char access[200];
int fd1;

/*if (argc != 3){

 fprintf( stderr, "Usage: %s dir_name\n", argv[0]);

 exit(1);
 }*/
//open directory
if ((dirp = opendir( direc)) == NULL){
 perror(direc);
 exit(2);
 }
fd1 = open(file, O_WRONLY | O_CREAT , 0644);
//Search
while ((direntp = readdir( dirp)) != NULL){

if( strcmp(direntp->d_name,".")==0 ){
printf(".\n");
 continue;}
if( strcmp(direntp->d_name,"..")==0 ){
printf("..\n"); continue;}

//name now has the name of the file
 sprintf(name,"%s/%s",direc,direntp->d_name);
 
if (lstat(name, &stat_buf)==-1){
 perror("lstat ERROR");
 exit(3);
 }
 // printf("%10d - ",(int) stat_buf.st_ino);

//get mode
if (S_ISREG(stat_buf.st_mode)) str = "regular";
else if (S_ISDIR(stat_buf.st_mode)) str = "directory";
else str = "other";

if(S_ISDIR(stat_buf.st_mode)){
	
		
		int return_value = listdir(name,file);
		if(return_value != 0)
			{
				closedir(dirp);
				return return_value;
			}
		}
	

sprintf(name,"%s\n", name);
//prints for testing purposes
 printf("%-25s - %s\n", direntp->d_name, str);

//open file for writing


if (fd1 == -1) {
 perror(file);
 close(fd1);
 return 3;
 } 

//strcpy(access,stat_buf.st_mode);

int x = strlen(name);
int size = stat_buf.st_size - 48;

char sizec;
sizec = size + '0';

char sc[200];
sprintf(sc,"%i\n", sizec);



//get the time
time_t timethen;
timethen = stat_buf.st_mtime;
struct tm *ts;
char zetime[200];



ts = localtime(&timethen);
strftime(zetime, sizeof(zetime), "%a %Y-%m-%d %H:%M:%S %Z", ts);
sprintf(zetime,"%s\n", zetime);



/*char access = stat_buf.st_mode;
int y = strlen(access);
*/
int y = strlen(sc);
int z = strlen(zetime);

write(fd1, name, x);
write(fd1, sc, y);
write(fd1, zetime, z);

/*write(fd1,access, y);*/







 }

close(fd1);
 closedir(dirp);
 exit(0);
} 


int main(int argc, char *argv[]){


pid_t pid = fork();
	char *exec_error = "Failed to execute execlp. \n";

	switch(pid)
	{
	case -1: //error
		perror("fork");
		
		return 3;
	case 0: //child process
		listdir(argv[1],argv[2]);
		write(STDOUT_FILENO,exec_error,strlen(exec_error));
		return 4;
	}
	

	



}
