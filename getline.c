#include "main.h"

/**
 * _getline - Reads  an  entire  line from stream,
 * storing the address of the buffer containing the text into **buf.
 * @buf: Is the buffer to store the line that has been read
 * @size: Is the size of the buffer (buf)
 * @fd: Is the file descriptor to determine where to read from
 * Return: The number of character that has been read
 * or -1 if read process has faild
*/
ssize_t _getline(char **buf, size_t *size, int fd)
{
	static char buffer[7000];
	static ssize_t command_len, buffer_index;
	ssize_t line_len, alloc_size = 0, i;
	char *ptr = NULL, *new_buf = NULL, c = '\0';

	if (*size == INT_MAX)
	{
		*size = 0, buffer_index = 0;
	}
	ptr = *buf;
	if (buffer_index == 0)
	{
		while (c != '\n')
		{
			line_len = read(fd, buffer + buffer_index, 1024);
			if (line_len == -1)
				return (-1);
			if (line_len == 0 && buffer_index == 0)
				return (-2);
			if (line_len == 0 && buffer_index != 0)
				break;
			buffer_index += line_len;
			c = buffer[buffer_index - 1];
		}
	}
	for (i = command_len; i < buffer_index; i++)
	{
		alloc_size++;
		if (buffer[i] == '\n')
			break;
	}
	new_buf = _realloc(ptr, 0, alloc_size + 1);
	if (new_buf == NULL)
		return (-1);
	_strncpy(new_buf, buffer + command_len, alloc_size);
	command_len += alloc_size;
	if (command_len == buffer_index)
		command_len = 0, buffer_index = 0;
	*buf = new_buf;
	return (alloc_size);
}

/**
 * open_file - Opens a file
 * @file_name: Is the name of the file to open
 * Return: The file descriptor or -1 if it faild to open the file
*/
int open_file(char *file_name)
{
	int fd;

	if (file_name == NULL)
	{
		return (-1);
	}

	fd = open(file_name, O_RDONLY);

	if (fd == -1)
	{
		return (-1);
	}
	return (fd);
}
