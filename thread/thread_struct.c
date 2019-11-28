#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//#include <sys/types.h>
typedef struct my_data
{
    int a;
    int b;
    int result;
} my_data;

void *child(void *arg)
{
    my_data *data = (my_data *)arg;

    int a = data->a;
    int b = data->b;
    int result = b - a;

    data->result = result;
    pthread_exit(NULL);
}

int main()
{
    pthread_t t;
    my_data data;
    data.a = 15;
    data.b = 50;
    pthread_create(&t, NULL, child, (void *)&data);
    pthread_join(t, NULL);

    printf("pthread_self: %lu \n", pthread_self());
    printf("%d - %d =%d\n", data.b, data.a, data.result);
    return 0;
}