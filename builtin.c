#include "shell.h"

/**
 * execute_builtin - A function that use a struct to define
 * builtin commands and call its functions
 * @argv: Argument vector
 * @count: Count of shell input
 * @alias: Array of aliases
 * @name: Name of the shell program
 *
 * Return: -1 if it fails otherwise pointer to the function
 * to be executed
 */
ssize_t execute_builtin(char **argv, unsigned long count,
		char **alias, char *name)
{
	builtin_t commands[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"cd", my_cd},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
	};
	int index;

	if (!_strncmp("env", argv[0], 3) && argv[1])
		return (-1);
	else if (!_strncmp("alias", argv[0], 5))
		return (shell_alias(argv, alias));
	for (index = 0; index < 5; index++)
	{
		if (!_strncmp(commands[index].command, argv[0], 8))
		{
			return (commands[index].fp(argv, count, name));
		}
	}
	return (-1);
}
