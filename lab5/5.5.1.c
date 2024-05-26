#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>

#define INITIAL_SELLS 0
#define INITIAL_PRODUCTS 0
#define EXTRA_SELLS 235

int sells = INITIAL_SELLS, products = INITIAL_PRODUCTS;
sem_t sem, sem1;

void* processA(void* arg) {
    while (1) {
        sem_wait(&sem);
        sells++;
        printf("SELL = %d\n", sells);
        printf("SELL_1 = %d\n", sells + EXTRA_SELLS);
        sem_post(&sem1);
    }
    return NULL;
}

void* processB(void* arg) {
    while (1) {
        sem_wait(&sem1);
        products++;
        printf("PRODUCT = %d\n", products);
        sem_post(&sem);
    }
}

int main() {
    sem_init(&sem, 0, 1); 
    sem_init(&sem1, 0, EXTRA_SELLS); 

    pthread_t pA, pB;
    pthread_create(&pA, NULL, processA, NULL);
    pthread_create(&pB, NULL, processB, NULL); 
    pthread_join(pA, NULL);
    pthread_join(pB, NULL);

    sem_destroy(&sem);
    sem_destroy(&sem1);

    return 0; 
}
