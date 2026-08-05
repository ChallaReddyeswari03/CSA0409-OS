#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("Child Process Running...\n");
        sleep(3);
        printf("Child Process Completed.\n");
    }
    else
    {
        wait(NULL);
        printf("Parent Process Resumed.\n");
    }
    return 0;
}
