#include <stdio.h>
#include "main.h"

/**
 * main - Entry point of the program
 *
 * Description: This function checks the endianness of the machine
 *              and prints "Little Endian" or "Big Endian" accordingly.
 *
 * Return: Always 0.
 */
int main(void)
{
	int n;

	n = get_endianness();
	if (n != 0)
	{
		printf("Little Endian\n");
	}
	else
	{
		printf("Big Endian\n");
	}
	return (0);
}

