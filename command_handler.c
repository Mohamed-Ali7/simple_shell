#include "main.h"

char *check_syntax_error(char *command);
int check_operator_sperator(char *command, char *operator);
/**
 * check_quote - Checks if the command args inside double quotaion
 * @cmnd: Is the command to check
 * @ind: Is the current index where the command stopped
 * Return: The updated index of the command
*/
int check_quote(char **cmnd, int ind)
{
	int index = ind, x = 0;

	if (**cmnd == '\"')
	{
		x = 0, (*cmnd)++, index++;
		while (**cmnd != '\"')
		{
			if (**cmnd == '\0')
			{
				(*cmnd) -= x;
				index -= x;
				break;
			}
			(*cmnd)++, x++, index++;
		}
	}
	return (index);
}

/**
 * line_commands - Finds multiple commands in the line and
 * return one command on every call till there are no more commands in line
 *
 * @command_line: Is the line to fetch its commands
 * Return: Command to be executed
*/
char *line_commands(char *command_line)
{
	static char *updated_line, prev_operator;
	char *error = NULL, *command = NULL, operator = '\0';
	static ssize_t line_len, checker;
	int index = 0;

	while (true)
	{
		index = 0;
		if (line_len == 0)
			updated_line = command_line, line_len = _strlen(updated_line);
		if (*updated_line == '\0')
		{
			line_len = checker = 0, prev_operator = '\0';
			return (NULL);
		}

		if (checker == 0)
		{
			error = check_syntax_error(updated_line);
			checker++;
			if (error != NULL)
			{
				*updated_line = '\0', prev_operator = '\0';
				return (error);
			}
		}
		index = check_operator_sperator(updated_line, &operator);
		command = updated_line;
		updated_line += index;
		if (prev_operator == '|' && exit_status == 0)
		{
			prev_operator = operator;
			continue;
		}
		if (prev_operator == '&' && exit_status != 0)
		{
			prev_operator = operator;
			continue;
		}
		break;
	}
	prev_operator = operator;
	return (command);
}

/**
 * check_operator_sperator - Checks for logical operators (|| OR &&)
 *  or command sperators (;)
 * @command: Is the command to check
 * @operator: Is a pointer to character to assign the logical operator
 * that the function has encountered with to apply this operator logic
 * Return: The updated index
*/
int check_operator_sperator(char *command, char *operator)
{
	int index = 0;

	while (command[index] != '\0')
	{
		if (command[index] == '\"')
			index = check_quote(&command, index);
		if (command[index] == ';')
		{
			command[index] = '\0', index++;
			if (command[index] == ' ')
				index++;
			return (index);
		}
		else if (command[index] == '|')
		{
			command[index] = '\0', index++;
			if (command[index] == '|')
			{
				index++;
				if (command[index] == ' ')
					index++;
			}
			*operator = '|';
			return (index);
		}
		else if (command[index] == '&')
		{
			command[index] = '\0', index++;
			if (command[index] == '&')
			{
				index++;
				if (command[index] == ' ')
					index++;
			}
			*operator = '&';
			return (index);
		}
		index++;
	}
	return (index);
}


/**
 * check_syntax_error - Checks if the code contains syntax errors
 * @command: Is the command to check
 * Return: The part that caused the error or NULL if there are no errors
*/

char *check_syntax_error(char *command)
{
	char next = '\0';
	int index = 0;

	while (*command != '\0')
	{
		index = check_quote(&command, index);
		if (*command == ';')
		{
			next = *(command + 1);
			if (next == ';')
				return (";;");
			else if (index == 0)
				return (";");
			else if (index != 0)
			{
				if (*(command - 1) == '|' || *(command - 1) == '&')
				{
					if (next == ';')
						return (";;");
					else
						return (";");
				}
			}
		}
		else if (*command == '|')
		{
			next = *(command + 1);
			if (next == '|' && *(command + 2) != '\0' && *(command + 2) == '|')
			{
				if (*(command + 3) != '\0' && *(command + 3) == '|')
					return ("||");
				return ("|");
			}
			else if (index == 0)
				return ("|");
			else if (index != 0)
			{
				if (*(command - 1) == ';')
				{
					if (next == '|')
						return ("||");
					else
						return ("|");
				}
			}
		}
		else if (*command == '&')
		{
			next = *(command + 1);
			if (next == '&' && *(command + 2) != '\0' && *(command + 2) == '&')
			{
				if (*(command + 3) != '\0' && *(command + 3) == '&')
					return ("&&");
				return ("&");
			}
			else if (index == 0)
				return ("&");
			else if (index != 0)
			{
				if (*(command - 1) == ';')
				{
					if (next == '&')
						return ("&&");
					else
						return ("&");
				}
			}
		}
		command++, index++;
	}
	return (NULL);
}

/**
 * replace_variable - Replaces variables ($) with it values
 * @args: Are the argument to check for variables
 * Return: void
*/
void replace_variable(char *args[])
{
	int i = 0;
	char *tmp = NULL;

	while (args[i] != NULL)
	{
		if (args[i][0] == '$' && args[i][1] == '$')
		{
			free(args[i]);
			args[i] = int_to_string(getpid());
		}
		else if (args[i][0] == '$' && args[i][1] == '?')
		{
			free(args[i]);
			args[i] = int_to_string(exit_status);
		}
		else if (args[i][0] == '$' && args[i][1] != '\0')
		{
			tmp = _getenv((args[i]) + 1);
			free(args[i]);
			if (tmp == NULL)
			{
				args[i] = malloc(sizeof(char) * 1);
				args[i][0] = '\0';
			}
			else
			{
			args[i] = malloc(sizeof(char) * (_strlen(tmp) + 1));
			_strcpy(args[i], tmp);
			}
		}
		i++;
	}
}
