#include "main.h"

int main(__attribute_maybe_unused__ int argc, char *argv[])
{
	char *buffer = NULL;
	char *line, *path, *fullpath;
	char **tokens;
	int flag, child_status;
	/*size_t i = 0;*/
	/*ssize_t read_n;*/
	/*pid_t pid;*/
	struct stat buf;

	while (1)
	{
		prompt(STDIN_FILENO, buf);

		line = _getline(stdin);
		if (_strcmp(line, "\n", 1) == 0)
		{
			free(line);
			continue;
		}

		tokens = tokenizer(line);
		if (tokens[0] == NULL)
			continue;

		if (strcmp(tokens[0], "cd") == 0)
		{
			const char *directory;
			char prev_directory[CHAR_MAX];
			char current_directory[CHAR_MAX];

			directory = (tokens[1] == NULL) ? getenv("HOME") : tokens[1];

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

			free(tokens);

			continue;
		}

		if (strcmp(tokens[0], "setenv") == 0)
		{
			if (tokens[1] != NULL && tokens[2] != NULL)
			{
				if (setenv(tokens[1], tokens[2], 1) != 0)
				{
					perror("setenv");
				}
			}
			else
			{
				exit(0);
			}

			free(tokens);

			continue;
		}

		if (strcmp(tokens[0], "unsetenv") == 0)
		{
			if (tokens[1] != NULL)
			{
				if (unsetenv(tokens[1]) != 0)
				{
					perror("unsetenv");
				}
			}
			else
			{
				exit(0);
			}

			free(tokens);

			continue;
		}

		if (strcmp(tokens[0], "exit") == 0)
		{
			int exit_status = 0;

			if (tokens[1] != NULL)
			{
				exit_status = atoi(tokens[1]);
			}

			free(tokens);
			free(buffer);
			exit(exit_status);
		}

		/* pid = fork(); */
		flag = 0;
		path = _getenv("PATH");
		fullpath = _which(tokens[0], fullpath, path);
		if (fullpath == NULL)
		{
			fullpath = tokens[0];
		}
		else
		{
			flag = 1;
		}

		child_status = child(fullpath, tokens, argv);
		if (child_status == -1)
		{
			errors(2);
		}
		free(path);
		free(tokens);
		if (flag == 1)
			free(fullpath);
	}
	free(buffer);

	return (0);
}
