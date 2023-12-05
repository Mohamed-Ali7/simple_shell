#include "main.h"

/**
* print_error - Produces output according to a format.
* @format: Is string contains both text and format specifiers, which are
* placeholders for the values to print
* Return: The number of printed characters
*/

int print_error(const char *format, ...)
{
	int j, i, buffer_index = 0, printed_chars = 0;
	spec_format spec[] = {
		{"c", print_char_format}, {"s", print_string_format},
		{"d", print_int_format}, {NULL, NULL}
	};
	char buffer[1024];
	va_list listPtr;

	if (format == NULL)
		exit(1);
	va_start(listPtr, format);
	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] == '%' && format[++i] != '%')
		{
			if (format[i] == '\0' || (format[i] == ' ' && format[i + 1] == '\0'))
				exit(1);
			for (j = 0; spec[j].specifier != NULL; j++)
			{
				if (*(spec[j].specifier) == format[i])
				{
					printed_chars += spec[j].func(listPtr, buffer, &buffer_index);
					break;
				}
				if (spec[j + 1].specifier == NULL)
				{
					printed_chars += add_to_buffer(buffer, &buffer_index, format[i - 1]);
					printed_chars += add_to_buffer(buffer, &buffer_index, format[i]);
				}
			}
			continue;
		}
		printed_chars += add_to_buffer(buffer, &buffer_index, format[i]);
	}
	printed_chars += free_buffer(buffer, &buffer_index);
	va_end(listPtr);
	return (printed_chars);
}

/**
 * add_to_buffer - Add character to the buffer to be printed
 * @buffer: Is the buffer in usage
 * @buffer_index: Is the current index of the buffer
 * @src: Is the character that will be saved in the buffer
 * Return: The number of printed characters
 */

int add_to_buffer(char *buffer, int *buffer_index, char src)
{
	int printed_characters = 0;

	buffer[*buffer_index] = src;
	*buffer_index = *buffer_index + 1;

	if (*buffer_index == 1024)
	{
		printed_characters += free_buffer(buffer, buffer_index);

	}

	return (printed_characters);
}

/**
 * free_buffer - prints the buffer content to the standard output to reuse it
 * and reinitialize the buffer index with 0
 * @buf: Is the buffer to be printed
 * @buf_index: Is the current index of the buffer
 * which in this case is the buffer size
 * Return: The number of printed character
 */

int free_buffer(char *buf, int *buf_index)
{
	int index = *buf_index;

	write(STDERR_FILENO, buf, index);

	*buf_index = 0;
	return (index);
}
/**
* print_char_format - Prints the print_error function's argument in char format
* @ptr: Is the pointer to the list of arguments of the print_error function
* @buffer: Is the buffer to store the printable character
* @buffer_index: Is the current index of the buffer
* Return: The number of printed characters
*/

int print_char_format(va_list ptr, char *buffer, int *buffer_index)
{
	char c = va_arg(ptr, int);
	int printed_characters = 0;

	printed_characters += add_to_buffer(buffer, buffer_index, c);

	return (printed_characters);
}

/**
* print_string_format - Prints the print_error function's
* argument in string format
* @ptr: Is the pointer to the list of arguments of the print_error function
* @buffer: Is the buffer to store the printable character
* @buffer_index: Is the current index of the buffer
* Return: The number of printed characters
*/
int print_string_format(va_list ptr, char *buffer, int *buffer_index)
{
	char *str = va_arg(ptr, void *);
	int i;
	int printed_characters = 0;

	if (str == NULL)
	{
		str = "(null)";
	}

	for (i = 0; str[i] != '\0'; i++)
	{
		printed_characters += add_to_buffer(buffer, buffer_index, str[i]);
	}

	return (printed_characters);
}

