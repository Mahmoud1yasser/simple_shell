#include "shell.h"

/**
 * _memset - Entery point
 *
 * @s: the pointer char
 *
 * @b: the character
 *
 * @n: the integer
 *
 * Return: (s) a pointer to the memory area s
*/

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 * ffree - Entery point
 *
 * @pp: string og char
*/

void ffree(char **pp)
{
	char **b = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(b);
}

/**
 * _realloc - Entery point
 *
 * @ptr: pointer
 *
 * @old_size: integer
 *
 * @new_size: intger
 *
 * Return: pointer to da ol'block nameen.
*/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *b;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	b = malloc(new_size);
	if (!b)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		b[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (b);
}
