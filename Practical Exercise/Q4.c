#include <stdio.h>
int  main(){
    int process[] = {1,2,3,4};
    int i;
    printf("Execution order:\n");
    for(i=0;i<4;i++)
       printf("Executing Process P%d\n",process[i]);
       return 0;
}
