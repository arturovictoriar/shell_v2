#include "headersh.h"

/**
* _setenv - adds the variable name to the environment with the value
* @name: variable to add
* @value: value of the variable name
* @overwrite: flag to decide if overwrite or not
* @en: environment variable
* Return: 0 on success otherwise -1
*/
int _setenv(const char *name, const char *value, int overwrite, char ***en)
{
	(void)name;
	(void)value;
	(void)overwrite;
	(void)en;

	return (0);
}

/**
* _unsetenv - deletes the variable name from the environment
* @name: variable to delete
* @en: environment variable
* Return: 0 on success otherwise -1
*/
int _unsetenv(const char *name, char ***en)
{
	(void)name;
	(void)en;

	return (0);
}
