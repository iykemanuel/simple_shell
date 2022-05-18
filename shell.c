#include "shell.h"

/**
 * main - Starts/runs our shell.
 * @ac: Counts  number of input arguments.
 * @av: Pointer to array of input arguments.
 * @env: The pointer to array of enviromental variables.
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	char *buffer = NULL, **cmd = NULL;
	size_t buf_size = 0;
	ssize_t chars_read = 0;
	int cycles = 0;
	(void)ac;

	while (1)
	{
		cycles++;
		prompt();
		signal(SIGINT, handler);
		chars_read = getline(&buffer, &buf_size, stdin);
		if (chars_read == EOF)
			_EOF(buffer);
		else if (*buffer == '\n')
			free(buffer);
		else
		{
			buffer[_strlen(buffer) - 1] = '\0';
			cmd = tokenization(buffer, " \0");
			free(buffer);
			if (_strcmp(cmd[0], "exit") != 0)
				shell_exit(cmd);
			else if (_strcmp(cmd[0], "cd") != 0)
				cd_dir(cmd[1]);
			else
				start_child(cmd, av[0], env, cycles);
		}
		fflush(stdin);
		buffer = NULL, buf_size = 0;
	}
	if (chars_read == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


/**
 * prompt - Prints the shell prompt
 * Return: Nothing.
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}


/**
 * handler - Function to handle Ctr + C signal.
 * @signals: The signal to handle.
 * Return: Nothing.
 */
void handler(int signals)
{
	(void)signals;
	write(STDOUT_FILENO, "\n$ ", 3);
}


/**
 * _EOF - Checks if buffer is EOF
 * @buffer: Points to the input string.
 * Return: Nothing
 */
void _EOF(char *buffer)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(buffer);
	exit(EXIT_SUCCESS);
}


/**
 * shell_exit - Exit the shell.
 * @cmd: The pointer to tokenized command.
 * Return: Nothing.
 */
void shell_exit(char **cmd)
{
	int sta_tus = 0;

	if (cmd[1] == NULL)
	{
		free_all(cmd);
		exit(EXIT_SUCCESS);
	}

	sta_tus = _atoi(cmd[1]);
	free_all(cmd);
	exit(sta_tus);
}
