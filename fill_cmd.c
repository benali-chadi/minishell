/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:08:59 by cbenali-          #+#    #+#             */
/*   Updated: 2021/01/29 18:45:49 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*clean_command(char *command)
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
		if (command[i] == '\'')
		{
			if (quote == 0)
				quote = 1;
			else if (quote == 1)
				quote = 0;
			else
				str[k++] = command[i];
		}
		else if (command[i] == '"')
		{
			if (quote == 0)
				quote = 2;
			else if (quote == 2)
				quote = 0;
			else
				str[k++] = command[i];
		}
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
		if (redirection(args, 0) < 0)
			return (-1);
		i++;
	}
	g_cmd->command = m_malloc(ft_strlen(split[i]) + 1);
	ft_strcpy(g_cmd->command, clean_command(split[i]));
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
