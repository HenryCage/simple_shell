#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @note: struct address
 */
void clear_info(info_t *note)
{
note->arg = NULL;
note->argv = NULL;
note->path = NULL;
note->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @note: struct address
 * @avr: argument vector
 */
void set_info(info_t *note, char **avr)
{
int i;
i = 0;

note->fname = avr[0];
if (note->arg)
{
note->argv = strtow(note->arg, " \t");
if (!note->argv)
{

note->argv = malloc(sizeof(char *) * 2);
if (note->argv)
{
note->argv[0] = _strdup(note->arg);
note->argv[1] = NULL;
}
}
for (i = 0; note->argv && note->argv[i]; i++);
note->argc = i;

replace_alias(note);
replace_vars(note);
}
}

/**
 * free_info - frees info_t struct fields
 * @note: struct address
 * @total: true if freeing all fields
 * Return: 0
 */
void free_info(info_t *note, int total)
{
ffree(note->argv);
note->argv = NULL;
note->path = NULL;
if (total)
{
if (!note->cmd_buf)
free(note->arg);
if (note->env)
free_list(&(note->env));
if (note->history)
free_list(&(note->history));
if (note->alias)
free_list(&(note->alias));
free(note->environ);
note->environ = NULL;
bfree((void **)note->cmd_buf);
if (note->readfd > 2)
close(note->readfd);
_putchar(BUF_FLUSH);
}
}
