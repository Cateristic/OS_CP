#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>  // for sleep()

#define N 10

sem_t mutex, empty, full;
int in = 0, out = 0, buf[N];

int produce_item() {
    return rand() % 100;
}

void insert_item(int item) {
    buf[in] = item;
    in = (in + 1) % N;
}

int remove_item() {
    int item = buf[out];
    out = (out + 1) % N;
    return item;
}

void* producer(void* arg) {
    while (1) {
        int item = produce_item();
        sem_wait(&empty);
        sem_wait(&mutex);
        insert_item(item);
        printf("Produced item: %d\n", item);
        sem_post(&mutex);
        sem_post(&full);
        sleep(2);  // slow down producer
    }
}

void* consumer(void* arg) {
    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);
        int item = remove_item();
        printf("Consumed item: %d\n", item);
        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main() {
    pthread_t pro, con;

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);

    pthread_create(&pro, NULL, producer, NULL);
    pthread_create(&con, NULL, consumer, NULL);

    pthread_join(pro, NULL);
    pthread_join(con, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}