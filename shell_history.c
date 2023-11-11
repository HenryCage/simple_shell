#include "shell.h"

/**
 * get_history_file - Achieve the history file
 * @note: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *note)
{
char *duf, *dir;

dir = _getenv(note, "HOME=");
if (!dir)
return (NULL);
duf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
if (!duf)
return (NULL);
duf[0] = 0;
_strcpy(duf, dir);
_strcat(duf, "/");
_strcat(duf, HIST_FILE);
return (duf);
}

/**
 * write_history - creates a file, or appends onto an existing file
 * @note: the parameter struct
 *
 * Return: 1 on success, else -1 on fail.
 */
int write_history(info_t *note)
{
ssize_t fd;
char *filename;
list_t *node;
filename = get_history_file(note);
node = NULL;

if (!filename)
return (-1);
fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = note->history; node; node = node->next)
{
_putsfd(node->str, fd);
_putfd('\n', fd);
}
_putfd(BUF_FLUSH, fd);
close(fd);
return (1);
}

/**
 * read_history - reads history from file
 * @note: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *note)
{
ssize_t fd, rdlen, fsize;
struct stat st;
char *buf, *filename;
int i;
int last;
int linecount;
buf = NULL;
filename = get_history_file(note);
fsize = 0;
last = 0;
linecount = 0;
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
build_history_list(note, buf + last, linecount++);
last = i + 1;
}
if (last != i)
build_history_list(note, buf + last, linecount++);
free(buf);
note->histcount = linecount;
while (note->histcount-- >= HIST_MAX)
delete_node_at_index(&(note->history), 0);
renumber_history(note);
return (note->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @note: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *note, char *buf, int linecount)
{
list_t *node;
node = NULL;
if (note->history)
node = note->history;
add_node_end(&node, buf, linecount);

if (!note->history)
note->history = node;
return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes.
 * @note: Structure containing potential arguments.
 *
 * Return: the new histcount
 */
int renumber_history(info_t *note)
{
int i;
list_t *node;
node = note->history;
i = 0;
while (node)
{
node->num = i++;
node = node->next;
}
return (note->histcount = i);
}
