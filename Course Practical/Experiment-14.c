-> CODE :

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex;
void *thread_function(void *arg)
{
    int id = *(int *)arg;
    pthread_mutex_lock(&mutex);
    printf("Thread %d entered Critical Section\n", id);
    sleep(2);
    printf("Thread %d leaving Critical Section\n", id);
    pthread_mutex_unlock(&mutex);
    return NULL;
}
int main()
{
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&t1, NULL, thread_function, &id1);
    pthread_create(&t2, NULL, thread_function, &id2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&mutex);
    return 0;
}

-> OUTPUT :

Thread 2 entered Critical Section
Thread 2 leaving Critical Section
Thread 1 entered Critical Section
Thread 1 leaving Critical Section
