#include "shell.h"

/**
 * exec - Executes a command.
 * @cmd: Points to the tokenized command
 * @name: The name of the shell.
 * @env: The pointer to the enviromental variables.
 * @cycles: Number of executed cicles.
 * Return: Nothing.
 */
void exec(char **cmd, char *name, char **env, int cycles)
{
	char **pathways = NULL, *full_path = NULL;
	struct stat st;
	unsigned int i = 0;

	if (_strcmp(cmd[0], "env") != 0)
		print_env(env);
	if (stat(cmd[0], &st) == 0)
	{
		if (execve(cmd[0], cmd, env) < 0)
		{
			perror(name);
			free_exit(cmd);
		}
	}
	else
	{
		pathways = _getPATH(env);
		while (pathways[i])
		{
			full_path = _strcat(pathways[i], cmd[0]);
			i++;
			if (stat(full_path, &st) == 0)
			{
				if (execve(full_path, cmd, env) < 0)
				{
					perror(name);
					free_all(pathways);
					free_exit(cmd);
				}
				return;
			}
		}
		msgerror(name, cycles, cmd);
		free_all(pathways);
	}
}


/**
 * print_env - Prints all enviromental variables.
 * @env: Pointer to enviromental variables.
 * Return: Nothing.
 */
void print_env(char **env)
{
	size_t i = 0, len = 0;

	while (env[i])
	{
		len = _strlen(env[i]);
		write(STDOUT_FILENO, env[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}


/**
 * _getPATH - Gets the full value from enviromental variable PATH.
 * @env: The pointer to enviromental variables.
 * Return: All tokenized pathways for commands.
 */
char **_getPATH(char **env)
{
	char *pathvalue = NULL, **pathways = NULL;
	unsigned int i = 0;

	pathvalue = strtok(env[i], "=");
	while (env[i])
	{
		if (_strcmp(pathvalue, "PATH"))
		{
			pathvalue = strtok(NULL, "\n");
			pathways = tokenization(pathvalue, ":");
			return (pathways);
		}
		i++;
		pathvalue = strtok(env[i], "=");
	}
	return (NULL);
}


/**
 * msgerror - Prints error when message not found.
 * @name: The name of the shell.
 * @cycles: Number of cycles.
 * @cmd: Points to tokenized command.
 * Return: Nothing.
 */
void msgerror(char *name, int cycles, char **cmd)
{
	char p;

	p = cycles + '0';
	write(STDOUT_FILENO, name, _strlen(name));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, &p, 1);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, cmd[0], _strlen(cmd[0]));
	write(STDOUT_FILENO, ": not found\n", 12);
}
