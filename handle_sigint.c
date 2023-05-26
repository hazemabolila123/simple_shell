#include "shell.h"

/**
 * handle_sigint - a function used to prind new line
 * with a prompt when ctrl + c is pressed
 * @sign: The number passed by the operating system when
 * new signal is generated
 */
void handle_sigint(int sign)
{
	(void) sign;
	write(STDOUT_FILENO, "\n$ ", 3);
}

