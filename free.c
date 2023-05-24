#include "shell.h"
/**
  * free_array - A fuction that frees Array of strings
  * @str_arr: Array of strings
  */
void free_array(char **str_arr)
{
	int i = 0;

	while (str_arr && str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
}

/**
 * free_variable - A function that free a variable
 */
void free_variable(void)
{
	char **variables_arr = _strtok(my_getenv("DONOT_EDIT"), ":"), *args[2];
	size_t i;

	for (i = 0; variables_arr && variables_arr[i]; i++)
	{
		args[1] = variables_arr[i];
		my_unsetenv(args, 0, NULL);
	}
	args[1] = "DONOT_EDIT";
	my_unsetenv(args, 0, NULL);
	free_array(variables_arr);
}

/**
 * remove_comments - A function that handels the comments passed
 * to the command line
 * @commands_arr: Array of comments to check if any of them
 * is equql to #
 */
void remove_comments(char **commands_arr)
{
	size_t i, j;

	for (i = 0; commands_arr && commands_arr[i]; i++)
	{
		if (commands_arr[i][0] == '#')
		{
			for (j = i; commands_arr[j]; j++)
			{
				free(commands_arr[j]);
			}
			commands_arr[i] = NULL;

			return;
		}
	}
}
