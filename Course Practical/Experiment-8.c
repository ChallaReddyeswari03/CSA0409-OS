-> CODE :

#include <stdio.h>
int main() {
    int bt[10], rem[10], n, tq;
    int i, time = 0, done;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Burst Time:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
        rem[i] = bt[i];
    }
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);
    printf("\nExecution Order:\n");
    do {
        done = 1;
        for(i = 0; i < n; i++) {
            if(rem[i] > 0) {
                done = 0;
                if(rem[i] > tq) {
                    time += tq;
                    rem[i] -= tq;
                } else {
                    time += rem[i];
                    rem[i] = 0;
                }
                printf("P%d ", i + 1);
            }
        }
    } while(!done);
    return 0;
}

-> OUTPUT :

Enter number of processes: 3
Enter Burst Time:
5
4
2
Enter Time Quantum: 2
Execution Order:
P1 P2 P3 P1 P2 P1 
