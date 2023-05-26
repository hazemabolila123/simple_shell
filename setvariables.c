#include "shell.h"

/**
 * create_modifyvar - A function that set a create a modified var
 *
 * Return: 1 if it fails otherwise 0
 */
char create_modifyvar(void)
{
	size_t i;
	char *variables = malloc(_strlen("DONOT_EDIT=") + 1000);

	if (!variables)
		return (1);
	_strcpy(variables, "DONOT_EDIT=");
	for (i = 0; environ[i]; i++)
		;
	environ[i] = variables;
	environ[i + 1] = NULL;
	return (0);
}


/**
 * append2modifyvar - A function taht append a name to modified var
 * @name: The name to be appended
 */
void append2modifyvar(char *name)
{
	_strcat(_strcat(my_getenv("DONOT_EDIT"), name), ":");
}


/**
 * check_appended - A function that checks if the var name is
 * modified before
 * @name: The name to be checked
 *
 * Return: 0 if it doesnot appenend otherwise 1
 */
char check_appended(char *name)
{
	char **variables = _strtok(my_getenv("DONOT_EDIT"), ":");
	size_t i;

	for (i = 0; variables && variables[i]; i++)
	{
		if (!_strncmp(variables[i], name, _strlen(name)))
		{
			free_array(variables);
			return (1);
		}
	}
	free_array(variables);
	return (0);
}

