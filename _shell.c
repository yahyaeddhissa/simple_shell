#include <stdio.h>
#include "main.h"

int main(void)
{
	char *buffer = NULL, **args;
	size_t i = 0;
	ssize_t read_n;

	while(1)
	{
		_prompt();
		read_n = getline(&buffer, &i, stdin);
		if (read_n == -1)
		{
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}
