-> CODE :

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
int main()
{
    key_t key = 1234;
    int shmid;
    char *str;
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    str = (char *)shmat(shmid, NULL, 0);
    printf("Writing to shared memory...\n");
    strcpy(str, "Hello from Shared Memory!");
    printf("Data in shared memory: %s\n", str);
    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

-> OUTPUT :

Writing to shared memory...
Data in shared memory: Hello from Shared Memory!
