/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:32:40 by cbenali-          #+#    #+#             */
/*   Updated: 2021/05/13 15:15:00 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static void	red_out(t_command_info *cmd, int n)
{
	int	i;

	i = 0;
	while (i < cmd->reds.out_num)
	{
		if (ft_strcmpr(cmd->reds.out[i].sym, ">>"))
			g_fd[n][1] = open(cmd->reds.out[i++].file_name,
					O_CREAT | O_WRONLY | O_APPEND, 0666);
		else
			g_fd[n][1] = open(cmd->reds.out[i++].file_name,
					O_CREAT | O_WRONLY | O_TRUNC, 0666);
	}
	dup2(g_fd[n][1], 1);
}

int	open_in(char *file, int *in)
{
	*in = open(file, O_RDONLY);
	return (*in);
}

void	pipe_or_red(t_command_info *cmd, int *in, int n, int last)
{
	int	i;

	i = 0;
	if (cmd->reds.in_num > 0)
	{
		while (i < cmd->reds.in_num)
		{
			*in = open(cmd->reds.in_file_name[i++], O_RDONLY);
			if (*in < 0)
			{
				ft_printf("minishell: %s\n", strerror(errno));
				exit(1);
			}
			dup2(*in, STDIN_FILENO);
		}
	}
	else if (*in != 0)
		dup2(*in, STDIN_FILENO);
	if (cmd->reds.out_num > 0)
		red_out(cmd, n);
	else if (n != last - 1 && n != last)
		dup2(g_fd[n][1], STDOUT_FILENO);
}

void	ft_fork(t_command_info *cmd, int n, int last)
{
	int		in;
	char	*var;
	int		p;

	p = 0;
	if (!n)
		in = 0;
	else
		in = g_fd[n - 1][0];
	if (last)
		pipe(g_fd[n]);
	if (fork() == 0)
	{
		pipe_or_red(cmd, &in, n, last);
		if (test_cmds(cmd))
			;
		else
		{
			var = check_cmd(cmd->command, &p);
			find_path(cmd, var, p);
		}
		exit(0);
	}
	if (n == last - 1 || n == last)
		close_all(last);
	else
		close(g_fd[n][1]);
}

void	exec_cmd(t_command_info *cmd, int i, int last)
{
	if (cmd->tests.exit && !cmd->pipe)
		leave(cmd->string);
	else if (cmd->tests.cd)
	{
		add_last_cmd(g_utils.pwd, "OLDPWD");
		if (!cmd->string[0])
			cmd->string[0] = search_lgnam();
		else if (cmd->string[0][0] == '~')
			cmd->string[0] = ft_strjoin(search_lgnam(), (*cmd->string) + 1);
		if (chdir(cmd->string[0]) < 0)
		{
			ft_printf("minishell: cd: %s: %s\n", cmd->string[0], strerror(errno));
			g_return = 256;
		}
		getcwd(g_utils.pwd, 100);
		add_last_cmd(g_utils.pwd, "PWD");
		add_last_cmd("cd", "_");
		if (ft_strcmpr(cmd->string[0], ".") || ft_strcmpr(cmd->string[0], ".."))
			add_last_cmd(cmd->string[0], "_");
	}
	else if (cmd->tests.export_t)
		ft_export(cmd);
	else if (cmd->tests.unset)
		ft_remove_node(cmd);
	else
		ft_fork(cmd, i, last);
}
