/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:08:59 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/10 16:47:24 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	check_end_1(char **args, char **split, int *i)
{
	char	a1;
	char	a2;

	a1 = split[*i][0];
	a2 = '\0';
	if (split[*i + 1])
		a2 = split[*i + 1][0];
	if (split[*i + 1] && (ft_strcmpr(split[*i], ">")
			|| ft_strcmpr(split[*i], "<") || ft_strcmpr(split[*i], ">>"))
		&& a2 != '>' && a2 != '<' )
		join_lonely_red(args, split, i);
	else if ((split[*i + 1] && a2 != '>' && a2 != '<'
			&& check_last_char(split[*i])))
		join_friendly_red(args, split, i);
	else if (split[*i + 1] && check_if_at_the_last(split[*i])
		&& (a2 == '>' || a2 == '<'))
	{
		printf("minishell: syntax error near unexpected token `%c'\n", a2);
		return (0);
	}
	if (redirection(args, 0) < 0)
		return (0);
	return (1);
}

int	continue_helper(int i, char ***split)
{
	if (!(*split)[i])
	{
		g_cmd->command = ft_strdup("");
		g_cmd->options = NULL;
		return (i);
	}
	g_cmd->command = m_malloc(ft_strlen((*split)[i]) + 1);
	ft_strcpy(g_cmd->command, (*split)[i]);
	i++;
	g_cmd->options = NULL;
	if ((*split)[i] && (*split)[i][0] == '-')
	{
		g_cmd->options = m_malloc(ft_strlen((*split)[i]) + 1);
		ft_strcpy(g_cmd->options, (*split)[i]);
		i++;
	}
	//printf("g_cmd=|%s|\n", g_cmd->command);
	return (i);
}

int	fill_cmd_helper(char ***split)
{
	char	**args;
	int		i;
	int		j;

	j = 0;
	i = 0;
	g_cmd = m_malloc(sizeof (t_command_info));
	g_cmd->reds.in_num = 0;
	g_cmd->reds.out_num = 0;
	g_cmd_args = m_malloc(sizeof(char *) * 2);
	g_cmd_args[0] = NULL;
	(*split)[i] = clean_command_1(*split[i]);
	// g_cmd_args = mod_split(clean_command_1((*split)[i]), ' ');
	// while(g_cmd_args[j])
	// 	printf("args:|%s|\n", g_cmd_args[j++]);
	if(g_cmd_args[0])
		(*split) = join_2_tab(g_cmd_args, &(*split)[i + 1]);
	while ((*split)[i] && ((*split)[i][0] == '<' || (*split)[i][0] == '>'))
	{
		args = mod_split_red((*split)[i], "><");
		if (!check_end_1(args, (*split), &i))
			return (-1);
		i++;
	}
	i = continue_helper(i, split);
	return (i);
}

int	check_end_2(char **args, char **split, int *i, int *s)
{
	char	a1;
	char	a2;

	a1 = split[*i][0];
	a2 = '\0';
	if (split[*i + 1])
		a2 = split[*i + 1][0];
	if (split[*i + 1] && (ft_strcmpr(split[*i], ">")
			|| ft_strcmpr(split[*i], "<") || ft_strcmpr(split[*i], ">>"))
		&& a2 != '>' && a2 != '<' )
		join_lonely_red(args, split, i);
	else if ((split[*i + 1] && a2 != '>' && a2 != '<'
			&& check_last_char(split[*i])))
		join_friendly_red(args, split, i);
	else if (split[*i + 1] && check_if_at_the_last(split[*i])
		&& (a2 == '>' || a2 == '<'))
	{
		printf("minishell: syntax error near unexpected token `%c'\n", a2);
		return (0);
	}
	if (cat_command_string(args, s) < 0)
		return (0);
	return (1);
}

int	fill_cmd(char **split, int p)
{
	char	**args;
	int		i;
	int		s;

	if (!init_fill_cmd(&split, &i, &s))
		return (-1);
	while (split[++i])
	{
		args = mod_split_red(split[i], "><");
		if (g_move_and_pass == 1 || g_move_and_pass == 2)
		{
			g_move_and_pass = 0;
			if (!check_end_2(&args[1], split, &i, &s))
				return (-1);
		}
		else
		{
			if (!check_end_2(args, split, &i, &s))
				return (-1);
		}
	}
	continue_our_road(s, p);
	return (1);
}
