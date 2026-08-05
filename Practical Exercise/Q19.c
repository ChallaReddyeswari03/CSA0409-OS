#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    char buffer[100];
    int n;
    int source = open("source.txt", O_RDONLY);
    int destination = open("destination.txt",
                           O_CREAT | O_WRONLY | O_TRUNC,
                           0644);
    while ((n = read(source, buffer, sizeof(buffer))) > 0)
    {
        write(destination, buffer, n);
    }
    close(source);
    close(destination);
    printf("File copied successfully.\n");
    return 0;
}
