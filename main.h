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

#define BUFFER 1024
#define TRUE 1
#define PROMPT "$ "
/* error strings */
#define ERR_MALLOC "Unable to malloc space\n"
#define ERR_FORK "Unable to fork and create child process\n"
#define ERR_PATH "No such file or directory\n"
extern char **environ;

/**
 * struct list_s - linked list of variables
 * @value: value
 * @next: pointer to next node
 *
 * Description: generic linked list struct for variables.
 **/
typedef struct list_s
{
    char *value;
    struct list_s *next;
} list_s;

extern char **environ;

int _putchar(char);
void prompt(int fd, struct stat buf);
char *_getline(FILE *fp);
char **tokenizer(char *str);
char **_tokenize(char *buffer);
char *_strdup(char *str);
int child(char *fullpath, char **tokens, char *argv[]);
char *_which(char *command, char *fullpath, char *path);
void errors(int error);

/* utility functions */
void _puts(char *str);
int _strlen(char *s);
int _strcmp(char *name, char *variable, unsigned int length);
int _strncmp(char *name, char *variable, unsigned int length);
char *_strcpy(char *dest, char *src);

/* prototypes for the helper functions for path linked list */
char *_getenv(const char *name);
char **copy_env(char **environ_copy, unsigned int environ_length);
list_s *pathlist(char *variable, list_s *head);

/* prototypes for free functions */
void free_all(char **tokens, char *path, char *line, char *fullpath, int flag);
void free_dp(char **array, unsigned int length);

#endif /* MAIN_H */
