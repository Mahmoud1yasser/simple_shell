#include "shell.h"

/**
 * input_buf - buffers command
 * @strctos: structure
 * @buf: buffer addr
 * @len: buffr lenght
 *
 * Return: bytes read
 */
ssize_t input_buf(strctos_t *strctos, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)strctos->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(strctos, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			strctos->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(strctos, *buf, strctos->histcount++);
			{
				*len = r;
				strctos->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - get line exclude new
 * @strctos: structure
 *
 * Return: bytes readen
 */
ssize_t get_input(strctos_t *strctos)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(strctos->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(strctos, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(strctos, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(strctos, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			strctos->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - read buff
 * @strctos: structure
 * @buf: constructed buffer
 * @i: size
 * Return: r
 */
ssize_t read_buf(strctos_t *strctos, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(strctos->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - get nextline from STDIN
 * @strctos: structure
 * @ptr: pointer to buffer
 * @length: lenght of buffer
 * Return: s
 */
int _getline(strctos_t *strctos, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(strctos, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - block ctrl-C
 * @sig_num: signal num
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
