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
			exit(0);
		}

		args = _tokenize(buffer);

		if (strcmp(args[0], "setenv") == 0)
		{
			if (args[1] != NULL && args[2] != NULL)
			{
				if (setenv(args[1], args[2], 1) != 0)
				{
					perror("setenv");
				}
			}
			else
			{
				exit(0);
			}

			free(args);

			continue;
		}

		if (strcmp(args[0], "unsetenv") == 0)
		{
			if (args[1] != NULL)
			{
				if (unsetenv(args[1]) != 0)
				{
					perror("unsetenv");
				}
			}
			else
			{
				exit(0);
			}

			free(args);

			continue;
		}

		if (strcmp(args[0], "exit") == 0)
		{
			int exit_status = 0;

			if (args[1] != NULL)
			{
				exit_status = atoi(args[1]);
			}

			free(args);
			free(buffer);
			exit(exit_status);
		}

		pid = fork();
		if (pid == 0)
		{
			execvp(args[0], args);
			exit(0);
		}
		else if (pid == -1)
		{
			exit(0);
		}
		else
		{
			wait(NULL);
		}

		free(args);
	}
	free(buffer);

	return (0);
}
