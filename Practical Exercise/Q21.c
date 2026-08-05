#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main()
{
    char name[100];
    printf("Enter Student Name: ");
    fgets(name, sizeof(name), stdin);
    int fd = open("student.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, name, strlen(name));
    close(fd);
    printf("Data written successfully.\n");
    return 0;
}
