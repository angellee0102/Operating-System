#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int static count = 0;
    int A[] = {1, 2, 3, 4, 5};
    int sum = 0;
    int fid, i;
    fork();
    fork() && fork() || fork();
    fork();
    count += 1;

    printf("mytest count: %d\n", count);
    //printf("pid %d\n",fork());

    return 0;
}
