#include "shell.h"

/**
  * display_aliases - A funcction that prints array of aliases
  * @str: Array of aliases
  */
void display_aliases(char **str)
{
	int index;

	for (index = 0; str[index]; ++index)
	{
		write(STDOUT_FILENO, str[index], _strlen(str[index]));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
  * new_def - A function that checks for =
  * @str: Shell arguments
  *
  * Return: 0 if it not found otherwise index of =
  */
size_t new_def(char *str)
{
	int index;

	for (index = 0; str[index]; index++)
	{
		if (str[index] == '=')
			return (index);
	}

	return (0);
}

/**
  * predefined_alias - A function checks if alias is defined before
  * @argument: Shell argument
  * @alias_arr: Array of aliases
  * @length: len of argument
  *
  * Return: -1 if it is not defined otherwise index of alias
  */
int predefined_alias(char *argument, char **alias_arr, size_t length)
{
	int i;

	for (i = 0; alias_arr[i]; i++)
	{
		if (!_strncmp(argument, alias_arr[i], length))
			return (i);
	}
	return (-1);
}


/**
  * check_alias - A function that checks if arguments exists in aliases
  * @argument: An array of shell commands
  * @alias_arr: An array of aliases
  *
  * Return: 1 on failure otherwise 0
  */
char check_alias(char *argument, char **alias_arr)
{
	char status = 0, *ptr;
	size_t length;

	if (!new_def(argument))
	{
		length = _strlen(argument) + 1;
		ptr = malloc(length + 1);
		if (!ptr)
			return (1);

		_strcpy(ptr, argument);
		_strcat(ptr, "=");

		if (predefined_alias(ptr, alias_arr, length) == -1)
		{
			write(STDOUT_FILENO, "alias: ", 7);
			write(STDOUT_FILENO, argument, length - 1);
			write(STDOUT_FILENO, " not found\n", 11);
			status = 1;
		}
		free(ptr);
	}

	return (status);
}

/**
  * display_alias - A function that prints an alias
  * @argument: An alias to be printed
  * @alias_arr: An array of aliases
  *
  * Return: 1 on failure otherwise 0
  */
char display_alias(char *argument, char **alias_arr)
{
	size_t length;
	int flag;
	char *ptr;

	length = _strlen(argument) + 1, ptr = malloc(length + 1);
	if (!ptr)
		return (1);

	_strcpy(ptr, argument);
	_strcat(ptr, "=");
	flag = predefined_alias(ptr, alias_arr, length);
	if (flag != -1)
	{
		write(STDOUT_FILENO, alias_arr[flag], _strlen(alias_arr[flag]));
		write(STDOUT_FILENO, "\n", 1);
	}
	free(ptr);

	return (0);
}
