/*
 *	Doughnut shop
 *	A simple Producer-Consumer relationship with POSIX Threads
 *	author: Kamran
 * */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define TRAY_CAPACITY 100

int tray=0;	//+++++++++ Tray [Critical]

pthread_mutex_t tray_mutex;
pthread_cond_t cond;

/*
 *	Producer thread function
 * */

void * bake(void * arg)
{
	int doughnuts=rand()%25+1;

	/*
	 *	Acquire lock
	 * */

	pthread_mutex_lock(&tray_mutex);

	printf("\nBaker %i wants to bake %i doughnuts : Tray contains %i",(int)arg,doughnuts,tray);

	/*
	 *	Wait while condition is not favorable
	 * */

	while(doughnuts+tray>TRAY_CAPACITY)
		pthread_cond_wait(&cond,&tray_mutex);

	tray+=doughnuts;

	printf("\nBaker %i baked %i doughnuts : Tray contains %i",(int)arg,doughnuts,tray);

	/*
	 *	Signal waiting threads and release lock
	 * */

	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&tray_mutex);

	pthread_exit(NULL);
}

/*
 *	Consumer thread function
 * */

void * consume(void * arg)
{
	int doughnuts=rand()%25+1;

	/*
	 *	Acquire lock
	 * */

	pthread_mutex_lock(&tray_mutex);

	printf("\nCustomer %i wants to consume %i doughnuts : Tray contains %i",(int)arg,doughnuts,tray);

	/*
	 *	Wait while condition is not favorable
	 * */

	while(tray-doughnuts<0)
		pthread_cond_wait(&cond,&tray_mutex);

	tray-=doughnuts;

	printf("\nCustomer %i consumed %i doughnuts : Tray contains %i",(int)arg,doughnuts,tray);

	/*
	 *	Signal waiting threads and release lock
	 * */

	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&tray_mutex);

	pthread_exit(NULL);
}

#define BAKERS 5
#define CUSTOMERS 5

int main(int argc, char ** argv)
{
	int i;				//+++++++++ Looping index
	int result;			//+++++++++ For error detection
	void * t_return;		//+++++++++ Thread return value
	pthread_t baker[BAKERS];	//+++++++++ Baker threads
	pthread_t customer[CUSTOMERS];	//+++++++++ Customer threads

	/*
	 *	Initialize mutex and condition variable
	 * */

	result=pthread_mutex_init(&tray_mutex,NULL);

	if(result!=0)
	{
		perror("\nMutex initialization failed");
		exit(EXIT_FAILURE);
	}

	result=pthread_cond_init(&cond,NULL);

	if(result!=0)
	{
		perror("\nCondition variable initialization failed");
		exit(EXIT_FAILURE);
	}

	/*
	 *	Setting seed for pseudo-random numbers
	 * */

	srand(getpid());

	/*
	 *	Creating Baker and Customer threads [Producers & Consumers]
	 * */

	for(i=0;i<BAKERS;i++)
	{
		result=pthread_create(&baker[i],NULL,bake,(void *)i);

		if(result!=0)
		{
			perror("\nThread creation failed");
			exit(EXIT_FAILURE);
		}

		printf("\nBaker %i ready to bake",i);
	}

	for(i=0;i<CUSTOMERS;i++)
	{
		result=pthread_create(&customer[i],NULL,consume,(void *)i);

		if(result!=0)
		{
			perror("\nThread creation failed");
			exit(EXIT_FAILURE);
		}

		printf("\nCustomer %i ready to consume",i);
	}

	/*
	 *	Wait for threads to finish execution
	 * */

	for(i=0;i<BAKERS;i++)
	{
		result=pthread_join(baker[i],&t_return);

		if(result!=0)
		{
			perror("\nThread join failed");
			exit(EXIT_FAILURE);
		}
	}

	for(i=0;i<CUSTOMERS;i++)
	{
		result=pthread_join(customer[i],&t_return);

		if(result!=0)
		{
			perror("\nThread join failed");
			exit(EXIT_FAILURE);
		}
	}

	/*
	 *	Clean-up mutex & condition variable
	 * */

	pthread_mutex_destroy(&tray_mutex);
	pthread_cond_destroy(&cond);

	printf("\n");

	return 0;
}