#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
    int pid_B;
    int pid;
    int pid_G;
    int pid_C;
    int a=0;
    pid_B = fork();
    if(pid_B==0){
        printf("Child Process B:\npid: %d\nppid:%d\n",getpid(),getppid());
        int pid_E;
        pid_E=fork();
        if(pid_E==0){
            printf("Child Process E:\npid: %d\nppid:%d\n",getpid(),getppid());
            int pid_H;
            pid_H=fork();
            if(pid_H==0){
                printf("Child Process H:\npid: %d\nppid:%d\n",getpid(),getppid());
                int pid_I;
                pid_I=fork();
                if(pid_I==0){
                    printf("Child Process I:\npid: %d\nppid:%d\n",getpid(),getppid());
                    exit(a);
                }
                else if(pid_I>0){
                    wait(&a);
                }
            }
            else if(pid_H>0){
                wait(&a);
            }
            wait(&a);
        }
        if(pid_E>0){
            int pid_D;
            pid_D=fork();
            if(pid_D==0){
                printf("Child Process D:\npid: %d\nppid:%d\n",getpid(),getppid());
                exit(a);
            }
            else if(pid_D>0){
                int pid_F;
                pid_F=fork();
                if(pid_F==0){
                    printf("Child Process F:\npid: %d\nppid:%d\n",getpid(),getppid());
                    exit(a);
                }
                else if(pid_F>0){
                    wait(&a);  
                }
                //printf("Parents Process D:\npid: %d\nppid:%d\n",getpid(),getppid());
                wait(&a);    
            }
            wait(&a);
        }
        wait(&a);
    }
    /*else{
         printf("Parent Process B:\npid: %d\nppid:%d\n",getpid(),getppid());
    }*/
    if(pid_B>0){
        pid = fork();
        if(pid>0){
            printf("Parents Process B:\npid: %d\nppid:%d\n",getpid(),getppid());
            wait(&a);
            //printf("%d\n", pid);            
            pid_C=fork();
            if(pid_C==0){
                printf("Child Process C:\npid: %d\nppid:%d\n",getpid(),getppid());
                int pid_G;
                pid_G=fork();
                if(pid_G==0){
                    printf("Child Process G:\npid: %d\nppid:%d\n",getpid(),getppid());
                    exit(a);
                }
                else if(pid_G>0){
                    wait(&a);
                }
                wait(&a);
                
            }
            else if(pid_C>0){ 
                wait(&a);     
            }
            
            
        
        
        /*else if(pid==0){
            printf("Child Process C:\npid: %d\nppid:%d\n",getpid(),getppid());
            int pid_G;
            pid_G=fork();
            if(pid_G>0){
                printf("\nParent Process :\npid: %d\nppid:%d\n",getpid(),getppid());   
            }
            else if(pid_G==0){
                 printf("Child Process G:\npid: %d\nppid:%d\n",getpid(),getppid());
            }*/
        }
        wait(&a);
    }
    

}
/*
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void procStatus(int level) {
   printf("L%d: PID[%d] (PPID[%d])\n", level, getpid(), getppid());
   fflush(NULL);
}

void levelFork(int *level,int maxlevel) {
    int locallevel= *level;
    while(locallevel!=maxlevel){
        int pid = fork();
        printf("pid : %d\n", pid);
        if (pid  == 0){
            (*level)++; // childs level is higher
            levelFork(level,maxlevel);
            return;
        }
        printf("pid : %d\n", pid);
        locallevel++;
        wait(NULL);
    }
}

int main() {
        int level = 0;
        int maxlevel=2;

        levelFork(&level,maxlevel);
        procStatus(level);

        return 0;
}*/
