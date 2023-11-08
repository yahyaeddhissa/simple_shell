#include "main.h"

/**
 * _putchar - print char of a string
 * Return: the char
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _prompt - print the string
 */
void _prompt(void)
{
	char *ptr = "$ ";
	int index = 0;

	while (ptr[index] != '\0')
	{
		_putchar(ptr[index]);
		index++;
	}
}
