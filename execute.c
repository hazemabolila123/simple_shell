#include "shell.h"

/**
 * execute - A function that excute the program
 * @argv: Array of shell commands
 * @count: Count of shell inputs
 * @arr: Array of aliasses parameters
 * @env: Array of environment strings
 * @name: Name of shell program
 *
 * Return: Exit status
 */
size_t execute(char **argv, unsigned long count, char **arr, char **env
		, char *name)
{
	pid_t pid = 0, wait_status;
	char *command = NULL, *real_command = NULL;
	ssize_t builtin_status;
	int status, exit_status;

	builtin_status = execute_builtin(argv, count, arr, name);
	if (builtin_status != -1)
		return (builtin_status);
	command = argv[0];
	real_command = create_path(command);
	if (real_command)
		pid = fork();

	if (pid == -1)
		exit(1);

	else if (pid == 0)
	{
		if (!real_command)
		{
			errors_Handling(10, count, argv[0], name);
			exit_status = 127;
		}
		else
			execve(real_command, argv, env);
	}
	else
	{
		do {
			wait_status = wait(&status);
			if (wait_status == -1)
				exit(1);
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	free(real_command);

	return (exit_status);
}

