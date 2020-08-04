#ifndef HEADERSH
#define HEADERSH

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/**
* struct path_node - singly linked list
* @str: string - it a path directory
* @next: points to the next node
*
* Description: Store all the path directories
*/

typedef struct path_node
{
	char *str;
	struct path_node *next;
} path_node;

/**
* struct op - Struct op
*
* @op: The operator
* @f: The function associated
*/
typedef struct op
{
	char *op;
	int (*f)(char ***, char ***, char **, int *, char **, int *);
} op_t;

char *_strcat(char *dest, char *src);
int _strlen(char *st);
char *_itoa(int num, char *strnum);
int simple_sh(char **av, char ***en);
int readsh(char **buffer, int *len);
void parsesh(char **buffer, int *len, char ***tokens, int *status);
int createandexesh(char ***, int *, char ***, char **, int *);
char *_getenv(const char *variable_env, char **en);
path_node *_getpathdir(char *path, char **);
int add_path(char ***tokens, char **en);
void get_path(path_node **list_path, char **en);
int _strcmp(char *s1, char *s2);

/*Free all allocate variables*/
void free_list(path_node *list_path);
void free_all(char **buffer, char ***tokens);

/*Print Error Built-in*/
void print_error_builtin(char *av, int cc, char **token, char *errmsg);

/*Built-ins*/
int built_ins_sh(char ***tokens, char ***, char **, int *, char **, int *);

int _setenv(char ***en, char ***tokens, char **buffer, int *, char **, int *);
int _unsetenv(char ***en, char ***tokens, char **, int *, char **, int *);

/*env utilities*/
char **envdup(char **env);
void freeenv(char **env);
#endif
