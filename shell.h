#ifndef SHELL_H
#define SHELL_H
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

/**
 * struct builtin - Associates a command line with a handler function.
 * @name: string - (malloc'ed string)
 * @func: function pointer
 */
typedef struct builtin
{
	char *name;
	void (*func)(char **args);
} builtin;

void posh_exit(void);
void posh_cd(char **args);
void posh_help(void);
int posh_num_builtins(void);
void posh_exec(char **args);
char **posh_split_line(char *line);
char *posh_read_line(void);
int main(void);

#endif
