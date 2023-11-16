#include <stdio.h>
#include "main.h"

/**
 * main - simple shell proram
 *
 * Return: 0 (success)
 */
int main(void)
{
	char *buffer = NULL, **args;
	size_t i = 0;
	ssize_t read_n;
	pid_t pid;

	while (1)
	{
		_prompt();

		read_n = getline(&buffer, &i, stdin);
		if (read_n == -1)
		{
			exit(EXIT_FAILURE);
		}

		args = _tokenize(buffer);

		pid = fork();
		if (pid == 0)
		{
			execve(args[0], args, environ);
			perror("Error");
			exit(EXIT_FAILURE);
		}
		else if (pid == -1)
		{
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}
		free(read_n);
		free(args);
		free(buffer);
	}

	return (0);
}