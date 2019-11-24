#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    printf("%ld\n", (long)getpid());
    printf("%ld\n", (long)getppid());
    printf("%ld\n", (long)getuid());
    return 0;
}