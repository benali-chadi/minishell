/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:01:08 by cbenali-          #+#    #+#             */
/*   Updated: 2021/02/18 18:01:11 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		free(g_utils.line);
		g_utils.line = NULL;
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
		else
			ft_putstr_fd("\b\b", 1);
	}
}

char	*search_lgnam(void)
{
	t_list_env	*read_env;

	read_env = g_list_env;
	while (read_env)
	{
		if (ft_strcmpr(read_env->name, "LOGNAME"))
			return (ft_strjoin("/home/", read_env->content));
		read_env = read_env->next;
	}
	return (NULL);
}

void	init_stuff(char **env)
{
	int i;

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
}

int		cmpr_maj(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			if (ft_abs(s1[i] - s2[i]) != 32)
				return (0);
		}
		i++;
	}
	return (1);
}

void	test(t_command_info *cmd)
{
	cmd->tests.echo = cmpr_maj(cmd->command, "echo") ||
	cmpr_maj(cmd->command, "/bin/echo") ? 1 : 0;
	cmd->tests.cd = cmpr_maj(cmd->command, "cd");
	cmd->tests.env = cmpr_maj(cmd->command, "env") ||
	cmpr_maj(cmd->command, "/usr/bin/env") ? 1 : 0;
	cmd->tests.exit = cmpr_maj(cmd->command, "exit");
	cmd->tests.export_t = cmpr_maj(cmd->command, "export");
	cmd->tests.pwd = cmpr_maj(cmd->command, "pwd") ||
	cmpr_maj(cmd->command, "/bin/pwd") ? 1 : 0;
	cmd->tests.unset = cmpr_maj(cmd->command, "unset");
}
