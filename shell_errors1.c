#include "shell.h"

/**
 * _putchar - Writes a character to standard output.
 * @c: The character to print.
 * Return: Number of characters written.
 */
int _putchar(char c)
{
return (write(1, &c, 1));
}

/**
 * _eputchar - Writes a character to standard error output.
 * @c: The character to print.
 * Return: Number of characters written.
 */
int _eputchar(char c)
{
return (write(STDERR_FILENO, &c, 1));
}

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *s)
{
int i;
unsigned long int res;
i = 0;
res = 0;

if (*s == '+')
s++;
for (i = 0;  s[i] != '\0'; i++)
{
if (s[i] >= '0' && s[i] <= '9')
{
res *= 10;
res += (s[i] - '0');
if (res > INT_MAX)
return (-1);
}
else
return (-1);
}
return (res);
}

/**
 * print_error - prints an error message
 * @note: the parameter & return note struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *note, char *estr)
{
_eputs(note->fname);
_eputs(": ");
print_d(note->line_count, STDERR_FILENO);
_eputs(": ");
_eputs(note->argv[0]);
_eputs(": ");
_eputs(estr);
}

/**
 * print_d - function prints a decimal(integer) number (base 10)
 * @input: For inserting of values or characters
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
int (*__putchar)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
int i, count;
unsigned int _abs_, current;
count = 0;

if (fd == STDERR_FILENO)
__putchar = _eputchar;
if (input < 0)
{
_abs_ = -input;
__putchar('-');
count++;
}
else
{
_abs_ = input;
}
current = _abs_;
for (i = 1000000000; i > 1; i /= 10)
{
if (_abs_ / i)
{
__putchar('0' + current / i);
count++;
}
current %= i;
}
__putchar('0' + current);
count++;

return (count);
}

/**
 * convert_number - converter function.
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
static char buffer[50];
char sign;
char *ptr, *array;
unsigned long n;
n = num;
sign = 0;

if (!(flags & CONVERT_UNSIGNED) && num < 0)
{
n = -num;
sign = '-';
}
array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';

do
{
*--ptr = array[n % base];
n /= base;
}
while (n != 0);

if (sign)
*--ptr = sign;

return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
int i;

for (i = 0; buf[i] != '\0'; i++)
{
if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
{
buf[i] = '\0';
break;
}
}
}
#ifdef TEST_REMOVE_COMMENTS

int main(void)
{
char testString[] = "This is a test #comment";
printf("Before: %s\n", testString);
remove_comments(testString);
printf("After: %s\n", testString);
return 0;
}
#endif
