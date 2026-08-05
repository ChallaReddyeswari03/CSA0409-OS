#include <stdio.h>
#include<pthread.h>
void *thread1(void *arg) {
    int i;
    for (i=1;i<=5;i+=2)
        printf("%d\n",i);
        return NULL;
}
 void *thread2(void *arg) {
     int i;
     for(i=2;i<=5;i+=2)
          printf("%d\n",i);
    return NULL;
}
int main() {
    pthread_t t1,t2;
    pthread_create(&t1,NULL,thread1,NULL);
    pthread_create(&t2,NULL,thread2,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
