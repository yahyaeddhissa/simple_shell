#include "main.h"

extern char **environ;

int main(__attribute_maybe_unused__ int argc, char *argv[])
{
	char *buffer = NULL, **args;
	size_t i = 0;
	ssize_t read_n;
	pid_t pid, parent_pid;

	while (1)
	{
		_prompt();

		read_n = getline(&buffer, &i, stdin);
		if (read_n == -1)
		{
			exit(0);
		}

		args = _tokenize(buffer);

		if (strcmp(args[0], "cd") == 0)
		{
			const char *directory;
			char prev_directory[PATH_MAX];
			char current_directory[PATH_MAX];

			directory = (args[1] == NULL) ? getenv("HOME") : args[1];

			if (strcmp(directory, "-") == 0)
			{
				if (getcwd(prev_directory, sizeof(prev_directory)) == NULL)
				{
					perror("getcwd");
					continue;
				}
				directory = getenv("OLDPWD");
			}

			if (chdir(directory) != 0)
			{
				perror("chdir");
			}
			else
			{
				if (getcwd(current_directory, sizeof(current_directory)) == NULL)
				{
					perror("getcwd");
				}
				else
				{
					setenv("PWD", current_directory, 1);
					setenv("OLDPWD", prev_directory, 1);
				}
			}

			free(args);

			continue;
		}

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

		parent_pid = getpid();

		pid = fork();
		if (pid == 0)
		{
			if (execve(args[0], args, environ) == -1)
			{
				char path_buffer[PATH_MAX];
				snprintf(path_buffer, sizeof(path_buffer), "/bin/%s", args[0]);
				execve(path_buffer, args, environ);

				exit(0);
			}
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
