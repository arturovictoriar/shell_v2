#include "headersh.h"

/**
* out_redir_in - choose the correct option to exe a commmand
* @tokens: strings from stdin
* @cc: is the counter of commans executes by user
* @en: list containing the end parameter for execve syscall
* @av: list containing the arguments given by user
* @status: previous loop status
* @head: all commands in a line
* @tok_com: ONE command of a line
* @copy_head: current node command
* Return: the process status
*/
int out_redir_in(char ***tokens, int *cc, char ***en, char **av,
	int *status, dlistint_t **head, char ***tok_com, dlistint_t *copy_head)
{
	int flag_terminator = 0, stdout_copy = dup(1), stdin_copy = dup(0);
	int pipefd[2];

	if (!copy_head->prev->status)
	{
		create_pipe(&pipefd);
		stdout_to_stdin(pipefd);
		if ((copy_head->prev)->buffer_in)
		{
			printf("%s", (copy_head->prev)->buffer_in);
			fflush(stdout);
		}
		close(pipefd[1]);
		set_normal_stdout(stdout_copy);
		createandexesh(tokens, cc, en, av, status, head, tok_com,
			copy_head);
		close(pipefd[1]);
		set_normal_stdin(stdin_copy);
	}
	else
		flag_terminator = 1;
	return (flag_terminator);
}
