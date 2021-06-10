/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:00:04 by smhah             #+#    #+#             */
/*   Updated: 2021/06/10 19:41:27 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	check_special_char(char a)
{
	if (!is_alpha_digit(a) && a != '_' && a != '\''
		&& a != '\"' && a != '$' && a != '\\')
	{
		g_all.next = a;
		return (1);
	}
	return (0);
}

int	is_red(char a)
{
	if (a == '>' || a == '<')
		return (1);
	return (0);
}

char	**join_2_tab(char **tab1, char **tab2)
{
	char	**tabtab;
	int		i;
	int		j;

	j = 0;
	i = 0;
	tabtab = (char **)m_malloc(mod_strlen(tab1)
			* sizeof(char *) + mod_strlen(tab2)
			* sizeof(char *) + sizeof(char *));
	while (tab1[i] != NULL)
	{
		tabtab[i] = ft_strdup(tab1[i]);
		i++;
	}
	while (tab2[j] != NULL)
	{
		tabtab[i++] = ft_strdup(tab2[j++]);
	}
	tabtab[i] = NULL;
	return (tabtab);
}

void	continue_our_road(int s, int p)
{
	if (s)
		add_last_cmd(g_all.cmd->string[s - 1], "_");
	else if (g_all.cmd->options)
		add_last_cmd(g_all.cmd->options, "_");
	else
		add_last_cmd(g_all.cmd->command, "_");
	test(g_all.cmd);
	g_all.cmd->pipe = p;
	cmd_lstadd_back(&g_all.commands, g_all.cmd);
}

int	init_fill_cmd(char ***split, int *i, int *s)
{
	*i = fill_cmd_helper(split) - 1;
	if (!*split || *i < 0)
		return (0);
	*s = 0;
	g_all.cmd->string[0] = NULL;
	g_all.move_and_pass = 0;
	return (1);
}
