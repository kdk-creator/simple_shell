#include "shell.h"

/**
 * add_keys - create a new environment variable
 * @varz: pointer to struct of variables
 *
 * Return: void
 */
void add_keys(vars_t *varz)
{
	unsigned int x;
	char **newenviron;

	for (x = 0; varz->environ[x] != NULL; x++)
		;
	newenviron = malloc(sizeof(char *) * (x + 2));
	if (newenviron == NULL)
	{
		print_error(varz, NULL);
		varz->stat = 127;
		new_exit(varz);
	}
	for (x = 0; varz->environ[x] != NULL; x++)
		newenviron[x] = varz->environ[x];
	newenviron[x] = add_value(varz->av[1], varz->av[2]);
	if (newenviron[x] == NULL)
	{
		print_error(varz, NULL);
		free(varz->buffer);
		free(varz->commands);
		free(varz->av);
		free_environ(varz->environ);
		free(newenviron);
		exit(127);
	}
	newenviron[x + 1] = NULL;
	free(varz->environ);
	varz->environ = newenviron;
}

/**
 * find_key - finds an environment variable
 * @environ: array of environment variables
 * @key: environment variable to find
 *
 * Return: pointer to address of the environment variable
 */
char **find_key(char **environ, char *key)
{
	unsigned int i, j, length;

	length = strlen(key);
	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; j < length; j++)
			if (key[j] != environ[i][j])
				break;
		if (j == length && environ[i][j] == '=')
			return (&environ[i]);
	}
	return (NULL);
}

/**
 * add_value - create a new environment variable string
 * @key: variable name
 * @value: variable value
 *
 * Return: pointer to the new string;
 */
char *add_value(char *key, char *value)
{
	unsigned int firstlen, seclen, i, j;
	char *new;

	firstlen = strlen(key);
	seclen = strlen(value);
	new = malloc(sizeof(char) * (firstlen + seclen + 2));
	if (new == NULL)
		return (NULL);
	for (i = 0; key[i] != '\0'; i++)
		new[i] = key[i];
	new[i] = '=';
	for (j = 0; value[j] != '\0'; j++)
		new[i + 1 + j] = value[j];
	new[i + 1 + j] = '\0';
	return (new);
}

/**
 * _atoi - converts a string into an integer
 * @strg: string to convert
 *
 * Return: the integer value, -1 if an error occurs
 */
int _atoi(char *strg)
{
	unsigned int x, digits;
	int num = 0, num_test;

	num_test = INT_MAX;
	for (digits = 0; num_test != 0; digits++)
		num_test /= 10;
	for (x = 0; strg[x] != '\0' && x < digits; x++)
	{
		num *= 10;
		if (strg[x] < '0' || strg[x] > '9')
			return (-1);
		if ((x == digits - 1) && (strg[x] - '0' > INT_MAX % 10))
			return (-1);
		num += strg[x] - '0';
		if ((x == digits - 2) && (strg[x + 1] != '\0') && (num > INT_MAX / 10))
			return (-1);
	}
	if (x > digits)
		return (-1);
	return (num);
}
