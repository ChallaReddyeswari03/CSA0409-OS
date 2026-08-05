#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
    fork();
    printf("Process ID:%d\n",getpid());
    fork();
    printf("Process ID: %d\n",getpid());
    wait(NULL);
    wait(NULL);
    return 0;
}
