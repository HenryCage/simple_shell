#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read and write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chains */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* for system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

#define EPUTS_H

void eputs(const char *str);
void eputchar(char c);

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguments to pass a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguments
 *@argv: an array of strings generated from arg
 *@path: a string path for a current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: filename of programs
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecount_flag;
char *fname;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;

char **cmd_buf;
int cmd_buf_type;
int readfd;
int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
char *type;
int (*func)(info_t *note);
} builtin_entry;


/* All shell loop.c functions */
int hsh(info_t *note, char **av);
int find_builtin(info_t *note);
void find_cmd(info_t *note);
void fork_cmd(info_t *note);
int loophsh(char **);

/* All functions for parser.c */
int is_cmd(info_t *note, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *note, char *pathstr, char *cmd);

/* All Addressing errors.c functions */
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* All errors.c functions */
int _erratoi(char *s);
void print_error(info_t *note, char *estr);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);

/* All string.c functions */
int _strlen(char *s);
int _strcmp(char *s0, char *s1);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);

/* All string.c edit functions */
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);

/* All exits.c functions */
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);

/* All tokenizer.c functions */
char **strtow(char *str, char *d);
char **strtow1(char *str, char d);

/* All realloc.c functions */
char *_memset(char *s, char b, unsigned int n);
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* All memory.c allocated functions */
int bfree(void **ptr);

/* All atoi.c functions */
int interactive(info_t *note);
int is_delim(char c, char *delim);
int _atoi(char *s);
int _isalpha(int c);

/* All builtin.c functions */
int _close(info_t *note);
int _micd(info_t *note);
int _mihelp(info_t *note);

/* All builtin.c functions edit */
int _mialias(info_t *note);
int _mihistory(info_t *note);
int unset_alias(info_t *note, char *str);
int set_alias(info_t *note, char *str);

/* All getline.c functions */
ssize_t get_input(info_t *note);
int _getline(info_t *note, char **buf, size_t *len);
void sigintHandler(__attribute__((unused))int sig_num);
int _getline(info_t *note, char **ptr, size_t *length);
ssize_t read_buf(info_t *note, char *buf, size_t *i);

/* All getinfo.c  functions */
void clear_info(info_t *note);
void set_info(info_t *note, char **avr);
void free_info(info_t *note, int total);

/* All environ.c functions */
char *_getenv(info_t *note, const char *name);
int _mienv(info_t *note);
int _mysetenv(info_t *note);
int _myunsetenv(info_t *note);
int populate_env_list(info_t *note);

/* All getenv.c functions */
char **get_environ(info_t *note);
int _unsetenv(info_t *note, char *var);
int _setenv(info_t *note, char *var, char *value);

/* Al history.c functions */
char *get_history_file(info_t *note);
int write_history(info_t *note);
int read_history(info_t *note);
int build_history_list(info_t *note, char *buf, int linecount);
int renumber_history(info_t *note);

/* All lists.c functions */
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);

/* All lists.c functions edit */
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

/* All vars.c functions */
int is_chain(info_t *note, char *buf, size_t *p);
void check_chain(info_t *note, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_t *note);
int replace_vars(info_t *note);
int replace_string(char **old, char *new);

#endif /* SHELL_H */
