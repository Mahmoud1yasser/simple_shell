#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @strctos: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(strctos_t *strctos)
{
	if (!strctos->environ || strctos->env_changed)
	{
		strctos->environ = list_to_strings(strctos->env);
		strctos->env_changed = 0;
	}

	return (strctos->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @strctos: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(strctos_t *strctos, char *var)
{
	list_t *node = strctos->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			strctos->env_changed = delete_node_at_index(&(strctos->env), i);
			i = 0;
			node = strctos->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (strctos->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @strctos: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(strctos_t *strctos, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = strctos->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			strctos->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(strctos->env), buf, 0);
	free(buf);
	strctos->env_changed = 1;
	return (0);
}

