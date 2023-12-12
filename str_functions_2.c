#include "main.h"
/**
 * *_strncat - concatenates two strings
 * @dest: the string that will hold the two strings (its value and src value)
 * @src: is the string that will be added to (dest) string
 * @n: it is the numbers of bytes that will be added from string (src) to dest
 * Return: a pointer to the resulting string dest
 */
char *_strncat(char *dest, char *src, int n)
{
	int i = 0;
	int r = 0;

	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[r] != '\0' && n > r)
	{
		dest[i] = src[r];
		i++;
		r++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * *_strncpy - Copies the (n) bytes from the string pointed to by src
 * to the buffer pointed to by dest.
 * @dest: the string that will hold the copied string
 * @src: is the string that will be copied to (dest) string
 * @n: it is the numbers of bytes that will be copied from string (src) to dest
 * Return: a pointer to the resulting string dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i = 0;

	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


/**
 * custom_atoi - Check string if its characters are all digits
 * and return them as an integer
 *
 * @s: is the string to search into
 *
 * Return: the digit numbers as integer or -1 if the string is contains
 * characters which are not digits or the string number is more than MAX_INT
 */
int custom_atoi(char *s)
{
	int i = 0;
	unsigned int integers = 0;

	while (s[i] != '\0')
	{
		if (i == 0 && s[i] == '+')
		{
			i++;
			continue;
		}
		if (s[i] >= '0' && s[i] <= '9')
		{
			integers *= 10;
			integers += (s[i] - '0');
			if (integers > INT_MAX)
				return (-1);
		}
		else
		{
			return (-1);
		}
		i++;
	}

	return (integers);
}

/**
 * *_strncmp - comapre firs n characters of two strings
 * @s1: is the first string to compare
 * @s2: is the second string to compare
 * @n: Is the number of characters to compare
 * Return: 0 if s1 = s2, more than 0 if s1 > s2, or less than 0 if s1 < s2
 */
int _strncmp(char *s1, char *s2, int n)
{
	int result = 0;
	int i = 0;

	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
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
 * free_recur - frees variables of type pointer to ponter recursevly
 * @args: Is the pointer to free
 * Return: void
*/
void free_recur(char *args[])
{
	int i;

	for (i = 0; args[i] != NULL; i++)
	{
		free(args[i]);
	}
	free(args[i]);
	free(args);
}
