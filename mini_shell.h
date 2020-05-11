#ifndef MINI_SHELL_H
#define MINI_SHELL_H

#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

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
	Command Structures
*/

typedef struct	s_command_info {
	char		*command;
	char		*options;
	char		*string;
	int			string_len;
}				t_command_info;

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

typedef struct	s_variables {
	int			num;
	char		*buffer;
}				t_variables;

/*
	Global Variables
*/

t_command_info	command_info;
t_tests			tests;
t_list_env		*list_env;
t_variables		variables;
int				g_one;
int				g_two;

/*Functions*/

/*
	Utils
*/

char			**mod_split(char const *s, char c);
void			*ft_realloc(void *ptr, int size);
char			*ft_strcpy(char *s1, char *s2);
int				ft_strcmpr(char *s1, char *s2);
int				is_alpha_digit(char a);

/*
	Linked List
*/
void			ft_export(char *variable);
void			loop_env(void);
void			ft_remove_node(char *name);
void			add_back(t_list_env **head, char *name, char *content, char *name_content);
t_list_env		*ft_lstlast(t_list_env *lst);
void			ft_lstadd_front(t_list_env **alst, t_list_env *new);
void			ft_lstadd_back(t_list_env **alst, t_list_env *new);
t_list_env		*ft_lstnew(char *name, char *content, char *name_content);

/*
	Environment
*/

void	stock_env(char **env);
void	ft_cpy_env(t_list_env *read_env);
void	compare_var(char *var, char *arg);

/*
	Fill The command
*/

void	fill_cmd(char **split);
void	cat_command_string(char	**args, int i);
void	change_one_two(char a);
void	init_one_two();
void	fill_command_string(char a);

#endif