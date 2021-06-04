/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:08:59 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/04 06:52:25 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	check_special_char(char a)
{
	if (!is_alpha_digit(a) && a != '_' && a != '\''
		&& a != '\"' && a != '$' && a != '\\' && (g_next = a))
		return (1);
	return (0);
}

int	check_end_1(char **args, char **split, int *i)
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
		printf("minishell: syntax error near unexpected token `%c'\n", a2);
		return (0);
	}
	if (redirection(args, 0) < 0)
		return (0);
	return (1);
}

int	fill_cmd_helper(char **split)
{
	char	**args;
	int		i;

	i = 0;
	g_cmd = m_malloc(sizeof(t_command_info));
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
	g_cmd->options = NULL;
	if (split[i] && split[i][0] == '-')
	{
		g_cmd->options = m_malloc(ft_strlen(split[i]) + 1);
		ft_strcpy(g_cmd->options, split[i]);
		i++;
	}
	return (i);
}

int		check_last_char(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	if (str[i - 1] && (str[i - 1] == '>' || str[i - 1] == '<'))
		return (1);
	return (0);
}

int		check_end_2(char **args, char **split, int *i, int *s)
{
	char	a1;
	char	a2;

	a1 = split[*i][0];
	a2 = '\0';
	if (split[*i + 1])
		a2 = split[*i + 1][0];
	if ((mod_strlen(args) < 3 && split[*i + 1] && a2 != '>' && a2 != '<'
	&& (a1 == '>' || a1 == '<' )))
	{
		printf("ENTER\n");
		args[0] = ft_strjoin(args[0], split[*i + 1]);
		*i = *i + 1;
	}
	else if ((mod_strlen(args) < 3 && split[*i + 1] && a2 != '>' && a2 != '<'
		&&  check_last_char(split[*i])))
	{
		printf("ENTER2\n");
		args[1] = ft_strjoin(args[1], split[*i + 1]);
		*i = *i + 1;
	}
	else if (split[*i + 1] && (a1 == '>' || a1 == '<')
		&& (a2 == '>' || a2 == '<'))
	{
		printf("minishell: syntax error near unexpected token `%c'\n", a2);
		return (0);
	}
	int oo = 0;
	while(args[oo])
		printf("args->[%s]\n", args[oo++]);
	if (cat_command_string(args, s) < 0)
		return (0);
	return (1);
}

int	fill_cmd(char **split, int p)
{
	char	**args;
	int		i;
	int		s;

	i = fill_cmd_helper(split);
	if (!*split || i < 0)
		return (-1);
	s = 0;
	g_cmd->string[0] = NULL;
	while (split[i])
	{
		args = mod_split_red(split[i], "><");
		if (!check_end_2(args, split, &i, &s))
			return (-1);
		i++;
	}
	if (s)
		add_last_cmd(g_cmd->string[s - 1], "_");
	else if (g_cmd->options)
		add_last_cmd(g_cmd->options, "_");
	else
		add_last_cmd(g_cmd->command, "_");
	test(g_cmd);
	g_cmd->pipe = p;
	cmd_lstadd_back(&g_commands, g_cmd);
	return (1);
}
