#include "shell.h"

/**
 * _strlen - Entery point
 *
 * @s: string of char
 *
 * Return: integer length of string
*/

int _strlen(char *s)
{
	int k = 0;

	if (!s)
		return (0);

	while (*s++)
		k++;
	return (k);
}

/**
 * _strcmp - Entery point
 *
 * @s1: character
 *
 * @s2: the second strang char
 *
 * Return: integrer number
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Entery ponit
 *
 * @haystack: const character
 *
 * @needle: const character
 *
 * Return: address of next char
*/

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Entery point
 *
 * @dest: character
 *
 * @src: the source buffer char
 *
 * Return: pointer to dest of type char
*/

char *_strcat(char *dest, char *src)
{
	char *re = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (re);
}
