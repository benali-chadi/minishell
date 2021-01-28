/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:15:57 by cbenali-          #+#    #+#             */
/*   Updated: 2021/01/28 15:12:53 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int		fill(int *j, int i)
{
	if (mod_strlen(g_utils.p_split) > 1)
	{
		while (g_utils.p_split[*j])
		{
			g_utils.c_split = mod_split(g_utils.p_split[*j], ' ');
			if (fill_cmd(g_utils.c_split, 1) < 0)
				return (0);
			(*j)++;
		}
	}
	else
	{
		g_utils.c_split = mod_split(g_utils.m_split[i], ' ');
		if (fill_cmd(g_utils.c_split, 0) < 0)
			return (0);
	}
	return (1);
}

void	execute(int j)
{
	int k;

	g_utils.cmd = g_commands;
	g_fd = m_malloc(j * sizeof(int *) + 1);
	k = 0;
	while (g_utils.cmd != NULL)
	{
		exec_cmd(g_utils.cmd, k, j);
		g_utils.cmd = g_utils.cmd->next;
		k++;
	}
	while (wait(&g_return) != -1)
		;
	g_return = WEXITSTATUS(g_return);
	if (g_return == 255)
		g_return = 127;
}

void	fill_and_execute(void)
{
	int		i;
	int		j;

	g_utils.m_split = mod_split(g_utils.line, ';');
	i = 0;
	while (g_utils.m_split[i])
	{
		g_status = 1;
		g_commands = NULL;
		g_fd = NULL;
		j = 0;
		g_utils.p_split = mod_split(g_utils.m_split[i], '|');
		if (!fill(&j, i))
			break ;
		execute(j);
		g_status = 0;
		i++;
	}
	free(g_utils.line);
	g_utils.line = NULL;
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	init_cnt();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	stock_env(env);
	g_utils.env = env;
	while (1)
	{
		ft_putstr_fd("\033[0;32mCS\033[0;31m@minishell \033[0m", 1);
		if (!(gnl(0, &g_utils.line)))
		{
			to_free();
			exit(0);
		}
		if (g_utils.line[0] == ';')
		{
			ft_putstr_fd("syntax error near unexpected token `;'\n", 2);
			free(g_utils.line);
			g_utils.line = NULL;
			continue;
		}
		fill_and_execute();
	}
	return (0);
}
