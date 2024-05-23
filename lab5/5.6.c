#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int x[6];
int w, v, y, z, ans;

sem_t sem[8];

void *process1(void *arg) {
    w = x[0] * x[1];
    sem_post(&sem[0]);
    sem_post(&sem[1]);
    pthread_exit(NULL);
}

void *process2(void *arg) {
    v = x[2] * x[3];
    sem_post(&sem[2]);
    sem_post(&sem[3]);
    pthread_exit(NULL);
}

void *process3(void *arg) {
    sem_wait(&sem[2]);
    y = v * x[4];
    sem_post(&sem[4]);
    pthread_exit(NULL);
}

void *process4(void *arg) {
    sem_wait(&sem[3]);
    z = v * x[5];
    sem_post(&sem[5]);
    pthread_exit(NULL);
}

void *process5(void *arg) {
    sem_wait(&sem[0]);
    sem_wait(&sem[4]);
    y = w * y;
    sem_post(&sem[6]);
    pthread_exit(NULL);
}

void *process6(void *arg) {
    sem_wait(&sem[1]);
    sem_wait(&sem[5]);
    z = w * z;
    sem_post(&sem[7]);
    pthread_exit(NULL);
}

void *process7(void *arg) {
    sem_wait(&sem[6]);
    sem_wait(&sem[7]);
    ans = y + z;
    pthread_exit(NULL);
}
void* (*process[7])(void*) = {process1, process2, process3, process4, process5, process6, process7};
int main() {
    pthread_t thread[7];

    for(int i = 0; i < 6; i++) {
        printf("Enter the value for x%d: ", i+1);
        scanf("%d", &x[i]);
    }

    for(int i = 0; i < 8; i++) {
        sem_init(&sem[i], 0, 0);
    }

    for(int i = 0; i < 7; i++) {
        pthread_create(&thread[i], NULL, process[i], NULL);
    }

    for(int i = 0; i < 7; i++) {
        pthread_join(thread[i], NULL);
    }

    printf("Ans: %d\n", ans);

    return 0;
}