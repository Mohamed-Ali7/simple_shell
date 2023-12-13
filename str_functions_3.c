#include "main.h"
/**
 * remove_extra_speaces - Reomves extra spaces or tabs from a string
 * @str: Is the string to update
 * Return: The (str) string after removing extra spaces
*/

char *remove_extra_speaces(char *str)
{
	int i, new_index = 0;
	char cur, next, *delim = " \t", *next_delim = " \t;|&";
	char *new_str = NULL;

	for (i = 0; str[i] != '\0'; i++)
	{
		cur = str[i];
		next = str[i + 1];
		if (is_delim(cur, delim) && is_delim(next, next_delim))
			continue;

		new_index++;
	}
	new_str = malloc(sizeof(char) * (new_index + 1));
	if (new_str == NULL)
	{
		free(str);
		exit(1);
	}
	new_index = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		cur = str[i];
		next = str[i + 1];
		if (is_delim(cur, delim) && is_delim(next, next_delim))
			continue;
		new_str[new_index] = cur;
		new_index++;
	}
	new_str[new_index] = '\0';

	free(str);
	return (new_str);
}

/**
 * remove_quote - Reomves quotation marks from a string
 * @str: Is the string to update
 * Return: The (str) string after removing quotation marks
*/
int remove_quote(char **str)
{
	int i, new_index = 0;
	char *new_str = NULL;

	for (i = 0; (*str)[i] != '\0'; i++)
	{
		if ((*str)[i] == '\"' || (*str)[i] == '\'')
			continue;
		new_index++;
	}
	new_str = malloc(sizeof(char) * (new_index + 1));

	if (new_str == NULL)
		return (-1);

	new_index = 0;
	for (i = 0; (*str)[i] != '\0'; i++)
	{
		if ((*str)[i] == '\"' || (*str)[i] == '\'')
			continue;
		new_str[new_index] = (*str)[i];
		new_index++;
	}
	new_str[new_index] = '\0';
	*str = new_str;
	return (0);
}


/**
 * trim_delimiters - Deletes leading and ending delimiters
 * @str: Is the string to trim its delimiters
 * @delim: Are the delimiters to split the string with
 * Return: The (str) String after terminating leading and ending delimiters
*/
char *trim_delimiters(char *str, char *delim)
{
	int str_len;
	int str_start = 0;
	int i = 0;
	int r = 0;
	char *new_str;

	if (str == NULL)
		return (NULL);
	str_len = _strlen(str) - 1;
	while (str_len >= 0 && is_delim(str[str_len], delim))
	{
		str[str_len] = '\0';
		str_len--;
	}
	while (str_len >= 0 && is_delim(str[str_start], delim))
	{
		str[str_start] = '\0';
		str_start++;
		str_len--;
	}
	str_len++;
	new_str = malloc(sizeof(char) * (str_len + 1));
	if (new_str == NULL)
	{
		free(str);
		exit(1);
	}
	while (r < str_len)
	{
		if (str[i] != '\0')
		{
			new_str[r] = str[i];
			r++;
		}
		i++;
	}
	new_str[r] = '\0';
	free(str);
	return (new_str);
}

#include "main.h"
/**
* int_to_string - Converts an integer to string
* @i: Is the number to convert
* Return: String that contais the number as characters
*/

char *int_to_string(int i)
{
	int number_len = 0;
	unsigned int tmp = i;
	char *nums = NULL;

	while (tmp != 0)
	{
		tmp = tmp / 10;
		if (tmp > 0)
			number_len++;
	}
	if (tmp == 0)
		number_len++;

	nums = malloc(sizeof(char) * (number_len + 1));
	nums[number_len] = '\0';

	while (number_len >= 1)
	{
		nums[number_len - 1] = (i % 10) + '0';
		i = i / 10;
		number_len--;
	}

	return (nums);
}
