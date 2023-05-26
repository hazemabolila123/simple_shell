#include "shell.h"

/**
  * shell_inputs- A function that gets shell input
  * @ptr: A pointer to the shell input
  * @n: The size of input buffer
  * @argv: An array of shell arguments
  *
  * Return: Int
  */
size_t shell_inputs(char **ptr, size_t *n, char **argv)
{
	ssize_t commands;

	if (argv[1])
	{
		int file;

		*ptr = malloc(1000);
		if (!*ptr)
			return (1);
		file = open(argv[1], O_RDONLY);
		if (file == -1)
		{
			errors_Handling(11, 0, argv[1], argv[0]);
			return (1);
		}
		commands = read(file, *ptr, 1000);
		if (commands == -1)
			return (1);
		(*ptr)[commands] = '\0';
		handle_newline(ptr);
		close(file);
	}
	else
	{
		commands = getline(ptr, n, stdin);
		if (commands == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			return (1);
		}
		(*ptr)[commands] = '\0';
	}
	return (0);
}

/**
 * handle_commands - A function that handles a command for execution
 * @arr: An array of shell arguments
 * @sargc: The index of delim after command
 * @cargc: The number of arguments
 * @alias_arr: An array of aliases arguments
 * @status: Exit status
 *
 * Return: A command
 */
char **handle_commands(char **arr, size_t sargc, size_t cargc,
		char **alias_arr, size_t *status)
{
	size_t i;
	char **ptr = malloc(sizeof(char *) * (cargc + 1));

	if (!ptr)
		return (NULL);

	for (i = 0; i < cargc; i++)
		ptr[i] = _strdup(arr[sargc - (cargc) + i]);

	ptr[i] = NULL;
	ptr = get_alias(ptr, cargc, alias_arr);

	if (!ptr)
		return (NULL);

	ptr = dollarsign(ptr, cargc, status);

	if (!ptr)
		return (NULL);

	return (ptr);
}

/**
  * main_helper - A function that handlea the shell input
  * @arr: An array of shell arguments
  * @count: Count of shell input
  * @status: Exit state
  * @aliases: An array of aliases
  * @env: An array of strings
  * @name: Name of shell program
  *
  * Return: 1 on failure, otherwise 0
  */
char main_helper(char **arr, unsigned long *count, size_t *status,
		char **aliases,  char **env, char *name)
{
	size_t sargc = 0, command_argc, exec_return;
	char **command, last_state = 1, execute_case = 1, is_and = 1;

	if (concat_seperator(arr) != -1)
		errors_Handling(6 + concat_seperator(arr), *count, NULL, name), (*count)--;
	else
		while (arr && arr[sargc])
		{
			for (command_argc = 0; arr[sargc] && arr[sargc][0] != ';'
					&& arr[sargc][0] != '&' && arr[sargc][0] != '|'; sargc++)
				command_argc++;
			if (command_argc)
			{
				command = handle_commands(arr, sargc, command_argc, aliases, status);
				if (!command)
					return (1);
				if (execute_case)
				{
					exec_return = execute(command, *count, aliases, env, name);
					if (exec_return != 1000)
						*status = exec_return;
					else
					{
						free_array(command);
						return (1);
					}
					last_state = (!*status) ? 1 : 0;
				}
				else
					last_state = (is_and) ? 0 : 1;
				if (arr[sargc] && arr[sargc][0] == '&')
					is_and = 1, execute_case = last_state;
				else if (arr[sargc] && arr[sargc][0] == '|')
					is_and = 0, execute_case = (last_state) ? 0 : 1;
				free_array(command);
			}
			if (arr[sargc])
				sargc++;
		}
	return (0);
}

/**
  * main - An entry point of the shell program
  * @argc: Argument count
  * @argv: Argument vector
  * @env: Environment variables
  *
  * Return: 0 on success
  */
int main(int argc, char *argv[], char *env[])
{
	size_t n = 0, status = 0, eof = 0;
	char *ptr = NULL, **sargv = NULL;
	char  *prompt = "$ ", *delimiter = " \n";
	unsigned long count = 0;
	char **alias_arr = malloc(sizeof(char *) * 1024);

	alias_arr[0] = NULL, signal(SIGINT, handle_sigint);
	do {
		if (isatty(STDIN_FILENO) && argc == 1)
			write(STDOUT_FILENO, prompt, 2);
		eof = shell_inputs(&ptr, &n, argv);
		if (eof)
		{
			free_variable(), free(ptr);
			free_array(alias_arr);
			return ((argv[1]) ? 2 : status);
		}
		count++, sargv = _strtok(ptr, delimiter);
		remove_comments(sargv);
		if (main_helper(sargv, &count, &status, alias_arr, env, argv[0]))
		{
			free_variable(), free_array(sargv);
			free(ptr), free_array(alias_arr);
			return (status);
		}
		free_array(sargv);
		if (status >= 256)
		{
			free_variable(), free(ptr);
			free_array(alias_arr);
			return (status - 256);
		}
	} while (argc == 1);
	free(ptr), free_array(alias_arr);
	free_variable();
	return (status);
}

