/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:46:33 by smhah             #+#    #+#             */
/*   Updated: 2021/06/11 11:22:19 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	first_condition_cmd(int i, char *command)
{
	i++;
	g_all.var_cmd = m_malloc(ft_strlen(command));
	g_all.cmd_k = 0;
	while (command[i] && (is_alpha_digit(command[i]) || command[i] == '_'))
		g_all.var_cmd[g_all.cmd_k++] = command[i++];
	g_all.var_cmd[g_all.cmd_k] = '\0';
	if (ft_strcmpr(g_all.var_cmd, "?"))
	{
		g_all.s_ret = ft_itoa(g_all.returnn);
		g_all.s_cmd = ft_realloc(g_all.s_cmd, ft_strlen(g_all.s_cmd)
				+ ft_strlen(command) + ft_strlen(g_all.s_ret) + 1 + g_all.two);
		g_all.cmd_k = 0;
		while (g_all.s_ret[g_all.cmd_k])
			g_all.s_cmd[g_all.c_l++] = g_all.s_ret[g_all.cmd_k++];
		g_all.s_cmd[g_all.c_l] = '\0';
	}
	else
	{
		if (check_special_char(command[i]))
			g_all.print_next = 1;
		compare_var_command(g_all.var_cmd, command);
		if (g_all.print_next)
			fill_command(g_all.next);
	}
	return (i);
}

int	check_first_char_cmd(char a1, char a2, int *i, char *str)
{
	if (condition1(a1, a2, str, *i))
		return (1);
	else if ((a1 == '$' && a2 && g_all.one != 1 && is_digit(a2) && a2 != '.')
		|| (a1 == '$' && a2 && g_all.one == 1
			&& g_all.two == 1 && is_digit(a2) && a2 != '.'))
	{
		*i = *i + 2;
		return (2);
	}
	else if ((a1 == '$' && a2 && g_all.one != 1 && !is_digit(a2) && a2 == '.')
		|| (a1 == '$' && a2 && g_all.one == 1
			&& g_all.two == 1 && !is_digit(a2) && a2 == '.'))
	{
		fill_command(a1);
		*i = *i + 1;
	}
	return (0);
}

void	fix_cmd_quotes_next_to_var(char *command, int i)
{
	if ((command[i] == '"' || command[i] == '\''))
	{
		if ((command[i] == '"' && g_all.two != 2)
			|| (command[i] == '\'' && g_all.one != 2))
			fill_command(command[i]);
	}
	else
		fill_command(command[i]);
}

void	to_while_cmd(char *command, int i, int *indice)
{
	while (command[i])
	{
		if (check_first_char_cmd(command[i], command[i + 1], &i, command) == 1)
		{
			*indice = 1;
			g_all.print_next = 0;
			i = first_condition_cmd(i, command) - 1;
		}
		else if (check_first_char_cmd(command[i],
				command[i + 1], &i, command) == 2)
			fill_command(command[i]);
		else
		{
			if (check_char_first(&command, 0, i))
				fill_command(command[i]);
		}
		if (check_if_can_increment(&command, 0, i))
			i++;
		g_all.s_cmd[g_all.c_l] = '\0';
	}
}

char	*clean_command_1(char *command)
{
	int		quote;
	int		i;
	int		j;
	int		indice;

	indice = 0;
	j = 0;
	i = 0;
	g_all.cmd_k = 0;
	quote = 0;
	g_all.s_cmd = m_malloc(ft_strlen(command) + 1);
	ft_strcpy(g_all.s_cmd, command);
	init_one_two();
	g_all.c_l = 0;
	to_while_cmd(command, i, &indice);
	return (g_all.s_cmd);
}
