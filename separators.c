#include "shell.h"

/**
 * concat_seperator - A function that checks if there id any
 * concatented separators
 * @arr: Array of commands
 *
 * Return: Integer depending on the case
 * 0 for ';' case
 * 1 for ';;' case
 * 2 for unexpected &&
 * 3 for unexpected
 * otherwise -1
 */
ssize_t concat_seperator(char **arr)
{
	int i, j;

	for (i = 0; arr && arr[i]; i++)
	{
		for (j = 1; arr[i][j]; j++)
		{
			if (arr[i][j] == ';' && arr[i][j - 1] == ';')
				return (1);
			else if (arr[i][j] == '&' && arr[i][j - 1] == '&'
					&& j == 2)
				return (2);
			else if (arr[i][j] == '|' && arr[i][j - 1] == '|'
					&& j == 2)
				return (3);
		}
		if (i && arr[i][0] == ';' && arr[i - 1][0] == ';')
			return (0);
		else if (i && arr[i][0] == '&' && arr[i - 1][0] == '&')
			return (2);
		else if (i && arr[i][0] == '|' && arr[i - 1][0] == '|')
			return (3);
		else if (i == 0 && arr[0][0] == ';')
			return (0);
		else if (i == 0 && arr[0][0] == '&')
			return (2);
		else if (i == 0 && arr[0][0] == '|')
			return (3);
	}
	return (-1);
}

