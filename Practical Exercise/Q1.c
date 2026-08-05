#include <stdio.h>
int main() {
    int bt[4]={5,3,8,6};
    int wt[4];
    int i,sum=0;
    wt[0]=0;
    for(i=1;i<4;i++)
        wt[i]=wt[i-1]+bt[i-1];
    for(i=0;i<4;i++){
        printf("Process %d Waiting Time = %d\n",i+1,wt[i]);
        sum+=wt[i];
    }
    printf("Average Waiting Time = %.2f",(float)sum/4);
    return 0;
}
