#include "shell.h"

/**
 * interactive - Entery point
 *
 * @strctos: structure address pointer
 *
 * Return: 1 if interactive mode, 0 otherwise
*/

int interactive(strctos_t *strctos)
{
	return (isatty(STDIN_FILENO) && strctos->readfd <= 2);
}

/**
 * is_delim - Entery point
 *
 * @c: the charater
 *
 * @delim: the delimeter string char
 *
 * Return: 1 if yes, 0 if fail
*/

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - Enter pointer
 *
 * @c: character
 *
 * Return: 1 if success, 0 otherwise
*/

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Enter point
 *
 * @s: string to convert
 *
 * Return: 0 if no numbers
*/

int _atoi(char *s)
{
	int j, sign = 1, flag = 0, output;
	unsigned int res = 0;

	for (j = 0; s[j] != '\0' && flag != 2; j++)
	{
		if (s[j] == '-')
			sign *= -1;

		if (s[j] >= '0' && s[j] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (s[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -res;
	else
		output = res;

	return (output);
}
