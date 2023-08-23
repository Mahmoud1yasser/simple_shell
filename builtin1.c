#include "shell.h"

/**
 * _myhistory - entery point
 *
 * @info: Structu
 *
 * Description: constant function prototype.
 *
 *  Return: Always 0
*/

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - entery point
 *
 * @info: parameter struct
 *
 * @str: character
 *
 * Return: Always 0 on success, 1 on error
*/

int unset_alias(info_t *info, char *str)
{
	char *b, d;
	int a;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	d = *b;
	*b = 0;
	a = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*b = d;
	return (a);
}

/**
 * set_alias - entery ponit
 *
 * @info: character
 *
 * @str: character
 *
 * Return: Always 0 on success, 1 on error
*/

int set_alias(info_t *info, char *str)
{
	char *b;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	if (!*++b)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
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
 * @info: Structure containing
 *
 *  Return: Always 0
*/

int _myalias(info_t *info)
{
	int j = 0;
	char *b = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		b = _strchr(info->argv[j], '=');
		if (b)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}
