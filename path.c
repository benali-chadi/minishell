/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:00:57 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/11 18:12:55 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	is_option(t_command_info *cmd, int op)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	g_all.utils.args[i++] = clean_cmd(cmd->command);
	if (op)
		g_all.utils.args[i++] = clean_cmd(cmd->options);
	while (cmd->string[j])
		g_all.utils.args[i++] = cmd->string[j++];
	g_all.utils.args[i] = NULL;
}

void	execute_cmd(t_command_info *cmd, char *command)
{
	int	i;
	int	j;
	int	error;
	DIR	*dir;

	i = 1;
	j = 0;
	if (cmd->options)
		is_option(cmd, 1);
	else
		is_option(cmd, 0);
	if (execve(command, g_all.utils.args, g_all.utils.env) < 0)
	{
		error = errno;
		dir = opendir(command);
		if (opendir(command))
		{
			error = 21;
			closedir(dir);
		}
		printf("minishell: %s: %s\n", command, strerror(error));
		exit(error);
	}
}

char	*search_path(void)
{
	t_list_env	*read_env;

	read_env = g_all.list_env;
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
	while (split && split[i])
	{
		command = ft_strjoin(split[i], var);
		if (!stat(command, &g_all.utils.buf))
			execute_cmd(cmd, command);
		i++;
	}
	if (!ft_strcmpr(cmd->command, "exit"))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->command, 2);
		ft_putstr_fd(" command not found\n", 2);
	}
	exit(127);
}
