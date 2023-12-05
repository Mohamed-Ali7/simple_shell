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
