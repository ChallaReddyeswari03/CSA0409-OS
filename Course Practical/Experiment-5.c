-> CODE :

#include <stdio.h>
int main() {
    int n, i, j;
    int bt[10], p[10], wt[10], tat[10], temp;
    float avgwt = 0, avgtat = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Burst Time and Priority:\n");
    for(i = 0; i < n; i++) {
        printf("P%d BT Priority: ", i + 1);
        scanf("%d%d", &bt[i], &p[i]);
    }
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(p[i] > p[j]) {
                temp = p[i]; p[i] = p[j]; p[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
            }
        }
    }

    wt[0] = 0;
    for(i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];
    for(i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        avgwt += wt[i];
        avgtat += tat[i];
    }
    printf("\nPriority\tBT\tWT\tTAT\n");
    for(i = 0; i < n; i++)
        printf("%d\t\t%d\t%d\t%d\n", p[i], bt[i], wt[i], tat[i]);
    printf("\nAverage Waiting Time = %.2f", avgwt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgtat / n);
    return 0;
}

-> OUTPUT :

Enter number of processes: 5
Enter Burst Time and Priority:
P1 BT Priority: 6
7
P2 BT Priority: 10
6
P3 BT Priority: 6
8
P4 BT Priority: 
9
8
P5 BT Priority: 9
6
Priority        BT      WT      TAT
6               10      0       10
6               9       10      19
7               6       19      25
8               9       25      34
8               6       34      40

Average Waiting Time = 17.60
Average Turnaround Time = 25.60
