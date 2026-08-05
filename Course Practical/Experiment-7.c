-> CODE :

#include <stdio.h>
int main() {
    int n, i, j, temp;
    int bt[10];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Burst Time:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &bt[i]);
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(bt[i] > bt[j]) {
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
            }
        }
    }
    printf("\nExecution Order:\n");
    for(i = 0; i < n; i++)
        printf("%d ", bt[i]);
    return 0;
}

-> OUTPUT :

Enter number of processes: 4
Enter Burst Time:
6
2
8
4
Execution Order:
2 4 6 8 
