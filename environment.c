#include "shell.h"

/**
 * make_environ - make shell environment from environment passed to main
 * @environ: environment passed to main
 *
 * Return: points to the new environment
 */

char **make_environ(char **environ)
{
	char **newenviron = NULL;
	size_t i;

	for (i = 0; environ[i] != NULL; i++)
		;
	newenvron = malloc(sizeof(char *) * (i + 1));
	if (newenviron == NULL)
	{
		perror("Fatal Error");
		exit(1);
	}
	for (i = 0; environ[i] != NULL; i++)
		newenviron[i] = _strdup(environ[i]);
	newenviron[i] = NULL;
	return (newenviron);
}

/**
 * free_environ - free the shell's environment
 * @environ: shell's environment
 *
 * Return: void
 */

void free_environ(char **environ)
{
	unsigned int i;

	for (i = 0; environ[i] != NULL; i++)
		free(environ[i]);
	free(environ);
}
