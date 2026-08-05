-> CODE :

#include <stdio.h>
#include <stdlib.h>
int mutex = 1;
int full = 0;
int empty = 5, x = 0;
int wait(int s)
{
    return (--s);
}
int signal(int s)
{
    return (++s);
}
void producer()
{
    mutex = wait(mutex);
    full = signal(full);
    empty = wait(empty);
    x++;
    printf("Producer produces item %d\n", x);
    mutex = signal(mutex);
}
void consumer()
{
    mutex = wait(mutex);
    full = wait(full);
    empty = signal(empty);
    printf("Consumer consumes item %d\n", x);
    x--;
    mutex = signal(mutex);
}
int main()
{
    int choice;
    while(1)
    {
        printf("\n1. Produce");
        printf("\n2. Consume");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                if((mutex == 1) && (empty != 0))
                    producer();
                else
                    printf("Buffer is Full!\n");
                break;
            case 2:
                if((mutex == 1) && (full != 0))
                    consumer();
                else
                    printf("Buffer is Empty!\n");
                break;
            case 3:
                exit(0);

            default:
                printf("Invalid Choice\n");
        }
    }

    return 0;
}

-> OUTPUT :

1. Produce
2. Consume
3. Exit
Enter your choice: 1
Producer produces item 1

1. Produce
2. Consume
3. Exit
Enter your choice: 1
Producer produces item 2

1. Produce
2. Consume
3. Exit
Enter your choice: 2
Consumer consumes item 2

1. Produce
2. Consume
3. Exit
Enter your choice: 2
Consumer consumes item 1

1. Produce
2. Consume
3. Exit
Enter your choice: 3
