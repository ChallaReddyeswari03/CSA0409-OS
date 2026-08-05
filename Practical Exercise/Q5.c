#include <stdio.h>
int main() {
    FILE *fp;
    char str[100];
    fp= fopen("sample.txt", "w");
    fprintf(fp,"Hello operating system");
    fclose(fp);
    fp=fopen("sample.txt","r");
    fgets(str,100,fp);
    printf("File Content: %s",str);
    fclose(fp);
    return 0;
}
