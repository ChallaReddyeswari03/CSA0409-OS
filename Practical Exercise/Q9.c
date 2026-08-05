 #include <stdio.h>
#define SIZE 5
int buffer[SIZE];
int front=0,rear=0,count=0;
void produce(int item){
    if(count==SIZE)
        printf("Buffer Full\n");
    else{
        buffer[rear]=item;
        rear=(rear+1)%SIZE;
        count++;
    }
}
void consume(){
    if(count==0)
        printf("Buffer Empty\n");
    else{
        printf("Consumed %d\n",buffer[front]);
        front=(front+1)%SIZE;
        count--;
    }
}
int main(){
    produce(10);
    produce(20);
    produce(30);
    consume();
    consume();

    return 0;
}    
     
