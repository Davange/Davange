#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
sem_t wrt;
pthread_mutex_t mutex;
int data = 0, reader_count = 0;
void *reader(void *arg) {
int thread_num = *(int *)arg;
while (1) {
pthread_mutex_lock(&mutex);
sem_wait(&mutex);
reader_count++;
if (reader_count == 1) {
sem_wait(&wrt);
}
pthread_mutex_unlock(&mutex);
printf("Reader %d read data: %d\n", thread_num, data);
sleep(1);
pthread_mutex_lock(&mutex);
reader_count--;
if (reader_count == 0) {
sem_post(&wrt);
}
pthread_mutex_unlock(&mutex);
sleep(1);
}
}
void *writer(void *arg) {
int thread_num = *(int *)arg;
while (1) {
sem_wait(&wrt);
data++;
printf("Writer %d wrote data: %d\n", thread_num, data);
sleep(1);
sem_post(&wrt);
sleep(1);
}
}
int main() {
pthread_mutex_init(&mutex, NULL);
sem_init(&wrt, 0, 1);
pthread_t reader_thread[5], writer_thread[5];
int i;
for (i = 0; i < 5; i++) {
int *arg = malloc(sizeof(*arg)); *arg = i + 1;
pthread_create(&reader_thread[i], NULL, reader, arg);
pthread_create(&writer_thread[i], NULL, writer, arg);
}
for (i = 0; i < 5; i++) {
pthread_join(reader_thread[i], NULL);
pthread_join(writer_thread[i], NULL);
}
pthread_mutex_destroy(&mutex);
sem_destroy(&wrt);
return 0;
}