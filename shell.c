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
#define MAXTAM 100

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

void rodeVeja(char** path) {
    pid_t pid = fork();
    int status;
    char** argv = path;
    char *envp[] = {"HOME=/", "PATH=/bin:/usr/bin", NULL};
    char bin[] = "/bin/";
    char *program = malloc(strlen(bin) + strlen(path[0]) + 2);
    int e = 0;

    sprintf(program, "%s%s", bin, path[0]);
    argv[0] = program;

    if (pid == 0) {
        e = execve(argv[0], argv, envp);
    } else {
        waitpid(pid, NULL, 0);
        printf("=> programa '%s' retornou com código %d\n", program, e);
    }

    free(program);
}

void readCommand(void) {
    char *prog;
    char *param;
    char c;
    int i = 0;

    prog = malloc(MAXTAM);
    c = fgetc(stdin);

    while(c != ' ') {
        prog[i++] = c;
        c = fgetc(stdin);
    }
    prog[i] = '\0';

    c = fgetc(stdin);
    i = 0;
    param = malloc(MAXTAM);

    while(c != '\n') {
        param[i++] = c;

        c = fgetc(stdin);
    }
    param[i] = '\0';

    char **command = malloc(sizeof(char *) * 10);
    char *parsed;
    int index = 0;

    parsed = strtok(param, " ");
    while(parsed != NULL) {
        command[index++] = parsed;
        parsed = strtok(NULL, " ");
    }
    command[index] = NULL; 

    /* protegepracaramba */
    if (!strcmp(prog, "protegepracaramba")) {
        protegePraCaramba(param);
    }

    /* liberageral */
    if (!strcmp(prog, "liberageral")) {
        liberaGeral(param);
    }

    /* rodeveja */
    if (!strcmp(prog, "rodeveja")) {
        rodeVeja(command);
    }

    free(prog);
    free(param);
    free(command);
}

int main(int argc, char **argv  ) {
    while(TRUE) {
        readCommand();
    }

    return 0;
}
