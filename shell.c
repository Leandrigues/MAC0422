#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

void protegePraCaramba(char* path) {
    pid_t pid = fork();
    if(pid == 0) {
        printf("Liberando\n");
        chmod(path, 00000);
        exit(0);
    }
}

void liberaGeral(char* path) {
    pid_t pid = fork();
    if(pid == 0) {
        printf("Liberando\n");
        chmod(path, 00777);
        exit(0);
    }
}

void rodeVeja(char* path) {
    
}

void readCommand(void) {
    char *prog;
    char *param;
    char c;
    int size = 10;
    int i = 0;

    prog = malloc(size);
    c = fgetc(stdin);

    while(c != ' ') {
        prog[i++] = c;

        if(i == size) {
            size = size*2;
            prog = realloc(prog, size);
        }

        c = fgetc(stdin);
    }

    c = fgetc(stdin);
    i = 0;
    size = 10;
    param = malloc(size);

    while(c != '\n') {
        param[i++] = c;

        if(i == size) {
            size = size*2;
            param = realloc(param, size);
        }

        c = fgetc(stdin);
    }

    /* protegepracaramba */
    if (!strcmp(prog, "protegepracaramba")) {
        protegePraCaramba(param);
    }

    /* liberageral */
    if (!strcmp(prog, "liberageral")) {
        liberaGeral(param);
    }

    if (!strcmp(prog, "rodeveja")) {
        rodeVeja(param);
    }
    free(prog);
    free(param);
}

int main(int argc, char **argv  ) {
    while(TRUE) {
        readCommand();
    }

    return 0;
}