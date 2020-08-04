#include "headersh.h"

/**
* count_characters - count the numbers of characters there is in a pointer
* @str: pointer with the name of the directory
* Return: the length of the name
*/
int count_characters(char *str)
{
	int index = 0;

	for (index = 0; str && str[index] != '\0'; index++)
		continue;
	return (index);
}

/**
* concat_two_strings - concatenate 2 strings
* @str1: pointer with a string
* @str2: pointer with a string
* Return: ponter with the two string concatenate
*/
char *concat_two_strings(char *str1, char *str2)
{
	char *full_str = NULL;
	int str1_length = 0;
	int str2_length = 0;
	int index = 0;

	str1_length = count_characters(str1);
	str2_length = count_characters(str2);

	full_str = malloc((sizeof(char) * (str1_length + str2_length)) + 1);

	if (!full_str)
		return (NULL);

	for (index = 0; index <= (str2_length + str1_length); index++)
	{
		if (index < str2_length)
		{
			full_str[index] = str2[index];
		}
		else
			full_str[index] = str1[index - str2_length];
		if (index == (str2_length + str1_length))
			full_str[index] = '\0';
	}

	return (full_str);
}

/**
* _setenv - adds the variable name to the environment with the value
* @tokens: the value to print
* @en: environ variable
* @buffer: read it from user
* @statuss: previous loop status
* Return: 0 on success otherwise -1
*/
int _setenv(char ***en, char ***tokens, char **buffer, int *statuss)
{
	int i = 0, j = 0, flag = 0, size_env = 0;
	char *new_str = NULL, *new_str_eq, **new_en = NULL;
	(void)buffer, (void)statuss;

	if (!(*tokens)[1] || !(*tokens)[2])
		return (0);
	new_str_eq = concat_two_strings("=", (*tokens)[1]);
	new_str = concat_two_strings((*tokens)[2], new_str_eq);
	free(new_str_eq);
	if (!_getenv((*tokens)[1], *en))
	{
		while ((*en)[size_env])
			size_env++;
		new_en = malloc(sizeof(char *) * (size_env + 2));
		if (!new_en)
			return (0);
		for (i = 0; (*en)[i]; i++)
			new_en[i] = (*en)[i];
		free(*en);
		new_en[i] = new_str, new_en[i + 1] = NULL, *en = new_en;
	}
	else
	{
		for (i = 0; (*en)[i]; i++)
		{
			flag = 1;
			for (j = 0; (*tokens)[1][j]; j++)
			{
				if ((*tokens)[1][j] != (*en)[i][j])
				{
					flag = 0;
					break;
				}
			}
			if (flag)
				free((*en)[i]), (*en)[i] = new_str;
		}
	}
	return (1);
}

/**
* _unsetenv - deletes the variable name from the environment
* @tokens: the value to print
* @en: environ variable
* @buffer: read it from user
* @statuss: previous loop status
* Return: nothing
*/

int _unsetenv(char ***en, char ***tokens, char **buffer, int *statuss)
{
	int i = 0, j = 0, k = 0, flag = 0, size_env = 0;
	char **new_en = NULL;
	(void)buffer;
	(void)statuss;

	if (!(*tokens)[1])
		return (0);
	if (!_getenv((*tokens)[1], *en) || !(*en))
		return (1);

	while ((*en)[size_env])
		size_env++;

	new_en = malloc(sizeof(char *) * (size_env));
	if (!new_en)
		return (1);

	for (i = 0; (*en)[i]; i++)
	{
		flag = 1;
		for (j = 0; (*tokens)[1][j]; j++)
		{
			if ((*tokens)[1][j] != (*en)[i][j])
			{
				flag = 0;
				break;
			}
		}
		if (!flag)
			new_en[k++] = (*en)[i];
		else
			free((*en)[i]);
	}
	new_en[k] = NULL;
	free(*en);
	*en = new_en;
	return (1);
}