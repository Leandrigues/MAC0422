#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

#define TRUE 1
#define FALSE 0
#define MAXTAM 20

void protegePraCaramba(char *path) {
    pid_t pid = fork();
    int status = 0;
    int e = 0;

    if(pid == 0) {
        chmod(path, 00000);
        exit(e);
    } else {
        waitpid(pid, &status, 0);
    }
}

void liberaGeral(char *path) {
    pid_t pid = fork();
    int status = 0;
    int e = 0;

    if(pid == 0) {
        e = chmod(path, 00777);
        exit(e);
    } else {
        waitpid(pid, &status, 0);
    }
}

void rodeVeja(char **path) {
    pid_t pid = fork();
    char **argv = path;
    int e = 0;
    int status = 0;

    if (pid == 0) {
        e = execve(argv[0], argv, 0);
        printf("shell: command not found: %s\n", path[0]);
    } else {
        /* aguarda finalização do processo filho */ 
        waitpid(pid, &status, 0);
        printf("=> programa '%s' retornou com código %d\n", path[0], status);
    }
}

void rode(char **path) {
    pid_t pid = fork();
    char **argv = path;
    int e;
    
    if (pid == 0) {
        /* evita que CTRL+C interrompa o processo filho (o shell monopoliza o teclado) */
        close(STDIN_FILENO);
        e = execve(argv[0], argv, 0);
        printf("shell: command not found: %s\n", path[0]);
        exit(e);
    } else {
        /* evita que o processo filho se torne um zombie */
        signal(SIGCHLD, SIG_IGN);
    }
}

int readCommand(void) {
    char *prog;
    char *param;
    char c;
    int i = 0;
    char **command;
    char *parsed;
    int index;
    
    prog = malloc(MAXTAM);
    printf("$ ");

    c = fgetc(stdin);
    while(c != ' ' && c != '\n') {
        prog[i++] = c;
        c = fgetc(stdin);
    }

    prog[i] = '\0';

    /* exit shell */
    if (!strcmp(prog, "exit")) {
        free(prog); 
        return TRUE;
    }

    c = fgetc(stdin);
    i = 0;
    param = malloc(2*MAXTAM);


    /* lê os parâmetros em forma de string */
    while(c != '\n') {
        param[i++] = c;
        c = fgetc(stdin);
    }
    param[i] = '\0';

    command = malloc(sizeof(char *) * 10);
    index = 0;
    parsed = strtok(param, " ");

    /* transforma os parâmetros numa lista */
    while(parsed != NULL) {
        command[index++] = parsed;
        parsed = strtok(NULL, " ");
    }
    command[index] = NULL; 

    /* protegepracaramba */
    if (!strcmp(prog, "protegepracaramba"))
        protegePraCaramba(param);

    /* liberageral */
    else if (!strcmp(prog, "liberageral"))
        liberaGeral(param);

    /* rodeveja */
    else if (!strcmp(prog, "rodeveja"))
        rodeVeja(command);

    /* rode */
    else if (!strcmp(prog, "rode"))
        rode(command);

    free(command);
    free(param);
    free(prog);

    return FALSE;
}

int main(int argc, char **argv) {
    int flag = 0;

    while(!flag) {
        flag = readCommand();
    }

    return 0;
}
