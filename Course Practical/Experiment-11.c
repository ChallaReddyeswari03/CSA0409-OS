-> CODE :

#include <stdio.h>
#include <pthread.h>
void *display(void *arg)
{
    printf("Thread is executing.\n");
    return NULL;
}
int main()
{
    pthread_t t1;
    pthread_create(&t1, NULL, display, NULL);
    pthread_join(t1, NULL);
    printf("Thread execution completed.\n");
    return 0;
}

-> OUTPUT :

Thread is executing.
Thread execution complet
