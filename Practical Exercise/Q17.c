#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
int main()
{
    struct stat file;
    stat("student.txt", &file);
    printf("File Size: %ld bytes\n", file.st_size);
    printf("Permissions: %o\n", file.st_mode & 0777);
    printf("Last Modified: %s", ctime(&file.st_mtime));
    return 0;
}
