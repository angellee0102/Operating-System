#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    if (fork())
    {
        wait(NULL);
        fork() || fork();
        wait(NULL);
    }
    else
    {
        wait(NULL);
        if (fork())
        {
            wait(NULL);
            fork() && fork();
            wait(NULL);
        }
        else
        {
            wait(NULL);
            fork() || fork();
            wait(NULL);
        }
        wait(NULL);
    }
    printf("My PID is %d\n", getpid());
    printf("My parent PID is %d\n", getppid());
    return 0;
}
