#include "main.h"
int add_alias(alias_list **head, char *name, char *value);
void print_all_alias(alias_list *head);
void print_alias(alias_list *head, char *name);

/**
 * _alias - Checks of the command is an alias
 * @command: Is the command to process
 * @args: Are the arguments of the command
 * Return: process result
*/
int _alias(char *command, char *args[])
{
	int exit_result = 0, args_size, exit_result_flag = 0;
	char *name = NULL, *value = NULL, **tmp_args = NULL;

	(void) (command);

	if (args[1] == NULL)
	{
		print_all_alias(head);
		return (0);
	}
	for (args_size = 1; args[args_size] != NULL; args_size++)
	{
		if (is_alias_to_set(args[args_size]))
		{
			tmp_args = str_split(args[args_size], "=");
			name = tmp_args[0];
			value = tmp_args[1];
			exit_result = add_alias(&head, name, value);
			free_recur(tmp_args);
			if (exit_result == -1)
				return (1);
		}
		else
		{
			if (!is_found(head, args[args_size]))
				exit_result_flag = 1;
			print_alias(head, args[args_size]);
		}
	}

	if (exit_result_flag)
		exit_result = 1;
	return (exit_result);
}

/**
 * add_alias - Adds a new alias to the list or update existing one
 * @head: Is a pointer to the pointer that points to the first element of list
 * @name: Is the name of the alias to set
 * @value: Is the value of the alias to set
 * Return: 0 if code executed with no errors or -1 otherwise
*/
int add_alias(alias_list **head, char *name, char *value)
{
	alias_list *new_alias;
	alias_list *tmp = *head;

	while (tmp != NULL)
	{
		if (_strcmp(tmp->name, name) == 0)
		{
			free(tmp->value);
			tmp->value = _strdup(value);
			return (0);
		}
		tmp = tmp->next;
	}
	tmp = *head;

	new_alias = malloc(sizeof(alias_list));

	if (new_alias == NULL)
	{
	return (-1);
	}
	new_alias->name = _strdup(name);
	new_alias->value = _strdup(value);
	new_alias->next = NULL;

	if (*head == NULL)
	{
		*head = new_alias;
		return (0);
	}

	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_alias;
	return (0);
}

/**
 * print_alias - Prints a specific alias
 * @head: Is a pointer to the first element of the list
 * @name: Is the name of the alias to print
*/
void print_alias(alias_list *head, char *name)
{
	alias_list *tmp = head;

	while (tmp != NULL)
	{
		if (_strcmp(tmp->name, name) == 0)
		{
			write(STDOUT_FILENO, tmp->name, _strlen(tmp->name));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, "'", 1);
			write(STDOUT_FILENO, tmp->value, _strlen(tmp->value));
			write(STDOUT_FILENO, "'", 1);
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		tmp = tmp->next;
	}
}


/**
 * print_all_alias - Prints a list of aliases
 * @head: Is a pointer to the first element of the list
 * Return: void
*/
void print_all_alias(alias_list *head)
{
	alias_list *tmp = head;

	while (tmp != NULL)
	{
		write(STDOUT_FILENO, tmp->name, _strlen(tmp->name));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, "'", 1);
		write(STDOUT_FILENO, tmp->value, _strlen(tmp->value));
		write(STDOUT_FILENO, "'", 1);
		write(STDOUT_FILENO, "\n", 1);
		tmp = tmp->next;
	}
}
/**
 * check_alias - Checks if the command is a stored alias
 * @command: Is the command to check
 * Return: The original command if it is found as an alias
*/
char *check_alias(char *command)
{
	char *command_value = command;
	int found_alias = 0;
	alias_list *tmp;

	while (true)
	{
		tmp = head;
		found_alias = 0;
		while (tmp != NULL)
		{
			if (_strcmp(tmp->name, command_value) == 0)
			{
				free(command_value);

				command_value = malloc(sizeof(char) * (_strlen(tmp->value) + 1));
				if (command_value == NULL)
					return (NULL);
				_strcpy(command_value, tmp->value);
				found_alias = 1;
				break;
			}
			tmp = tmp->next;
		}
		if (!found_alias)
			return (command_value);
	}
	return (command);
}
