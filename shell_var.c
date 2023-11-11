#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @note: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *note, char *buf, size_t *p)
{
size_t k;
k = *p;

if (buf[k] == '|' && buf[k + 1] == '|')
{
buf[k] = 0;
k++;
note->cmd_buf_type = CMD_OR;
}
else if (buf[k] == '&' && buf[k + 1] == '&')
{
buf[k] = 0;
k++;
note->cmd_buf_type = CMD_AND;
}
else if (buf[k] == ';')
{
buf[k] = 0;
note->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*p = k;
return (1);
}

/**
 * check_chain - checks should continue chaining based on last status
 * @note: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *note, char *buf, size_t *p, size_t i, size_t len)
{
size_t k;
k = *p;

if (note->cmd_buf_type == CMD_AND)
{
if (note->status)
{
buf[i] = 0;
k = len;
}
}
if (note->cmd_buf_type == CMD_OR)
{
if (!note->status)
{
buf[i] = 0;
k = len;
}
}

*p = k;
}

/**
 * replace_alias - replaces an alias in the tokenized string
 * @note: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *note)
{
int i;
list_t *node;
char *p;

for (i = 0; i < 10; i++)
{
node = node_starts_with(note->alias, note->argv[0], '=');
if (!node)
return (0);
free(note->argv[0]);
p = _strchr(node->str, '=');
if (!p)
return (0);
p = _strdup(p + 1);
if (!p)
return (0);
note->argv[0] = p;
}
return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @note: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *note)
{
int i;
list_t *node;
i = 0;

for (i = 0; note->argv[i]; i++)
{
if (note->argv[i][0] != '$' || !note->argv[i][1])
continue;

if (!_strcmp(note->argv[i], "$?"))
{
replace_string(&(note->argv[i]),
_strdup(convert_number(note->status, 10, 0)));
continue;
}
if (!_strcmp(note->argv[i], "$$"))
{
replace_string(&(note->argv[i]),
_strdup(convert_number(getpid(), 10, 0)));
continue;
}
node = node_starts_with(note->env, &note->argv[i][1], '=');
if (node)
{
replace_string(&(note->argv[i]),
_strdup(_strchr(node->str, '=') + 1));
continue;
}
replace_string(&note->argv[i], _strdup(""));

}
return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
