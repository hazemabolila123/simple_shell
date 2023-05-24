#include "shell.h"


/**
 * _strlen - A function that returns the length of a string
 * @str: String
 *
 * Return: Length of that string
 */
int _strlen(char *str)
{
	int i = 0, cnt = 0;

	for (i = 0; str && str[i] != '\0'; i++)
		cnt++;

	return (cnt);
}


/**
 * _strcat - A function that concatenates two strings
 * @dest: String 1
 * @src: String 2
 *
 * Return: Concatanted String
 */
char *_strcat(char *dest, char *src)
{
	int dlen = 0, i;

	for (i = 0; dest[i] != '\0'; i++)
		dlen++;
	for (i = 0; src[i] != '\0'; i++)
		dest[dlen + i] = src[i];
	dest[dlen + i] = '\0';

	return (dest);
}


/**
 * _strncmp - A function that compares two strimgs according to specific length
 * @str1: String one
 * @str2: string two
 * @n: length
 *
 * Return: 0 if success
 */
int _strncmp(char *str1, char *str2, size_t n)
{
	while (*str1 != '\0' && *str2 != '\0' && --n)
	{
		if (*str1 != *str2)
			break;
		str1++, str2++;
	}
	return (*str1 - *str2);
}

/**
 * _strdup - A function that returns a pointer
 * to a newly allocated space in memory.
 * @str: Function parameter
 *
 * Return: a pointer to a newly allocated space in memory.
 *
 */
char *_strdup(char *str)
{
	if (str != NULL)
	{
		char *strcp = str, *strdup, *strdup2;
		int len = 1;

		while (*strcp != '\0')
		{
			len++;
			strcp++;
		}
		strdup = (char *)malloc(len * sizeof(char));
		strdup2 = strdup;
		strcp = str;
		while (strdup != NULL && len--)
		{
			*strdup2 = *strcp;
			strcp++;
			strdup2++;
		}
		return (strdup);
	}
	else
	{
		return (str);
	}
}


/**
 * _strrev - A function that reverses a string.
 * @str : String to be reversed
 *
 * Return: Reversed string
 */
char *_strrev(char *str)
{
	int i,	j = 0;
	char tmp;

	while (str[j])
	{
		j++;
	}

	for (i = 0; i < j / 2; i++)
	{
		tmp = str[i];
		str[i] = str[j - i - 1];
		str[j - i - 1] = tmp;
	}
	return (str);
}
