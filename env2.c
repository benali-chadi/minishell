/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:54:19 by smhah             #+#    #+#             */
/*   Updated: 2021/06/11 05:56:10 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_cpy_env(t_list_env *read_env, int s)
{
	int	e;

	e = 0;
	while (read_env->content[e])
		g_all.cmd->string[s][g_all.cmd->string_len++] = read_env->content[e++];
	g_all.cmd->string[s][g_all.cmd->string_len] = '\0';
}

void	compare_var(char *var, char *arg, int s)
{
	t_list_env	*read_env;

	read_env = g_all.list_env;
	while (read_env)
	{
		if (ft_strcmpr(read_env->name, var))
		{
			g_all.cmd->string[s] = ft_realloc(g_all.cmd->string[s],
					ft_strlen(g_all.cmd->string[s]) + ft_strlen(arg) + ft_strlen
					(read_env->content) + 1 + g_all.two);
			ft_cpy_env(read_env, s);
			break ;
		}
		read_env = read_env->next;
	}
}

void	ft_cpy_env_command(t_list_env *read_env)
{
	int	e;

	e = 0;
	while (read_env->content[e])
		g_all.s_cmd[g_all.c_l++] = read_env->content[e++];
	g_all.s_cmd[g_all.c_l] = '\0';
	if (g_all.one == 0 && g_all.two == 0
		&& mod_strlen(mod_split(read_env->content, ' ')) > 1)
	{
		g_all.cmd_args
			= join_2_tab(g_all.cmd_args, mod_split(read_env->content, ' '));
	}
}

int	check_var(char *name, char *content, char *name_content)
{
	t_list_env	*read_env;

	read_env = g_all.list_env;
	while (read_env)
	{
		if (ft_strcmpr(read_env->name, name))
		{
			if (!ft_strcmpr(read_env->name_content, name_content))
			{
				read_env->content = content;
				read_env->name_content = name_content;
			}
			return (0);
		}
		read_env = read_env->next;
	}
	return (1);
}

void	compare_var_command(char *var, char *command)
{
	t_list_env	*read_env;

	read_env = g_all.list_env;
	while (read_env)
	{
		if (ft_strcmpr(read_env->name, var))
		{
			g_all.s_cmd = ft_realloc(g_all.s_cmd, ft_strlen
					(g_all.s_cmd) + ft_strlen(command) + ft_strlen
					(read_env->content) + 1 + g_all.two);
			ft_cpy_env_command(read_env);
			break ;
		}
		read_env = read_env->next;
	}
}
