#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/fcntl.h>

#include "string.h"
#include "cmd.h"

#define UNUSED(x) (void)(x)
#define IN_BUFFER_SIZE 128

/* --- GLOBAL --- */

/**
 * enum access_options - options for global variable functions
 * @SET_VARIABLE: Set a global variable
 * @GET_VARIABLE: Get a variable without updating the global state
 */
enum access_options
{
SET_VARIABLE,
GET_VARIABLE
};

int exit_status(enum access_options, int);
char **_env(enum access_options access_option, char **value);
char **prog_args(char **value);
void my_exit(int code);

/* --- TEST --- */

void test(void);

/* --- MEMORY --- */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* --- INPUT --- */

char **get_input(int fd, char **temp);
int get_line(char **lineptr, int *n, int fd);
char **line_to_tokens(char *line);

/* --- ALIASES --- */

char resolve_aliases(char **aliases, char *line);
char add_alias(char **aliases, char *line);

/* --- OUTPUT --- */

size_t put_s(const char *str);
int put_c(char c);
char *ultos(unsigned long ul);

/* --- PATHS --- */

int is_path(const char *command);
int is_dir(const char *pathname);
char *path_concat(const char *s1, const char *s2);
char *find_in_PATH(const char *command, char **temp);
int can_access(const char *command, const char *pathname);

/* --- GETCMD --- */

cmd *getcommand(const char *command, char **temp);

/* --- RUNCMD --- */

int runcommand(cmd *command, char **args);
int run_exe(file_cmd *command, char **args);
int run_builtin(builtin_cmd *command, char **args);
int run_multi(multi_cmd *command, char **args);

/* --- ERRORS --- */

int _errno(int update);
int print_err(const char *command, const char *error);

/* --- ENV --- */

void initialize_env(char **env);
void free_env_end(void);
int get_env(const char *varname);

/* --- BUILTIN --- */

/**
 * struct builtin_f - command-function pair
 * @command: command that calls builtin
 * @func: function to call, returns exit status
 */
struct builtin_f
{
char *command;
int (*func)(char **args);
};
typedef struct builtin_f builtin_f;

cmd *find_builtin(const char *command);

int exit_builtin(char **args);
int env_builtin(char **args);

/* --- SPECIAL CHARS --- */

char *resolve_special(char *s);

#endif /* MAIN_H */

