#include "main.h"

/**
 * execmd - Entery point
 *
 * Description: execution of progarm
 *
 * @argv: character pointer to pointer
 *
 * Return: 0
*/

void execmd(char **argv)
{
	char *command = NULL, *actual_command = NULL;
	pid_t child_pid;

	if (argv)
	{
		command = argv[0];

		if (strcmp(command, "cd") == 0)
		{
			if (argv[1])
			{
			if (chdir(argv[1]) == -1)
				perror("cd");
			}
			else
				printf("Usage: cd <directory>\n");
			return;
		}
		actual_command = get_location(command);
		child_pid = fork();

		if (child_pid == -1)
		{
			perror("Fork error");
			return;
		}
		else if (child_pid == 0)
		{
			if (execve(actual_command, argv, NULL) == -1)
				perror("Error:");
			exit(1);
		}
		else
			wait(NULL);
	}
}
