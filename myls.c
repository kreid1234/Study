#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv){
    DIR *dp;
    struct dirent *dent;
    int cnt = 0;
    if(argc != 2){
        printf("[!]Usage : myls [Directory Path]\n");
        return 0;
    }
    if((dp = opendir(argv[1])) == NULL){
        perror("opendir : ");
        return 0;
    }
    while((dent = readdir(dp))){
        cnt++;
        if(cnt > 2){
            printf("%d %s\n", (cnt - 2), dent->d_name);
        }
    }
    closedir(dp);
    return 0;
}