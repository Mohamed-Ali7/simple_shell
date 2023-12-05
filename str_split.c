#include "main.h"

void init_arr(char *trim_str, char **str_arr, int arr_size, char *delim);
int is_delim(char c, char *delimiters);
char *trim_delimiters(char *trim_str, char *delim);
/**
 * str_split - splits a string into words.
 * @str: Is the string to split
 * @delim: Are the delimiters to split the string with
 * Return: A pointer to an array of strings (words)
 */

char **str_split(char *str, char *delim)
{
	char **str_arr;
	int arr_size = 1;
	int i, x;
	int str_len = 0;
	char cur;
	char next;
	char *trimed_str;

	trimed_str = trim_delimiters(str, delim);
	if (trimed_str[0] == '\0')
	{
		return (NULL);
	}

	for (i = 0; trimed_str[i] != '\0'; i++)
	{
		if (is_delim(trimed_str[i], delim) && !is_delim(trimed_str[i + 1], delim))
		{
			arr_size++;
		}
	}
	if (trimed_str[0] == '\0')
		return (NULL);

	str_arr = malloc(sizeof(char *) * (arr_size + 1));
	if (str_arr == NULL)
	{
		return (NULL);
	}
	i = 0;
	for (x = 0; x < arr_size; x++)
	{
		str_len = 0;
		while (trimed_str[i] != '\0')
		{
			cur = trimed_str[i];
			next = trimed_str[i + 1];
			if (is_delim(cur, delim) && is_delim(next, delim))
			{
				i++;
				continue;
			}

			if (is_delim(trimed_str[i], delim))
			{
				i++;
				break;
			}
			str_len++;
			i++;
		}
		str_arr[x] = malloc(sizeof(char) * (str_len + 1));
		if (str_arr[x] == NULL)
		{
			for (i = 0; i < x; i++)
			{
				free(str_arr[i]);
			}
			free(str_arr);
			return (NULL);
		}
	}
	init_arr(trimed_str, str_arr, arr_size, delim);
	free(trimed_str);
	return (str_arr);
}

/**
 * **init_arr - Initialize the passed array of strings
 * @str: Is the string which will be used to init the array
 * @str_arr: Is the String to initialize with proper data
 * @arr_size: Is the size of the  array str_arr
 * @delim: Are the delimiters to split the string with
 * Return: void
 */

void init_arr(char *str, char **str_arr, int arr_size, char *delim)
{
	int i = 0;
	int x = 0;
	int j = 0;
	char cur;
	char next;

	for (x = 0; x < arr_size; x++)
	{
		j = 0;
		while (str[i] != '\0')
		{
			cur = str[i];
			next = str[i + 1];
			if (is_delim(cur, delim) && is_delim(next, delim))
			{
				i++;
				continue;
			}

			if (is_delim(str[i], delim))
			{
				i++;
				break;
			}
			str_arr[x][j] = str[i];
			j++;
			i++;
		}
		str_arr[x][j] = '\0';
	}
	str_arr[x] = NULL;
}

/**
 * is_delim - checks if a character is delimeter
 * @c: Is the character to check
 * @delimiters: Are the delimiters to split the string with
 * Return: 1 if the character is a delimeter or 0 otherwise
*/
int is_delim(char c, char *delimiters)
{
	int i;

	for (i = 0; delimiters[i] != '\0'; i++)
	{
		if (c == delimiters[i])
			return (1);
	}
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
	while (is_delim(str[str_len], delim) && str_len >= 0)
	{
		str[str_len] = '\0';
		str_len--;
	}

	while (is_delim(str[str_start], delim) && str_len >= 0)
	{
		str[str_start] = '\0';
		str_start++;
		str_len--;
	}
	str_len++;

	new_str = malloc(sizeof(char) * str_len + 1);
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
	return (new_str);
}
