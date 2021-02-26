/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:46:33 by smhah             #+#    #+#             */
/*   Updated: 2021/02/26 19:26:51 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int		check_special_char(char a)
{
	if (!is_alpha_digit(a) && a != '_' && a != '\''
		&& a != '\"' && a != '$' && a != '\\' && (g_next = a))
		return (1);
	return (0);
}

int		first_condition_cmd(int i, char *command)
{
	i++;
	g_var_cmd = m_malloc(ft_strlen(command));
	g_cmd_k = 0;
	while (command[i] && (is_alpha_digit(command[i]) || command[i] == '_'))
		g_var_cmd[g_cmd_k++] = command[i++];
	g_var_cmd[g_cmd_k] = '\0';
	if (ft_strcmpr(g_var_cmd, "?"))
	{
		g_str_return = ft_itoa(g_return);
		g_str_command = ft_realloc(g_str_command, ft_strlen(g_str_command)
			+ ft_strlen(command) + ft_strlen(g_str_return) + 1 + g_two);
		g_cmd_k = 0;
		while (g_str_return[g_cmd_k])
			g_str_command[g_command_len++] = g_str_return[g_cmd_k++];
		g_str_command[g_command_len] = '\0';
	}
	else
	{
		if (check_special_char(command[i]))
			g_print_next = 1;
		compare_var_command(g_var_cmd, command);
		if (g_print_next)
			fill_command(g_next);
	}
	return (i);
}

void	to_while_cmd(char *command, int i)
{
	while (command[i])
	{
		if ((command[i] == '$' && command[i + 1] && g_one != 1) ||
		(command[i] == '$' && command[i + 1] && g_one == 1 && g_two == 1))
		{
			g_print_next = 0;
			i = first_condition_cmd(i, command);
			if (command[i] == '"' || command[i] == '\'')
				fill_command(command[i]);
		}
		else
			fill_command(command[i]);
		if (command[i] && (command[i] != '$' ||
			(g_one == 1 && command[i] == '$')))
			i++;
		g_str_command[g_command_len] = '\0';
	}
}

char	*clean_command_1(char *command)
{
	int		quote;
	int		i;
	int		j;

	j = 0;
	i = 0;
	g_cmd_k = 0;
	quote = 0;
	g_str_command = m_malloc(ft_strlen(command) + 1);
	ft_strcpy(g_str_command, command);
	init_one_two();
	g_command_len = 0;
	to_while_cmd(command, i);
	return (clean_cmd(g_str_command));
}
