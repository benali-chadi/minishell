#ifndef MINI_SHELL_H
#define MINI_SHELL_H

// #include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

/*
	Envirenment Stucture
*/

typedef	struct		s_list_env
{
	char				*content;
	char				*name;
	char				*name_content;
	struct s_list_env	*next;
}					t_list_env;

/*
	Commands Structures
*/
typedef struct	s_tests {
	int			echo;
	int			cd;
	int			pwd;
	int			export_t;
	int			unset;
	int			env;
	int			exit;
	int			ls;
}				t_tests;

typedef struct	s_out
{
	char		sym[3];
	char		*file_name;
}				t_out;


typedef struct	s_redirection
{
	char		*in_file_name[100];
	t_out		out[100];
	int			in_num;
	int			out_num;
}				t_redirection;


typedef struct	s_command_info {
	char					*command;
	char					*options;
	char					*string[200];
	int						string_len;
	t_tests					tests;
	int						pipe;
	t_redirection			reds;
	struct s_command_info	*next;
}				t_command_info;


/*
	Utils Structure
*/

typedef struct	s_utils {
	char		cnt[128];
	char		*args[200];
	int			save_in;
	int			save_out;
	char		**env;
}				t_utils;


/*
	Global Variables
*/

t_command_info	*commands;
t_list_env		*list_env;
t_utils			utils;
int				(*fd)[2];
int				g_q;
int				g_one;
int				g_two;
int				g_status;
int				g_return;
char			*g_str_return;
/*Functions*/

/*
	Utils
*/

int				gnl(int fd, char **line);

char			**mod_split(char const *s, char c);
void			*ft_realloc(void *ptr, int size);
char			*ft_strcpy(char *s1, char *s2);
int				ft_strcmpr(char *s1, char *s2);
int				is_alpha_digit(char a);
void			init_cnt();

void			sig_handler(int signum);

char			*search_lgnam();

/*
	For freeing
*/
void			*m_malloc(size_t n);
void			m_free(void *elm);
void			to_free(void);
/*
	Linked List
*/

// For env

void			ft_remove_node(t_command_info *cmd);
void			add_back(t_list_env **head, char *name, char *content, char *name_content);
t_list_env		*ft_lstlast(t_list_env *lst);
void			ft_lstadd_front(t_list_env **alst, t_list_env *new);
void			ft_lstadd_back(t_list_env **alst, t_list_env *new);
t_list_env		*ft_lstnew(char *name, char *content, char *name_content);

// for cmd

void				cmd_lstadd_back(t_command_info **commands, t_command_info *new);
t_command_info		*cmd_lstlast(t_command_info *lst);

/*
	Environment
*/

void			ft_export(t_command_info *cmd);
void			loop_env(void);
void			stock_env(char **env);
void			compare_var(t_command_info *cmd, char *var, char *arg, int s);
void			ft_cpy_env(t_command_info *cmd, t_list_env *read_env, int s);

/*
	Commands
*/

int				fill_cmd(char **split, int p);
int				cat_command_string(t_command_info *cmd, char **args, int i);
void			change_one_two(char a);
void			init_one_two();
void			fill_command_string(t_command_info *cmd, char a, int i);
void			exec_cmd(t_command_info *cmd, int i, int last);
void			test(t_command_info *cmd);

void			echo(t_command_info *cmd);

void			ft_fork(t_command_info *cmd, int n, int last);

char			*check_cmd(char *command, int *p);

void			close_all(int last);

int				redirection(t_command_info *cmd, char **args, int *i);

/*
	Path
*/

void			find_path(t_command_info *cmd, char *var, int p);
char			*search_path(void);
void			execute_cmd(t_command_info *cmd, char *command);

#endif