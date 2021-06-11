/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_command_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:04:47 by smhah             #+#    #+#             */
/*   Updated: 2021/06/11 12:31:00 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	fix_quotes_next_to_var(char **args, int i, int j, int *s)
{
	fill_command_string(args[i][j], *s);
}

void	change_one_two(char a)
{
	if (a == '\'' && g_all.two != 1)
	{
		if (g_all.one)
			g_all.one = 0;
		else
			g_all.one = 2;
	}
	if (a == '"' && g_all.one != 1)
	{
		if (g_all.two)
			g_all.two = 0;
		else
			g_all.two = 2;
	}
}

void	fill_command_string(char a, int i)
{
	g_all.cmd->string[i][g_all.cmd->string_len++] = a;
	g_all.cmd->string[i][g_all.cmd->string_len] = '\0';
}

void	init_one_two(void)
{
	g_all.one = 0;
	g_all.two = 0;
}

void	replace_var(char **args, int i, int j, int *s)
{
	if (check_special_char(args[i][j]))
		g_all.print_next = 1;
	compare_var(g_all.str_var, args[i], *s);
}
