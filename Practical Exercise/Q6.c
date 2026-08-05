#include<stdio.h>
int main(){
    int pages[] = {1,2,3,1,4,5};
    int frame[3] = {-1,-1,-1};
    int i,j,k=0,flag;
    for(i=0;i<6;i++){
        flag=0;
        for(j=0;j<3;j++)
           if(frame[j]==pages[i])
              flag=1;
        if(flag==0){
            frame[k]=pages[i];
            k=(k+1)%3;
        }
        printf("Frames: ");
        for(j=0;j<3;j++)
           printf("%d", frame[j]);
        printf("\n");
}
  return 0;
}
