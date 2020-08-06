#include "headersh.h"

/**
* createandexesh - creat and execute the command given by user
* @tokens: strings from stdin
* @cc: is the counter of commans executes by user
* @en: list containing the end parameter for execve syscall
* @av: list containing the arguments given by user
* @status: previous loop status
* @head: first element of the list of commands
* Return: the process status
*/
int exe_mul_commands(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head)
{
	dlistint_t *copy_head = NULL;
	char ***tok_com = NULL;

	copy_head = *head;
	while (copy_head)
	{
		tok_com = &(copy_head->tokens);
		createandexesh(tokens, cc, en, av, status, head, tok_com);
		copy_head = copy_head->next;
	}
	return (0);
}
