#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char* argv[])
{
    struct timeval start, end;
    pid_t pid;
    double elapsed_time;
    gettimeofday(&start, NULL);

    pid = fork();
    if (pid == 0) // child process
    {
        execl("/bin/sh", "sh", "-c", argv[1], (char*)NULL);
    }
    else if (pid > 0) // parent process
    {
        wait(NULL);
        gettimeofday(&end, NULL);

        elapsed_time = (end.tv_sec - start.tv_sec) * 1000.0;      
        elapsed_time += (end.tv_usec - start.tv_usec) / 1000.0;   
        printf("Execution time: %.5f ms\n", elapsed_time);
    }
    else
    {
        printf("Fork failed!\n");
        return 1;
    }

    return 0;
}