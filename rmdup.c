#include "rmdup.h"


int cmpcont(char* file1, char* file2, char* path1, char* path2){
int fd1;
int fd2;
int size1;
int size2;
char byte1[1];
char byte2[1];





chdir(path1);
fd1 = open(file1, O_RDONLY);
	if (fd1 == -1)
	{
		perror("open");
		return 2;
	}

	int cdir = chdir(path2);
	if (cdir == -1){
	 perror(path2);
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



int cmpfiles(char* file1, char* file2, char* path1, char* path2){
int fd1;
int fd2;


fd1 = open(file1, O_RDONLY);
char currd[1024];
getcwd(currd,sizeof(currd));
if(currd != path1){
chdir(path1);}

if (fd1 == -1) {
 	perror(file1);
 	return 2;
 } 
struct stat sb;
if (stat(file1, &sb) == -1  )
{
	perror("stat1()");
	return 4;
}

int cdir = chdir(path2);
if (cdir == -1){
 	perror(path2);
 	return 7;
 }


fd2 = open(file2, O_RDONLY);
if (fd2 == -1) {
	 perror(file2);
 	return 3;
 } 
printf("%s",file2);

struct stat sb2;

if (stat(file2, &sb2) == -1)
{
	perror("stat1()");
	return 4;
}
char name1[100];
char name2[100];
strcpy(name1, file1);
strcpy(name2, file2);

int cdir2 = chdir("..");
if (cdir2 == -1){
 	perror("..");
 	return 7;
 }

printf("%i",strcmp(file1,file2));
if(!strcmp(file1,file2)){
	printf("same name\n");
	if(sb.st_size == sb2.st_size){
		printf("same size\n");
 		if(sb.st_mode == sb2.st_mode){
			if(cmpcont(file1,file2,path1,path2) == 1){

			
			printf("equals\n");
			return 1;}
  		} 
 	}
}
printf(" not equals\n");

return 0;


}

int crthls(File* files, int arr_size){
printf("start the linking\n");
char hardlinksFile[BUFF_LENGTH];
int hardlinkSave;
printf("opening\n");
hardlinkSave = open("hardlinks.txt",O_WRONLY|O_CREAT|O_TRUNC, 0664);
printf("opened\n");
int i =0;
for(i=0; i < arr_size ; i++){
	printf("cycle of for\n");
	int j = i+1;
	printf("%s - %s\n",files[i].name,files[j].name);
	while(strcmp(files[i].name,files[j].name) == 0){
		printf("cycle of while\n");
		if(cmpfiles(files[i].name, files[j].name, files[i].name_path, files[j].name_path)){
			printf("%s\n",files[j].name_path);
			printf("%s\n",files[i].name_path);
			if(unlink(files[j].name_path) == -1){
				perror("unlink");
				return -1;
				}
			if(link(files[i].name_path,files[j].name_path) == -1){
				perror("link");
				return -1;
				}
			sprintf(hardlinksFile,"%s %s %s %s\n",files[j].name,files[j].name_path, files[j].perm , files[j].date);
			write(hardlinkSave,hardlinksFile,strlen(hardlinksFile));

			}
		j++;
		}
	i = j-1;		 
	}
	return 0;
}

int prplist(){

	
	FILE* fil = fopen(FILE_NAME,"r");
	int ch =0;
	int lines =0;
	int i;
	while(!feof(fil)){	
  		ch = fgetc(fil);
  		if(ch == '\n'){
   	 	lines++;
 	 	}
	}	
	fclose(fil);

	int array = lines-1;

	
	printf("allocc\n");
	File* files = malloc(array * sizeof(*files));
	fil =fopen(FILE_NAME,"r");
	printf("allocced\n");
	
	
	for(i = 0; i < array; i++){
		fscanf(fil,"%s %s %s %s", files[i].name,files[i].name_path, files[i].perm , files[i].date);
	}
	printf("close it\n");
	fclose(fil);
	printf("start the loinking\n");
	if(crthls(files, array) == -1){
	
	perror("links");
	return -1;	
	
	}

	return 0;
	

}

int main(int argc, char *argv[]){
 	char cdir[PATH_MAX];
	pid_t pid;
	
	char currd[1024];
	getcwd(currd,sizeof(currd));

	sprintf(currd,"%s/lsdir", currd);
printf("%s", currd);
	pid = fork();
	if (pid == 0) {
	  
	  execl(currd,"lsdir", argv[1], "files,txt", NULL);
	}
	waitpid(pid, NULL, 0);

	
	


return prplist();


}








