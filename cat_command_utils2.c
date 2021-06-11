/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_command_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:25:55 by smhah             #+#    #+#             */
/*   Updated: 2021/06/11 11:54:00 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	check_quots_after_dollar(char **args, int i, int j, int *s)
{
	if (g_all.two == 1)
		fill_command_string(args[i][j], *s);
	else
		change_one_two(args[i][j]);
}

int	check_if_print(char *str, int j)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	if (g_all.one == 1)
		return (0);
	while (str[i])
	{
		if (i == j)
		{
			if (c == 0)
				return (0);
			if (c % 2 == 0)
				return (0);
			return (1);
		}
		if (str[i] != '\\')
			c = 0;
		if (str[i] == '\\')
			c++;
		i++;
	}
	return (0);
}

int	check_quotes_and_ret(char **args, int i, int j)
{
	if (g_all.one != 1 && j > 0 && check_if_print(args[i], j))
		return (1);
	if (args[i][j] == '"' && g_all.one != 1 && !check_if_print(args[i], j))
	{
		if (g_all.one == 1)
			return (1);
		switch_one_two(args[i][j]);
		return (0);
	}
	if (args[i][j] == '\'' && g_all.two != 1 && !check_if_print(args[i], j))
	{
		if (g_all.two == 1)
			return (1);
		switch_one_two(args[i][j]);
		return (0);
	}
	return (1);
}

int	check_char_first(char **args, int i, int j)
{
	int	e;

	e = 0;
	if (args[i][j] == '\\' && g_all.one != 1 && g_all.two != 1)
	{
		if (j == 0)
			return (0);
		if (!check_if_print(args[i], j))
			return (0);
	}
	else if (args[i][j] == '\\' && g_all.one != 1)
	{
		if (args[i][j + 1] && !is_special(args[i][j + 1]))
			return (1);
		if (j > 0 && args[i][j - 1] == '\\'
			&& check_if_print(args[i], j) && args[i][j + 1])
			return (1);
		else if (j > 0 && args[i][j - 1] == '\\')
			return (0);
		if (args[i][j + 1] && is_special(args[i][j + 1]))
			return (0);
	}
	return (check_quotes_and_ret(args, i, j));
}

void	switch_one_two(char a)
{
	if (a == '\'' && g_all.two != 1)
	{
		if (g_all.one)
			g_all.one = 0;
		else
			g_all.one = 1;
	}
	if (a == '"' && g_all.one != 1)
	{
		if (g_all.two)
			g_all.two = 0;
		else
			g_all.two = 1;
	}
}
