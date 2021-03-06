/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:00:57 by cbenali-          #+#    #+#             */
/*   Updated: 2021/02/22 15:33:20 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	execute_cmd(t_command_info *cmd, char *command)
{
	int i;
	int j;

	if (cmd->options)
	{
		g_utils.args[0] = clean_cmd(cmd->command);
		g_utils.args[1] = clean_cmd(cmd->options);
		i = 2;
		j = 0;
		while (cmd->string[j])
			g_utils.args[i++] = clean_cmd(cmd->string[j++]);
		g_utils.args[i] = NULL;
	}
	else
	{
		g_utils.args[0] = clean_cmd(cmd->command);
		i = 1;
		j = 0;
		while (cmd->string[j])
			g_utils.args[i++] = clean_cmd(cmd->string[j++]);
		g_utils.args[i] = NULL;
	}
	if (execve(command, g_utils.args, g_utils.env) < 0)
		exit(-1);
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
	{
		if (stat(cmd->command, &g_utils.buf))
			ft_printf("minishell: %s: No such file or directory\n",
			cmd->command);
		execute_cmd(cmd, var);
	}
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
