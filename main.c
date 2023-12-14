#include "main.h"

char *get_command(char *command);
int _execve(char *command, char *cmd_full_path, char *args[]);
void remove_comments(char *command);

/**
 * signal_handler - Handles signals and
 * its main purpose here is to handle SIGINT signal to prevent Ctrl + C
 * from terminating the running process which in our case the simple_shell
 * @sig: Is the signal value
 * Return: void
*/
void signal_handler(int sig)
{
	(void) (sig);

	write(STDOUT_FILENO, "\n$ ", 3);
}

int counter;
char *name;
int exit_status;
alias_list *head;
/**
 * main - Entry point
 * @argc: The number of command line arguments
 * @argv: An array containing the program command line arguments
 * Return: 0
 */
int main(int argc, char *argv[])
{
	char *command = NULL, *cmd = NULL, *delim = " \n\t", **args = NULL;
	char *filterd_command = NULL;
	size_t buf_size = 0;
	int i, line_len, is_builtin = 0, flag = 0, fd = STDIN_FILENO;
	builtin_cmd b_cmd[] = {
		{"env", _envs}, {"exit", exit_process}, {"setenv", _setenv},
		{"unsetenv", _unsetenv}, {"cd", _cd}, {"alias", _alias}, {NULL, NULL}
	};

	name = argv[0];
	if (argc == 2)
	{
		fd = open_file(argv[1]);
		if (fd == -1)
		{
			print_error("%s: %d: Can't open %s\n", name, counter, argv[1]);
			return (127);
		}
	}
	environ = _environ();
		if (environ == NULL)
			exit(-100);
	signal(SIGINT, signal_handler);
	while (true)
	{
		line_len = 0;
		if (isatty(STDIN_FILENO) && fd <= 2)
			write(STDOUT_FILENO, "$ ", 2);

		line_len = _getline(&command, &buf_size, fd);
		if (line_len == 1)
		{
			if (*command == '\n')
			{
				counter++;
				continue;
			}
		}

		if (line_len == -1 || line_len == -2)
		{
			if (isatty(STDIN_FILENO) && fd <= 2)
				write(STDOUT_FILENO, "\n", 1);
			if (line_len == -1)
				exit_status = 1;
			break;
		}
		command = remove_extra_speaces(command);
		command = trim_delimiters(command, " \n\t");
		remove_comments(command);
		while ((filterd_command = line_commands(command)) != NULL)
		{
			counter++;
			is_builtin = 0;
			flag = 0;
			if (filterd_command[0] == ';' || filterd_command[0]  == '&' ||
			filterd_command[0] == '|')
			{
				buf_size = INT_MAX;
				print_error("%s: %d: Syntax error: \"%s\" unexpected\n",
							name, counter, filterd_command);
				exit_status = 2;
				counter--;
				continue;
			}

			if (remove_quote(&filterd_command) == -1)
				free(command), exit(1);
			args = str_split(filterd_command, delim);
			if (args == NULL)
			{
				free(filterd_command), exit_status = 127;
				continue;
			}
			replace_variable(args);
			for (i = 0; b_cmd[i].cmd != NULL; i++)
			{
				if (_strcmp(b_cmd[i].cmd, args[0]) == 0)
				{
					if (_strcmp(b_cmd[i].cmd, "exit") == 0)
						free(filterd_command), flag = 1;
					exit_status = b_cmd[i].func(command, args);
					is_builtin = 1;
					break;
				}
			}
			if (is_builtin)
			{
				free_recur(args);
				if (!flag)
					free(filterd_command);
				continue;
			}
			args[0] = check_alias(args[0]);
				if (args[0] == NULL)
				{
					print_error("%s: %d: %s: not found\n", name, counter, args[0]);
					free_recur(args), free(filterd_command);
					exit_status = 127;
				}
			cmd = get_command(args[0]);
			if (cmd == NULL || (access(cmd, X_OK) == -1))
			{
				if (errno == EACCES)
				{
					print_error("%s: %d: %s: Permission denied\n",
							name, counter, args[0]);
					exit_status = 126;
					free(cmd);
				}
				else
				{
					print_error("%s: %d: %s: not found\n", name, counter, args[0]);
					exit_status = 127;
				}
				free_recur(args), free(filterd_command);
				continue;
			}
			exit_status = _execve(filterd_command, cmd, args);
			free_recur(args), free(cmd), free(filterd_command);
		}
	}
	free(command), free_recur(environ), free_alias_list(head);
	if (fd != STDIN_FILENO)
		close(fd);
	return (exit_status);
}


/**
 * _execve - Execute a shell command throw a new process
 * @command: Is the command that user entered
 * @cmd_full_path: The full path of the command that user entered to execute
 * @args: Are the arguements of the command
 * Return: process result
*/
int _execve(char *command, char *cmd_full_path, char *args[])
{
	int pid;
	int exec_result = 0;

	pid = fork();
		if (pid == -1)
		{
			exit(1);
		}
		if (pid == 0)
		{
			if (execve(cmd_full_path, args, environ) == -1)
			{
				if (errno == EACCES)
				{
					print_error("%s: %d: %s: Permission denied\n", name, counter, args[0]);
					free_recur(args), free(cmd_full_path), free(command), free_recur(environ);
					exit(126);

				}
				else
				{
					print_error("%s: %d: %s: not found\n", name, counter, args[0]);
					exit(127);
				}
				exit(1);
			}
		}
		else
		{
			wait(&exec_result);
			exec_result = WEXITSTATUS(exec_result);
		}
	return (exec_result);
}
/**
 * get_command - Finding a command using path variable
 * @command: Is the command to look for
 * Return: The path of the command
*/
char *get_command(char *command)
{
	char *path = _getenv("PATH");
	char **tokens, *command_path, *cpy_path;
	int i;

	command_path = malloc(sizeof(char) * (_strlen(command) + 700));
	if (command_path == NULL)
		return (NULL);
	if (command[0] == '/' || command[0] == '.')
	{
		_strcpy(command_path, command);
		return (command_path);
	}
	cpy_path = _strdup(path);
	if (cpy_path == NULL)
	{
		free(command_path);
		return (NULL);
	}

	tokens = str_split(cpy_path, ":");
	if (tokens == NULL)
	{
		free(command_path), free(cpy_path);
		return (NULL);
	}
	for (i = 0; tokens[i] != NULL; i++)
	{
		_strcpy(command_path, tokens[i]);
		_strcat(command_path, "/");
		_strcat(command_path, command);

		if (access(command_path, X_OK) == 0)
		{
			free(cpy_path), free_recur(tokens);
			return (command_path);
		}
	}
	free(cpy_path), free(command_path), free_recur(tokens);
	return (NULL);
}

/**
 * remove_comments - Reomves comment from the command
 * @command: Is the command to remove the comments from
 * Return: void
*/
void remove_comments(char *command)
{
	int i;

	for (i = 0; command[i] != '\0'; i++)
	{
		if (command[i] == '#')
		{
			if (i == 0)
			{
				command[i] = '\0';
				break;
			}
			else if (i != 0 && command[i - 1] == ' ')
			{
				command[i - 1] = '\0';
				break;
			}
		}
	}
}
