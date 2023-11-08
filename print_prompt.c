#include "main.h"
int _putchar(char c)
{
	return (write(1, &c, 1));
}
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
