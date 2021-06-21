#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<semaphore.h>


int n = 35000, i = 0;
sem_t sm1, sm2;

static int count = 0;
int a[40000];
////////////////////////
void wait(int sec){
	clock_t ew;
	ew = clock() + sec* CLOCKS_PER_SEC;
	while(clock() < ew){
	}
}
////////////////////////
void* PROS1(){
	while(1){
		if (count < n){
			a[i++] = rand()%(n-1);
			count++;
			printf("\n[PUSH] Number of elements in array a: %2d", count);
		}
		wait(1);
		sem_post(&sm1);

	}
}
////////////////////////
void* PROS2(){
	int m;
	while(1){
		sem_wait(&sm1);
		m = rand() % n;
		
		if (count < m +1){
			printf("\n[POP] Nothing in array a");
		}
		else{
			count--;
			for(int j = m;j<count;j++){
				a[j] = a[j+1];
			}
			printf("\n[POP] Number of elements in array a: %2d", count);
		}

	}
}
void main()
{

	sem_init(&sm1,1,0);
	sem_init(&sm2,0,0);
	
	pthread_t th1, th2;
	pthread_create(&th1, NULL,PROS1,NULL);
	pthread_create(&th2, NULL,PROS2,NULL);
	while(1);
}
		
			
