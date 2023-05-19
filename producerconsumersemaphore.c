#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#define buffersize 5
sem_t empty;
sem_t full;
int in = 0, out = 0, count = 0;
int buffer[buffersize];
void *producer()
{
int data, temp;
temp = rand() % 3;
for(int i = 0; i<100; i++)
{
data = rand() % 100;
sleep(temp);
sem_wait(&empty);
buffer[in] = data;
count += 1;
printf("\nProducer Inserted Data %d at %d", data, in);
in = (in + 1) % buffersize;
sem_post(&full);
if (count == 5){
printf("\nBuffer is full");
}
}
}
void *consumer()
{
int temp, data;
temp = rand() % 5;
for(int i = 0; i<100; i++)
{
sleep(temp);
sem_wait(&full);
data = buffer[out];
count -= count;
printf("\nConsumer Consumed Data %d from %d", data, out);
out = (out + 1) % buffersize;
sem_post(&empty);
}
}
int main()
{
int n = 0;
pthread_t prod, cons;
sem_init(&empty, 0, buffersize);
sem_init(&full, 0, 0);
pthread_create(&prod, NULL, &producer, NULL);
pthread_create(&cons, NULL, &consumer, NULL);
pthread_join(cons, NULL);
pthread_join(prod, NULL);
pthread_join(cons, NULL);
pthread_join(prod, NULL);
pthread_join(cons, NULL);
pthread_join(prod, NULL);
return 0;
}