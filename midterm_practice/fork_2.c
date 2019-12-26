#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
    fork();
    fork();
    fork();
    fork();
    fork();
    printf("hi\n");

    return 0;
}