/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:46:33 by smhah             #+#    #+#             */
/*   Updated: 2021/03/04 15:10:50 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

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

int		check_first_char_cmd(char a1, char a2, int *i)
{
	if (condition1(a1, a2))
		return (1);
	else if ((a1 == '$' && a2 && g_one != 1 && is_digit(a2) && a2 != '.')
		|| (a1 == '$' && a2 && g_one == 1
				&& g_two == 1 && is_digit(a2) && a2 != '.'))
	{
		*i = *i + 2;
		return (2);
	}
	else if ((a1 == '$' && a2 && g_one != 1 && !is_digit(a2) && a2 == '.')
		|| (a1 == '$' && a2 && g_one == 1
				&& g_two == 1 && !is_digit(a2) && a2 == '.'))
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
		if ((command[i] == '"' && g_two != 2) ||
		(command[i] == '\'' && g_one != 2))
			fill_command(command[i]);
	}
	else
		fill_command(command[i]);
}

void	to_while_cmd(char *command, int i, int *indice)
{
	while (command[i])
	{
		if (check_first_char_cmd(command[i], command[i + 1], &i) == 1)
		{
			*indice = 1;
			g_print_next = 0;
			i = first_condition_cmd(i, command);
			if (command[i] == '"' || command[i] == '\'')
				change_one_two(command[i]);
		}
		else if (check_first_char_cmd(command[i], command[i + 1], &i) == 2)
			fill_command(command[i]);
		else
			fix_cmd_quotes_next_to_var(command, i);
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
	int		indice;

	indice = 0;
	j = 0;
	i = 0;
	g_cmd_k = 0;
	quote = 0;
	g_str_command = m_malloc(ft_strlen(command) + 1);
	ft_strcpy(g_str_command, command);
	init_one_two();
	g_command_len = 0;
	to_while_cmd(command, i, &indice);
	if (indice == 1)
		return (g_str_command);
	return (clean_cmd(g_str_command));
}
