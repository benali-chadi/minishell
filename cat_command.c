/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:21:41 by cbenali-          #+#    #+#             */
/*   Updated: 2021/05/15 23:01:16 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	first_condition(int j, char **args, int i, int *s)
{
	g_print_next = 0;
	j++;
	g_str_var = m_malloc(ft_strlen(args[i]));
	g_var_k = 0;
	while (args[i][j] && (is_alpha_digit(args[i][j]) || args[i][j] == '_'))
		g_str_var[g_var_k++] = args[i][j++];
	g_str_var[g_var_k] = '\0';
	if (ft_strcmpr(g_str_var, "?"))
	{
		g_str_return = ft_itoa(g_return);
		g_cmd->string[*s] = ft_realloc(g_cmd->string[*s],
				ft_strlen(g_cmd->string[*s]) + ft_strlen(args[i])
				+ ft_strlen(g_str_return) + 1 + g_two);
		g_var_k = 0;
		while (g_str_return[g_var_k])
		{
			g_cmd->string[*s][g_cmd->string_len++] = g_str_return[g_var_k];
			g_var_k++;
		}
		g_cmd->string[*s][g_cmd->string_len++] = '\0';
	}
	else
		replace_var(args, i, j, s);
	return (j);
}

int	condition1(char a1, char a2)
{
	if ((a1 == '$' && a2 && g_one != 1 && !is_digit(a2) && a2 != '.')
		|| (a1 == '$' && a2 && g_one == 1
			&& g_two == 1 && !is_digit(a2) && a2 != '.'))
		return (1);
	return (0);
}

int	check_first_char(char **args, int *i, int *j)
{
	char	a1;
	char	a2;

	a1 = args[*i][*j];
	a2 = '\0';
	if (args[*i][*j + 1])
		a2 = args[*i][*j + 1];
	if (condition1(a1, a2))
	{
		if (a1 == '$' && a2 == '"' && !args[*i][*j + 2])
			return (0);
		return (1);
	}
	else if ((a1 == '$' && a2 && g_one != 1 && is_digit(a2) && a2 != '.')
		|| (a1 == '$' && a2 && g_one == 1
			&& g_two == 1 && is_digit(a2) && a2 != '.'))
	{
		*j = *j + 2;
		return (2);
	}
	else if ((a1 == '$' && a2 && g_one != 1 && !is_digit(a2) && a2 == '.')
		|| (a1 == '$' && a2 && g_one == 1
			&& g_two == 1 && !is_digit(a2) && a2 == '.'))
	{
		fill_command_string(a1, *i);
		*j = *j + 1;
	}
	return (0);
}

void	to_while(char **args, int i, int *s)
{
	int	j;

	j = 0;
	while (args[i][j])
	{
		if (check_first_char(args, &i, &j) == 1)
		{
			if(args[i][j] == '$' && j > 0 && (args[i][j - 1] == '"' || args[i][j - 1] == '\'') && !g_two)
				g_cmd->indice[*s] = 0;
			else if (!g_two)
			{
				g_cmd->indice[*s] = 1;
			}
			j = first_condition(j, args, i, s);
			if (args[i][j] == '"' || args[i][j] == '\'')
				check_quots_after_dollar(args, i, j, s);
		}
		else if (check_first_char(args, &i, &j) == 2)
		{
			fill_command_string(args[i][j], *s);
		}
		else
		{
			fix_quotes_next_to_var(args, i, j, s);
		}
		if (args[i][j] && (args[i][j] != '$'
				|| ((g_one == 1 && args[i][j] == '$') || (args[i][j] == '$' && ((args[i][j + 1] == '"' && args[i][j + 2] == '\0' ) || args[i][j + 1] == '\0')))))
		{
			j++;
		}
	}
	g_cmd->string[*s][g_cmd->string_len] = '\0';
}

int	cat_command_string(char **args, int *s)
{
	int	j;
	int	i;

	i = 0;
	while (args[i])
	{
		g_cmd->indice[*s] = 0;
		j = 0;
		if (args[i] && (args[i][j] == '<' || args[i][j] == '>'))
			if (redirection(args, i) < 0)
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
