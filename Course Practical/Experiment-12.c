-> CODE :

#include <stdio.h>
int main()
{
    int n, m, i, j, k;
    int alloc[10][10], max[10][10], need[10][10];
    int avail[10], finish[10], safeSeq[10];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);
    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }
    printf("\nEnter Maximum Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++)
    {
        scanf("%d", &avail[i]);
    }
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    for(i = 0; i < n; i++)
        finish[i] = 0;
    int count = 0;
    while(count < n)
    {
        int found = 0;
        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                for(j = 0; j < m; j++)
                {
                    if(need[i][j] > avail[j])
                        break;
                }
                if(j == m)
                {
                    for(k = 0; k < m; k++)
                        avail[k] += alloc[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if(found == 0)
        {
            printf("\nSystem is NOT in Safe State.\n");
            return 0;
        }
    }
    printf("\nSystem is in Safe State.\n");
    printf("Safe Sequence: ");
    for(i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    return 0;
}

-> OUTPUT :

Enter number of processes: 5
Enter number of resource types: 3

Enter Allocation Matrix:
3 7 9
5 9 8
0 1 0
8 9 7
4 2 3

Enter Maximum Matrix:
1 2 3   
4 5 6
7 8 9
4 6 8
2 5 7

Enter Available Resources:
3 3 2

System is in Safe State.
Safe Sequence: P0 P1 P2 P3 P4 
