#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int counter=0;
//加入mutex
pthread_mutex_t mutex1 =PTHREAD_MUTEX_INITIALIZER;

void* child(){
        pthread_mutex_lock(&mutex1); //上鎖
    for (int i=0;i<3;i++){
        int tmp = counter;
        sleep(1);
        counter=tmp+1;
        printf("counter=%d\n",counter);
        printf("pthread_self: %lu \n", pthread_self());
        // printf("process id: %d\n", getpid());
    }
        pthread_mutex_unlock(&mutex1);//解鎖
    pthread_exit(NULL);
}
int main(){
    pthread_t t1, t2;
    pthread_create(&t1,NULL, child,NULL);
    pthread_create(&t2,NULL, child,NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
