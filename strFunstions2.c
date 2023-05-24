#include "shell.h"

/**
 * *_strcpy - A function that copies a  string
 * @src: Source parameter
 * @dest: Destination string
 *
 * Return: Copied string
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}


/**
  * _strncpy - A function thatcopies n chars from one string to another
  * @dest: Destination string
  * @src: Source parameter
  * @n: Number of chars
  *
  * Return: Copied string
  */
char *_strncpy(char *dest, char *src, int n)
{
	char *destcpy = dest;

	while (n--)
	{
		if (*src != '\0')
		{
			*destcpy = *src;
			src++;
		}
		else
		{
			*destcpy = '\0';
		}
		destcpy++;
	}
	return (dest);
}


/**
  * _atoi - A function that converta str to int
  * @str: str to be converted
  * @status: pointer to the status variable
  *
  * Return: intger
  */
int _atoi(char *str, char *status)
{
	char sign = 1;
	unsigned int num = 0;

	while (*str != '\0')
	{
		if (*str == '-')
		{
			sign *= -1;
		}
		else if (*str >= '0' && *str <= '9')
		{
			num = num * 10 + *str - '0';
		}
		else if (*str != '+')
		{
			*status = -1;
			return (0);
		}
		str++;
	}
	*status = 0;
	return (sign * num);
}


/**
 * my_itoa - A function that converts integer to ascii
 * @num: the integer will be converted
 * @strout: String holds the same value of the number
 * @base: base
 *
 * Return: A pointer to the first occurunce in that string
 */

char *my_itoa(long int num, char *strout, int base)
{
	int i = 0, digit, sign = 0;
	unsigned long int cpnum;

	if (num >= 0)
		cpnum = num;
	else
	{
		cpnum = -1 * num;
		sign = 1;
	}

	if (cpnum == 0)
	{
		strout[i++] = '0';
		strout[i] = '\0';
		return (strout);
	}

	while (cpnum != 0)
	{
		digit = cpnum % base;
		strout[i++] = (digit > 9) ? ('a' + digit - 10) : ('0' + digit);
		cpnum /=  base;
	}

	if (sign == 1)
	{
		strout[i] = '-';
		i++;
	}

	strout[i] = '\0';

	_strrev(strout);
	return (strout);
}
