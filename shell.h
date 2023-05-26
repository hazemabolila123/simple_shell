#ifndef SHELL_H
#define SHELL_H

/** Libraries used in the code **/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <linux/limits.h>
#include <fcntl.h>
#include <signal.h>
extern char **environ;
#define _GNU_SOURCE


/** String Manipulation Functions **/
int _strlen(char *str);
char *_strcat(char *dest, char *src);
int _strncmp(char *str1, char *str2, size_t n);
char *_strdup(char *str);
char *_strrev(char *str);
char *_strcpy(char *dest, char *src);
char *_strncpy(char *dest, char *src, int n);
int _atoi(char *str, char *status);
char *my_itoa(long int num, char *strout, int base);

/** Prototypes of user defined function used in the code **/
char isdelim(char, char *);
int words_count(char *, char *);
int token_len(char *, char *);
char **_strtok(char *, char *);
void display_aliases(char **);
size_t new_def(char *);
int predefined_alias(char *, char **, size_t);
char check_alias(char *, char **);
char display_alias(char *, char **);
char *alias_value(char *, size_t);
char set_alias(char *, char **, size_t);
char *get_aliasval(char *, char **);
char **get_alias(char **, size_t, char **);
size_t shell_alias(char **, char **);
ssize_t execute_builtin(char **, unsigned long, char **, char *);
size_t my_exit(char **, unsigned long, char *);
size_t my_env(char **, unsigned long, char *);
size_t my_setenv(char **, unsigned long, char *);
size_t my_unsetenv(char **, unsigned long, char *);
size_t my_cd(char **, unsigned long, char *);
void sep_cases(char, char **);
void err_cases(char, char **, size_t *);
void errors_Handling(char, unsigned int, char *, char *);
size_t execute(char **, unsigned long, char **, char **, char *);
void free_array(char **);
void free_variable(void);
void remove_comments(char **);
void handle_newline(char **);
char **dollarsign(char **, size_t, size_t *);
void handle_sigint(int);
char *my_getenv(char *);
char *create_path(char *);
ssize_t concat_seperator(char **);
char create_modifyvar(void);
void append2modifyvar(char *);
char check_appended(char *);

/**
 * struct builtin_s - A struct to handel builtin commands
 * @command: Command to be handeled
 * @fp: Pointer to the command function should be called
 */
typedef struct builtin_s
{
	char *command;
	size_t (*fp)(char **, unsigned long, char *);
} builtin_t;
#endif

