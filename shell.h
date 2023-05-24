#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>


/**
 * struct variables - variables
 * @av: command line arguments
 * @buffer: buffer of command
 * @env: environment variables
 * @count: count of commands entered
 * @argv: arguments at opening of shell
 * @status: exit status
 * @commands: double pointer to commands
 */
typedef struct variables
{
	char **av;
	char *buffer;
	char **environ;
	size_t count;
	char **argv;
	int stat;
	char **commands;
} vars_t;

/**
 * struct builtins - struct for the builtin functions
 * @name: name of builtin command
 * @f: function for corresponding builtin
 */
typedef struct builtins
{
	char *name;
	void (*f)(vars_t *);
} builtins_t;

char **make_environ(char **environ);
void free_environ(char **environ);

ssize_t _puts(char *strg);
char *_strdup(char *strtodup);
int _strcmpr(char *strcmp1, char *strcmp2);
char *_strcat(char *strc1, char *strc2);
unsigned int _strlength(char *strg);

char **tokenize(char *buffer, char *delimiter);
char **_realloc(char **ptr, size_t *size);
char *new_strtok(char *strg, const char *delim);

void (*check_for_builtins(vars_t *vars))(vars_t *vars);
void new_exit(vars_t *varz);
void _environ(vars_t *varz);
void new_setenviron(vars_t *varz);
void new_unsetenviron(vars_t *varz);

void add_key(vars_t *varz);
char **find_key(char **environ, char *key);
char *add_value(char *key, char *value);
int _atoi(char *strg);

void check_for_path(vars_t *varz);
int path_execute(char *command, vars_t *varz);
char *find_path(char **environ);
int execute_cwd(vars_t *varz);
int check_for_dir(char *strg);

void print_error(vars_t *varz, char *message);
void _puts2(char *strg);
char *_uitoa(unsigned int count);

#endif /* _SHELL_H_ */
