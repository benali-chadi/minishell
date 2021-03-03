/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:21:41 by cbenali-          #+#    #+#             */
/*   Updated: 2021/03/03 17:10:50 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	fill_command_string(char a, int i)
{
	g_cmd->string[i][g_cmd->string_len++] = a;
	if (a == '\'')
	{
		if (g_one)
			g_one = 0;
		else
			g_one = 1;
	}
	if (a == '"')
	{
		if (g_two)
			g_two = 0;
		else
			g_two = 1;
	}
}

void	init_one_two(void)
{
	g_one = 0;
	g_two = 0;
}

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
	{
		if (check_special_char(args[i][j]))
			g_print_next = 1;
		compare_var(g_str_var, args[i], *s);
		if (g_print_next)
			fill_command_string(g_next, *s);
	}
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
		return (1);
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

void	change_one_two(char a)
{
	if (a == '\'')
	{
		if (g_one)
			g_one = 0;
		else
			g_one = 2;
	}
	if (a == '"')
	{
		if (g_two)
			g_two = 0;
		else
			g_two = 2;
	}
}

void	to_while(char **args, int i, int *s)
{
	int	j;
	int	f;

	j = 0;
	f = 0;
	while (args[i][j])
	{
		if (check_first_char(args, &i, &j) == 1)
		{
			j = first_condition(j, args, i, s);
			if (args[i][j] == '"' || args[i][j] == '\'')
			{
				f = 1;
				change_one_two(args[i][j]);
			}
			g_cmd->indice[*s] = 1;
		}
		else if (check_first_char(args, &i, &j) == 2)
			fill_command_string(args[i][j], *s);
		else
		{
			if((args[i][j] == '"' || args[i][j] == '\''))
			{
				if((args[i][j] == '"' && g_two != 2) || (args[i][j] == '\'' && g_one != 2))
					fill_command_string(args[i][j], *s);
			}
			else
				fill_command_string(args[i][j], *s);
		}
		if (args[i][j] && (args[i][j] != '$'
				|| (g_one == 1 && args[i][j] == '$')))
			j++;
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
	add_last_cmd(g_cmd->string[*s - 1]);
	return (1);
}
