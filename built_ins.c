#include "headersh.h"

/**
* _atoi - convert a string into a integer.
* @s: string
* @is_number: check if is a number
* Return: the representation of the string in integer.
*/
int _atoi(char *s, int *is_number)
{
	int negative = 1, i = 0;
	unsigned int numero = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '-')
			negative *= -1;
		else if (s[i] > 57 || s[i] < 48)
		{
			*is_number = 1;
			return (0);
		}
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
* @cc: is the counter of commans executes by user
* @av: list containing the arguments given by user
* Return: nothing
*/

int exi(char ***en, char ***tokens, char **buffer,
	int *statuss, char **av, int *cc)
{
	int s = *statuss, is_number = 0;
	char err_message[] = "Illegal number: ";

	(void)av, (void)cc;
	if ((*tokens)[1])
	{
		s = _atoi((*tokens)[1], &is_number);
		if (s < 0 || is_number == 1)
		{
			print_error_builtin(*av, *cc, *tokens, err_message);
			*statuss = 2;
			return (1);
		}
	}
	free_all(buffer, tokens);
	freeenv(*en);
	exit(s);
}

/**
* print_error_cd - prints output error of cd builtin
* @av: first parameter that called the shell
* @cc: error counter
* @tokens: command inputed by user
* Return: nothing
*/
int print_error_cd(char *av, int cc, char **tokens)
{
	char errmsg[] = "can't cd to ";

	print_error_builtin(av, cc, tokens, errmsg);
	return (1);
}

/**
* cd - changes the current working directory
* @tokens: the value to print
* @en: environ variable
* @buffer: read it from user
* @statuss: previous loop status
* @cc: is the counter of commans executes by user
* @av: list containing the arguments given by user
* Return: nothing
*/

int cd(char ***en, char ***tokens, char **buffer,
	int *statuss, char **av, int *cc)
{
	char *home_env = NULL, *prewd = NULL, *_set1[3], **set_old = _set1;
	char *_set2[3], **set_new = _set2;
	int ret = 0;

	(void)buffer, (void)av, (void)cc, (void)ret;
	prewd = _getenv("OLDPWD", *en), home_env = _getenv("HOME", *en);
	set_old[0] = NULL, set_old[1] = "OLDPWD";
	set_old[2] = _getenv("PWD", *en);
	set_new[0] = NULL, set_new[1] = "PWD";
	if (!prewd)
	{
		_setenv(en, &set_old, buffer, statuss, av, cc);
		prewd = _getenv("OLDPWD", *en);
	}
	if (!(*tokens)[1])
		ret = chdir(home_env), set_new[2] = home_env;
	else
	{
		if (!_strcmp((*tokens)[1], "-"))
		{
			ret = chdir(prewd);
			if (ret == -1)
				return (print_error_cd(*av, *cc, *tokens));
			printf("%s\n", prewd), set_new[2] = prewd;
		}
		else
		{
			ret = chdir((*tokens)[1]);
			if (ret == -1)
				return (print_error_cd(*av, *cc, *tokens));
			set_new[2] = (*tokens)[1];
		}
	}
	_setenv(en, &set_old, buffer, statuss, av, cc);
	_setenv(en, &set_new, buffer, statuss, av, cc);
	return (1);
}

/**
* built_ins_sh - fills memory with a constant byte
* @tokens: the value to print
* @en: environ variable
* @buffer: read it from user
* @statuss: previous loop status
* @cc: is the counter of commans executes by user
* @av: list containing the arguments given by user
* Return: numbers of characters printed
*/

int built_ins_sh(char ***tokens, char ***en, char **buffer,
	int *statuss, char **av, int *cc)
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
			return (o[j].f(en, tokens, buffer, statuss, av, cc));
	return (0);
}
