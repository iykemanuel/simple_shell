#include <stdio.h>                                         #include <stdlib.h>
#include <sys/stat.h>                                      #include <sys/types.h>                                     #include <sys/wait.h>                                      #include <unistd.h>
#include <string.h>                                        #include <stdbool.h>
#include <errno.h>
/**
 * posh_exit - exit the shell
 */
void posh_exit(void)
{
	exit(0);
}

/**
 * posh_cd - Change working directory.
 * @args: pointer to passed arguments.
 */
void posh_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "posh: cd: missing argument\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("posh: cd");
		}
	}
}

/**
 * posh_help - Print the shell's help text.
 */
void posh_help(void);
{
	char *helptext =
		"Kash - the Primary Ordinary Shell. The following commands are built in:\n"
		" cd		Change the working directory.\n"
		" exit		Exit the shell.\n"
		" help		Print this help text.\n"
		;
	printf("%s", helptext);
}

/* Array of built in commands*/
	builtin builtins[] = {
	{
		"help", posh_help
	},
	{
		"exit", posh_exit
	},
	{
		"cd", posh_cd
	},
};

/**
 * posh_num_builtins - Returns the number of registered commands.
 * Return: returns sizeof().
 */
int posh_num_builtins(void)
{
	return (sizeof(builtins) / sizeof(builtin));
}

/**
 * posh_exec - process/command launcher.
 * @args: list of passed arguments.
 */
void posh_exec(char **args)
{
	for (int i = 0; i < posh_num_builtins(); i++)
	{
		if (strcmp(args[0], builtins[i].name) == 0)
		{
			builtins[i].func(args);
			return;
		}
	}

	pid_t child_pid = fork();

	if (child_pid == 0)
	{
		execvp(args[0], args);
		perror("posh");
		exit(1);
	}
	else if (child_pid > 0)
	{
		int status;
	do {
		waitpid(child_pid, &status, WUNTRACED);
		}
	while
	(!WIFEXITED(status) && !WIFSIGNALED(status));
	else
	{
		perror("posh");
	}
	}
}

/**
 * posh_split_line - input parser, tokenize  a string
 * @line: string - points to user input
 * Return: returns a NULL.
 */
char **posh_split_line(char *line)
{
	int length = 0;
	int capacity = 16;

	char **tokens = malloc(capacity * sizeof(char *));

	if (!tokens)
	{
		perror("posh");
		exit(1);
	}

	char *delimeters = "\t\r\n";
	char *token = strtok(line, delimeters);

	while (token != NULL)
	{
		tokens[length] = token;
		length++;

	if (length >= capacity)
	{
		capacity = (int) (capacity * 1.5);
		tokens = realloc(tokens, capacity * sizeof(char *));

	if (!tokens)
	{
		perror("kash");
		exit(1);
	}
	}

	token = strtok(NULL, delimeters);

	}

	tokens[length] = NULL;
	return (tokens);

/**
 * posh_read_line - Reads a singke line of input from stdin
 * Return: Returns a string pointer.
 */
char *posh_read_line(void)
{
	char *line = NULL;
	size_t buflen = 0;

	errno = 0;

	ssize_t strlen = getline(&line, &buflen, stdin);

	if (strlen < 0)
	{
	if (errno)
	{
		perror("posh");
	}
	exit(1);
	}
	return (line);
}

