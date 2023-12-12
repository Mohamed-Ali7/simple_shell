#include "main.h"

/**
 * *_realloc -  reallocates a memory block using malloc and free
 * @ptr: Is a pointer to the memory previously allocated
 * @old_size: Is the size, in bytes, of the allocated space for ptr
 * @new_size: Is the new size, in bytes of the new memory block
 * Return: A pointer to the new allocated memory block
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *rst;
	unsigned int i = 0;

	if (old_size == new_size)
	{
		return (ptr);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	rst = malloc(new_size);

	if (rst == NULL)
	{
		return (NULL);
	}

	if (ptr == NULL)
	{
		return (rst);
	}

	while (i < old_size)
	{
		rst[i] = ((char *)ptr)[i];
		i++;
	}
	free(ptr);
	return (rst);

}
