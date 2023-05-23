#include "shell.h"

/**
 * _realloc - reallocates a pointer to double the space
 * @ptr: pointer to the old array
 * @size: pointer to number of elements in the old array
 * Return: pointer to the new array
 */
char **_realloc(char **ptr, size_t *size)
{
	char **new;
	size_t b;

	new = malloc(sizeof(char *) * ((*size + 10)));
	if (new == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (b = 0; b < (*size); b++)
	{
		new[b] = ptr[b];
	}
	*size += 10;
	free(ptr);
	return (new);
}

