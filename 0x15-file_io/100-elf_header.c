#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void validate_elf(unsigned char *e_ident);
void display_magic(unsigned char *e_ident);
void display_class(unsigned char *e_ident);
void display_data(unsigned char *e_ident);
void display_version(unsigned char *e_ident);
void display_abi(unsigned char *e_ident);
void display_osabi(unsigned char *e_ident);
void display_type(unsigned int e_type, unsigned char *e_ident);
void display_entry(unsigned long int e_entry, unsigned char *e_ident);
void close_elf(int elf);

/**
 * validate_elf - Check if a file is an ELF file.
 * @e_ident: Pointer to an array with ELF magic numbers.
 *
 * Description: Exit with code 98 if not an ELF file.
 */
void validate_elf(unsigned char *e_ident)
{
	int index;

	for (index = 0; index < 4; index++)
	{
		if (e_ident[index] != 127 &&
		    e_ident[index] != 'E' &&
		    e_ident[index] != 'L' &&
		    e_ident[index] != 'F')
		{
			dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
			exit(98);
		}
	}
}

/**
 * display_magic - Print the ELF header's magic numbers.
 * @e_ident: Pointer to an array with ELF magic numbers.
 *
 * Description: Magic numbers are separated by spaces.
 */
void display_magic(unsigned char *e_ident)
{
	int index;

	printf("  Magic:   ");

	for (index = 0; index < EI_NIDENT; index++)
	{
		printf("%02x", e_ident[index]);

		if (index == EI_NIDENT - 1)
			printf("\n");
		else
			printf(" ");
	}
}

/**
 * display_class - Print the ELF header's class.
 * @e_ident: Pointer to an array with the ELF class.
 */
void display_class(unsigned char *e_ident)
{
	printf("  Class:                             ");

	switch (e_ident[EI_CLASS])
	{
	case ELFCLASSNONE:
		printf("none\n");
		break;
	case ELFCLASS32:
		printf("ELF32\n");
		break;
	case ELFCLASS64:
		printf("ELF64\n");
		break;
	default:
		printf("<unknown: %x>\n", e_ident[EI_CLASS]);
	}
}



/**
 * main - Display ELF header information from a file.
 * @argc: Number of arguments.
 * @argv: Array of argument strings.
 *
 * Return: 0 on success, 98 on failure.
 *
 * Description: Exit with code 98 for non-ELF or errors.
 */
int main(int __attribute__((__unused__)) argc, char *argv[])
{
	Elf64_Ehdr *header;
	int fd, read_result;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}

	header = malloc(sizeof(Elf64_Ehdr));
	if (header == NULL)
	{
		close_elf(fd);
		dprintf(STDERR_FILENO, "Error: Can't allocate memory\n");
		exit(98);
	}

	read_result = read(fd, header, sizeof(Elf64_Ehdr));
	if (read_result == -1)
	{
		free(header);
		close_elf(fd);
		dprintf(STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
		exit(98);
	}

	validate_elf(header->e_ident);
	printf("ELF Header:\n");
	display_magic(header->e_ident);
	display_class(header->e_ident);



	free(header);
	close_elf(fd);
	return (0);
}

