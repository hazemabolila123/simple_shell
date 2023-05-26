#include "shell.h"

/**
 * dollarsign - A function taht handels variable replacement
 * @c: Array of commands
 * @argc: Argument count
 * @status: The status of exit
 *
 * Return: A pointer to the modified commands
 */
char **dollarsign(char **c, size_t argc, size_t *status)
{
	size_t i;
	int j, k;
	char temp[100], *nospace, dollarsign;

	for (i = 0; i < argc; i++)
	{
		dollarsign = 0;
		for (j = 0; j < _strlen(c[i]); j++)
		{
			if (c[i][j] == '$' && c[i][j + 1])
			{
				dollarsign = 1;
				if (c[i][j + 1] == '?')
				{
					free(c[i]);
					c[i] = _strdup(my_itoa(*status, temp, 10));
				}
				else if (c[i][j + 1] == '$')
				{
					free(c[i]);
					my_itoa(getpid(), temp, 10);
					c[i] = _strdup(temp);
				}
				else
				{
					for (k = 0; k < _strlen(c[i]); k++)
						c[i][k] = c[i][k + 1];
					nospace = c[i];
					c[i] = _strdup(my_getenv(c[i]));
					free(nospace);
				}
			}
		}
		if (!dollarsign)
		{
			nospace = c[i];
			c[i] = _strdup(c[i]), free(nospace);
		}
	}
	return (c);
}

