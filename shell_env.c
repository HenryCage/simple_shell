#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @note: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *note)
{
	if (!note->environ || note->env_changed)
	{
		note->environ = list_to_strings(note->env);
		note->env_changed = 0;
	}

	return (note->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @note: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */

int _unsetenv(info_t *note, char *var)
{
	list_t *node;
	size_t i;
	char *p;

	node = note->env;
	i = 0;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);

		if (p && *p == '=')
		{
			note->env_changed = delete_node_at_index(&(note->env), i);
			i = 0;
			node = note->env;
			continue;
		}

		node = node->next;
		i++;
	}
	return (note->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             / modify an existing one
 * @note: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */

int _setenv(info_t *note, char *var, char *value)
{
	char *buf;
	list_t *node;
	char *p;

	buf = NULL;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);

	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = note->env;

	while (node)
	{
		p = starts_with(node->str, var);

		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			note->env_changed = 1;
			return (0);
		}

		node = node->next;
	}

	add_node_end(&(note->env), buf, 0);
	free(buf);
	note->env_changed = 1;

	return (0);
}
