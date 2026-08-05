#include <stdio.h>
#define SIZE 5
int queue[SIZE], front = -1,rear = -1;
void enqueue(int x){
    if (rear== SIZE -1)
    printf("Queue FULL\n");
   else {
       if (front == -1)
           front = 0;
       queue[++rear] = x;
   }
}
void display() {
    int i;
    for (i= front; i <= rear; i++)
    {
        printf("P%d ",queue[i]);
    }
}
 int main() {
    enqueue(1);
    enqueue(2);
    enqueue(3);
    printf("Ready Queue: ");
    display();
    return 0;
}
