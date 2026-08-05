#include<stdio.h>
int main() {
    int memory[5]={100,200,300,400,500};
    int i;
    printf("Memory Blocks:\n");
    for(i=0;i<5;i++)
       printf("Block %d = %dKB\n",i+1,memory[i]);
       return 0;
}
