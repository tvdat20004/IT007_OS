#include <stdio.h>
#include <pthread.h>

int x = 0;
pthread_mutex_t lock;

void* processA(void* arg) {
    while(1) {
        pthread_mutex_lock(&lock);
        x = (x + 1) % 20;
        printf("Process A: %d\n", x);
        pthread_mutex_unlock(&lock);
    }
}

void* processB(void* arg) {
    while(1) {
        pthread_mutex_lock(&lock);
        x = (x + 1) % 20;
        printf("Process B: %d\n", x);
        pthread_mutex_unlock(&lock);
    }
}

int main() {
    pthread_t thread_id1, thread_id2;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&thread_id1, NULL, processA, NULL);
    pthread_create(&thread_id2, NULL, processB, NULL);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    return 0;
}