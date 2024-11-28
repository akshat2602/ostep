#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


// This program will cause interleaving of i/o between the parent and child processes
// If you want to see the output without interleaving, write the strings in one go instead of character by character as done in h2a.c
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
        for (int i = 0; i < 30; i++)
        {
            char *child_str = "Child ";
            for (size_t j = 0; j < strlen(child_str); j++)
            {
                write(fd, &child_str[j], 1);
                fsync(fd);
            }
            write(fd, "\n", 1);
        }
    }
    else
    {
        printf("Hello, I am parent of %d (pid: %d)\n", rc, (int)getpid());
        for (int i = 0; i < 30; i++)
        {
            char *child_str = "Parent ";
            for (size_t j = 0; j < strlen(child_str); j++)
            {
                write(fd, &child_str[j], 1);
                fsync(fd);
            }
            write(fd, "\n", 1);
        }
    }
    close(fd);
}