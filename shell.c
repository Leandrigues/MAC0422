#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

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
    pid_t pid = fork();
    int status;
    char *argv[] = {NULL, NULL};
    char *envp[] = {"HOME=/", "PATH=/bin:/usr/bin", NULL};
    char bin[] = "/bin/";
    char *program = malloc(strlen(bin) + strlen(path) + 2);
    int e = 0;
    sprintf(program, "%s%s", bin, path);
    argv[0] = program;
    if (pid == 0) {
        e = execve(argv[0], argv, envp);
        printf("programa '%s' retornou com código %d.\n",path, e);
    } else {
        wait(&status);
	printf("programa '%s' retornou com codigo %d.\n", path, e);
    }
    free(program);
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
