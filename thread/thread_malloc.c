#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *child(void *arg)
{
    int *input = (int *)arg;
    int *result = malloc(sizeof(int) * 1);
    result[0] = input[1] - input[0];
    pthread_exit((void *)result);
}

int main()
{
    pthread_t t;
    void *ret;
    int input[2] = {10, 20};
    pthread_create(&t, NULL, child, (void *)input);

    pthread_join(t, &ret);
    int *result = (int *)ret;

    printf("%d - %d =%d\n", input[1], input[0], result[0]);
    free(result);
    return 0;
}