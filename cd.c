#include "main.h"

int _home(void);
int _recent_directory(char *arg);

/**
 * _cd - Changes the current directory
 * @command: Is the command to process
 * @args: Are the arguments of the command
 * Return: Process result
*/
int _cd(char *command, char *args[])
{
	struct stat st;
	char *pwd, *old_pwd, *pwd_details[4], *old_pwd_details[4];
	int exec_status = 0;

	(void) (command);
	old_pwd = getcwd(NULL, 0);
	if (old_pwd == NULL)
		return (-1);
	if (args[1] == NULL)
		exec_status = _home();
	else if (args[1][0] == '-')
	{
		exec_status = _recent_directory(args[1]);
		if (exec_status == -2)
		{
			write(STDOUT_FILENO, old_pwd, _strlen(old_pwd));
			write(STDOUT_FILENO, "\n", 1);
			exec_status = 0;
		}
	}
	else
	{
		if (stat(args[1], &st) != 0)
		{
			print_error("%s: %d: %s: can't cd to %s\n",
				name, counter, args[0], args[1]);
			free(old_pwd);
			return (2);
		}
		if (chdir(args[1]) == -1)
		{
			print_error("%s: %d: %s: can't cd to %s\n",
				name, counter, args[0], args[1]);
			free(old_pwd);
			return (2);
		}
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		free(old_pwd);
		return (-1);
	}
	old_pwd_details[0] = "setenv", old_pwd_details[1] = "OLDPWD";
	old_pwd_details[2] = old_pwd, old_pwd_details[3] = NULL;
	pwd_details[0] = "setenv", pwd_details[1] = "PWD";
	pwd_details[2] = pwd, pwd_details[3] = NULL;
	if (_setenv("setenv", old_pwd_details) == -1)
	{
		free(old_pwd), free(pwd);
		return (-1);
	}
	if (_setenv("setenv", pwd_details) == -1)
	{
		free(old_pwd), free(pwd);
		return (-1);
	}
	free(pwd), free(old_pwd);
	return (exec_status);
}

/**
 * _home - Changes the current directory to $HOME directory.
 * Return: Execution status
*/
int _home(void)
{
	char *home_dir = _getenv("HOME");

	if (home_dir == NULL)
		return (-1);


	if (chdir(home_dir) == -1)
	{
		print_error("%s: %d: %s: can't cd to %s\n", name, counter, "cd", home_dir);
		return (2);
	}
	return (0);
}

/**
 * _recent_directory - Changes the current directory
 * to the last accessed directory
 * @arg: Are the options of the command cd -
 * Return: Execution status
*/
int _recent_directory(char *arg)
{
	char *dir = _getenv("OLDPWD");

	if (arg[1] != '\0' && arg[1] == '-' && arg[2] == '\0')
		return (_home());

	if (arg[1] != '\0' && arg[2] != '\0')
	{
		print_error("%s: %d: %s: can't cd to %s\n", name, counter, "cd", arg);
		return (2);
	}
	if (dir == NULL)
		return (-2);

	if (chdir(dir) == -1)
	{
		print_error("%s: %d: %s: can't cd to %s\n", name, counter, "cd", arg);
		return (2);
	}
	write(STDOUT_FILENO, dir, _strlen(dir));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
