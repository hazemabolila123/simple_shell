#include "shell.h"

/**
 * alias_value - A function that concatenates
 * "'" before and after alias value
 * @argument: An alias
 * @index: the index of '='
 *
 * Return: A pointer of a new alias after concatenation
 */
char *alias_value(char *argument, size_t index)
{
	char *ptr;

	ptr = malloc(_strlen(argument) + 3);
	if (!ptr)
		return (NULL);

	_strncpy(ptr, argument, index + 1);
	ptr[index + 1] = '\0';
	_strcat(ptr, "'");
	_strcat(ptr, argument + index + 1);
	_strcat(ptr, "'");

	return (ptr);
}


/**
  * set_alias - A function that set an alias
  * @argument: An alias argument
  * @arr: An array of aliases
  * @length: the index of '='
  *
  * Return: 1 on failure otherwise 0
  */
char set_alias(char *argument, char **arr, size_t length)
{
	int index;
	size_t weight;
	char *ptr;

	index = predefined_alias(argument, arr, length);
	if (index != -1)
	{
		free(arr[index]), arr[index] = alias_value(argument, length);
	}
	else
	{
		ptr = alias_value(argument, length);
		for (weight = 0; arr[weight]; weight++)
			;
		for (index = weight; index >= 0; index--)
		{
			arr[index + 1] = arr[index];
		}
		arr[0] = ptr;
	}
	return (0);
}

/**
  * get_aliasval - A function that returns an alias value
  * @command: An input command
  * @alias: An array of aliases
  *
  * Return: A pointer to str that contains alias value
  */
char *get_aliasval(char *command, char **alias)
{
	size_t length = _strlen(command);
	char **arr = alias;

	for (; *arr != NULL; arr++)
		if (!_strncmp(*arr, command, length) && (*arr)[length] == '=')
			return (&(*arr)[length + 1]);
	return (NULL);
}


/**
  * get_alias - A function that gets value of alias if it exist
  * @command: An array of command arguments
  * @num: Number of command argument
  * @arr: An array of aliases
  *
  * Return: A pointer to the new modified command
  */
char **get_alias(char **command, size_t num, char **arr)
{
	char *val = get_aliasval(command[0], arr), **tokens;
	char **ptr = NULL;
	size_t tok_argc, len, i, toki = 0, comi = 1;

	if (val)
		while (val)
		{
			toki = 0, comi = 1, val = _strdup(val);
			if (!val)
				return (NULL);
			if (val[0] == '\'')
				val[0] = ' ',	val[_strlen(val) - 1] = ' ';
			tokens = _strtok(val, " \n");
			if (!tokens)
				return (NULL);
			free(val);
			if (ptr)
			{
				command = ptr;
				num = tok_argc + num - 1;
			}
			for (tok_argc = 0; tokens[tok_argc]; tok_argc++)
				;
			ptr = malloc(sizeof(char *) * (tok_argc + num));
			if (!ptr)
				return (NULL);
			len = tok_argc + num - 1;
			for (i = 0; i < len; i++)
				if (toki < tok_argc)
					ptr[i] = _strdup(tokens[toki++]);
				else
					ptr[i] = _strdup(command[comi++]);
			ptr[len] = NULL, free_array(tokens);
			free_array(command);
			val = get_aliasval(ptr[0], arr);
		}
	else
		ptr = command;
	return (ptr);
}

/**
  * shell_alias - A function that defines alias
  * @argv: An array of shell arguments
  * @alias: An array of aliases
  *
  * Return: Exit status
  */
size_t shell_alias(char **argv, char **alias)
{
	size_t status = 0, i, length, argc;
	char *arg;

	if (!argv[1])
		display_aliases(alias);
	else
	{
		for (argc = 1; argv[argc]; argc++)
			;
		arg = malloc(sizeof(char) * argc);
		if (!arg)
			return (1);
		for (i = 1; argv[i]; i++)
		{
			length = new_def(argv[i]);
			if (length)
			{
				if (set_alias(argv[i], alias, length))
				{
					free(arg);
					return (1);
				}
				arg[i] = 0;
			}
			else
			{
				arg[i] = check_alias(argv[i], alias) ? 0 : 1;
				status = !arg[i] ? 1 : status;
			}
		}
		for (i = 1; argv[i]; i++)
			if (!new_def(argv[i]) && arg[i])
				if (display_alias(argv[i], alias))
				{
					free(arg);
					return (1);
				}
		free(arg);
	}
	return (status);
}
