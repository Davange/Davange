#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include<unistd.h>
#define buffersize 5
sem_t empty;
sem_t full;
int in = 0, out = 0;
int buffer[buffersize];
pthread_mutex_t mutex;
void *producer()
{
int data, temp;
temp = rand()%3;
//printf("\n\nProducer\n\n");
while(in <= 5)
{
data = rand()%100;
sleep(temp);
sem_wait(&empty);
pthread_mutex_lock(&mutex);
buffer[in] = data;
printf("\n\nProducer Inserted Data %d at %d",data,in);
in = (in+1)%buffersize;
pthread_mutex_unlock(&mutex);
sem_post(&full);
}
}
void *consumer()
{
int temp, data;
temp = rand()%5;
// printf("\n\nConsumer\n\n");
while(out <= 5 && out >= 0)
{
sleep(temp);
sem_wait(&full);
pthread_mutex_lock(&mutex);
data = buffer[out];
printf("\n\nConsumer Consumed Data %d from %d",data,out);
out = (out+1)%buffersize;
pthread_mutex_unlock(&mutex);
sem_post(&empty);
}
}
int main()
{
pthread_t prod, cons;
pthread_mutex_init(&mutex, NULL);
sem_init(&empty, 0, buffersize);
sem_init(&full, 0, 0);
pthread_create(&prod, NULL, &producer, NULL);
pthread_create(&cons, NULL, &consumer, NULL);
pthread_join(prod, NULL);
pthread_join(cons, NULL);
return 0;
}