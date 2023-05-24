#include "shell.h"

/**
 * isdelim - A function to handel check if there is any delimiter
 * in the command line
 * @sp: Char to be checked
 * @delim: String of delims
 *
 * Return: 0 if there is no delimiter in the command line otherwise
 * 1 or 2 or 3 or 4 depending on the case
 */
char isdelim(char sp, char *delim)
{
	int index;

	for (index = 0; delim[index]; index++)
	{
		if (delim[index] == sp)
			return (1);
		else if (';' == sp)
			return (2);
		else if ('&' == sp)
			return (3);
		else if ('|' == sp)
			return (4);
	}
	return (0);
}

/**
 * words_count - A function that counts num of words in string
 * @str: String to be counted
 * @delim: Delimiters
 *
 * Return: Number of words
 */
int words_count(char *str, char *delim)
{
	int chars = 0, i = 0;
	char is_one = -1;

	if (isdelim(str[0], delim) != 1)
		chars++;
	if (str[0] == '\'')
		is_one = 1;
	for (i = 1; str[i]; i++)
	{
		if (is_one == -1)
		{
			if (isdelim(str[i - 1], delim) && !isdelim(str[i], delim))
				chars++;
			else if (isdelim(str[i - 1], delim) != 2 && isdelim(str[i], delim) == 2)
				chars++;
			else if (isdelim(str[i - 1], delim) != 3 && isdelim(str[i], delim) == 3)
				chars++;
			else if (isdelim(str[i - 1], delim) != 4 && isdelim(str[i], delim) == 4)
				chars++;
		}
		if (str[i] == '\'')
			is_one *= -1;
	}
	return (chars);
}


/**
 * token_len - A function that calculates a token length
 * @strcp: String
 * @delim: Delimiter
 *
 * Return: The token length
 */
int token_len(char *strcp, char *delim)
{
	int length = 0;

	if (isdelim(*strcp, delim) == 0)
	{
		if (*strcp == '\'')
		{
			length = 1;
			while (strcp[length] != '\'')
				length++;
			length++;
		}
		else
			while (isdelim(*(strcp + length), delim) == 0 && strcp[length] != '\0')
			{
				if (strcp[length] == '\'')
				{
					length++;
					while (strcp[length] != '\'')
						length++;
					length++;
				}
				else
					length++;
			}
	}
	else if (isdelim(*strcp, delim) == 2)
		while (isdelim(*(strcp + length), delim) == 2)
			length++;
	else if (isdelim(*strcp, delim) == 3)
		while (isdelim(*(strcp + length), delim) == 3)
			length++;
	else if (isdelim(*strcp, delim) == 4)
		while (isdelim(*(strcp + length), delim) == 4)
			length++;
	return (length);
}


/**
 * _strtok - A function that splits a command line into number
 * of commands and store them in an array
 * @str: String to be split
 * @delim: Delimiter
 *
 * Return: Array of split commands
 */
char **_strtok(char *str, char *delim)
{
	char *strcp = str, **commands_arr;
	int words = 1, length, i = 0;

	if (str == NULL || *str == '\0')
		return (NULL);
	words += words_count(str, delim);
	if (words == 1)
		return (NULL);
	commands_arr = (char **)malloc(words * sizeof(char *));
	if (commands_arr != NULL)
	{
		strcp = str;
		while (*strcp != '\0')
		{
			length = token_len(strcp, delim);
			if (length)
			{
				commands_arr[i] = (char *)malloc
					((length + 1) * sizeof(char));
				if (commands_arr[i] == NULL)
				{
					free_array(commands_arr);
					return (NULL);
				}
				_strncpy(commands_arr[i], strcp, length);
				strcp += length - 1;
				commands_arr[i][length] = '\0', i++;
			}
			strcp++;
		}
		commands_arr[i] = NULL;
	}
	return (commands_arr);
}
