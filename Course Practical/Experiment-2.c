-> CODE :

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
    int src, dest;
    char buffer[100];
    int bytesRead;
    src = open("source.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (src < 0) {
        printf("Error creating source file.\n");
        return 1;
    }
    write(src, "Operating Systems Lab\nFile Copy using System Calls\n", 52);
    close(src);
    src = open("source.txt", O_RDONLY);
    if (src < 0) {
        printf("Error opening source file.\n");
        return 1;
    }
    dest = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest < 0) {
        printf("Error creating destination file.\n");
        close(src);
        return 1;
    }
    while ((bytesRead = read(src, buffer, sizeof(buffer))) > 0) {
        write(dest, buffer, bytesRead);
    }
    close(src);
    close(dest);
    printf("File copied successfully.\n");
    dest = open("destination.txt", O_RDONLY);
    printf("\nContents of destination.txt:\n");
    while ((bytesRead = read(dest, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytesRead] = '\0';
        printf("%s", buffer);
    }
    close(dest);
    return 0;
}

-> OUTPUT :
Contents of destination.txt:
Operating Systems Lab
File Copy using System Calls
