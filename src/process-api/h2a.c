#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// This program will probably not cause interleaving of i/o between the parent and child processes
// If you want to see the output without interleaving, write the strings in one go instead of character by character as done in h2b.c or h2c.c
int main(int argc, char *argv[])
{
    int fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC);
    if (fd == -1)
    {
        fprintf(stderr, "open failed\n");
        exit(1);
    }
    int rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        printf("Hello, I am child (pid: %d)\n", (int)getpid());
        char *child_str = "Child process\n";
        write(fd, child_str, strlen(child_str));
    }
    else
    {
        printf("Hello, I am parent of %d (pid: %d)\n", rc, (int)getpid());
        char *child_str = "Parent process\n";
        write(fd, child_str, strlen(child_str));
    }
    close(fd);
}