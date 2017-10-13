#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv){
    DIR *dp;
    struct dirent *dent;
    int cnt = 0;
    if(argc != 2){
        printf("[!]Usage : myrm [Directory Path]\n");
        return 0;
    }
    if((dp = opendir(argv[1])) == NULL){
        perror("opendir : ");
        return 0;
    }
    while((dent = readdir(dp))){
        cnt++;
    }
    closedir(dp);
    if(cnt > 2){
        printf("Failed! The directory is not empty.\n");
        return 0;
    }else{
        if(rmdir(argv[1]) == -1){
            perror("remove dir : ");
        }
    }
    return 0;
}