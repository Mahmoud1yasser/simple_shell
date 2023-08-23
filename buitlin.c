#include "shell.h"

/**
 * _myexit - entery point
 *
 * @strctos: Structure contain
 *
 * constant function prototype.
 *
 * Return: exits with a given exit status
*/

int _myexit(strctos_t *strctos)
{
	int exit1;

	if (strctos->argv[1])
	{
		exit1 = _erratoi(strctos->argv[1]);
		if (exit1 == -1)
		{
			strctos->status = 2;
			print_error(strctos, "Illegal number: ");
			_eputs(strctos->argv[1]);
			_eputchar('\n');
			return (1);
		}
		strctos->err_num = _erratoi(strctos->argv[1]);
		return (-2);
	}
	strctos->err_num = -1;
	return (-2);
}

/**
 * _mycd - Entery point
 *
 * @strctos: Structure containing
 *
 * constant function prototype.
 *
 * Return: Always 0
*/

int _mycd(strctos_t *strctos)
{
	char *s, *dir, buffer[1024];
	int cdir;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!strctos->argv[1])
	{
		dir = _getenv(strctos, "HOME=");
		if (!dir)
			cdir = /* TODO: what should this be? */
				chdir((dir = _getenv(strctos, "PWD=")) ? dir : "/");
		else
			cdir = chdir(dir);
	}
	else if (_strcmp(strctos->argv[1], "-") == 0)
	{
		if (!_getenv(strctos, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(strctos, "OLDPWD=")), _putchar('\n');
		cdir = /* TODO: what should this be? */
			chdir((dir = _getenv(strctos, "OLDPWD=")) ? dir : "/");
	}
	else
		cdir = chdir(strctos->argv[1]);
	if (cdir == -1)
	{
		print_error(strctos, "can't cd to ");
		_eputs(strctos->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(strctos, "OLDPWD", _getenv(strctos, "PWD="));
		_setenv(strctos, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - Entery point
 *
 * @strctos: Structure containing
 *
 *Description: constant function prototype.
 *
 * Return: Always 0
*/

int _myhelp(strctos_t *strctos)
{
	char **arg_ar;

	arg_ar = strctos->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_ar);
	return (0);
}
