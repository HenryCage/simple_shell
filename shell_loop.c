#include "shell.h"

/**
 * hsh - main shell looping
 * @note: the parameter & return note struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error.
 */
int hsh(info_t *note, char **av)
{
ssize_t s;
int builtin_let;
s = 0;
builtin_let = 0;

while (s != -1 && builtin_let != -2)
{
clear_info(note);
if (interactive(note))
_puts("$ ");
_eputchar(BUF_FLUSH);
s = get_input(note);
if (s != -1)
{
set_info(note, av);
builtin_let = find_builtin(note);
if (builtin_let == -1)
find_cmd(note);
}
else if (interactive(note))
_putchar('\n');
free_info(note, 0);
}
write_history(note);
free_info(note, 1);
if (!interactive(note) && note->status)
exit(note->status);
if (builtin_let == -2)
{
if (note->err_num == -1)
exit(note->status);
exit(note->err_num);
}
return (builtin_let);
}

/**
 * find_builtin - finds a builtin command
 * @note: the parameter & return note struct
 *
 * Return: -1 if builtin not found,
 *		0 if builtin executed successfully,
 *		1 if builtin found but not successful,
 *		-2 if builtin signals exit()
 */
int find_builtin(info_t *note)
{
int i, built_in_let;
built_in_let = -1;

builtin_entry builtintbl[] = {
{"exit", _exit},
{"env", _mienv},
{"help", _mihelp},
{"history", _mihistory},
{"setenv", _mysetenv},
{"unsetenv", _myunsetenv},
{"cd", _micd},
{"alias", _mialias},
{NULL, NULL}
};

for (i = 0; builtintbl[i].type; i++)
{
if (_strcmp(note->argv[0], builtintbl[i].type) == 0)
{
note->line_count++;
built_in_let = builtintbl[i].func(note);
break;
}
}
return (built_in_let);
}

/**
 * find_cmd - finds a command in PATH
 * @note: the parameter & return note struct
 *
 * Return: void
 */
void find_cmd(info_t *note)
{
char *path = NULL;
int i, m;

note->path = note->argv[0];
if (note->linecount_flag == 1)
{
note->line_count++;
note->linecount_flag = 0;
}
for (i = 0, m = 0; note->arg[i]; i++)
if (!is_delim(note->arg[i], " \t\n"))
m++;
if (!m)
return;

path = find_path(note, _getenv(note, "PATH="), note->argv[0]);
if (path)
{
note->path = path;
fork_cmd(note);
}
else
{
if ((interactive(note) || _getenv(note, "PATH=")
|| note->argv[0][0] == '/') && is_cmd(note, note->argv[0]))
fork_cmd(note);
else if (*(note->arg) != '\n')
{
note->status = 127;
print_error(note, "not found\n");
}
}
}

/**
 * fork_cmd - forks an execution thread to run cmd
 * @note: the parameter & return note struct
 *
 * Return: void
 */
void fork_cmd(info_t *note)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(note->path, note->argv, get_environ(note)) == -1)
{
free_info(note, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(note->status));
if (WIFEXITED(note->status))
{
note->status = WEXITSTATUS(note->status);
if (note->status == 126)
print_error(note, "Permission denied\n");
}
}
}
