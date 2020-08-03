#include "headersh.h"

/**
* free_env - free copy enviroment variable
* @en: copy external variable environment parsed by lines
* Return: nothing
*/
void free_env(char **en)
{
	int i = 0;

	for (i = 0; en[i] != NULL; i++)
		free(en[i]);
	free(en[i]);
	free(en);
}

/**
* main - call the shell by Arturo and Juani
* @ac: argument count
* @av: argument vector
* @env: external variable environment parsed by lines
* Return: nothing
*/
int main(int ac, char **av, char **env)
{
	int status = 0;

	if (ac == 1)
	{
		/*cpy of env*/
		/*en  = cpy_env(env)*/
		status = simple_sh(av, env);
		/*free_env(en)*/
		return (status);
	}
	return (0);
}
