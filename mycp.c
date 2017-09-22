#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int argc, char** argv){
    int fd_dst;
    int fd_src;
    unsigned long data;
    int num = 0;
    if(argc != 3){
        printf("Usage : mycat [SRC File] [DST File]\n");
        exit(1);
    }

    fd_src = open(argv[1], O_RDONLY);
    fd_dst = open(argv[2], O_CREAT| O_WRONLY | O_TRUNC, 0644);

    if(fd_src == -1 || fd_dst == -1){
        perror("open");
        exit(1);
    }

    while((num = read(fd_src, &data, 4))>0){
        if(write(fd_dst, &data, num) != num ){
            perror("write");
            exit(1);
        }
    }

    close(fd_src);
    close(fd_dst);
    return 0;
}

    
