#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

typedef struct stat Stat;

void AccessModeChange(unsigned short mode, Stat* stFileMeta);

void Usage(){
    printf("mychmod2 : [ (S/U/G/O) ] [FilePath]\n");
}

void printAccess(Stat* stFileMeta){
    char r,w,x,gr,gw,gx,or,ow,ox;
    if(stFileMeta->st_mode & S_IRWXU & S_IRUSR) r = 'r'; else r = '-';
    if(stFileMeta->st_mode & S_IRWXU & S_IWUSR) w = 'w'; else w = '-';
    if(stFileMeta->st_mode & S_IRWXU & S_IXUSR) x = 'x'; else x = '-';

    if(stFileMeta->st_mode & S_IRWXG & S_IRGRP) gr = 'r'; else gr = '-';
    if(stFileMeta->st_mode & S_IRWXG & S_IWGRP) gw = 'w'; else gw = '-';
    if(stFileMeta->st_mode & S_IRWXG & S_IXGRP) gx = 'x'; else gx = '-';

    if(stFileMeta->st_mode & S_IRWXO & S_IROTH) or = 'r'; else or = '-';
    if(stFileMeta->st_mode & S_IRWXO & S_IWOTH) ow = 'w'; else ow = '-';
    if(stFileMeta->st_mode & S_IRWXO & S_IXOTH) ox = 'x'; else ox = '-';
    printf("\t[**]File Permissions : %c%c%c%c%c%c%c%c%c\n", r,w,x,gr,gw,gx,or,ow,ox);
}


int main(int argc, char** argv){
    unsigned short Am = 0;
    unsigned short x1,x2,x3,x4;
    Stat stFileMeta;
    if(argc != 3){
        printf("[!]Usage : mychmod2 [Access Mode] [File Path]\n");
        printf("[ex] mychmod2 0777 test.txt\n");
        return 0;
    }
    printf("[*]FileName : %s\n", argv[2]);
    memset(&stFileMeta, 0x0, sizeof(struct stat));
    if(stat(argv[2], &stFileMeta) == -1){
        perror("[!] Get Stat Error : ");
        return 0;
    }

    if(strlen(argv[1]) != 4){
        Usage();
        return 0;
    }
    x1 = (unsigned short) (argv[1][0]&0x0F);
    x2 = (unsigned short) (argv[1][1]&0x0F);
    x3 = (unsigned short) (argv[1][2]&0x0F);
    x4 = (unsigned short) (argv[1][3]&0x0F);
    Am |= (x1<<9);
    Am |= (x2<<6);
    Am |= (x3<<3);
    Am |= (x4);

    printAccess(&stFileMeta);
    printf("changed!\n");
    AccessModeChange(Am, &stFileMeta); 
    chmod(argv[2], stFileMeta.st_mode);
    printAccess(&stFileMeta);
    return 0;

}

void AccessModeChange(unsigned short mode, Stat* stFileMeta){
    mode_t prMode;
    prMode = stFileMeta->st_mode;
    prMode &= 0xF000;
    mode |= prMode;
    stFileMeta->st_mode = (mode_t)mode;
}