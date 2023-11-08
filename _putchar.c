#include "main.h"

/**
 * _putchar - print char of a string
 * Return: the char
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}