#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

int _putchar(char);
void _prompt();
char **_tokenize(char *buffer);
char *_strdup(char *str);

#endif /* MAIN_H */
