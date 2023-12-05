#include "main.h"

/**
 * exit_process - Exits the current process
 * @command: Is the command to process
 * @args: Are the arguments of the command
 * Return: process result
*/
int exit_process(char *command, char *args[])
{
	(void) (command);
	free_recur(args);
	exit(0);
	return (0);
}
