#include "shell.h"

/**
 * start_child - Creates a sub process.
 * @cmd: The pointer to tokenized command
 * @name: The points to the shell name.
 * @env: The pointer to the enviromental variables.
 * @cycles: Number of executed cicles.
 * Return: Nothing.
 */
void start_child(char **cmd, char *name, char **env, int cycles)
{
	int pid = 0;
	int status = 0;
	int wait_error = 0;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: ");
		free_exit(cmd);
	}
	else if (pid == 0)
	{
		exec(cmd, name, env, cycles);
		free_all(cmd);
	}
	else
	{
		wait_error = waitpid(pid, &status, 0);
		if (wait_error < 0)
		{
			free_exit(cmd);
		}
		free_all(cmd);
	}
}


/**
  * cd_dir - Function that changes working directory.
  * @path: The current working directory.
  * Return: 0 on success, -1 on failure.
  */
int cd_dir(const char *path)
{
	char *buf = NULL;
	size_t size = 1024;

	if (path == NULL)
		path = getcwd(buf, size);
	if (chdir(path) == -1)
	{
		perror(path);
		return (98);
	}
	return (1);
}
