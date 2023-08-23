#include "shell.h"

/**
 * clear_strctos - Entery point
 *
 * @strctos: struct address
 *
 * Retrun: 0 if success
 */
void clear_strctos(strctos_t *strctos)
{
	strctos->arg = NULL;
	strctos->argv = NULL;
	strctos->path = NULL;
	strctos->argc = 0;
}

/**
 * set_strctos - Entery point
 *
 * @strctos: strct pointer
 *
 * @av: argument vector
 *
 * Return: 0 if success
*/

void set_strctos(strctos_t *strctos, char **av)
{
	int k = 0;

	strctos->fname = av[0];
	if (strctos->arg)
	{
		strctos->argv = strtow(strctos->arg, " \t");
		if (!strctos->argv)
		{
			strctos->argv = malloc(sizeof(char *) * 2);
			if (strctos->argv)
			{
				strctos->argv[0] = _strdup(strctos->arg);
				strctos->argv[1] = NULL;
			}
		}
		for (k = 0; strctos->argv && strctos->argv[k]; k++)
			;
		strctos->argc = k;

		replace_alias(strctos);
		replace_vars(strctos);
	}
}

/**
 * free_strctos - Entery point
 *
 * @strctos: struct address pointer
 *
 * @all: integer
 *
 * Return: 0 if success
*/

void free_strctos(strctos_t *strctos, int all)
{
	ffree(strctos->argv);
	strctos->argv = NULL;
	strctos->path = NULL;
	if (all)
	{
		if (!strctos->cmd_buf)
			free(strctos->arg);
		if (strctos->env)
			free_list(&(strctos->env));
		if (strctos->history)
			free_list(&(strctos->history));
		if (strctos->alias)
			free_list(&(strctos->alias));
		ffree(strctos->environ);
			strctos->environ = NULL;
		bfree((void **)strctos->cmd_buf);
		if (strctos->readfd > 2)
			close(strctos->readfd);
		_putchar(BUF_FLUSH);
	}
}
