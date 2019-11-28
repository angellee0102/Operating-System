#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// https://stackoverflow.com/questions/48556171/threading-in-c-producer-consumer-taking-forever-to-run?fbclid=IwAR2-hT1vklvCAmbsBI0Af7gHAOEsEv3rb1JNKW1KFI1Z4LWTuYFRnOi9cVI
volatile int P = 0;
volatile int C = 0;
volatile int value = 0;

void produce(int v)
{
    value = v;
    P++;
}
int consume()
{
    int v = value;
    C++;
    return v;
}

void waitForConsumer()
{
    while (C != P)
        ;
}

void waitForProducer()
{
    while (C == P)
        ;
}


void *producer(void *n)
{
    int i = *(int *)n;
    while (1) {
        waitForConsumer();
        printf("Producing item %d\n", i);
        produce(i);
        i--;
        if (i < 0) {
            printf("Exiting: producer\n");
            pthread_exit(0);
        }
    }
}

void *consumer(void *n)
{
    while (1) {
        waitForProducer();
        int v = consume();
        printf("Consumed item %d\n", v);
        if (v == 0) {
            printf("Exiting: consumer\n");
            pthread_exit(0);
        }
    }
}

int main(int argc, char *argv[])
{

    int pro = 5;

    pthread_t pid, cid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    pthread_create(&pid, &attr, producer, (void *)&pro);
    pthread_create(&cid, &attr, consumer, NULL);

    pthread_join(pid, NULL);
    pthread_join(cid, NULL);
}