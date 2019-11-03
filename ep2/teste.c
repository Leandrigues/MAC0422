#include <unistd.h>
#include <lib.h>
#include <stdio.h>
#include <sys/types.h>
int main(char* argc, char** argv) {
	pid_t pid = fork();
	int status, i = 0;
	if(pid == 0) {
            while(i < 1000000000) {
		    i++;}
	}
	if(pid != 0) {
	    printf("Executando batch(%d) em teste.c\n", pid);
	    batch(pid);
	    waitpid(pid, &status, 0);
	}
	
	return 0;
}
