-> CODE:

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        printf("Process creation failed!\n");
    }
    else if (pid == 0) {
        printf("\n--- Child Process ---\n");
        printf("Child Process ID (PID) : %d\n", getpid());
        printf("Parent Process ID (PPID): %d\n", getppid());
    }
    else {
        printf("\n--- Parent Process ---\n");
        printf("Parent Process ID (PID): %d\n", getpid());
        printf("Parent's Parent ID (PPID): %d\n", getppid());
        printf("Child Process ID: %d\n", pid);
    }
    return 0;
}

-> OUTPUT:

--- Parent Process ---
Parent Process ID (PID): 12554
Parent's Parent ID (PPID): 12543
Child Process ID: 12555

--- Child Process ---
Child Process ID (PID) : 12555
Parent Process ID (PPID): 12554
