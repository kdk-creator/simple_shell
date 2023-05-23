#include "shell.h"

/**
 * tokenize - tokenizes a buffer with a delimiter
 * @buffer: buffer to tokenize
 * @delimiter: delimiter to tokenize along
 * Return: pointer to an array of pointer to the tokens
 */
char **tokenize(char *buffer, char *delimiter)
{
	char **tokens = NULL;
	size_t a = 0, ncount = 10;

	if (buffer == NULL)
		return (NULL);
	tokens = malloc(sizeof(char *) *ncount);

	if (tokens == NULL)
	{
		 perror("Fatal Error");
		 return (NULL);
	}

	while ((tokens[a] = new_strtlk(buffer, delimiter)) != NULL)
	{
		a++;
		if (a == ncount)
		{
			tokens = _realloc(tokens, &ncount);
			if (tokens == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		buffer = NULL;
	}
	return (tokens);
}
