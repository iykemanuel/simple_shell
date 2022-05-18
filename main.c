#include "shell.h"
/**
 * main - Entry point of program to start the shell
 * Return: Always 0.
 */
int main(void)
{
	while (true)
	{
		printf("$ ");
		char *line = posh_read_line();
		char **tokens = posh_split_line(line);

		if (tokens[0] != NULL)
		{
			posh_exec(tokens);
		}
		free(tokens);
		free(line);
	}
}
