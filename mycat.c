#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define  READCOUNT 1
#define BUFFERSIZE 1024
int main(int argc, char** argv){
    char buffer[BUFFERSIZE] = {0,};
    int j = 1;
    int i = 0;
    int fd_target;
    if(argc != 2){
        printf("Usage : mycat [Target File]\n");
        exit(1);
    }

    if( (fd_target = open(argv[1], O_RDONLY)) == -1){
        perror("open");
        exit(-1);
    }
    
    for(; i < BUFFERSIZE; i++){
        if(read(fd_target, &buffer[i], READCOUNT)>0){
            if(buffer[i] == 0x0A){
                buffer[i+1] = 0;
                printf("%02d| %s", j, buffer);
                memset(buffer, 0, i+1);
                i = -1;
                j++;
            }
        }else{
            break;
        }
    }
    
    printf("\n");
    close(fd_target);
    return 0;
}