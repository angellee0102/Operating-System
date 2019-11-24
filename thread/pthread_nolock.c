#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int counter = 0;

void *child(void *arg)
{
    for (int i = 0; i < 3; ++i)
    {
        int tmp = counter;
        sleep(1);
        counter = tmp + 1;
        printf("Counter=%d\n", counter);
        printf("pthread_self: %lu \n", pthread_self());
        printf("process id: %d\n", getpid());
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, child, NULL);
    pthread_create(&t2, NULL, child, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}