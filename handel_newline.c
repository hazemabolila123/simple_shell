#include "shell.h"

/**
 * handle_newline - commands sepesrated by ;
 * @delim: pointer
 */
void handle_newline(char **delim)
{
	char flag = -1;
	size_t i;

	for (i = 0; *delim && (*delim)[i]; i++)
	{
		if (flag == 1)
		{
			if ((*delim)[i] == '\n')
			{
				(*delim)[i] = ';';
				flag *= -1;
			}
		}
		else if ((*delim)[i] != '\n')
			flag *= -1;
	}
}

