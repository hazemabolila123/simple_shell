#include "shell.h"

/**
 * my_exit - A function that exit the shell
 * @arr: Array of commands
 * @count: Count of shell input
 * @name: Name of shell program
 *
 * Return: Exit status
 */
size_t my_exit(char **arr, unsigned long count, char *name)
{
	if (arr[1])
	{
		char argument_weight;
		int weight = _atoi(arr[1], &argument_weight);

		if (!argument_weight && weight >= 0)
			return (256 + (unsigned char)weight);

		errors_Handling(0, count, arr[1], name);
	}
	else
		return (1000);

	return (2);
}

/**
 * my_env - A function that prints an environment
 * @arr: Array of commands
 * @count: Count of shell input
 * @name: Name of shell program
 *
 * Return: Exit status
 */
size_t my_env(char **arr, unsigned long count, char *name)
{
	int index;

	(void) arr, (void) count, (void) name;
	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
		write(STDOUT_FILENO, "\n", 1);
	}

	return (0);
}

/**
 * my_setenv - A function that sets an environment variable
 * @arr: Array of commands
 * @count: Count of shell input
 * @name: Name of shell program
 *
 * Return: Exit status
 */
size_t my_setenv(char **arr, unsigned long count, char *name)
{
	size_t weight, i;
	int j, len;
	char *new_ptr, flag = 1;

	if (!arr[1] || !arr[2])
	{
		errors_Handling(2, count, NULL, name);
		return (2);
	}
	for (i = 0; arr[1][i]; i++)
		if (arr[1][i] == '=')
		{
			errors_Handling(3, count, arr[1], name);
			return (2);
		}
	new_ptr = malloc(_strlen(arr[1]) + _strlen(arr[2]) + 2);
	if (!new_ptr)
		return (2);

	_strcpy(new_ptr, arr[1]), _strcat(new_ptr, "=");
	_strcat(new_ptr, arr[2]), len = _strlen(arr[1]) + 1;
	if (!my_getenv("DONOT_EDIT") && create_modifyvar())
		return (2);
	if (!check_appended(arr[1]))
		append2modifyvar(arr[1]), flag = 0;
	if (my_getenv(arr[1]))
		for (j = 0; environ[j]; j++)
			if (_strncmp(new_ptr, environ[j], len) == 0)
			{
				if (flag)
					free(environ[j]);
				environ[j] = new_ptr;
				return (0);
			}
	for (weight = 0; environ[weight]; weight++)
		;
	environ[weight] = new_ptr, environ[weight + 1] = NULL;
	return (0);
}

/**
 * my_unsetenv - A function that deletes an environment variable
 * @arr: Array of commands
 * @count: Count of shell input
 * @name: Name of shell program
 *
 * Return: Exit status
 */
size_t my_unsetenv(char **arr, unsigned long count, char *name)
{
	char *ptr;
	size_t weight, i;
	int j, k, length;

	if (!arr[1])
	{
		errors_Handling(4, count, NULL, name);
		return (2);
	}
	for (i = 0; arr[1][i]; i++)
		if (arr[1][i] == '=')
		{
			errors_Handling(5, count, arr[1], name);
			return (2);
		}
	if (!my_getenv(arr[1]))
		return (0);
	ptr = malloc(_strlen(arr[1]) + 2);
	if (!ptr)
		return (2);
	_strcpy(ptr, arr[1]), _strcat(ptr, "=");
	length = _strlen(arr[1]) + 1;
	for (weight = 0; environ[weight]; weight++)
		;
	for (j = 0, k = 0; environ[j]; j++)
	{
		if (_strncmp(ptr, environ[j], weight) == 0)
		{
			if (!_strncmp("DONOT_EDIT", arr[1], length - 1) ||
					check_appended(arr[1]))
			{
				free(environ[j]);
			}
			continue;
		}
		environ[k] = environ[j], k++;
	}
	environ[weight - 1] = NULL, free(ptr);

	return (0);
}


/**
 * my_cd - A function that changes a directory
 * @arr: Array of commands
 * @count: Count of shell input
 * @name: Name of shell program
 *
 * Return: Exit status
 */
size_t my_cd(char **arr, unsigned long count, char *name)
{
	char *arguments[3];
	char current_directory[PATH_MAX], prev_directory[PATH_MAX];

	if (arr[1] == NULL && my_getenv("HOME"))
	{
		getcwd(current_directory, PATH_MAX);
		arguments[0] = "setenv", arguments[1] = "OLDPWD";
		arguments[2] = current_directory, my_setenv(arguments, count, name);
		chdir(my_getenv("HOME"));
	}
	else if (arr[1] && _strncmp(arr[1], "-", 1) == 0)
	{
		if (my_getenv("OLDPWD"))
		{
			getcwd(prev_directory, PATH_MAX);
			chdir(my_getenv("OLDPWD"));
			arguments[0] = "setenv", arguments[1] = "OLDPWD";
			arguments[2] = prev_directory, my_setenv(arguments, count, name);
		}
		getcwd(current_directory, PATH_MAX);
		write(STDOUT_FILENO, current_directory, _strlen(current_directory));
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (arr[1])
	{
		getcwd(current_directory, PATH_MAX);
		arguments[0] = "setenv", arguments[1] = "OLDPWD";
		arguments[2] = current_directory;
		my_setenv(arguments, count, name);
		if (chdir(arr[1]) != 0)
		{
			errors_Handling(1, count, arr[1], name);
			return (2);
		}
	}
	getcwd(current_directory, PATH_MAX);
	arguments[0] = "setenv", arguments[1] = "PWD";
	arguments[2] = current_directory;
	my_setenv(arguments, count, name);
	return (0);
}
