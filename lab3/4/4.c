#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/ipc.h>

#define BUFFER_SIZE 10

int main() {
    const char *name = "bounded_buffer";
    const int SIZE = (BUFFER_SIZE + 1) * sizeof(int);
    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) 
    {
        perror("shm_open");
        return 1;
    }
    if (ftruncate(shm_fd, SIZE) == -1) 
    {
        perror("ftruncate");
        return 1;
    }

    int *buffer = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (buffer == MAP_FAILED) 
    {
        perror("mmap");
        return 1;
    }
    for (int i = 0; i <= BUFFER_SIZE; ++i) 
    {
        buffer[i] = 0;
    }
    pid_t pid = fork();
    if (pid < 0) 
    {
        perror("fork");
        return 1;
    } 
    else if (pid == 0) // Consumer
    { 
        int total = 0;
        while (1) 
        {
            for (int i = 0; i < BUFFER_SIZE; ++i) 
            {
                if (buffer[i] != 0) 
                {
                    printf("Send to buffer: %d\n", buffer[i]);
                    total += buffer[i];
                    buffer[i] = 0; 
                    printf("Sum = %d\n", total);
                    if (total > 100) 
                    {
                        printf("Consumner: Sum is over 100. Stopping.\n");
                        buffer[BUFFER_SIZE] = 1;
                        exit(0);
                    }
                }
            }
        }
    } 
    else // Parent process (Producer)
    { 
        srand(time(NULL)); 
        printf("Parent PID: %d\n", getpid());
        while (1) {
            int is_full = 1;
            for (int i = 0; i < BUFFER_SIZE; ++i) 
            {
                if (buffer[i] == 0) 
                {
                    is_full = 0;
                    break;
                }
            }
            if (!is_full) 
            {
                int num = rand() % 11 + 10;
                for (int i = 0; i < BUFFER_SIZE; ++i) 
                {
                    if (buffer[i] == 0) 
                    {
                        buffer[i] = num;
                        break;
                    }
                }
            }

            usleep(1000000); // 1 second            
            if (buffer[BUFFER_SIZE] == 1) 
            {
                printf("Producer: Consumer requests to stop. Stopping.\n");
                break;
            }
        }
        wait(NULL);
        shm_unlink(name);
    }

    return 0;
}