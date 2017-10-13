#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char** argv){

    struct stat stFileMeta;
    char r,w,x,gr,gw,gx,or,ow,ox;
    if(argc != 2){
        printf("[!]Usage : mystat [FilePath]\n");
        return 0;
    }
    printf("[*]FileName : %s\n", argv[1]);
    memset(&stFileMeta, 0x0, sizeof(struct stat));
    if(stat(argv[1], &stFileMeta) == -1){
        perror("[!] stat : ");
        return 0;
    }
    printf("\t[**]Inode Number : %d\n", stFileMeta.st_ino);
    printf("\t[**]fileType : ");
    switch(stFileMeta.st_mode & S_IFMT){
        case S_IFIFO:
            printf("FIFO special\n");
            break;
        case S_IFCHR:
            printf("Character special\n");
            break;
        case S_IFBLK:
            printf("Block special\n");
            break;
        case S_IFREG:
            printf("Regular\n");
            break;
        case S_IFDIR:
            printf("Directory\n");
            break;
        case S_IFLNK:
            printf("Symbolic link\n");
            break;
        case S_IFSOCK:
            printf("Socket\n");
            break;
    }
    if(stFileMeta.st_mode & S_IRWXU & S_IRUSR) r = 'r'; else r = '-';
    if(stFileMeta.st_mode & S_IRWXU & S_IWUSR) w = 'w'; else w = '-';
    if(stFileMeta.st_mode & S_IRWXU & S_IXUSR) x = 'x'; else x = '-';

    if(stFileMeta.st_mode & S_IRWXG & S_IRGRP) gr = 'r'; else gr = '-';
    if(stFileMeta.st_mode & S_IRWXG & S_IWGRP) gw = 'w'; else gw = '-';
    if(stFileMeta.st_mode & S_IRWXG & S_IXGRP) gx = 'x'; else gx = '-';

    if(stFileMeta.st_mode & S_IRWXO & S_IROTH) or = 'r'; else or = '-';
    if(stFileMeta.st_mode & S_IRWXO & S_IWOTH) ow = 'w'; else ow = '-';
    if(stFileMeta.st_mode & S_IRWXO & S_IXOTH) ox = 'x'; else ox = '-';
    printf("\t[**]File Permissions : %c%c%c%c%c%c%c%c%c\n", r,w,x,gr,gw,gx,or,ow,ox);
    printf("\t[**]UID : %d\n", stFileMeta.st_uid);
    printf("\t[**]Updating Time : %d\n", stFileMeta.st_atime);
    return 0;

}