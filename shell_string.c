#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
int i;
i = 0;

if (!s)
return (0);
while (*s++)
i++;
return (i);
}

/**
 * _strcmp - performs a comparison of two strangs.
 * @s0: the first strang
 * @s1: the second strang
 *
 * Return: negative if s0 < s1, positive if s0 > s1, zero if s0 == s1
 */
int _strcmp(const char *s0, const char *s1)
{
while (*s0 && *s1)
{
if (*s0 != *s1)
return (*s0 - *s1);
s0++;
s1++;
}
if (*s0 == *s1)
return (0);
else
return (*s0 < *s1 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: An address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: A pointer to destination buffer
 */
char *_strcat(char *dest, const char *src)
{
char *let = dest;

while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = '\0';
return (let);
}
