#include "main.h"

void init_arr(char *trim_str, char **str_arr, int arr_size, char *delim);

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

	if (str[0] == '\0')
	{
		return (NULL);
	}

	for (i = 0; str[i] != '\0'; i++)
	{
		if (is_delim(str[i], delim) && !is_delim(str[i + 1], delim))
		{
			arr_size++;
		}
	}
	if (str[0] == '\0')
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
		while (str[i] != '\0')
		{
			if (is_delim(str[i], delim))
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
	init_arr(str, str_arr, arr_size, delim);
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

	for (x = 0; x < arr_size; x++)
	{
		j = 0;
		while (str[i] != '\0')
		{
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


