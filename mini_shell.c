/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:15:57 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/09 01:45:41 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	fill(int *j, int i)
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
	int	k;

	g_utils.cmd = g_commands;
	g_fd = m_malloc(j * sizeof(int *) + sizeof(int *));
	k = 0;
	while (g_utils.cmd != NULL)
	{
		exec_cmd(g_utils.cmd, k, j);
		g_utils.cmd = g_utils.cmd->next;
		k++;
	}
	while (wait(&g_return) != -1)
		;
	if (g_return && g_return < 255)
		g_return += 128;
	else if (g_return)
	{
		g_return = WEXITSTATUS(g_return);
		if (g_return == 13 || g_return == 21)
			g_return = 126;
	}
}

int	fill_and_execute(void)
{
	int	i;
	int	j;

	g_utils.m_split = mod_split(g_utils.line, ';');
	if (!g_utils.m_split)
		return (0);
	if (!check_white_spaces())
		return (0);
	i = 0;
	while (g_utils.m_split[i])
	{
		g_status = 1;
		g_commands = NULL;
		g_fd = NULL;
		j = 0;
		g_utils.p_split = mod_split(g_utils.m_split[i], '|');
		if (!g_utils.p_split)
			return (-1);
		if (!fill(&j, i))
			return (-1);
		execute(j);
		g_status = 0;
		i++;
	}
	return (1);
}

int	check_semicolon(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == ';')
	{
		ft_putstr_fd("minishell: syntax error near ", 2);
		ft_putstr_fd("unexpected token `;'\n", 2);
		g_utils.line = NULL;
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	init_stuff(env);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	stock_env(env);
	g_histo = NULL;
	getcwd(g_utils.pwd, 100);
	while (1)
	{
		print_prompt();
		if (!read_char(0, &g_utils.line))
			leave(NULL);
		if (check_semicolon(g_utils.line))
		{
			g_return = 258;
			continue ;
		}
		if (fill_and_execute() < 0)
			g_return = 258;
		g_utils.line = NULL;
	}
	return (0);
}
