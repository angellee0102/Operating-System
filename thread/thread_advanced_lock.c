#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int counter=1;
struct input
{
        pthread_mutex_t input_lock[5];
        int int_val[5];
        float float_val[
} input;

void *add_thread();

int main()
{

        for(int i=0;i<5;i++)
        {
        input.input_lock[i]= (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
        }
        pthread_t t1,t2,t3,t4,t5;
        pthread_create(&t1,NULL,add_thread,NULL);
        pthread_create(&t2,NULL,add_thread,NULL);
        pthread_create(&t3,NULL,add_thread,NULL);
        pthread_create(&t4,NULL,add_thread,NULL);
        pthread_create(&t5,NULL,add_thread,NULL);

        pthread_join(t1,NULL);
        pthread_join(t2,NULL);
        pthread_join(t3,NULL);
        pthread_join(t4,NULL);
        pthread_join(t5,NULL);

        for(int j=0;j<5;j++)
        {
        printf("int_val[%d]: %d\n",j,input.int_val[j]);
        printf("float_val[%d]: %f\n",j,input.float_val[j]);
        }

        return 0;
}
void *add_thread()
{
        int inv=counter;
        for(int i=0;i<10000;i++)
        {
        pthread_mutex_lock(&input.input_lock[i%5]);
        input.int_val[i%5]+=inv;
        input.float_val[i%5]+=(float)2.5*inv;
        pthread_mutex_unlock(&input.input_lock[i%5]);
        }

        pthread_exit(NULL);
}

        
                                