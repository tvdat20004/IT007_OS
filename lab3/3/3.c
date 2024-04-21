#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handle_sigint(int sig) 
{
    printf("\ncount.sh has stopped\n");
    exit(0);
}

int main(int argc, char* argv[])
{
    printf("Welcome to IT007, I am 22520235!\n");
    signal(SIGINT, handle_sigint);

    pid_t pid = fork();
    if (pid == 0) 
    {
        execl("/bin/sh", "sh", "count.sh", "120", (char*)NULL);
    }
    else if (pid > 0)
    {
        wait(NULL);
    }
    else
    {
        printf("Fork failed!\n");
        return 1;
    }

    return 0;
}