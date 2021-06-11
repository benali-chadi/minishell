/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:32:40 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/11 13:13:48 by smhah            ###   ########.fr       */
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
		{
			g_all.fd[n][1] = 56;
			g_all.fd[n][1] = open(cmd->reds.out[i++].file_name,
					O_CREAT | O_WRONLY | O_APPEND, 0666);
		}
		else
			g_all.fd[n][1] = open(cmd->reds.out[i++].file_name,
					O_CREAT | O_WRONLY | O_TRUNC, 0666);
	}
	dup2(g_all.fd[n][1], 1);
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
				print_error_and_exit();
			dup2(*in, STDIN_FILENO);
		}
	}
	else if (*in != 0)
	{
		dup2(*in, STDIN_FILENO);
		close(*in);
	}
	if (cmd->reds.out_num > 0)
		red_out(cmd, n);
	else if (n != last - 1 && n != last)
	{
		dup2(g_all.fd[n][1], STDOUT_FILENO);
		close(g_all.fd[n][1]);
	}
}

void	ft_fork(t_command_info *cmd, int n, int last)
{
	int		in;
	char	*var;
	int		p;

	in = in_value(n, &p);
	if (last)
		pipe(g_all.fd[n]);
	if (fork() == 0)
	{
		if (last)
			close(g_all.fd[n][0]);
		pipe_or_red(cmd, &in, n, last);
		if (test_cmds(cmd))
			;
		else if (!ft_strcmpr(cmd->command, ""))
		{
			var = check_cmd(cmd->command, &p);
			find_path(cmd, var, p);
		}
		exit(0);
	}
	if (n == last - 1 || n == last)
		close_all(last);
	else
		close(g_all.fd[n][1]);
}

void	exec_cmd(t_command_info *cmd, int i, int last)
{
	if (cmd->tests.exit && !cmd->pipe)
		leave(cmd->string);
	else if (cmd->tests.cd)
		exec_cd(cmd);
	else if (cmd->tests.export_t && cmd->string[0])
		ft_export(cmd);
	else if (cmd->tests.unset)
		ft_remove_node(cmd);
	else
		ft_fork(cmd, i, last);
}
