/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 19:12:17 by cbenali-          #+#    #+#             */
/*   Updated: 2021/02/26 19:21:17 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "ft_printf/libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>

/*
	**Envirenment Stucture
*/

typedef	struct				s_list_env
{
	char					*content;
	char					*name;
	char					*name_content;
	struct s_list_env		*next;
}							t_list_env;

/*
	**Commands Structures
*/
typedef struct				s_tests
{
	int						echo;
	int						cd;
	int						pwd;
	int						export_t;
	int						unset;
	int						env;
	int						exit;
	int						ls;
}							t_tests;

typedef struct				s_out
{
	char					sym[3];
	char					*file_name;
}							t_out;

typedef struct				s_redirection
{
	char					*in_file_name[100];
	t_out					out[100];
	int						in_num;
	int						out_num;
}							t_redirection;

typedef struct				s_command_info {
	char					*command;
	char					*options;
	char					*string[10000];
	int						string_len;
	t_tests					tests;
	int						pipe;
	t_redirection			reds;
	struct s_command_info	*next;
}							t_command_info;

/*
	**Utils Structure
*/

typedef struct				s_utils
{
	char					*line;
	char					**m_split;
	char					**p_split;
	char					**c_split;
	t_command_info			*cmd;
	char					cnt[128];
	char					*args[200];
	char					**env;
	int						out;
	struct stat				buf;
}							t_utils;

/*
	**Global Variables
*/

t_command_info				*g_cmd;
t_command_info				*g_commands;
t_list_env					*g_list_env;
t_utils						g_utils;
int							(*g_fd)[2];
int							g_q;
int							g_one;
int							g_two;
int							g_var_one;
int							g_var_two;
int							g_status;
int							g_return;
char						*g_str_return;
int							g_join_red;
char						*g_str_var;
int							g_var_k;
char						*g_str_command;
int							g_command_len;
char						*g_var_cmd;
int							g_cmd_k;
int							g_returned;
int							g_count_end;
char						g_case_index[10000];
int							g_print_next;
char						g_next;
/*
	**Functions
*/

/*
	**Utils
*/
int							check_special_char(char a);
int							ft_print_error(char a, t_command_info *cmd, int i);
int							is_min(char a);
int							is_maj(char a);
int							is_digit(char a);
char						*clean_command_1(char *command);
char						*clean_cmd(char *str);
int							gnl(int fd, char **line);
int							check_quots(const char *str, int i);
int							check_white_spaces(void);
int							re_check_quots(const char *str, int i);
int							ft_countlen_red(const char *str, char *c, int *i);
int							ft_countwords_red(const char *str, char *c);
char						**freetab(char **tab, int i);
char						**result_red(char **tab, const char *str, char *c);
char						**mod_split(char *s, char c);
int							skip_repeat(char *str, int *i, char c);
int							stock_index(int a);
char						**mod_split_red(char const *s, char *c);
int							mod_strlen(char **s);
void						*ft_realloc(void *ptr, int size);
char						*ft_strcpy(char *s1, char *s2);
int							ft_strcmpr(char *s1, char *s2);
int							is_alpha_digit(char a);
void						init_stuff(char **env);
void						fill_command(char a);
int							sing_or_doub_q(char *str,
							int *k, int quote, char q);
void						sig_handler(int signum);
char						*search_lgnam();

/*
	**For freeing
*/
void						*m_malloc(size_t n);
void						m_free(void *elm);
void						to_free(void);
/*
	**Linked List
*/

/*
	**env
*/

void						ft_remove_node(t_command_info *cmd);
void						add_back(t_list_env **head, char *name,
							char *content, char *name_content);
t_list_env					*ft_lstlast(t_list_env *lst);
void						ft_lstadd_front(t_list_env **alst, t_list_env *new);
void						ft_lstadd_back(t_list_env **alst, t_list_env *new);
t_list_env					*ft_lstnew(char *name, char *content,
							char *name_content);

/*
	**cmd
*/

void						cmd_lstadd_back(t_command_info **commands,
							t_command_info *new);
t_command_info				*cmd_lstlast(t_command_info *lst);

/*
	**Environment
*/

void						ft_export(t_command_info *cmd);
int							loop_env(int e);
void						stock_env(char **env);
void						compare_var(char *var, char *arg, int s);
void						ft_cpy_env(t_list_env *read_env, int s);
void						compare_var_command(char *var, char *command);
void						ft_cpy_env_command(t_list_env *read_env);
int							check_var(char *name, char *content,
char *name_content);
/*
	**Commands
*/

int							fill_cmd(char **split, int p);
int							cat_command_string(char **args, int *s);
void						init_one_two();
void						fill_command_string(char a, int i);
int							first_condition(int j, char **args, int i, int *s);
void						to_while(char **args, int i, int *s);

void						exec_cmd(t_command_info *cmd, int i, int last);
void						test(t_command_info *cmd);
int							test_cmds(t_command_info *cmd);
void						echo(t_command_info *cmd);

void						ft_fork(t_command_info *cmd, int n, int last);

char						*check_cmd(char *command, int *p);

void						close_all(int last);

/*
	**Redirection
*/

int							redirection(char **args, int i);
int							red_helper(char *arg, int *j, int *red);
void						red_file_names(char *args, int red, int j);

/*
	**Path
*/

void						find_path(t_command_info *cmd, char *var, int p);
char						*search_path(void);
void						execute_cmd(t_command_info *cmd, char *command);

#endif
