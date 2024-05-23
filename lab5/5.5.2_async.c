#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int* array;
int arraySize;
int currentSize = 0;

void rearrangeArray(int* array, int index) {
    if (index == currentSize) {
        currentSize--;
    } else {
        for (int i = index; i < currentSize - 1; ++i) {
            array[i] = array[i + 1];
        }
        currentSize--;
    }
}

void* processA(void* mess) {
    while (1) {
        srand((int)time(0));
        array[currentSize] = rand();
        currentSize++;
        printf("Number of elements in array: %d\n", currentSize);
    }
}

void* processB(void* mess) {
    while (1) {
        srand((int)time(0));
        if (currentSize == 0) { 
            printf("Nothing in array\n");
        } else {
            int r = rand() % currentSize;
            rearrangeArray(array, r);
            printf("Number of elements in array after removal: %d\n", currentSize);
        }
    }
}

int main() {
    printf("Enter number of elements: \n");
    scanf("%d", &arraySize);
    array = (int*)malloc(arraySize * sizeof(int));
    pthread_t threadA, threadB;
    pthread_create(&threadA, NULL, &processA, NULL);
    pthread_create(&threadB, NULL, &processB, NULL);
    while (1) {}
    return 0;
}