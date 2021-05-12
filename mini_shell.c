/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:15:57 by cbenali-          #+#    #+#             */
/*   Updated: 2021/04/19 17:33:37 by smhah            ###   ########.fr       */
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
	if (g_return)
		g_return = WEXITSTATUS(g_return);
	if (g_return == 256)
		g_return = 1;
	if (g_return == 255)
		g_return = 127;
}

int		fill_and_execute(void)
{
	int		i;
	int		j;

	if (!(g_utils.m_split = mod_split(g_utils.line, ';')))
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
			return (0);
		if (!fill(&j, i))
			return (-1);
		execute(j);
		g_status = 0;
		i++;
	}
	return (1);
}

int		check_semicolon(char *str)
{
	int i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == ';')
	{
		ft_putstr_fd("minishell: syntax error near ", 2);
		ft_putstr_fd("unexpected token `;'\n", 2);
		free(g_utils.line);
		g_utils.line = NULL;
		return (1);
	}
	return (0);
}

int		check_term()
{
	int ret;
	char *term_type = getenv("TERM");
	// int column_count;
	// int line_count;
	
	ret = tgetent(NULL, term_type);
	// char *blink_cmd = tgetstr("mb", NULL);
	char *af_cmd = tgetstr("AF", NULL);
	tputs(tparm(af_cmd, COLOR_RED), 1, putchar);
	// tputs(blink_cmd, 1, putchar);
	// column_count = tgetnum("co");
	// line_count = tgetnum("li");
	//printf("column:%d\n", column_count);
    return ret;
}

int	main(int ac, char **av, char **env)
{
	int	i;

	(void)ac;
	(void)av;
	i = 0;
	init_stuff(env);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	stock_env(env);
	g_echo = 0;
	g_histo = NULL;
	while (1)
	{
		if (!g_utils.buf.st_size)
			ft_putstr_fd("\033[0;32mCS\033[0;31m@minishell \033[0m",
				g_utils.out);
		// if (!(gnl(0, &g_utils.line)))
		if (!read_char(0, &g_utils.line))
			leave(NULL);
		ft_putchar_fd('\n', 1);
		if (check_semicolon(g_utils.line))
			continue ;
		if (fill_and_execute() < 0)
			g_return = 258;
		// free(g_utils.line);
		g_utils.line = NULL;
		i++;
	}
	printf("-------\n");
	loop_env_cmd();
	printf("---------\n");
	return (0);
}
