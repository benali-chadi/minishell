/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_g_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:11:55 by cbenali-          #+#    #+#             */
/*   Updated: 2021/01/19 18:09:37 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	fill_command_string(char a, int i)
{
	g_cmd->string[i][g_cmd->string_len++] = a;
	if (a == '\'')
		g_one = g_one == 1 ? 0 : 1;
	if (a == '"')
		g_two = g_two == 1 ? 0 : 1;
}

void	init_one_two(void)
{
	g_one = 0;
	g_two = 0;
}

void	red_file_names(char *args, int red, int j)
{
	int k;

	if (red == 1)
	{
		g_cmd->reds.out[g_cmd->reds.out_num].file_name =
		m_malloc(ft_strlen(args) + 1);
		k = 0;
		while (args[j])
			g_cmd->reds.out[g_cmd->reds.out_num].file_name[k++] = args[j++];
		g_cmd->reds.out[g_cmd->reds.out_num].file_name[k] = '\0';
		g_cmd->reds.out_num++;
	}
	else
	{
		g_cmd->reds.in_file_name[g_cmd->reds.in_num] =
		m_malloc(ft_strlen(args) + 1);
		k = 0;
		while (args[j])
			g_cmd->reds.in_file_name[g_cmd->reds.in_num][k++] = args[j++];
		g_cmd->reds.in_file_name[g_cmd->reds.in_num][k] = '\0';
		g_cmd->reds.in_num++;
	}
}

void	red_helper(char *arg, int *j, int *red)
{
	if (arg[*j] == '>')
	{
		while (arg[*j] && arg[*j] == '>')
		{
			g_cmd->reds.out[g_cmd->reds.out_num].sym[*j] = arg[*j];
			(*j)++;
		}
		*red = 1;
	}
	else
	{
		(*j)++;
		*red = 0;
	}
}

int		redirection(char **args, int *i)
{
	int j;
	int red;

	j = 0;
	red_helper(args[*i], &j, &red);
	if ((size_t)j >= ft_strlen(args[*i]))
	{
		(*i)++;
		j = 0;
	}
	if (!args[*i])
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 1);
		return (-1);
	}
	red_file_names(args[*i], red, j);
	(*i)++;
	if (!args[*i])
		return (1);
	j = 0;
	if (args[*i] && (args[*i][j] == '<' || args[*i][j] == '>'))
		if (!redirection(args, i))
			return (-1);
	return (1);
}
int		first_condition(int j, char **args, int i, int *s)
{
			j++;
			g_str_var = m_malloc(ft_strlen(args[i]));
			g_var_k = 0;
			while(is_alpha_digit(args[i][j]) && args[i][j] != '$' && args[i][j])
				g_str_var[g_var_k++] = args[i][j++];
			g_str_var[g_var_k] = '\0';
			if(ft_strcmpr(g_str_var, "?"))
			{
				g_str_return = ft_itoa(g_return);
				g_cmd->string[*s]  = ft_realloc(g_cmd->string[*s] 
					,ft_strlen(g_cmd->string[*s]) + ft_strlen(args[i]) + 
						ft_strlen(g_str_return) + 1 + g_two);
				g_var_k = 0;
				while(g_str_return[g_var_k])
				{
					g_cmd->string[*s][g_cmd->string_len++] = g_str_return[g_var_k];
					g_var_k++;
				}
				g_cmd->string[*s][g_cmd->string_len++] = '\0';			
			}
			else
			compare_var(g_str_var, args[i], *s);
			return(j);
}

void		to_while(char **args, int i,int *s)
{

	int j;
	//char *var;
	j = 0;

	while(args[i][j])
	{
		if((args[i][j] == '$' && args[i][j + 1] && g_one != 1 )|| (args[i][j] == '$' && args[i][j + 1] && g_one == 1 && g_two == 1))
		{	
			j = first_condition(j, args, i, s);
			if(args[i][j] == '"' || args[i][j] == '\'')
				fill_command_string(args[i][j], *s);
		}
		else
			fill_command_string(args[i][j], *s);
		if(args[i][j] && (args[i][j] != '$' || (g_one == 1 && args[i][j] == '$')))
			j++;
	}
	g_cmd->string[*s][g_cmd->string_len] = '\0';
	printf("g_cmd->string[s] is:[%s]\n", g_cmd->string[*s]);
}

int		cat_command_string(char **args, int i)
{
	int j;
	int s;

	s = 0;
	while(args[i])
	{	
		j = 0;
		if (args[i] && (args[i][j] == '<' || args[i][j] == '>'))
			if (redirection(args, &i) < 0)
				return (-1);
		if (!args[i])
			break;
		init_one_two();
		g_cmd->string[s] = m_malloc(ft_strlen(args[i]) + 1);
		g_cmd->string[s] = ft_strcpy(g_cmd->string[s], args[i]);
		g_cmd->string_len = 0;
		printf("g_cmd->string[s] is:[%s]\n", g_cmd->string[s]);
		to_while(args, i, &s);
		s++;
		i++;
	}
	g_cmd->string[s] = NULL;
	return (1);
}

int		fill_cmd(char **split, int p)
{
	int i;

	i = 0;
	if (!*split)
		return (0);
	g_cmd = malloc(sizeof(t_command_info));
	
	// initializing reds
	
	g_cmd->reds.in_num = 0;
	g_cmd->reds.out_num = 0;
	
	if (split[i][0] == '<' || split[i][0] == '>')
		if (redirection(split, &i) < 0)
			return (-1);
	
	g_cmd->command = m_malloc(ft_strlen(split[i]) + 1);

	ft_strcpy(g_cmd->command, split[i]);
	i++;

	if (split[i] && split[i][0] == '-')
	{
		g_cmd->options = m_malloc(ft_strlen(split[i]) + 1);
		ft_strcpy(g_cmd->options, split[i]);
		i++;
	}
	else
		g_cmd->options = NULL;
	if (split[i])
        if (cat_command_string(split, i) < 0)
			return (-1);

	test(g_cmd);
	g_cmd->pipe = p;
	cmd_lstadd_back(&g_commands, g_cmd);
	return (1);
}
