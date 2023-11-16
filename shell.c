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
	size_t bufsize = 32;
	ssize_t line;
	pid_t pid;

	while (1)
	{
		_prompt();

		line = getline(&buffer, &bufsize, stdin);
		if (line == -1)
		{
			exit(EXIT_FAILURE);
		}
		args = _tokenize(buffer);

		if (strcmp(args[0], "exit") == 0)
		{
			free(args);
			free(buffer);
			exit(0);
		}

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
		free(args);
		free(buffer);
	}

	return (0);
}