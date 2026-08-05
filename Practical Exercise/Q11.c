#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
int main()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("Executing ls -l...\n");
        execl("/bin/ls", "ls", "-l", NULL);
    }
    else
    {
        wait(NULL);
        printf("Parent Process Finished.\n");
    }
    return 0;
}
