#include "shell.h"

/**
 * _myexit - entery point
 *
 * @info: Structure contain
 *
 * constant function prototype.
 *
 * Return: exits with a given exit status
*/

int _myexit(info_t *info)
{
	int exit1;

	if (info->argv[1])
	{
		exit1 = _erratoi(info->argv[1]);
		if (exit1 == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Entery point
 *
 * @info: Structure containing
 *
 * constant function prototype.
 *
 * Return: Always 0
*/

int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int cdir;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			cdir = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			cdir = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		cdir = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		cdir = chdir(info->argv[1]);
	if (cdir == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - Entery point
 *
 * @info: Structure containing
 *
 *Description: constant function prototype.
 *
 * Return: Always 0
*/

int _myhelp(info_t *info)
{
	char **arg_ar;

	arg_ar = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_ar);
	return (0);
}
