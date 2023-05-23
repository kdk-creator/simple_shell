#include "shell.h"

/**
 * check_match - checks if a character matches any in a string
 * @c: character to check
 * @str: string to check
 *
 * Return: 1 if match, 0 if not
 */

unsigned int check_match(char c, const char *str)
{
	unsigned int f;

	for (f = 0; str[f] != '\0'; f++)
	{
		if (c == str[f])
			return (1);
	}
	return (0);
}

/**
 * new_strtok - custom strtok
 * @str: string to tokenize
 * @delim: delimiter to tokenize against
 *
 * Return: pointer to the next token or NULL
 */
char *new_strtok(char *str, const char *delim)
{
	static char *token_start;
	static char *next_token;
	unsigned int e;

	if (str != NULL)
		next_token = str;
	token_start = next_token;
	if (token_start == NULL)
		return (NULL);
	for (e = 0; next_token[e] != '\0'; e++)
	{
		if (check_match(next_token[e], delim) == 0)
			break;
	}
	if (next_token[e] == '\0' || next_token[e] == '#')
	{
		next_token = NULL;
		return (NULL);
	}
	token_start = next_token + e;
	next_token = token_start;
	for (e = 0; next_token[e] != '\0'; e++)
	{
		if (check_match(next_token[e], delim) == 1)
			break;
	}
	if (next_tokens[e] == '\0')
		next_token = NULL;
	else
	{
		next_token[e] = '\0';
		next_token = next_token + e + 1;
		if (*next_token == '\0')
			next_token = NULL;
	}
	return (token_start);
}
