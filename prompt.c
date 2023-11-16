#include "main.h"

/**
 * _prompt - checks mode and prints prompt if in interactive mode
 * @fd: file stream
 * @buf: buffer
 **/
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