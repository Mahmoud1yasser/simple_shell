#include "shell.h"

/**
 * _myenv - print current enviro
 * @strctos: structure of arguments.
 * Return: Always 0
 */
int _myenv(strctos_t *strctos)
{
	print_list_str(strctos->env);
	return (0);
}

/**
 * _getenv - get value of environ variable
 * @strctos: structure of arguments
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(strctos_t *strctos, const char *name)
{
	list_t *node = strctos->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - new inviron modify existing one
 * @strctos: structure of arguments
 *  Return: Always 0
 */
int _mysetenv(strctos_t *strctos)
{
	if (strctos->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(strctos, strctos->argv[1], strctos->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - remove environ variable
 * @strctos: structure of arguments.
 * Return: Always 0
 */
int _myunsetenv(strctos_t *strctos)
{
	int i;

	if (strctos->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= strctos->argc; i++)
		_unsetenv(strctos, strctos->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @strctos: structure of arguments.
 * Return: Always 0
 */
int populate_env_list(strctos_t *strctos)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	strctos->env = node;
	return (0);
}
