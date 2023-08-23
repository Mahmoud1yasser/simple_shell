#include "shell.h"

/**
 * is_cmd - Entery point
 *
 * @strctos: the strctos struct
 *
 * @path: Character
 *
 * Return: 1 if true, 0 fail
*/

int is_cmd(strctos_t *strctos, char *path)
{
	struct stat st;

	(void)strctos;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Entery point
 *
 * @pathstr: Charater
 *
 * @start: integer
 *
 * @stop: integer
 *
 * Return: pointer to new buffer
*/

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int j = 0, k = 0;

	for (k = 0, j = start; j < stop; j++)
		if (pathstr[j] != ':')
			buf[k++] = pathstr[j];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - Entery point
 *
 * @strctos: the strctos struct
 *
 * @pathstr: Charater
 *
 * @cmd: the cmd to find charater
 *
 * Return: full path of cmd if found or NULL
*/

char *find_path(strctos_t *strctos, char *pathstr, char *cmd)
{
	int j = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(strctos, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[j] || pathstr[j] == ':')
		{
			path = dup_chars(pathstr, curr_pos, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(strctos, path))
				return (path);
			if (!pathstr[j])
				break;
			curr_pos = j;
		}
		j++;
	}
	return (NULL);
}
