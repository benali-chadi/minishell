/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 19:12:17 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/11 13:40:34 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "ft_printf/libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "termcaps/termcaps.h"
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
# include <dirent.h>

/*
	**Envirenment Stucture
*/

typedef struct s_list_env
{
	char					*content;
	char					*name;
	char					*name_content;
	struct s_list_env		*next;
}							t_list_env;

typedef struct s_histo
{
	char					*command_line;
	struct s_histo			*next;
	struct s_histo			*previous;
}							t_histo;

/*
	**Commands Structures
*/
typedef struct s_tests
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

typedef struct s_out
{
	char					sym[3];
	char					*file_name;
}							t_out;

typedef struct s_redirection
{
	char					*in_file_name[100];
	t_out					out[100];
	int						in_num;
	int						out_num;
}							t_redirection;

typedef struct s_command_info {
	char					*command;
	char					*options;
	char					*string[10000];
	int						indice[10000];
	int						string_len;
	t_tests					tests;
	int						pipe;
	t_redirection			reds;
	struct s_command_info	*next;
}							t_command_info;

/*
	**Utils Structure
*/

typedef struct s_utils
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
	char					pwd[100];
	int						for_ctrl_c;
}							t_utils;

typedef struct s_all
{
	t_command_info				*cmd;
	void						*alloc[100000];
	int							all;
	t_command_info				*commands;
	t_list_env					*list_env;
	t_histo						*histo;
	t_utils						utils;
	int 						(*fd)[2];
	int							one;
	int							two;
	int							var_one;
	int							var_two;
	int							status;
	int							returnn;
	char						*s_ret;
	int							join_red;
	char						*str_var;
	int							var_k;
	char						*s_cmd;
	int							c_l;
	char						*var_cmd;
	int							cmd_k;
	int							returned;
	int							count_end;
	char						case_index[10000];
	int							print_next;
	char						next;
	int							move_and_pass;
	char						*env_tab[10000];
	char						**cmd_args;
}				t_all;

/*
	**Global Variables
*/

t_all	g_all;

/*
	**Functions
*/

/*
	**cat_command_utils
*/
void						fix_quotes_next_to_var(char **args,
								int i, int j, int *s);
void						change_one_two(char a);
void						fill_command_string(char a, int i);
void						init_one_two(void);
void						replace_var(char **args, int i, int j, int *s);
void						loop_env_cmd(void);
/*
	**Utils
*/
void						check_error_type(int i, char *s, char a);
int							check_if_void(char *s);
int							check_equal_at_the_last(char *str);
int							chck_spc(char *s, char a);
int							check_if_void(char *s);
void						print_error_and_exit(void);
int							fill_cmd_helper(char ***split);
int							init_fill_cmd(char ***split, int *i, int *s);
void						continue_our_road(int s, int p);
char						**join_2_tab(char **tab1, char **tab2);
int							is_red(char a);
int							check_solo_at_the_first(char *str);
int							check_backslash(char *str, int e);
int							check_quotes_and_ret(char **args, int i, int j);
int							check_if_print(char *str, int j);
int							check_special_char(char a);
void						join_friendly_red(char **args,
								char **split, int *i);
void						join_lonely_red(char **args, char **split, int *i);
int							check_if_at_the_last(char *str);
int							check_if_last(char *srch, char **str);
int							check_last_char(char *str);
int							check_if_can_increment(char **args, int i, int j);
void						switch_one_two(char a);
int							check_char_first(char **args, int i, int j);
int							is_special(char a);
int							condition1(char a1, char a2, char *str, int e);
void						change_one_two(char a);
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
void						print_prompt(void);
int							in_value(int n, int *p);

/*
	split
*/
int							ft_countlen(const char *str, char c, int *i);
int							alloc_1(char ***tab1, int casee);
int							alloc_2(char **tab1, int i, int len);
int							calcule_len(int *len, char *s, char c, int *p);
int							re_check_quots(const char *str, int i);
int							ft_countlen_red(const char *str, char *c, int *i);
int							ft_countwords_red(const char *str, char *c);
char						**freetab(char **tab1, int i);
char						**result_red(char **tab1, const char *str, char *c);
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
char						*search_lgnam(void);
void						leave(char **strings);

/*
	**For freeing
*/
void						*m_malloc(size_t n);
void						m_free(void *elm);
void						to_free(void);

/*
	**Linked List
*/

int							ft_read_line(int fd, t_read *reads, t_histo **read);

/*
	**env
*/
void						ft_export(t_command_info *cmd);
void						add_quotes_and_fill(t_list_env *tmp, int *i);
int							check_var_solo(char *name);
void						ft_remove_node_cmd_1(void);
void						ft_remove_node(t_command_info *cmd);
void						add_back(t_list_env **head, char *name,
								char *content, char *name_content);
t_list_env					*ft_lstlast(t_list_env *lst);
void						ft_lstadd_front(t_list_env **alst, t_list_env *new);
void						ft_lstadd_back(t_list_env **alst, t_list_env *new);
t_list_env					*ft_lstnew(char *name, char *content,
								char *name_content);
void						add_back_cmd(t_histo **head, char *command_line);
int							add_last_cmd(char *s, char *name);
t_histo						*ft_lstlast_cmd(t_histo *lst);

/*
	**cmd
*/

void						cmd_lstadd_back(t_command_info **commands,
								t_command_info *new);
t_command_info				*cmd_lstlast(t_command_info *lst);

/*
	**Environment
*/
void						ft_next_node(t_list_env **read_list,
								t_list_env **prev);
void						bypass_ternarie_1(t_command_info *cmd,
								char **content, int i, int j);
void						ft_(t_command_info *cmd);
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
void						check_quots_after_dollar(char **args,
								int i, int j, int *s);
int							fill_cmd(char **split, int p);
int							cat_command_string(char **args, int *s);
void						init_one_two(void);
void						fill_command_string(char a, int i);
int							first_condition(int j, char **args, int i, int *s);
void						to_while(char **args, int i, int *s);

void						exec_cmd(t_command_info *cmd, int i, int last);
void						test(t_command_info *cmd);
int							test_cmds(t_command_info *cmd);
void						ft_echo(t_command_info *cmd);

void						ft_fork(t_command_info *cmd, int n, int last);

char						*check_cmd(char *command, int *p);

void						close_all(int last);
void						exec_cd(t_command_info *cmd);
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
