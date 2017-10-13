#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

typedef struct stat Stat;
#define MYCHMOD_ACCESS_ADD 1
#define MYCHMOD_ACCESS_DELETE 0

int AccessModeChange(char vi, char ac, char mo, Stat* stFileMeta);

void Usage(){
    printf("mychmod : [ (u/g/o) (+/-) (r/w/x) ] [FilePath]\n");
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

    Stat stFileMeta;
    if(argc != 3){
        printf("[!]Usage : mychmod [Access Mode] [File Path]\n");
        printf("[ex] mychmod g+w test.txt\n");
        return 0;
    }
    printf("[*]FileName : %s\n", argv[2]);
    memset(&stFileMeta, 0x0, sizeof(struct stat));
    if(stat(argv[2], &stFileMeta) == -1){
        perror("[!] Get Stat Error : ");
        return 0;
    }
    if(strlen(argv[1]) != 3){
        Usage();
        return 0;
    }
   
    printAccess(&stFileMeta);
    printf("changed!\n");
    if(AccessModeChange(argv[1][0], argv[1][2], argv[1][1], &stFileMeta) == -1){
        printf("[!] Failed to change the access mode.\n");
        Usage();
        return 0;
    }
    chmod(argv[2], stFileMeta.st_mode);
    printAccess(&stFileMeta);
    return 0;

}

int AccessModeChange(char vi, char ac, char mode, Stat* stFileMeta){
    int mo;
    if(mode == '+'){
        mo = MYCHMOD_ACCESS_ADD;
    }else if(mode == '-'){
        mo = MYCHMOD_ACCESS_DELETE;
    }else{
        return -1;
    }
    switch(vi){
        case 'u':
            if(mo == MYCHMOD_ACCESS_ADD){
                switch(ac){
                    case 'r':
                        stFileMeta->st_mode |= S_IRUSR;
                        break;
                    case 'w':
                        stFileMeta->st_mode |= S_IWUSR;
                        break;
                    case 'x':
                        stFileMeta->st_mode |= S_IXUSR;
                        break;
                    default :
                        return -1;
                }
            }else if(mo == MYCHMOD_ACCESS_DELETE){
                switch(ac){
                    case 'r':
                        stFileMeta->st_mode &= ~(S_IRUSR);
                        break;
                    case 'w':
                        stFileMeta->st_mode &= ~(S_IWUSR);
                        break;
                    case 'x':
                        stFileMeta->st_mode &= ~(S_IXUSR);
                        break;
                    default :
                        return -1;
                }

            }else{
                return -1;
            }
            break;
        case 'g':
            if(mo == MYCHMOD_ACCESS_ADD){
                switch(ac){
                    case 'r':
                        stFileMeta->st_mode |= S_IRGRP;
                        break;
                    case 'w':
                        stFileMeta->st_mode |= S_IWGRP;
                        break;
                    case 'x':
                        stFileMeta->st_mode |= S_IXGRP;
                        break;
                    default :
                        return -1;
                }
            }else if(mo == MYCHMOD_ACCESS_DELETE){
                switch(ac){
                    case 'r':
                        stFileMeta->st_mode &= ~(S_IRGRP);
                        break;
                    case 'w':

stFileMeta->st_mode &= ~(S_IWGRP);
                        break;
                    case 'x':
                        stFileMeta->st_mode &= ~(S_IXGRP);
                        break;
                    default :
                        return -1;
                }

            }else{
                return -1;
            }
            break;
        case 'o':
            if(mo == MYCHMOD_ACCESS_ADD){
                switch(ac){
                    case 'r':
                        stFileMeta->st_mode |= S_IROTH;
                        break;
                    case 'w':
                        stFileMeta->st_mode |= S_IWOTH;
                        break;
                    case 'x':
                        stFileMeta->st_mode |= S_IXOTH;
                        break;
                    default :
                        return -1;
                }
            }else if(mo == MYCHMOD_ACCESS_DELETE){
                switch(ac){
                    case 'r':
                        stFileMeta->st_mode &= ~(S_IROTH);
                        break;
                    case 'w':
                        stFileMeta->st_mode &= ~(S_IWOTH);
                        break;
                    case 'x':
                        stFileMeta->st_mode &= ~(S_IXOTH);
                        break;
                    default :
                        return -1;
                }

            }else{
                return -1;
            }
            break;
        default:
        return -1;

    }
    return 0;
}