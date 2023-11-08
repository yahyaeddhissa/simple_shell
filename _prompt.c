#include "main.h"

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
