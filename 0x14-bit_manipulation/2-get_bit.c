#include "main.h"

/**
 * get_bit - Retrieves the value of a bit at a specific index in a decimal number.
 * @n: The number to search.
 * @index: The index of the bit to retrieve.
 *
 * Return: The value of the bit at the given index, or -1 if the index is out of range.
 */
int get_bit(unsigned long int n, unsigned int index)
{
    int bit_val;

    if (index > 63)
        return (-1);

    bit_val = (n >> index) & 1;

    return (bit_val);
}

