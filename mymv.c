#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
 char buffer[BUFSIZ];
 if (argc != 3) {
        printf("[!]Usage: mymv [file] [to directory]\n");
        return 0;
 }

 snprintf(buffer, sizeof(buffer), "./%s/%s", argv[2], argv[1]);
    if (rename(argv[1], buffer) == -1) {
  perror("Move File : ");
 }
 return 0;
}