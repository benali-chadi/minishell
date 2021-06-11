/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:15:57 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/11 20:48:37 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	fill(int *j, int i)
{
	*j = 0;
	if (mod_strlen(g_all.utils.p_split) > 1)
	{
		while (g_all.utils.p_split[*j]
			&& !check_if_void(g_all.utils.p_split[*j]))
		{
			g_all.utils.c_split = mod_split(g_all.utils.p_split[*j], ' ');
			if (fill_cmd(g_all.utils.c_split, 1) < 0)
				return (0);
			(*j)++;
		}
	}
	else
	{
		g_all.utils.c_split = mod_split(g_all.utils.m_split[i], ' ');
		if (fill_cmd(g_all.utils.c_split, 0) < 0)
			return (0);
	}
	return (1);
}

void	execute(int j)
{
	int	k;

	g_all.utils.cmd = g_all.commands;
	g_all.fd = m_malloc(j * sizeof(int *) + sizeof(int *));
	k = 0;
	while (g_all.utils.cmd != NULL)
	{
		exec_cmd(g_all.utils.cmd, k, j);
		g_all.utils.cmd = g_all.utils.cmd->next;
		k++;
	}
	while (wait(&g_all.returnn) != -1)
		;
	if (g_all.returnn && g_all.returnn < 255)
		g_all.returnn += 128;
	else if (g_all.returnn)
	{
		g_all.returnn = WEXITSTATUS(g_all.returnn);
		if (g_all.returnn == 13 || g_all.returnn == 21)
			g_all.returnn = 126;
		if (g_all.returnn == 2)
			g_all.returnn = 127;
	}
}

int	fill_and_execute(void)
{
	int	i;
	int	j;

	if (!chck_spc(g_all.utils.line, ';'))
		return (-1);
	g_all.utils.m_split = mod_split(g_all.utils.line, ';');
	if (!g_all.utils.m_split)
		return (-1);
	i = -1;
	while ((g_all.utils.m_split[++i]) && !check_if_void(g_all.utils.m_split[i]))
	{
		g_all.status = 1;
		g_all.commands = NULL;
		g_all.fd = NULL;
		g_all.utils.p_split = mod_split(g_all.utils.m_split[i], '|');
		if ((!g_all.utils.p_split) || !chck_spc(g_all.utils.m_split[i], '|'))
			return (-1);
		if (check_solo_at_the_first(g_all.utils.m_split[i]))
			return (-1);
		if (!fill(&j, i))
			return (-1);
		execute(j);
		g_all.status = 0;
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
		if (str[i + 1] && str[i + 1] == ';')
			ft_putstr_fd("unexpected token `;;'\n", 2);
		else
			ft_putstr_fd("unexpected token `;'\n", 2);
		g_all.utils.line = NULL;
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
	g_all.histo = NULL;
	getcwd(g_all.utils.pwd, 100);
	while (1)
	{
		print_prompt();
		if (!read_char(0, &g_all.utils.line))
			leave(NULL);
		if (check_semicolon(g_all.utils.line))
		{
			g_all.returnn = 258;
			continue ;
		}
		if (fill_and_execute() < 0)
			g_all.returnn = 258;
		g_all.utils.line = NULL;
	}
	return (0);
}
