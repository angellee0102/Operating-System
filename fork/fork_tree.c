#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>
int main()
{
        int a,b,c,d,e,f,g,h,i,pid=0,pidd=0,piddd=0,child[9]={0},rv=1;
        pidd = fork();
        switch(pidd){
        case -1:
                printf("ERROR -- something wrong with fork()\n");
                exit(1);
        case 0 :
                pid = fork();
                if(pid<0)
                        exit(1);
                else if(pid==0)
                {
                        printf("---CHILD D process---\n");
                        printf("D: My PID is %d\n", getpid());
                        printf("D: My parent PID is %d\n", getppid());
                        exit(rv);
                        printf("D: I'm out here!\n");
                        piddd=fork();
                        if (piddd<0)exit(1);
                        else if(piddd==0){
                            printf("---CHILD I process---\n");
                            printf("I: My PID is %d\n", getpid());
                            printf("I: My parent PID is %d\n", getppid());
                            exit(rv);
                            printf("I: I'm out here!\n");
                        }
                        else{
                            printf("---PARENT I process---\n");
                            printf("I: My PID is %d\n", getpid());
                            printf("I: My child PID is %d\n", pid);
                            printf("I: I'm now waiting for my child to exit...\n");
                            wait(&rv);
                                               printf("---CHILD H process---\n");
                        printf("H: My PID is %d\n", getpid());
                        printf("H: My parent PID is %d\n", getppid());
                        printf("H: I'm out here!\n");
                        exit(rv);
                        }
                }
                else
                {
                        printf("---PARENT H process---\n");
                        printf("H: My PID is %d\n", getpid());
                        printf("H: My child PID is %d\n", pid);
                        printf("H: I'm now waiting for my child to exit...\n");
                        wait(&rv);
                }
                printf("---CHILD H process---\n");
                printf("H: My PID is %d\n", getpid());
                printf("H: My parent PID is %d\n", getppid());
                printf("H: I'm out here!\n");

            default :
                printf("D: This is the parent process!\n");
                printf("D: My PID is %d\n", getpid());
                printf("D: My child PID is %d\n", pidd);
                printf("D: I'm now waiting for my child to exit...\n");
                wait(&rv);
                printf("D: I'm out here!\n");
        }
        return 0;
}