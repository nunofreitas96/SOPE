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

int main(int argc, char *argv[]){


execlp("/usr/users2/mieic2014/up201404739/SOPE/SOPE/lsdir","lsdir", argv[1],argv[2], NULL);


return 0;

}
