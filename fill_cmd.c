/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:08:59 by cbenali-          #+#    #+#             */
/*   Updated: 2021/02/15 19:31:51 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	fill_command(char a)
{
	g_str_command[g_command_len++] = a;
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
		if (mod_strlen(args) < 2 && split[i + 1] && split[i + 1][0] != '>' && split[i + 1][0] != '<')
		{
			args[0] = ft_strjoin(args[0], split[i + 1]);
			i++;
		}
		else if (split[i + 1] && (split[i][0] == '>' || split[i][0] == '<') && (split[i + 1][0] == '>' || split[i + 1][0] == '<'))
			ft_printf("minishell: syntax error near unexpected token `%c'\n", split[i + 1][0]);
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
		if (mod_strlen(args) < 2 && split[i + 1] && split[i + 1][0] != '>' && split[i + 1][0] != '<')
		{
			args[0] = ft_strjoin(args[0], split[i + 1]);
			i++;
		}
		else if (split[i + 1] && (split[i][0] == '>' || split[i][0] == '<') && (split[i + 1][0] == '>' || split[i + 1][0] == '<'))
		{
			ft_printf("minishell: syntax error near unexpected token `%c'\n", split[i + 1][0]);
		}
		if (cat_command_string(args, &s) < 0)
			return (-1);
		i++;
	}
	test(g_cmd);
	g_cmd->pipe = p;
	cmd_lstadd_back(&g_commands, g_cmd);
	return (1);
}
