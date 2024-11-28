#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// This program will probably not cause interleaving of i/o between the parent and child processes
// Even if it does, the whole string will be written at once so the output will be more readable
// If you want to see other variations of this output, checkout h2a.c or h2b.c
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
        for (int i = 0; i < 30; i++)
        {
            write(fd, child_str, strlen(child_str));
            fsync(fd);
        }
    }
    else
    {
        printf("Hello, I am parent of %d (pid: %d)\n", rc, (int)getpid());
        char *child_str = "Parent process\n";
        for (int i = 0; i < 30; i++)
        {
            write(fd, child_str, strlen(child_str));
            fsync(fd);
        }
    }
    close(fd);
}