#include "main.h"

/**
 * exit_process - Exits the current process
 * @command: Is the command to process
 * @args: Are the arguments of the command
 * Return: process result
*/
int exit_process(char *command, char *args[])
{
	int exit_arg = 0;

	(void) (command);
	if (args[1] != NULL)
	{
		exit_arg = custom_atoi(args[1]);
		if (exit_arg == -1)
		{
			print_error("%s: %d: %s: Illegal number: %s\n",
					name, counter, args[0], args[1]);
			return (2);
		}
		free(command);
		free_recur(args);
		free_recur(environ);
		free_alias_list(head);
		if (exit_arg > 255)
			exit_arg %= 256;
		exit(exit_arg);
	}
	free(command);
	free_recur(environ);
	free_recur(args);
	free_alias_list(head);
	exit(exit_status);
	return (0);
}
