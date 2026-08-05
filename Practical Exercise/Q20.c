#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    char buffer[100];
    int fd = open("student.txt", O_RDONLY);
    int n = read(fd, buffer, sizeof(buffer) - 1);
    buffer[n] = '\0';
    printf("Contents of file:\n%s", buffer);
    close(fd);
    return 0;
}
