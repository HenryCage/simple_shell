#include "shell.h"

/**
 * **strtow - splits a string into words.
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
int i, j, k, m, numwords;
char **u;
numwords = 0;

if (str == NULL || str[0] == 0)
return (NULL);
if (!d)
d = " ";
for (i = 0; str[i] != '\0'; i++)
if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
numwords++;
if (numwords == 0)
return (NULL);
u = malloc((1 + numwords) *sizeof(char *));
if (!u)
return (NULL);
for (i = 0, j = 0; j < numwords; j++)
{
while (is_delim(str[i], d))
i++;
k = 0;
while (!is_delim(str[i + k], d) && str[i + k])
k++;
u[j] = malloc((k + 1) * sizeof(char));
if (!u[j])
{
for (k = 0; k < j; k++)
free(u[k]);
free(u);
return (NULL);
}
for (m = 0; m < k; m++)
u[j][m] = str[i++];
u[j][m] = 0;
}
u[j] = NULL;
return (u);
}

/**
 * **strtow1 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow1(char *str, char d)
{
int i, j, l, m, numwords;
char **u;
numwords = 0;
l = 0;

if (str == NULL || str[0] == 0)
return (NULL);
for (i = 0; str[i] != '\0'; i++)
if ((str[i] != d && str[i + 1] == d) ||
(str[i] != d && !str[i + 1]) || str[i + 1] == d)
numwords++;
if (numwords == 0)
return (NULL);
u = malloc((1 + numwords) *sizeof(char *));
if (!u)
return (NULL);
for (i = 0, j = 0; j < numwords; j++)
{
while (str[i] == d && str[i] != d)
i++;
while (str[i + l] != d && str[i + l] && str[i + l] != d)
l++;
u[j] = malloc((l + 1) * sizeof(char));
if (!u[j])
{
for (l = 0; l < j; l++)
free(u[l]);
free(u);
return (NULL);
}
for (m = 0; m < l; m++)
u[j][m] = str[i++];
u[j][m] = 0;
}
u[j] = NULL;
return (u);
}
