#include "shell.h"

/**
 * check_for_builtins - checks if the command is a builtin
 * @vars: variables
 *
 * Return: pointer to the function or NULL
 */
void (*check_for_builtins(vars_t *vars))(vars_t *vars)
{
	unsigned int i;
	builtins_t check[] = {
		{"exit", new_exit},
		{"env", _env},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{NULL, NULL}
	};

	for (i = 0; check[i].f != NULL; i++)
	{
		if (_strcmpr(vars->av[0], check[i].name) == 0)
			break;
	}
	if (check[i].f != NULL)
		check[i].f(vars);
	return (check[i].f);
}

/**
 * new_exit - exit program
 * @vars: variables
 *
 * Return: void
 */
void new_exit(vars_t *vars)
{
	int stat;

	if (_strcmpr(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
	{
		stat = _atoi(vars->av[1]);
		if (stat == -1)
		{
			vars->stat = 2;
			print_error(vars, ": Illegal number: ");
			_puts2(vars->av[1]);
			_puts2("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->stat = stat;
	}
	free(vars->buffer);
	free(vars->av);
	free(vars->commands);
	free_environ(vars->environ);
	exit(vars->stat);
}

/**
 * _environ - prints the current environment
 * @vars: struct of variables
 *
 * Return: void.
 */
void _environ(vars_t *vars)
{
	unsigned int i;

	for (i = 0; vars->environ[i]; i++)
	{
		_puts(vars->environ[i]);
		_puts("\n");
	}
	vars->stat = 0;
}

/**
 * new_setenv - create a new environment variable, or edit an existing variable
 * @vars: pointer to struct of variables
 *
 * Return: void
 */
void new_setenviron(vars_t *varz)
{
	char **key;
	char *var;

	if (varz->av[1] == NULL || varz->av[2] == NULL)
	{
		print_error(varz, ": Incorrect number of arguments\n");
		varz->stat = 2;
		return;
	}
	key = find_key(varz->environ, varz->av[1]);
	if (key == NULL)
		add_key(varz);
	else
	{
		var = add_value(varz->av[1], varz->av[2]);
		if (var == NULL)
		{
			print_error(varz, NULL);
			free(varz->buffer);
			free(varz->commands);
			free(varz->av);
			free_environ(varz->environ);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	varz->stat = 0;
}

/**
 * new_unsetenviron - remove an environment variable
 * @varz: pointer to a struct of variables
 *
 * Return: void
 */
void new_unsetenviron(vars_t *varz)
{
	char **key, **newenviron;

	unsigned int i, j;

	if (varz->av[1] == NULL)
	{
		print_error(varz, ": Incorrect number of arguments\n");
		varz->stat = 2;
		return;
	}
	key = find_key(varz->environ, varz->av[1]);
	if (key == NULL)
	{
		print_error(varz, ": No variable to unset");
		return;
	}
	for (i = 0; varz->environ[i] != NULL; i++)
		;
	newenviron = malloc(sizeof(char *) * i);
	if (newenviron == NULL)
	{
		print_error(varz, NULL);
		varz->stat = 127;
		new_exit(varz);
	}
	for (i = 0; varz->environ[i] != *key; i++)
		newenviron[i] = varz->environ[i];
	for (j = i + 1; varz->environ[j] != NULL; j++, i++)
		newenviron[i] = varz->environ[j];
	newenviron[i] = NULL;
	free(*key);
	free(varz->environ);
	varz->environ = newenviron;
	varz->stat = 0;
}
