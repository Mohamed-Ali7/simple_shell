#include "main.h"

/**
 * exit_process - Exits the current process
 * @command: Is the command to process
 * @args: Are the arguments of the command
 * Return: process result
*/
int exit_process(char *command, char *args[])
{
	int exit_status = 0;

	(void) (command);
	if (args[1] != NULL)
	{
		exit_status = custom_atoi(args[1]);
		if (exit_status == -1)
		{
			print_error("%s: %d: %s: Illegal number: %s\n",
					name, counter, args[0], args[1]);
			return (2);
		}
		free(command);
		free_recur(args);
		free_recur(environ);
		if (exit_status > 255)
			exit_status %= 256;
		exit(exit_status);
	}
	free(command);
	free_recur(environ);
	free_recur(args);
	exit(0);
	return (0);
}
