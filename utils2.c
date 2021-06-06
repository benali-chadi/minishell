/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:01:08 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/05 21:41:20 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_utils.for_ctrl_c = 1;
		if (!g_status)
			ft_putstr_fd("\n\033[0;32mCS\033[0;31m@minishell \033[0m",
				g_utils.out);
		else
		{
			ft_putstr_fd("\n", 0);
			g_status = 0;
		}
		return ;
	}
	else if (signum == SIGQUIT)
	{
		if (g_status)
			ft_putstr_fd("Quit: 3\n", 1);
	}
}

char	*search_lgnam(void)
{
	t_list_env	*read_env;

	read_env = g_list_env;
	while (read_env)
	{
		if (ft_strcmpr(read_env->name, "HOME"))
			return (read_env->content);
		read_env = read_env->next;
	}
	return ("");
}

void	init_stuff(char **env)
{
	int	i;

	i = 0;
	while (i < 128)
		g_utils.cnt[i++] = 0;
	g_utils.cnt['0'] = '\0';
	g_utils.cnt['a'] = '\a';
	g_utils.cnt['b'] = '\b';
	g_utils.cnt['t'] = '\t';
	g_utils.cnt['n'] = '\n';
	g_utils.cnt['v'] = '\v';
	g_utils.cnt['f'] = '\f';
	g_utils.cnt['r'] = '\r';
	g_utils.cnt['e'] = '\e';
	g_returned = 0;
	g_count_end = 0;
	fstat(0, &g_utils.buf);
	g_utils.out = open("/dev/tty", O_WRONLY);
	g_utils.env = env;
	g_move_and_pass = 0;
}

int	cmpr_maj(char *s1, char *s2)
{
	int	i;
	int	diff;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			diff = s1[i] - s2[i];
			if (diff != 32 && diff != -32)
				return (0);
		}
		i++;
	}
	return (1);
}

void	test(t_command_info *cmd)
{
	cmd->tests.cd = cmpr_maj(cmd->command, "cd");
	cmd->tests.exit = cmpr_maj(cmd->command, "exit");
	cmd->tests.export_t = cmpr_maj(cmd->command, "export");
	cmd->tests.unset = cmpr_maj(cmd->command, "unset");
	if (cmpr_maj(cmd->command, "echo") || cmpr_maj(cmd->command, "/bin/echo"))
		cmd->tests.echo = 1;
	if (cmpr_maj(cmd->command, "env") || cmpr_maj(cmd->command, "/usr/bin/env"))
		cmd->tests.env = 1;
	if (cmpr_maj(cmd->command, "pwd") || cmpr_maj(cmd->command, "/bin/pwd"))
		cmd->tests.pwd = 1;
}
