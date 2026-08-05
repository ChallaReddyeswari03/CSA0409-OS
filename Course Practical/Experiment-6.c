-> CODE :

#include <stdio.h>
struct Process {
    int pid, bt, pr;
};
int main() {
    int n, i, j;
    struct Process p[10], temp;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Burst Time and Priority:\n");
    for(i = 0; i < n; i++) {
        p[i].pid = i + 1;
        scanf("%d%d", &p[i].bt, &p[i].pr);
    }
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(p[i].pr > p[j].pr) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    printf("\nExecution Order:\n");
    for(i = 0; i < n; i++)
        printf("P%d ", p[i].pid);
    return 0;
}

-> OUTPUT :
Enter number of processes: 4
Enter Burst Time and Priority:
5 2
3 1
6 4
2 3
Execution Order:
P2 P1 P4 P3 
