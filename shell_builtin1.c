#include "shell.h"

/**
 * _mihistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @note: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mihistory(info_t *note)
{
print_list(note->history);
return (0);
}

/**
 * unset_alias - sets alias to string
 * @note: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *note, char *str)
{
char *p, c;
int ret;

p = _strchr(str, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = delete_node_at_index(&(note->alias),
get_node_index(note->alias, node_starts_with(note->alias, str, -1)));
*p = c;
return (ret);
}

/**
 * set_alias - sets alias to string
 * @note: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *note, char *str)
{
char *p;

p = _strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (unset_alias(note, str));

unset_alias(note, str);
return (add_node_end(&(note->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
char *p, *a;
p = NULL;
a = NULL;

if (node)
{
p = _strchr(node->str, '=');
for (a = node->str; a <= p; a++)
_putchar(*a);
_putchar('\'');
_puts(p + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
 * _mialias - mimics the alias builtin (man alias)
 * @note: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mialias(info_t *note)
{
int i;
char *p;
list_t *node;
p = NULL;
node = NULL;
i = 0;

if (note->argc == 1)
{
node = note->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; note->argv[i]; i++)
{
p = _strchr(note->argv[i], '=');
if (p)
set_alias(note, note->argv[i]);
else
print_alias(node_starts_with(note->alias, note->argv[i], '='));
}

return (0);
}
