#include <stdio.h> 
#include <pthread.h>
#define NLOOP 50
int counter = 0; /* incremented by threads */
void *threadfn(void *);
int main(int argc, char **argv)
{ 
	pthread_t tid1, tid2,tid3; 
	pthread_create(&tid1, NULL, &threadfn, NULL);
       	pthread_create(&tid2, NULL, &threadfn, NULL);
       	pthread_create(&tid3, NULL, &threadfn, NULL); /* wait for both threads to terminate */ 
	pthread_join(tid1, NULL); 
	pthread_join(tid2, NULL); 
	pthread_join(tid3, NULL); 
	return 0; 
} 
void *threadfn(void *vptr) 
{ 
	int i, val; 
	for (i = 0; i < NLOOP; i++) { 
		val = counter; 
		printf("%x: %d \n", (unsigned int)pthread_self(),  val+1); 
		counter = val+1; 
	} 
	return NULL; 
}
