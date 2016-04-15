#include <unistd.h>
#include <fcntl.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

int cmpcont(char* file1, char* file2){
int fd1;
int fd2;
int size1;
int size2;
char byte1[1];
char byte2[1];
DIR *dirp;

char *dire = malloc(2);
dire[0] = 'T';





fd1 = open(file1, O_RDONLY);
	if (fd1 == -1)
	{
		perror("open");
		return 2;
	}

	int cdir = chdir(dire);
	if (cdir == -1){
	 perror(dire);
 	 return 7;
 	}

		
	fd2 = open(file2, O_RDONLY);
	if (fd2 == -1)
	{
		perror("open");
		close(fd1);
		return 3;
	}

while(size1 = read(fd1,byte1,1), size1 == 1)
	{
		size2 = read(fd2,byte2,1);
		switch(size2)
		{
		case -1:
			perror("read");
			close(fd2);
			close(fd1);
			return 4;
		case 0: 
			close(fd2);
			close(fd1);
			return 0;
		}

		if(strncmp(byte1, byte2, 1) != 0) 
		{
			close(fd2);
			close(fd1);
			return 0;
		}
	}
	size2 = read(fd2,byte2,1);
	if(size2 == 1) {
		close(fd2);
		close(fd1);
		return 0;					
			
	}

	close(fd2);
	close(fd1);

	return 1;
	
}

int main(int argc, char *argv[]){
DIR *dirp;
int fd1;
int fd2;
int direct;

char *dire = malloc(2);
dire[0] = 'T';
fd1 = open(argv[1], O_RDONLY);
if (fd1 == -1) {
 perror(argv[1]);
 return 2;
 } 
struct stat sb;
if (-1 == stat(argv[1], &sb))
{
	perror("stat1()");
	return 4;
}

int cdir = chdir(dire);
if (cdir == -1){
 perror(dire);
 return 7;
 }


fd2 = open(argv[2], O_RDONLY);
if (fd2 == -1) {
 perror(argv[2]);
 return 3;
 } 
printf("%s",argv[2]);

struct stat sb2;

if (-1 == stat(argv[2], &sb2))
{
	perror("stat1()");
	return 4;
}
char name1[100];
char name2[100];
strcpy(name1, argv[1]);
strcpy(name2, argv[2]);

int cdir2 = chdir("..");
if (cdir2 == -1){
 perror("..");
 return 7;
 }

printf("%i",strcmp(argv[1],argv[2]));
if(!strcmp(argv[1],argv[2])){
	printf("same name\n");
	if(sb.st_size == sb2.st_size){
		printf("same size\n");
 		if(sb.st_mode == sb2.st_mode){
			if(cmpcont(argv[1],argv[2]) == 1){

			
			printf("equals\n");
			return 1;}
  		} 
 	}
}
printf(" not equals\n");
return 0;


}
