#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

int x = 0;

void* processA(void* mess) {
    while (1) {
        x++;
        if (x == 20) {
            x = 0;
        }
        printf("Process A: x = %d\n", x);
    }
}

void* processB(void* mess) {
    while (1) {
        x++;
        if (x == 20) {
            x = 0;
        }
        printf("Process B: x = %d\n", x);
    }
}

int main() {
    pthread_t threadA, threadB;

    pthread_create(&threadA, NULL, &processA, NULL);
    pthread_create(&threadB, NULL, &processB, NULL);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    return 0;
}