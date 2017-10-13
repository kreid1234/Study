#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char** argv){
    DIR *dp;
    struct dirent *dent;
    struct stat stFileMeta;
    
    if(argc != 2){
        printf("[!]Usage : myls2 [Directory Path]\n");
        return 0;
    }
    if((dp = opendir(argv[1])) == NULL){
        perror("opendir : ");
        return 0;
    }
    chdir(argv[1]);
    while((dent = readdir(dp))){
	memset(&stFileMeta, 0, sizeof(struct stat));       
	if(stat(dent->d_name, &stFileMeta) == -1){
		perror("Get File Data : ");
		printf("Error : %s\n", dent->d_name);
		continue;
	}
	if((stFileMeta.st_mode & S_IFMT) == S_IFDIR){
		printf("Directory : %s\n", dent->d_name);
	}else{
		printf("File : %s\n", dent->d_name);
	}
    }
    closedir(dp);
    return 0;
}