#include "shell.h"

/**
 * sep_cases - A function that prints error detects by the separator
 * @error_number: A number to detect which case will be displayed
 * @error_massage: Error message
 */
void sep_cases(char error_number, char **error_massage)
{
	switch (error_number)
	{
		case 6:
			*error_massage = ": Syntax error: \";\" unexpected"
			;
			break;
		case 7:
			*error_massage = malloc(sizeof(char) * 32);
			_strcpy(*error_massage, ": Syntax error: \";")
			;
			_strcat(*error_massage, ";\" unexpected")
			;
			break;
		case 8:
			*error_massage = ": Syntax error: \"&&\" unexpected";
			break;
		case 9:
			*error_massage = ": Syntax error: \"||\" unexpected";
	}
}


/**
 * err_cases - A function that prints an error
 * @error_number: A number to detect which case will be displayed
 * @error_massage: Error message
 * @massage_len: Length of the message
 */
void err_cases(char error_number, char **error_massage, size_t *massage_len)
{
	if (error_number >= 6 && error_number <= 9)
		sep_cases(error_number, error_massage);
	switch (error_number)
	{
		case 0:
			*error_massage = ": exit: Illegal number: ";
			break;
		case 1:
			*error_massage = ": cd: can't cd to ";
			break;
		case 2:
			*error_massage = ": setenv: too few arguments";
			break;
		case 3:
			*error_massage = ": setenv: Invalid argument: ";
			break;
		case 4:
			*error_massage = ": unsetenv: too few arguments";
			break;
		case 5:
			*error_massage = ": unsetenv: Invalid argument: ";
			break;
		case 10:
			*error_massage = ": not found";
			break;
		case 11:
			*error_massage = ": cannot open ";
	}
	*massage_len = _strlen(*error_massage);
}

/**
 * errors_Handling - A function that used to prints the
 * error message to STDERR
 * @error_number: A number to detect which case will be displayed
 * @count: Count of shell input
 * @firstarg: First argument
 * @name: Name of shell program
 */
void errors_Handling(char error_number, unsigned int count,
		char *firstarg, char *name)
{
	char *error_massage, *shell_error, buffer[100];
	size_t massage_len = 0, length = 0;

	err_cases(error_number, &error_massage, &massage_len);
	length = massage_len + _strlen(name)
		       + _strlen(my_itoa(count, buffer, 10))
		       + _strlen(firstarg) + 3;
	length += (error_number == 10) ? 2 : (error_number == 11) ? 14 : 0;
	shell_error = malloc(length + 1);
	_strcpy(shell_error, name), _strcat(shell_error, ": ");
	_strcat(shell_error, buffer);
	if (error_number == 10)
	{
		_strcat(shell_error, ": ");
		_strcat(shell_error, firstarg);
	}
	_strcat(shell_error, error_massage);
	if (firstarg && error_number != 10)
		_strcat(shell_error, firstarg);
	if (error_number == 11)
		_strcat(shell_error, ": No such file");
	_strcat(shell_error, "\n");
	write(STDERR_FILENO, shell_error, length), free(shell_error);
	if (error_number == 7)
		free(error_massage);
}
