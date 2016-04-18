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


int listdir(char *direc, char *file, int moder){
 DIR *dirp;
struct dirent *direntp;
struct stat stat_buf;
int modcounter = moder+1;
char *str;
char name[200];
char name2[200];
//char access[200];
int fd1;
int changed =0;

/*if (argc != 3){

 fprintf( stderr, "Usage: %s dir_name\n", argv[0]);

 exit(1);
 }*/
//open directory
if ((dirp = opendir( direc)) == NULL){
 perror(direc);
 exit(2);
 }
if(moder ==0){
fd1 = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0600);}
else if(moder != 0){
fd1 = open(file, O_WRONLY |O_CREAT | O_APPEND, 0600);
}
//Search
while ((direntp = readdir( dirp)) != NULL){

if( strcmp(direntp->d_name,".")== 0 ){
printf(".\n");
 continue;}
if( strcmp(direntp->d_name,"..")== 0 ){
printf("..\n"); 
continue;}

//name now has the name of the file
 sprintf(name2,"%s/%s",direc,direntp->d_name);
 sprintf(name, "%s",direntp->d_name);
printf("%s\n",name2);
if (lstat(name2, &stat_buf)==-1){
 perror("lstat ERROR");
 exit(3);
 }
 // printf("%10d - ",(int) stat_buf.st_ino);

//get mode
if (S_ISREG(stat_buf.st_mode)) str = "regular";
else if (S_ISDIR(stat_buf.st_mode)){ str = "directory";
}
else{ str = "other";
}

if(S_ISDIR(stat_buf.st_mode)){
	printf("modou\n");
		printf("%s\n", name2);
		int return_value = listdir(name2,file, modcounter);
		close(fd1);
		if(return_value != 0)
			{
				closedir(dirp);
				return return_value;
			}
		fd1 = open(file, O_WRONLY |O_CREAT | O_APPEND, 0600);
			char currd2[1024];


			/*getcwd(currd2,sizeof(currd2));
			printf("%s\n",currd2);
			char *dire = malloc(sizeof(direc));
			dire = direc;



			int cdir = chdir(dire);
			getcwd(currd2,sizeof(currd2));
			printf("%s\n",currd2);*/
	
		continue;
		
		}

	


//prints for testing purposes
 printf("%-25s - %s\n", direntp->d_name, str);

//open file for writing




//strcpy(access,stat_buf.st_mode);

int x = strlen(name);
int size = stat_buf.st_size - 48;

char sizec;
sizec = size + '0';

char sc[200];
sprintf(sc,"%i ", sizec);



//get the time
time_t timethen;
timethen = stat_buf.st_mtime;
struct tm *ts;
char zetime[200];



ts = localtime(&timethen);
strftime(zetime, sizeof(zetime), "%a-%Y-%m-%d-%H:%M:%S-%Z", ts);
sprintf(zetime,"%s\n", zetime);



/*char access = stat_buf.st_mode;
int y = strlen(access);
*/
char currd[1024];
if(moder != 0){
getcwd(currd,sizeof(currd));
			printf("%s\n",currd);
			char *dire = malloc(sizeof(direc));
			dire = direc;



			int cdir = chdir(dire);
			getcwd(currd,sizeof(currd));
			printf("%s\n",currd);
			changed = 1;


}


getcwd(currd,sizeof(currd));


sprintf(name2,"%s/%s",currd,direntp->d_name);
int k;
printf("backing");
for(k =1; k < modcounter; k++){
chdir("..");
getcwd(currd,sizeof(currd));
printf("%s\n",currd);}

int y = strlen(sc);
int z = strlen(zetime);
int l = strlen(name2);

if(name[x-1] != '~'){
printf("%s\n", zetime);
write(fd1, name, x);
write(fd1, " ", 1);
write(fd1, name2, l);
write(fd1, " ", 1);
write(fd1, sc, y);
write(fd1, " ", 1);
write(fd1, zetime, z);
}

/*write(fd1,access, y);*/







 }
/*if(moder ==1){
char* direcback;
sprintf(direcback,"%s/..",direc);
int cdir2 = chdir(direcback);}*/

closedir(dirp);
close(fd1);
 
 return 0;
} 


int main(int argc, char *argv[]){
		//pid_t pid;
		
		printf("start\n");
		listdir(argv[1],argv[2],0);
		execlp("sort", "sort", argv[2], "-no", argv[2], (char*)NULL);
/*
pid = fork();

	if (pid == 0) {
	  
	 
	}
	waitpid(pid, NULL, 0);*/
		
		printf("finish\n");
		return 0;
	}
	

	




