#include "main.h"
/**
 * *_strcat - concatenates two strings.
 * @dest: Is the first string to concat
 * @src: Is the second string to concat
 * Return: pointer points to a newly allocated space in memory which contains
 * the contents of dest, followed by the contents of src, and null terminated
 */
char *_strcat(char *dest, char *src)
{
	int i = 0;
	int r = 0;

	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[r] != '\0')
	{
		dest[i] = src[r];
		i++;
		r++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * *_strdup - Write a function that returns a pointer to a newly allocated
 * space in memory, which contains a copy of the string given as a parameter.
 * @str: Is the string to copy
 * Return: The created array
 */
char *_strdup(char *str)
{
	char *copiedStr;
	int len, i;

	if (str == NULL)
	{
		return (NULL);
	}
	len = _strlen(str);
	copiedStr = malloc(sizeof(char) * (len + 1));

	if (copiedStr == NULL)
	{
		exit(1);
	}

	for (i = 0; i <= len; i++)
	{
		copiedStr[i] = str[i];
	}
	return (copiedStr);
}


/**
 * *_strcmp - comapre two strings
 * @s1: is the first string to compare
 * @s2: is the second string to compare
 * Return: 0 if s1 = s2, more than 0 if s1 > s2, or less than 0 if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	int result = 0;
	int i = 0;

	while (s1[i] != '\0' || s2[i] != '\0')
	{
		result = s1[i] - s2[i];
		if (result != 0)
		{
			break;
		}
		i++;
	}

	return (result);
}

/**
 * _strlen - cout length of the received string
 * @s: is the string to return its length
 * Return: the length of the received string
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

/**
 * *_strcpy - copies the string (src) to (dest) string
 * @dest: is the char pointer that will hold the copied string
 * @src: is the string to copy
 * Return: the pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

