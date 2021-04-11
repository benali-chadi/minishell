/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_command_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:04:47 by smhah             #+#    #+#             */
/*   Updated: 2021/04/10 18:32:14 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	fix_quotes_next_to_var(char **args, int i, int j, int *s)
{
	if ((args[i][j] == '"' || args[i][j] == '\''))
	{
		if ((args[i][j] == '"' && g_two != 2) || (args[i][j] == '\''
			&& g_one != 2))
			fill_command_string(args[i][j], *s);
	}
	else
		fill_command_string(args[i][j], *s);
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

void	replace_var(char **args, int i, int j, int *s)
{
	if (check_special_char(args[i][j]))
		g_print_next = 1;
	compare_var(g_str_var, args[i], *s);
	if (g_print_next)
		fill_command_string(g_next, *s);
}
