/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:08:59 by cbenali-          #+#    #+#             */
/*   Updated: 2021/02/01 15:04:49 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	fill_command(char a)
{
	str_command[command_len++] = a;
	if (a == '\'')
		g_one = g_one == 1 ? 0 : 1;
	if (a == '"')
		g_two = g_two == 1 ? 0 : 1;
}

int		sing_or_doub_q(char *str, int *k, int quote, char q)
{
	if (quote == 0 && q == '\'')
		return (1);
	else if (quote == 0 && q == '"')
		return (2);
	else if ((quote == 2 && q == '"') || (quote == 1 && q == '\''))
		return (0);
	else
	{
		str[(*k)++] = q;
		return (quote);
	}
}

char	*clean_command_2(char *command)
{
	char	*str;
	int		quote;
	int		i;
	int		k;

	i = 0;
	k = 0;
	quote = 0;
	str = m_malloc(ft_strlen(command));
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '"')
			quote = sing_or_doub_q(str, &k, quote, command[i]);
		else
			str[k++] = command[i];
		i++;
	}
	return (str);
}

char	*clean_command_1(char *command)
{
	char	*var;
	int		quote;
	int		i;
	int		k;
	int		j;

	j = 0;
	i = 0;
	k = 0;
	quote = 0;
	str_command = m_malloc(ft_strlen(command) + 1);
	ft_strcpy(str_command, command);
	init_one_two();
	command_len = 0;
	while (command[i])
	{
		if ((command[i] == '$' && command[i + 1] && g_one != 1) ||
		(command[i] == '$' && command[i + 1] && g_one == 1 && g_two == 1))
		{
			i++;
			var = m_malloc(ft_strlen(command));
			k = 0;
			while(is_alpha_digit(command[i]) && command[i] != '$' && command[i])
				var[k++] = command[i++];
			var[k] = '\0';
			if (ft_strcmpr(var, "?"))
			{
				g_str_return = ft_itoa(g_return);
				str_command = ft_realloc(str_command, ft_strlen(str_command) + ft_strlen(command) + ft_strlen(g_str_return) + 1 + g_two);
				k = 0;
				while(g_str_return[k])
					str_command[command_len++] = g_str_return[k++];
				str_command[command_len] = '\0';
			}
			else
			{
				compare_var_command(var, command);
			}
		}
		else
			fill_command(command[i]);
		if (command[i] && (command[i] != '$' || (g_one == 1 && command[i] == '$')))
				i++;
	}
	i = 0;
	return(clean_command_2(str_command));
}

int		fill_cmd_helper(char **split)
{
	char	**args;
	int		i;

	i = 0;
	g_cmd = malloc(sizeof(t_command_info));
	g_cmd->reds.in_num = 0;
	g_cmd->reds.out_num = 0;
	while (split[i] && (split[i][0] == '<' || split[i][0] == '>'))
	{
		args = mod_split_red(split[i], "><");
		if (redirection(args, 0) < 0)
			return (-1);
		i++;
	}
	g_cmd->command = m_malloc(ft_strlen(split[i]) + 1);
	ft_strcpy(g_cmd->command, clean_command_1(split[i]));
	i++;
	if (split[i] && split[i][0] == '-')
	{
		g_cmd->options = m_malloc(ft_strlen(split[i]) + 1);
		ft_strcpy(g_cmd->options, split[i]);
		i++;
	}
	return (i);
}

int		fill_cmd(char **split, int p)
{
	char	**args;
	int		i;
	int		s;

	if (!*split)
		return (0);
	if ((i = fill_cmd_helper(split)) < 0)
		return (-1);
	s = 0;
	while (split[i])
	{
		args = mod_split_red(split[i], "><");
		if (cat_command_string(args, &s) < 0)
			return (-1);
		i++;
	}
	test(g_cmd);
	g_cmd->pipe = p;
	cmd_lstadd_back(&g_commands, g_cmd);
	return (1);
}
