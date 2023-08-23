#include "shell.h"

/**
 **_strncpy - Entery point
 *
 *@dest: the destination
 *
 *@src: the source string
 *
 *@n: integrer
 *
 *Return: the concatenated string
*/

char *_strncpy(char *dest, char *src, int n)
{
	int k, h;
	char *s = dest;

	k = 0;
	while (src[k] != '\0' && k < n - 1)
	{
		dest[k] = src[k];
		k++;
	}
	if (k < n)
	{
		h = k;
		while (h < n)
		{
			dest[h] = '\0';
			h++;
		}
	}
	return (s);
}

/**
 **_strncat - Entery point
 *
 *@dest: the firs
 *
 *@src: the sec
 *
 *@n: integer
 *
 *Return: the concatenated string
*/

char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	k = 0;
	j = 0;
	while (dest[k] != '\0')
		k++;
	while (src[j] != '\0' && j < n)
	{
		dest[k] = src[j];
		k++;
		j++;
	}
	if (j < n)
		dest[k] = '\0';
	return (s);
}

/**
 **_strchr - Entery point
 *
 *@s: character
 *
 *@c: the character
 *
 *Return: (s) a pointer
*/

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
