#include "shell.h"

/**
 * _close - exits the shell
 * @note: Structure containing potential arguments.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _close(info_t *note)
{
int exitcheck;

if (note->argv[1])
{
exitcheck = _erratoi(note->argv[1]);
if (exitcheck == -1)
{
note->status = 2;
print_error(note, "Illegal number: ");
_eputs(note->argv[1]);
_eputchar('\n');
return (1);
}
note->err_num = _erratoi(note->argv[1]);
return (-2);
}
note->err_num = -1;
return (-2);
}

/**
 * _micd - changes the current directory.
 * @note: Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int _micd(info_t *note)
{
char *t, *dir, buffer[1024];
int chdir_ret;

t = getcwd(buffer, 1024);
if (!t)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!note->argv[1])
{
dir = _getenv(note, "HOME=");
if (!dir)
chdir_ret =
chdir((dir = _getenv(note, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (_strcmp(note->argv[1], "-") == 0)
{
if (!_getenv(note, "OLDPWD="))
{
_puts(t);
_putchar('\n');
return (1);
}
_puts(_getenv(note, "OLDPWD=")), _putchar('\n');
chdir_ret =
chdir((dir = _getenv(note, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(note->argv[1]);
if (chdir_ret == -1)
{
print_error(note, "can't cd to ");
_eputs(note->argv[1]), _eputchar('\n');
}
else
{
_setenv(note, "OLDPWD", _getenv(note, "PWD="));
_setenv(note, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
 * _mihelp - changes the current directory of the process
 * @note: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mihelp(info_t *note)
{
char **arg_array;

arg_array = note->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array);
return (0);
}
