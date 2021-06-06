/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:08:59 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/06 02:01:09 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	check_special_char(char a)
{
	if (!is_alpha_digit(a) && a != '_' && a != '\''
		&& a != '\"' && a != '$' && a != '\\' && (g_next = a))
		return (1);
	return (0);
}

int	check_end_1(char **args, char **split, int *i)
{
	char	a1;
	char	a2;
	int		s;

	s = 0;
	a1 = split[*i][0];
	if (split[*i + 1])
		a2 = split[*i + 1][0];
	if (mod_strlen(args) < 2 && split[*i + 1] && a2 != '>'
		&& a2 != '<' && (a1 == '>' || a1 == '<'))
	{
		args[0] = ft_strjoin(args[0], split[*i + 1]);
		*i += 1;
	}
	else if (split[*i + 1] && (a1 == '>' || a1 == '<')
		&& (a2 == '>' || a2 == '<'))
	{
		printf("minishell: syntax error near unexpected token `%c'\n", a2);
		return (0);
	}
	if (redirection(args, 0) < 0)
		return (0);
	return (1);
}

int	fill_cmd_helper(char **split)
{
	char	**args;
	int		i;

	i = 0;
	g_cmd = m_malloc(sizeof(t_command_info));
	g_cmd->reds.in_num = 0;
	g_cmd->reds.out_num = 0;
	while (split[i] && (split[i][0] == '<' || split[i][0] == '>'))
	{
		args = mod_split_red(split[i], "><");
		if (!check_end_1(args, split, &i))
			return (-1);
		i++;
	}
	g_cmd->command = m_malloc(ft_strlen(split[i]) + 1);
	ft_strcpy(g_cmd->command, clean_command_1(split[i]));
	i++;
	g_cmd->options = NULL;
	if (split[i] && split[i][0] == '-')
	{
		g_cmd->options = m_malloc(ft_strlen(split[i]) + 1);
		ft_strcpy(g_cmd->options, split[i]);
		i++;
	}
	return (i);
}

int		check_last_char(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	if (i > 0 && (str[i - 1] == '>' || str[i - 1] == '<'))
		return (1);
	return (0);
}

void	remove_last_char(char **str)
{
	int i;

	i = 0;
	while((*str)[i])
		i++;
	// if(i > 1 && ((*str)[i - 2] == '>' || (*str)[i - 2] == '<'))
	// 	(*str)[i - 2] = '\0';
	// if(i > 0 && (*str)[i - 1] == '>' || (*str)[i - 1] == '<')
	// 	(*str)[i - 1] = '\0';
}

int		check_if_last(char *srch, char **str)
{
	int i;
	int j;

	i = 0;
	j = ft_strlen(*str);
	printf("str=[%s]\n", *str);
	while((*str)[i] && ft_strchr(srch, (*str)[i]))
		i++;
	while((*str)[i])
	{
		if((ft_strchr(srch, (*str)[i])))
		{
			printf("i is %d|j is %d\n", i, j);
			if (i == j - 1)
			{
				(*str)[i] = '\0'; 
				return (1);
			}
			(*str)[i] = '\0';
			return(2);
		}
		i++;
	}
	return (0);
}
int		check_if_at_the_last(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	if(i > 2)
		if((str[i - 1] == '>' || str[i - 1] == '<') && (str[i] == '>' || str[i] == '<'))
			return (1);
	if(str[i] == '>' || str[i] == '<')
		return (1);
	return (0);
}

int		check_end_2(char **args, char **split, int *i, int *s)
{
	char	a1;
	char	a2;
	int		ret_slash;

	a1 = split[*i][0];
	a2 = '\0';
	if (split[*i + 1])
		a2 = split[*i + 1][0];
	//--------mod_strlen(args) < 3----
	printf("split[i]: %s\n", split[*i]);
	if (( split[*i + 1] && a2 != '>' && a2 != '<'
	&& (args[0][0] == '>' || args[0][0] == '<' || a1 == '>' || a1 == '<')))//(a1 == '>' || a1 == '<' )))
	{
		printf("ENTER1\n");
		printf("[%s]<==>JOINED\n", split[*i + 1]);
		args[0] = ft_strjoin(args[0], split[*i + 1]);
		printf("args[0]={%s}|args[1]={%s}\n", args[0], args[1]);
		//if(!check_if_last("><", args[0]))
		ret_slash = check_if_last("><", &args[0]);
		if(!ret_slash)
			*i = *i + 1;
		else
		{
			g_move_and_pass = ret_slash;
			printf("g_move_and_pass_2:%d\n", g_move_and_pass);
		}
		// else
		// {
		// 	g_move_and_pass = check_if_last("><", args[0]);////
		// }
			
	}
	//--------mod_strlen(args) < 3----
	else if (( split[*i + 1] && a2 != '>' && a2 != '<'
		&&  check_last_char(split[*i])))
	{
		printf("ENTER2|split[i + 1]=[%s]\n", split[*i + 1]);
		//printf("split[i]=[%s],arg[i]=[%s]\n", split[*i]);
		args[1] = ft_strjoin(args[1], split[*i + 1]);
		ret_slash = check_if_last("><", &args[1]);
		printf("args[1]: %s\n", args[1]);
		printf("ret_slash:[%d]\n", ret_slash);
		if(!ret_slash)
			*i = *i + 1;
		else
		{
			g_move_and_pass = ret_slash;
			printf("g_move_and_pass_1:%d\n", g_move_and_pass);
		}
		// if(remove_last_char(&args[0]))
		// {
			
		// }
		//*i = *i + 1;
	}
	else if (split[*i + 1] && check_if_at_the_last(split[*i])
		&& (a2 == '>' || a2 == '<'))
	{
		printf("minishell: syntax error near unexpected token `%c'\n", a2);
		return (0);
	}
	int xx = 0;
	while(args[xx])
	{
		printf("{%s}\n", args[xx++]);
	}
	if (cat_command_string(args, s) < 0)
		return (0);
	return (1);
}

void	move_what(char **split, int i)
{
	int j;

	j = 0;
	while(split[i][j])
	{
		
	}		
}

int	fill_cmd(char **split, int p)
{
	char	**args;
	int		i;
	int		s;

	i = fill_cmd_helper(split) - 1;
	if (!*split || i < 0)
		return (-1);
	s = 0;
	g_cmd->string[0] = NULL;
	g_move_and_pass = 0;
	while (split[++i])
	{
		// if (g_move_and_pass)
		// {
		// 	move_what(split, i);
		// }
		printf("split=[%s]\n", split[i]);
		args = mod_split_red(split[i], "><");
		if(g_move_and_pass == 1)
		{
			printf("%s<--->deleted\n", args[1]);
			args[0] = ft_strdup(args[1]);
			args[1] = NULL;
			printf("check_delete, args[0] = |%s|  |   args[1] = |%s|\n", args[0], args[1]);
			g_move_and_pass = 0;
		}
		if (!check_end_2(args, split, &i, &s))
			return (-1);
	}
	if (s)
		add_last_cmd(g_cmd->string[s - 1], "_");
	else if (g_cmd->options)
		add_last_cmd(g_cmd->options, "_");
	else
		add_last_cmd(g_cmd->command, "_");
	test(g_cmd);
	g_cmd->pipe = p;
	cmd_lstadd_back(&g_commands, g_cmd);
	return (1);
}
