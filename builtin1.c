#include "shell.h"

/**
 * _myhistory - entery point
 *
 * @strctos: Structu
 *
 * Description: constant function prototype.
 *
 *  Return: Always 0
*/

int _myhistory(strctos_t *strctos)
{
	print_list(strctos->history);
	return (0);
}

/**
 * unset_alias - entery point
 *
 * @strctos: parameter struct
 *
 * @str: character
 *
 * Return: Always 0 on success, 1 on error
*/

int unset_alias(strctos_t *strctos, char *str)
{
	char *b, d;
	int a;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	d = *b;
	*b = 0;
	a = delete_node_at_index(&(strctos->alias),
		get_node_index(strctos->alias, node_starts_with(strctos->alias, str, -1)));
	*b = d;
	return (a);
}

/**
 * set_alias - entery ponit
 *
 * @strctos: character
 *
 * @str: character
 *
 * Return: Always 0 on success, 1 on error
*/

int set_alias(strctos_t *strctos, char *str)
{
	char *b;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	if (!*++b)
		return (unset_alias(strctos, str));

	unset_alias(strctos, str);
	return (add_node_end(&(strctos->alias), str, 0) == NULL);
}

/**
 * print_alias - Entery point
 *
 * @node: charcte
 *
 * Return: Always 0 on success, 1 on error
*/

int print_alias(list_t *node)
{
	char *b = NULL, *a = NULL;

	if (node)
	{
		b = _strchr(node->str, '=');
		for (a = node->str; a <= b; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(b + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - entery point
 *
 * @strctos: Structure containing
 *
 *  Return: Always 0
*/

int _myalias(strctos_t *strctos)
{
	int j = 0;
	char *b = NULL;
	list_t *node = NULL;

	if (strctos->argc == 1)
	{
		node = strctos->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; strctos->argv[j]; j++)
	{
		b = _strchr(strctos->argv[j], '=');
		if (b)
			set_alias(strctos, strctos->argv[j]);
		else
			print_alias(node_starts_with(strctos->alias, strctos->argv[j], '='));
	}

	return (0);
}
