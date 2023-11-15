#include "main.h"

/**
 * _tokenize - Tokenize a string based on delimiters
 * @buffer: Input string to tokenize
 *
 * Return: An array of tokens or NULL on error
 */
char **_tokenize(char *buffer)
{
	char **args, *token, *buf_copy, *delimeter = " \t\n";
	int count = 0;
	int index = 0;

	if (buffer == NULL)
	{
		return (NULL);
	}

	buf_copy = _strdup(buffer); /* Dynamic mem allocation */
	if (buf_copy == NULL)
	{
		return (NULL);
	}

	token = strtok(buf_copy, delimeter);
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, delimeter);
	}

	count++;

	args = malloc(sizeof(char *) * count);
	if (args == NULL)
	{
		free(buf_copy);
		return (NULL);
	}

	token = strtok(buffer, delimeter);
	while (token != NULL)
	{
		args[index] = token;
		index++;
		token = strtok(NULL, delimeter);
	}

	args[index] = NULL;
	free(buf_copy);

	return (args);
}
