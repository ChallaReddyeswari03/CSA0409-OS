#include <unistd.h>
#include <string.h>
int main()
{
    char msg[] = "Hello, Welcome!\n";
    write(1, msg, strlen(msg));
    return 0;
}
