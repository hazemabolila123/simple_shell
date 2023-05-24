#include "shell.h"

/**
  * my_getenv - A function that gets an evironment variable
  * @varname: variable name
  *
  * Return: NULL if fails otherwise a pointer to str contains variable value
  */
char *my_getenv(char *varname)
{
	size_t len = _strlen(varname);
	char **envir;

	for (envir = environ; *envir != NULL; envir++)
		if (!_strncmp(*envir, varname, len) && (*envir)[len] == '=')
			return (&(*envir)[len + 1]);
	return (NULL);
}

/**
 * create_path - A function that find the path of the command
 * @command: Command
 *
 * Return: NULL if it fails otherwise  path of the command
 */
char *create_path(char *command)
{
	char **path_arr = NULL, *path, *file_path;
	int command_len, directory_len, i = 0;
	struct stat st;

	path = my_getenv("PATH");
	if (path && path[0] != '\0')
	{
		path_arr = _strtok(path, ":");
		command_len = _strlen(command);
		while (path_arr[i])
		{
			directory_len = _strlen(path_arr[i]);
			if (!stat(command, &st))
			{
				free_array(path_arr);
				return (_strdup(command));
			}
			else
			{
				file_path = malloc(command_len + directory_len + 2);
				_strcpy(file_path, path_arr[i]);
				_strcat(file_path, "/");
				_strcat(file_path, command);
				_strcat(file_path, "\0");
				if (stat(file_path, &st) == 0)
				{
					free_array(path_arr);
					return (file_path);
				}
				free(file_path);
			}
			i++;
		}
	}
	else if (command[0] == '/' && !stat(command, &st))
		return (_strdup(command));

	free_array(path_arr);
	return (NULL);
}
