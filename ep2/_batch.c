#include <lib.h>
#include <unistd.h>
#include <minix/syslib.h>
#include <stdio.h>

PUBLIC int batch(pid)
int pid;
{
    message m;
    pid_t processCaller;
    int processCallerInt;
   
   printf("1\n"); 
    processCaller = getpid();
    
   printf("2\n"); 
    processCallerInt = processCaller;
    
   printf("3\n"); 
    m.m1_i1 = pid;

   printf("4\n"); 
    m.m1_i2 = processCallerInt;

   printf("5\n"); 
    
   printf("Chamando batch(%d)\n", m.m1_i1);
    _syscall(0, 70, &m);

   printf("6\n"); 
    return 0;
}
