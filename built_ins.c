#include "headersh.h"

/**
* env - fills memory with a constant byte
* @tokens: the value to print
* @en: environ variable
* @buffer: read it from user
* @statuss: previous loop status
* Return: nothing
*/

int env(char ***en, char ***tokens, char **buffer, int *statuss)
{
	int i, j;

	(void)tokens;
	(void)buffer;
	(void)statuss;
	for (i = 0; (*en)[i] != NULL; i++)
	{
		for (j = 0; (*en)[i][j] != '\0'; j++)
			continue;
		write(STDOUT_FILENO, (*en)[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (1);
}

/**
 * _atoi - convert a string into a integer.
 * @s: string
 * Return: the representation of the string in integer.
 */
int _atoi(char *s)
{
	int negative = 1, i = 0;
	unsigned int numero = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '-')
			negative *= -1;

		else if (s[i] >= 0 + '0' && s[i] < 10 + '0')
			numero = numero * 10 + (s[i] - '0');

		else if (s[i - 1] >= 0 + '0' && s[i - 1] < 10 + '0')
			break;
	}

	return (numero * negative);
}

/**
* exi - fills memory with a constant byte
* @tokens: the value to print
* @en: environ variable
* @buffer: read it from user
* @statuss: previous loop status
* Return: nothing
*/

int exi(char ***en, char ***tokens, char **buffer, int *statuss)
{
	int s = *statuss;

	if ((*tokens)[1])
		s = _atoi((*tokens)[1]);
	free_all(buffer, tokens);
	freeenv(*en);
	exit(s);
}

/**
* cd - changes the current working directory
* @tokens: the value to print
* @en: environ variable
* @buffer: read it from user
* @statuss: previous loop status
* Return: nothing
*/

int cd(char ***en, char ***tokens, char **buffer, int *statuss)
{
	int ret = 0;
	char *home_env = NULL, *prewd = NULL, *set[3];

	(void)buffer;
	home_env = _getenv("HOME", *en);
	if (!(*tokens)[1])
		ret = chdir(home_env);
	else
	{
		prewd = _getenv("OLDPWD", *en);
		if (!(*tokens)[1] == '-')
		{
			if (!prewd)
			{
				perror("-hsh: cd: OLDPWD not set");
				*statuss = 1;
				return (0);
			}
			ret = chdir(prewd);
		}
		else
		{
			ret = chdir((*tokens)[1]);
		}
		set[0] = NULL;
		set[1] = "OLDPWD";
		set[2] = _getenv("PWD", *en);
		_setenv(env, &set, buffer, statuss);
	}
	return (!ret);
}

/**
* built_ins_sh - fills memory with a constant byte
* @tokens: the value to print
* @en: environ variable
* @buffer: read it from user
* @statuss: previous loop status
* Return: numbers of characters printed
*/

int built_ins_sh(char ***tokens, char ***en, char **buffer, int *statuss)
{
	int j;
	op_t o[] = {
		{"env", env},
		{"exit", exi},
		{"cd", cd},
		{"unsetenv", _unsetenv},
		{"setenv", _setenv},
		{NULL, NULL},
	};

	for (j = 0; o[j].op != NULL; j++)
		if (_strcmp((*tokens)[0], o[j].op) == 0)
			return (o[j].f(en, tokens, buffer, statuss));
	return (0);
}
