/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:00:57 by cbenali-          #+#    #+#             */
/*   Updated: 2021/05/15 17:24:04 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	option_true(int i, int j, t_command_info *cmd)
{
	g_utils.args[0] = clean_cmd(cmd->command);
	g_utils.args[1] = clean_cmd(cmd->options);
	i = 2;
	j = 0;
	while (cmd->string[j])
		g_utils.args[i++] = clean_cmd(cmd->string[j++]);
	g_utils.args[i] = NULL;
}

void	execute_cmd(t_command_info *cmd, char *command)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmd->options)
		option_true(i, j, cmd);
	else
	{
		g_utils.args[0] = clean_cmd(cmd->command);
		i = 1;
		j = 0;
		while (cmd->string[j])
		{
			g_utils.args[i++] = clean_cmd(cmd->string[j++]);
		}
		g_utils.args[i] = NULL;
	}
	int ret;
	if (( ret = execve(command, g_utils.args, g_utils.env)) < 0)
	{
		//DIR *dir = opendir(command);
		if (opendir(command))
		{
			ft_printf("minishell : %s", strerror(12));
			//closedir();
			exit(12);
		}
		ft_printf("minishell : %s\n", strerror(errno));
		exit(errno);
	}
}

char	*search_path(void)
{
	t_list_env	*read_env;

	read_env = g_list_env;
	while (read_env)
	{
		if (ft_strcmpr(read_env->name, "PATH"))
			return (read_env->content);
		read_env = read_env->next;
	}
	return (NULL);
}

void	find_path(t_command_info *cmd, char *var, int p)
{
	char		**split;
	char		*command;
	int			i;

	split = mod_split(search_path(), ':');
	i = 0;
	if (p)
		execute_cmd(cmd, var);
	while (split[i])
	{
		command = ft_strjoin(split[i], var);
		if (!stat(command, &g_utils.buf))
			execute_cmd(cmd, command);
		i++;
	}
	if (!ft_strcmpr(cmd->command, "exit"))
		ft_printf("minishell: %s: command not found\n", cmd->command);
	exit(-1);
}
