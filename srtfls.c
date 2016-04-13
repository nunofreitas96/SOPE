#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h> 
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char *argv[]){
 DIR *dirp;
struct dirent *direntp;
struct stat stat_buf;
int fd1;
char name[200];

//open directory
if ((dirp = opendir( argv[1])) == NULL){
 perror(argv[1]);
 exit(2);
 }

while ((direntp = readdir( dirp)) != NULL){
printf("test barrier 3");
sprintf(name,"%s/%s",argv[1],direntp->d_name);

if (lstat(name, &stat_buf)==-1){
 perror("lstat ERROR");
 exit(3);
 }

if(S_ISDIR(stat_buf.st_mode)){
	printf("test barrier 1");
	
	dirp = opendir(name);

	char writes[200];
	
	sprintf(writes,"chuopamos");
	int x = strlen(writes);
	fd1 = open(writes, O_WRONLY | O_CREAT, 0644);
	write(fd1, writes, x); 
			
	close(fd1);
	closedir(dirp);
	

	}

	
	}
printf("test barrier 2");
exit(0);
}