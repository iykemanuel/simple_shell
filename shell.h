#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

int main(int ac, char **av, char **env);
void prompt(void);
void handler(int signals);
void _EOF(char *buffer);
void shell_exit(char **cmd);
void start_child(char **cmd, char *name, char **env, int cycles);
int cd_dir(const char *path);

void exec(char **cmd, char *name, char **env, int cycles);
void print_env(char **env);
char **_getPATH(char **env);
void msgerror(char *name, int cycles, char **cmd);

int _strcmp(char *s1, char *s2);
unsigned int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _atoi(char *s);
char *_strcat(char *dest, char *src);

void free_all(char **cmd);
void free_exit(char **cmd);

char **tokenization(char *buffer, const char *s);
#endif
