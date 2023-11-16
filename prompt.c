#include "main.h"

/**
 * _prompt - checks mode and prints prompt if in interactive mode
 * @fd: file stream
 * @buffer: buffer
 **/
void _prompt()
{
    if (isatty(STDIN_FILENO))
    {
        write(STDOUT_FILENO, "$ ", 2);
    }
}