#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
    int pid = 0;
    int rv = 0;
    pid = fork();
    switch (pid)
    {
    case -1:
        printf("Error with fork\n");
        exit(1);
    case 0:
        printf("this is child\n");
        printf("my id is %d\n", getpid());
        printf("parent's id is %d\n", getppid());
    default:
        printf("this is parent\n");
        printf("my id is %d\n", getpid());
        printf("my child id is %d\n", pid);
    }

    return 0;
}