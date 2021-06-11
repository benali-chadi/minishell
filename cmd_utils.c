/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 18:49:57 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/11 13:45:01 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	test_cmds(t_command_info *cmd)
{
	if (cmd->tests.pwd)
		printf("%s\n", g_all.utils.pwd);
	else if (cmd->tests.echo)
		ft_echo(cmd);
	else if (cmd->tests.export_t && !cmd->string[0])
		ft_export(cmd);
	else if (cmd->tests.env)
		loop_env(0);
	else
		return (0);
	return (1);
}

void	close_all(int last)
{
	int	i;

	i = 0;
	while (i < last)
	{
		close(g_all.fd[i][0]);
		close(g_all.fd[i][1]);
		i++;
	}
}

char	*check_cmd(char *command, int *p)
{
	int		i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
		{
			*p = 1;
			return (command);
		}
		i++;
	}
	return (ft_strjoin("/", command));
}
