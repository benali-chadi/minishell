/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:21:41 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/11 11:53:31 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	first_condition(int j, char **args, int i, int *s)
{
	g_all.print_next = 0;
	j++;
	g_all.str_var = m_malloc(ft_strlen(args[i]));
	g_all.var_k = 0;
	while (args[i][j] && (is_alpha_digit(args[i][j]) || args[i][j] == '_'))
		g_all.str_var[g_all.var_k++] = args[i][j++];
	g_all.str_var[g_all.var_k] = '\0';
	if (ft_strcmpr(g_all.str_var, "?"))
	{
		g_all.s_ret = ft_itoa(g_all.returnn);
		g_all.cmd->string[*s] = ft_realloc(g_all.cmd->string[*s],
				ft_strlen(g_all.cmd->string[*s]) + ft_strlen(args[i])
				+ ft_strlen(g_all.s_ret) + 1 + g_all.two);
		g_all.var_k = 0;
		while (g_all.s_ret[g_all.var_k])
		{
			g_all.cmd->string[*s][g_all.cmd->string_len++]
				= g_all.s_ret[g_all.var_k];
			g_all.var_k++;
		}
		g_all.cmd->string[*s][g_all.cmd->string_len++] = '\0';
	}
	else
		replace_var(args, i, j, s);
	return (j);
}

int	condition1(char a1, char a2, char *str, int e)
{
	(void)e;
	(void)str;
	if (a1 == '$' && a2 && g_all.one != 1 && !is_digit(a2)
		&& a2 != '.')
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
	if (condition1(a1, a2, args[*i], *j))
	{
		if (a1 == '$' && a2 == '"' && !args[*i][*j + 2])
			return (0);
		return (1);
	}
	else if ((a1 == '$' && a2 && g_all.one != 1 && is_digit(a2) && a2 != '.')
		|| (a1 == '$' && a2 && g_all.one == 1
			&& g_all.two == 1 && is_digit(a2) && a2 != '.'))
	{
		*j = *j + 2;
		return (2);
	}
	else if ((a1 == '$' && a2 && g_all.one != 1 && !is_digit(a2) && a2 == '.')
		|| (a1 == '$' && a2 && g_all.one == 1
			&& g_all.two == 1 && !is_digit(a2) && a2 == '.'))
		*j = *j + 1;
	return (0);
}

void	to_while(char **args, int i, int *s)
{
	int	j;

	j = 0;
	while (args[i][j])
	{
		if (!check_if_print(args[i], j) && check_first_char(args, &i, &j) == 1)
			j = first_condition(j, args, i, s) - 1;
		else if (!check_if_print(args[i], j)
			&& check_first_char(args, &i, &j) == 2)
			fill_command_string(args[i][j], *s);
		else
		{
			if (check_char_first(args, i, j))
				fill_command_string(args[i][j], *s);
		}
		if (check_if_can_increment(args, i, j))
			j++;
	}
	g_all.cmd->string[*s][g_all.cmd->string_len] = '\0';
}

int	cat_command_string(char **args, int *s)
{
	int	j;
	int	i;

	i = 0;
	while (args[i])
	{
		g_all.cmd->indice[*s] = 0;
		j = 0;
		if (args[i] && (args[i][j] == '<' || args[i][j] == '>'))
			if (redirection(args, i) < 0)
				return (-1);
		while (args[i] && (args[i][j] == '<' || args[i][j] == '>'))
			i++;
		if (!args[i])
			break ;
		init_one_two();
		g_all.cmd->string[*s] = m_malloc(ft_strlen(args[i]) + 1);
		g_all.cmd->string[*s] = ft_strcpy(g_all.cmd->string[*s], args[i]);
		g_all.cmd->string_len = 0;
		to_while(args, i, s);
		(*s)++;
		i++;
	}
	g_all.cmd->string[*s] = NULL;
	return (1);
}
