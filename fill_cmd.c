/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:08:59 by cbenali-          #+#    #+#             */
/*   Updated: 2021/02/24 17:25:09 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int		check_end_1(char **args, char **split, int *i)
{
	char	a1;
	char	a2;
	int		s;

	s = 0;
	a1 = split[*i][0];
	if (split[*i + 1])
		a2 = split[*i + 1][0];
	if (mod_strlen(args) < 2 && split[*i + 1] && a2 != '>'
		&& a2 != '<' && (a1 == '>' || a1 == '<'))
	{
		args[0] = ft_strjoin(args[0], split[*i + 1]);
		*i += 1;
	}
	else if (split[*i + 1] && (a1 == '>' || a1 == '<')
		&& (a2 == '>' || a2 == '<'))
	{
		ft_printf("minishell: syntax error near unexpected token `%c'\n", a2);
		return (0);
	}
	if (redirection(args, 0) < 0)
		return (0);
	return (1);
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
		if (!check_end_1(args, split, &i))
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

int		check_end_2(char **args, char **split, int *i, int *s)
{
	char	a1;
	char	a2;

	a1 = split[*i][0];
	a2 = '\0';
	if (split[*i + 1])
		a2 = split[*i + 1][0];
	if (mod_strlen(args) < 2 && split[*i + 1] && a2 != '>' && a2 != '<'
	&& (a1 == '>' || a1 == '<'))
	{
		args[0] = ft_strjoin(args[0], split[*i + 1]);
		*i = *i + 1;
	}
	else if (split[*i + 1] && (a1 == '>' || a1 == '<')
		&& (a2 == '>' || a2 == '<'))
	{
		ft_printf("minishell: syntax error near unexpected token `%c'\n", a2);
		return (0);
	}
	if (cat_command_string(args, s) < 0)
		return (0);
	return (1);
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
		if (!check_end_2(args, split, &i, &s))
			return (-1);
		i++;
	}
	test(g_cmd);
	g_cmd->pipe = p;
	cmd_lstadd_back(&g_commands, g_cmd);
	return (1);
}
