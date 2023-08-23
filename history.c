#include "shell.h"

/**
 * get_history_file - history file
 * @strctos: structure
 *
 * Return: string to hist_file
 */

char *get_history_file(strctos_t *strctos)
{
	char *buf, *dir;

	dir = _getenv(strctos, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - create or append file
 * @strctos: structure
 * Return: 1 on success, else -1
 */
int write_history(strctos_t *strctos)
{
	ssize_t fd;
	char *filename = get_history_file(strctos);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = strctos->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads hist file
 * @strctos: structure
 * Return: histcount on success, 0 otherwise
 */
int read_history(strctos_t *strctos)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(strctos);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(strctos, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(strctos, buf + last, linecount++);
	free(buf);
	strctos->histcount = linecount;
	while (strctos->histcount-- >= HIST_MAX)
		delete_node_at_index(&(strctos->history), 0);
	renumber_history(strctos);
	return (strctos->histcount);
}

/**
 * build_history_list - build linked list
 * @strctos: Structure of arguments
 * @buf: buffer
 * @linecount: hist line count
 * Return: Always 0
 */
int build_history_list(strctos_t *strctos, char *buf, int linecount)
{
	list_t *node = NULL;

	if (strctos->history)
		node = strctos->history;
	add_node_end(&node, buf, linecount);

	if (!strctos->history)
		strctos->history = node;
	return (0);
}

/**
 * renumber_history - renumber history list after change
 * @strctos: Structure of arguments
 * Return: the new hist count
 */
int renumber_history(strctos_t *strctos)
{
	list_t *node = strctos->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (strctos->histcount = i);
}
