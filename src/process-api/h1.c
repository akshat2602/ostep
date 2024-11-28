#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int x = 100;

    int rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("Hello, I am child (pid: %d)\n", (int)getpid());
        printf("Current value of x: %d\n", x);
        x = 300;
    }
    else
    {
        printf("Hello, I am parent of %d (pid: %d)\n", rc, (int)getpid());
        printf("Current value of x: %d\n", x);
        x = 200;
    }
    printf("x: %d\n", x);
}