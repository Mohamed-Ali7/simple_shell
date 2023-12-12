#include "main.h"

/**
 * _envs - Prints all the current running environment variables
 * @command: Is the command to process
 * @args: Are the arguments of the command
 * Return: Process result
*/
int _envs(char *command, char *args[])
{
	int i, len;
	char n = '\n';

	(void) (args);
	(void) (command);
	if (environ == NULL)
		return (-1);

	for (i = 0; environ[i] != NULL; i++)
	{
		len = _strlen(environ[i]);
		write(STDOUT_FILENO, environ[i], len);
		write(STDOUT_FILENO, &n, 1);
	}

	return (0);
}

/**
 * **_environ - Creates my own copy of environ variable to be able to
 * manipulate freely. for example set new variable or unset exixting variable
 *
 * Return: void
*/
char **_environ(void)
{
	int index, j;
	char **my_environ;

	if (environ == NULL)
		return (NULL);

	for (index = 0; environ[index] != NULL; index++)
	;

	my_environ = malloc(sizeof(char *) * (index + 1));
	if (my_environ == NULL)
		return (NULL);

	for (index = 0; environ[index] != NULL; index++)
	{
		my_environ[index] = malloc(sizeof(char) * (_strlen(environ[index]) + 1));

		if (my_environ[index] == NULL)
		{
			for (j = 0; j < index; j++)
				free(my_environ[index]);
			free(my_environ);
			return (NULL);
		}
		_strcpy(my_environ[index], environ[index]);
	}

	my_environ[index] = NULL;

	return (my_environ);
}

/**
 * **_getenv - Finds a certain enviornment variable and returns it
 * @env_name: Is the name of the variable to look for
 * Return: The environment variable or NULLL id it doesn't exist
*/
char *_getenv(char *env_name)
{
	int index = 0, env_len = 0;
	char *result = NULL;

	env_len = _strlen(env_name);

	if (environ == NULL)
		return (NULL);
	for (index = 0; environ[index] != NULL; index++)
	{
		if (_strncmp(environ[index], env_name, env_len) == 0)
		{
			result = environ[index] + env_len + 1;
			break;
		}
	}
	return (result);
}

/**
 * _setenv - Sets new environment variable
 * @command: Is the command to process
 * @args: Are the arguments of the command
 * Return: Process result
*/
int _setenv(char *command, char *args[])
{
	char *new_variable, **new_environ;
	int index = 0, env_len, value_len;

	(void) (command);
	if (args[1] == NULL || args[2] == NULL || args[3] != NULL)
	{
		print_error("%s: %d: %s: Invalid arguments\n", name, counter, args[0]);
		return (-1);
	}
	env_len = _strlen(args[1]), value_len = _strlen(args[2]);
	new_variable = malloc(sizeof(char) * (env_len + value_len + 2));
	if (new_variable == NULL)
	{
		print_error("%s: %d: %s: Failed set new variable\n", name, counter, args[0]);
		return (-1);
	}
	_strcpy(new_variable, args[1]);
	_strcat(new_variable, "=");
	_strcat(new_variable, args[2]);
	for (index = 0; environ[index] != NULL; index++)
	{
		if (_strncmp(environ[index], new_variable, env_len) == 0)
		{
			free(environ[index]);
			environ[index] = new_variable;
			return (0);
		}
	}
	new_environ = malloc(sizeof(char *) * (index + 2));
	if (new_environ == NULL)
	{
		print_error("%s: %d: %s: Failed to set new variable\n",
				 name, counter, args[0]), free(new_variable);
		return (-1);
	}
	for (index = 0; environ[index] != NULL; index++)
		new_environ[index] = environ[index];
	free(environ), new_environ[index] = new_variable;
	new_environ[index + 1] = NULL, environ = new_environ;
	return (0);
}

/**
 * _unsetenv - Unsets new environment variable
 * @command: Is the command to process
 * @args: Are the arguments of the command
 * Return: Process result
*/
int _unsetenv(char *command, char *args[])
{
	char **new_environ;
	int index = 0, new_environ_index = 0, del_var_len;

	(void) (command);
	if (args[1] == NULL || args[2] != NULL)
	{
		print_error("%s: %d: %s: Invalid arguments\n", name, counter, args[0]);
		return (-1);
	}

	if (_getenv(args[1]) == NULL)
		return (0);

	del_var_len = _strlen(args[1]);
	for (index = 0; environ[index] != NULL; index++)
	;

	new_environ = malloc(sizeof(char *) * index);

	if (new_environ == NULL)
	{
		print_error("%s: %d: %s: Failed to set new variable\n",
				 name, counter, args[0]);
		return (-1);
	}

	for (index = 0; environ[index] != NULL; index++)
	{
		if (_strncmp(environ[index], args[1], del_var_len) == 0)
		{
			free(environ[index]);
			continue;
		}
		new_environ[new_environ_index] = environ[index];
		new_environ_index++;
	}
	free(environ);
	new_environ[new_environ_index] = NULL;
	environ = new_environ;
	return (0);
}
