#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv){
    char* cwd;
    char wd[BUFSIZ];
    if(argc != 2){
        printf("[!]Usage : mymkch [Directory Path]\n");
        return 0;
    }

    if(mkdir(argv[1], 0755) == -1){
        perror("Make Directory : ");
        return 0;
    }

    cwd = getcwd(NULL, BUFSIZ);

    printf("1. Current Directory : %s\n", cwd);

    chdir(argv[1]);

    getcwd(&wd, BUFSIZ);
    printf("2. Current Directory : %s\n", wd);
    return 0;
}