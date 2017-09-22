
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char** argv){
    int fd_data;
    char buffer = 0;
    if(argc < 2){
        printf("Usage : mystring [Data File]");
        exit(1);
    }

    fd_data = open(argv[1], O_RDONLY);
    if(fd_data == -1){
        perror("open");
        exit(1);
    }
    while(read(fd_data, &buffer, 1)>0){
        printf("%c", buffer);
        lseek(fd_data, 1, SEEK_CUR);
    }
    close(fd_data);
    return 0;
}