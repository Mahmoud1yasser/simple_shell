#include "shell.h"

/**
 * hsh - main shell loop
 * @strctos: the parameter & return strctos struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(strctos_t *strctos, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_strctos(strctos);
		if (interactive(strctos))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(strctos);
		if (r != -1)
		{
			set_strctos(strctos, av);
			builtin_ret = find_builtin(strctos);
			if (builtin_ret == -1)
				find_cmd(strctos);
		}
		else if (interactive(strctos))
			_putchar('\n');
		free_strctos(strctos, 0);
	}
	write_history(strctos);
	free_strctos(strctos, 1);
	if (!interactive(strctos) && strctos->status)
		exit(strctos->status);
	if (builtin_ret == -2)
	{
		if (strctos->err_num == -1)
			exit(strctos->status);
		exit(strctos->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @strctos: the parameter & return strctos struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int find_builtin(strctos_t *strctos)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(strctos->argv[0], builtintbl[i].type) == 0)
		{
			strctos->line_count++;
			built_in_ret = builtintbl[i].func(strctos);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @strctos: the parameter & return strctos struct
 *
 * Return: void
 */
void find_cmd(strctos_t *strctos)
{
	char *path = NULL;
	int i, k;

	strctos->path = strctos->argv[0];
	if (strctos->linecount_flag == 1)
	{
		strctos->line_count++;
		strctos->linecount_flag = 0;
	}
	for (i = 0, k = 0; strctos->arg[i]; i++)
		if (!is_delim(strctos->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(strctos, _getenv(strctos, "PATH="), strctos->argv[0]);
	if (path)
	{
		strctos->path = path;
		fork_cmd(strctos);
	}
	else
	{
		if ((interactive(strctos) || _getenv(strctos, "PATH=")
					|| strctos->argv[0][0] == '/') && is_cmd(strctos, strctos->argv[0]))
			fork_cmd(strctos);
		else if (*(strctos->arg) != '\n')
		{
			strctos->status = 127;
			print_error(strctos, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @strctos: the parameter & return strctos struct
 *
 * Return: void
 */
void fork_cmd(strctos_t *strctos)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(strctos->path, strctos->argv, get_environ(strctos)) == -1)
		{
			free_strctos(strctos, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(strctos->status));
		if (WIFEXITED(strctos->status))
		{
			strctos->status = WEXITSTATUS(strctos->status);
			if (strctos->status == 126)
				print_error(strctos, "Permission denied\n");
		}
	}
}
