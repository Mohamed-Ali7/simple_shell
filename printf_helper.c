#include "main.h"
/**
* print_int_format - Prints the print_error function's argument in int format
* @ptr: Is the pointer to the list of arguments of the print_error function
* @buffer: Is the buffer to store the printable character
* @buffer_index: Is the current index of the buffer
* Return: The number of printed characters
*/

int print_int_format(va_list ptr, char *buffer, int *buffer_index)
{
	int i = va_arg(ptr, int);
	int x = 0;
	unsigned int tmp = i;
	int printed_characters = 0;
	char nums[10];

	if (i == 0)
	{
		printed_characters += add_to_buffer(buffer, buffer_index, '0');
		return (printed_characters);
	}
	if (i < 0)
	{
		printed_characters += add_to_buffer(buffer, buffer_index, '-');
		tmp *= -1;
	}
	while (tmp != 0)
	{
		nums[x] = (tmp % 10) + '0';
		tmp = tmp / 10;
		x++;
	}
	while (x >= 1)
	{
		printed_characters += add_to_buffer(buffer, buffer_index, nums[x - 1]);
		x--;
	}

	return (printed_characters);
}
