#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#define NOT_FOUND "not found"
#define PERMISSION_DENIED "Permission denied"

#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <signal.h>
#include <stdarg.h>
#include <errno.h>
#include <stdio.h>

/* printf helper functions */
int print_error(const char *format, ...);
int print_int_format(va_list ptr, char *buffer, int *buffer_index);
int print_char_format(va_list ptr, char *buffer, int *buffer_index);
int print_string_format(va_list ptr, char *buffer, int *buffer_index);
int add_to_buffer(char *buffer, int *buffer_index, char src);
int free_buffer(char *buf, int *buf_index);

/**
* struct specifier_format - Is a struct that contains format specifiers
* and format functions
* @specifier: Is the specifier character
* @func: Is the pointer to a format function
*/
typedef struct specifier_format
{
	char *specifier;
	int (*func)(va_list ptr, char *buffer, int *buffer_index);
} spec_format;

extern char **environ;
extern int counter;
extern char *name;


/**
 * struct builtin_cmd - Is a struct to define builtin commands
 * @cmd: Is the name of the command
 * @func: Is a pointer to the command function
*/
typedef struct builtin_cmd
{
	char *cmd;
	int (*func)(char *command, char *args[]);
} builtin_cmd;

int get_all_envs(char *command, char *args[]);
int exit_process(char *command, char *args[]);
ssize_t _getline(char **buf, size_t *size, int fd);

void free_recur(char *args[]);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

char **str_split(char *str, char *delim);

char *_strcat(char *dest, char *src);
char *_strncat(char *dest, char *src, int n);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);
#endif
