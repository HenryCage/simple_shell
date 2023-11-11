#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @note: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *note, char **buf, size_t *len)
{
ssize_t u;
size_t len_q;
u = 0;
len_q = 0;

if (!*len)
{
b
signal(SIGINT, sigintHandler);

#if USE_GETLINE
u = getline(buf, &len_q, stdin);
#else
u = _getline(note, buf, &len_q);
#endif
if (u > 0)
{
if ((*buf)[u - 1] == '\n')
{
(*buf)[u - 1] = '\0';
u--;
}
note->linecount_flag = 1;
remove_comments(*buf);
build_history_list(note, *buf, note->histcount++);

{
*len = u;
note->cmd_buf = buf;
}
}

return (u);
}

/**
 * get_input - gets a line minus the newline
 * @note: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *note)
{
static char *buf;
static size_t i, m, len;
ssize_t u;
char **buf_p;
char **p;
*buf_p = &(note->arg);
u = 0;

_putchar(BUF_FLUSH);
u = input_buf(note, &buf, &len);
if (u == -1)
return (-1);
if (len)
{
m = i;
p = buf + i;
check_chain(note, buf, &m, i, len);
while (m < len)
{
if (is_chain(note, buf, &m))
break;
m++;
}
i = m + 1;
if (i >= len)
{
i = len = 0;
note->cmd_buf_type = CMD_NORM;
}
*buf_p = p;
return (_strlen(p));
*buf_p = buf;
return (u);
}

/**
 * read_buf - reads a buffer
 * @note: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: u
 */
ssize_t read_buf(info_t *note, char *buf, size_t *i)
{
ssize_t u;
u = 0;
if (*i)
return (0);
u = read(note->readfd, buf, READ_BUF_SIZE);
if (u >= 0)
*i = u;
return (u);
}

/**
 * _getline - gets the next line of input from STDIN
 * @note: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *note, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t i, len;
size_t m;
ssize_t r, s;
char *p, *new_p, *c;
p = NULL;
new_p = NULL;
r = 0;
s = 0;
p = *ptr;
if (p && length)
s = *length;
if (i == len)
i = len = 0;
r = read_buf(note, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);

c = _strchr(buf + i, '\n');
m = c ? 1 + (unsigned int)(c - buf) : len;
new_p = _realloc(p, s, s ? s + m : m + 1);
if (!new_p)
return (p ? free(p), -1 : -1);

if (s)
_strncat(new_p, buf + i, m - i);
else
_strncpy(new_p, buf + i, m - i + 1);
S += m - i;
i = m;
p = new_p;

if (length)
*length = s;
*ptr = p;
return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
