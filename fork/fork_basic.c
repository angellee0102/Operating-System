#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
    int A[] = {1, 2, 3, 4, 5};
    int sum = 0;
    int fid, i;
    fork();
    fork();
    fork();
    printf("mytest\n");
    //printf("pid %d\n",fork());

    return 0;
}