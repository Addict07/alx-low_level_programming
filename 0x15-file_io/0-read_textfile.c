#include "main.h"
#include <stdlib.h>

/**
 * read_textfile- This read text file print to STDOUT.
 * @filename: Name of text file being read
 * @letters: number of letters to be read
 * Return: x- number of bytes read and printed
 *        0 when function fails or filename is NULL.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	char *buf;
	ssize_t fd;
	ssize_t x;
	ssize_t t;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	buf = malloc(sizeof(char) * letters);
	t = read(fd, buf, letters);
	x = write(STDOUT_FILENO, buf, t);

	free(buf);
	close(fd);
	return (x);
}

