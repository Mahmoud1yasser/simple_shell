#include "shell.h"

/**
 * main - entry point
 *
 * @ac: arg for count
 *
 * @av: arg for vector
 *
 * Return: 0 on success, 1 on fail
*/

int main(int ac, char **av)
{
	strctos_t strctos[] = { strctos_INIT };
	int fd1 = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd1)
			: "r" (fd1));

	if (ac == 2)
	{
		fd1 = open(av[1], O_RDONLY);
		if (fd1 == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		strctos->readfd = fd1;
	}
	populate_env_list(strctos);
	read_history(strctos);
	hsh(strctos, av);
	return (EXIT_SUCCESS);
}
