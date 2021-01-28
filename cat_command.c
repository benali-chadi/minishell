/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:21:41 by cbenali-          #+#    #+#             */
/*   Updated: 2021/01/28 15:51:32 by cbenali-         ###   ########.fr       */
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

int		first_condition(int j, char **args, int i, int *s)
{
	j++;
	g_str_var = m_malloc(ft_strlen(args[i]));
	g_var_k = 0;
	while (is_alpha_digit(args[i][j]) && args[i][j] != '$' && args[i][j])
		g_str_var[g_var_k++] = args[i][j++];
	g_str_var[g_var_k] = '\0';
	if (ft_strcmpr(g_str_var, "?"))
	{
		g_str_return = ft_itoa(g_return);
		g_cmd->string[*s] = ft_realloc(g_cmd->string[*s]
			, ft_strlen(g_cmd->string[*s]) + ft_strlen(args[i]) +
				ft_strlen(g_str_return) + 1 + g_two);
		g_var_k = 0;
		while (g_str_return[g_var_k])
		{
			g_cmd->string[*s][g_cmd->string_len++] = g_str_return[g_var_k];
			g_var_k++;
		}
		g_cmd->string[*s][g_cmd->string_len++] = '\0';
	}
	else
		compare_var(g_str_var, args[i], *s);
	return (j);
}

void	to_while(char **args, int i, int *s)
{
	int j;

	j = 0;
	while (args[i][j])
	{
		if ((args[i][j] == '$' && args[i][j + 1] && g_one != 1) ||
		(args[i][j] == '$' && args[i][j + 1] && g_one == 1 && g_two == 1))
		{
			j = first_condition(j, args, i, s);
			if (args[i][j] == '"' || args[i][j] == '\'')
				fill_command_string(args[i][j], *s);
		}
		else
			fill_command_string(args[i][j], *s);
		if (args[i][j] && (args[i][j] != '$' ||
		(g_one == 1 && args[i][j] == '$')))
			j++;
	}
	g_cmd->string[*s][g_cmd->string_len] = '\0';
}

int		cat_command_string(char **args, int *s)
{
	int j;
	int i;

	i = 0;
	while (args[i])
	{
		j = 0;
		if (args[i] && (args[i][j] == '<' || args[i][j] == '>'))
			if (redirection(args, 0) < 0)
				return (-1);
		while (args[i] && (args[i][j] == '<' || args[i][j] == '>'))
			i++;
		if (!args[i])
			break ;
		init_one_two();
		g_cmd->string[*s] = m_malloc(ft_strlen(args[i]) + 1);
		g_cmd->string[*s] = ft_strcpy(g_cmd->string[*s], args[i]);
		g_cmd->string_len = 0;
		to_while(args, i, s);
		(*s)++;
		i++;
	}
	g_cmd->string[*s] = NULL;
	return (1);
}
