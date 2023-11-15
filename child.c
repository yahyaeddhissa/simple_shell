#include "main.h"

/**
 * child - Creates a child process
 * @path: Path of the executable
 * @tokens: Tokenized user input
 * Return: 0
 */
int child(char *fullpath, char **tokens, char *argv[])
{
    pid_t child_pid, parent_pid;
    int status;
    char **envp = environ;

    parent_pid = getpid();

    child_pid = fork();
    if (child_pid == -1)
    {
        errors(1);
        exit(EXIT_FAILURE);
    }
    if (child_pid == 0)
    {
        execve(fullpath, tokens, envp);

        write(STDERR_FILENO, argv[0], strlen(argv[0]));
        write(STDERR_FILENO, ": ", 2);
        {
            char pid_str[32];
            int pid_len = snprintf(pid_str, sizeof(pid_str), "%lu", (unsigned long)parent_pid);
            if (pid_len > 0)
            {
                write(STDERR_FILENO, pid_str, (size_t)pid_len);
            }
        }
        write(STDERR_FILENO, ": ", 2);
        write(STDERR_FILENO, fullpath, strlen(fullpath));
        write(STDERR_FILENO, ": not found\n", 12);
    }
    else
    {
        wait(&status);
    }
    return (0);
}