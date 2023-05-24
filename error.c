#include "shell.h"

/**
 * print_error - prints error messages to standard error
 * @vars: pointer to struct of variables
 * @message: message to be  printed out
 *
 * Return: void
 */
void print_error(vars_t *vars, char *message)
{
	char *count;

	_puts2(vars->argv[0]);
	_puts2(": ");
	count = _uitoa(vars->count);
	_puts2(count);
	free(count);
	_puts2(": ");
	_puts2(vars->av[0]);
	if (message)
	{
		_puts2(message);
	}
	else
		perror("");
}

/**
 * _puts2 - prints a string to standard error
 * @strg: string to print
 *
 * Return: void
 */
void _puts2(char *strg)
{
	ssize_t number, length;

	number = _strlen(str);
	length = write(STDERR_FILENO, str, num);
	if (length != number)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
 * _uitoa - converts an unsigned int to a string
 * @counts: unsigned int to convert
 *
 * Return: pointer to the converted string
 */
char *_uitoa(unsigned int counts)
{
	char *numstrg;
	unsigned int tmp, dgt;

	tmp = counts;
	for (dgt = 0; tmp != 0; dgt++)
		tmp /= 10;
	numstr = malloc(sizeof(char) * (dgt + 1));
	if (numstrg == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	numstrg[dgt] = '\0';
	for (--dgt; counts; --dgt)
	{
		numstrg[dgt] = (counts % 10) + '0';
		counts /= 10;
	}
	return (numstrg);
}
