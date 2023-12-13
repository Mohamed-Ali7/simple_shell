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
#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <fcntl.h>

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
extern int exit_status;


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

/**
 * struct alias - Is a linked list struct of aliases
 * @name: Is the name of the alias
 * @value: Is the value of the alias
 * @next: Is a pointer to the next alias in the list
*/
typedef struct alias
{
	char *name;
	char *value;
	struct alias *next;
} alias_list;

extern alias_list *head;

int _envs(char *command, char *args[]);
char **_environ(void);
char *_getenv(char *env_name);
int _setenv(char *command, char *args[]);
int _unsetenv(char *command, char *args[]);

int exit_process(char *command, char *args[]);
int _cd(char *command, char *args[]);

int _alias(char *command, char *args[]);
char *check_alias(char *command);
int is_alias_to_set(char *arg);
void free_alias_list(alias_list *head);
int is_found(alias_list *head, char *name);

ssize_t _getline(char **buf, size_t *size, int fd);
char *line_commands(char *command_line);
void replace_variable(char *args[]);
int open_file(char *file_name);

void free_recur(char *args[]);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

char **str_split(char *str, char *delim);
char *trim_delimiters(char *str, char *delim);
int is_delim(char c, char *delimiters);
char *remove_extra_speaces(char *str);
int remove_quote(char **str);
char *int_to_string(int i);

char *_strcat(char *dest, char *src);
char *_strncat(char *dest, char *src, int n);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
int _strncmp(char *s1, char *s2, int n);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);
int custom_atoi(char *s);
#endif
