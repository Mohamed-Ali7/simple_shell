#include "main.h"

/**
 * get_all_envs - Prints all the current running environment variables
 * @command: Is the command to process
 * @args: Are the arguments of the command
 * Return: process result
*/
int get_all_envs(char *command, char *args[])
{
	int i, len;
	char n = '\n';

	(void) (args);
	(void) (command);
	if (environ == NULL)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		len = _strlen(environ[i]);
		write(STDOUT_FILENO, environ[i], len);
		write(STDOUT_FILENO, &n, 1);
	}

	return (0);
}
