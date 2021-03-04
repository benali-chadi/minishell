/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:54:19 by smhah             #+#    #+#             */
/*   Updated: 2021/03/04 14:43:06 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_cpy_env(t_list_env *read_env, int s)
{
	int e;

	e = 0;
	while (read_env->content[e])
		g_cmd->string[s][g_cmd->string_len++] = read_env->content[e++];
	g_cmd->string[s][g_cmd->string_len] = '\0';
}

void	compare_var(char *var, char *arg, int s)
{
	t_list_env	*read_env;

	read_env = g_list_env;
	while (read_env)
	{
		if (ft_strcmpr(read_env->name, var))
		{
			g_cmd->string[s] = ft_realloc(g_cmd->string[s],
			ft_strlen(g_cmd->string[s])
			+ ft_strlen(arg) + ft_strlen(read_env->content) + 1 + g_two);
			ft_cpy_env(read_env, s);
			break ;
		}
		read_env = read_env->next;
	}
}

void	ft_cpy_env_command(t_list_env *read_env)
{
	int e;

	e = 0;
	while (read_env->content[e])
		g_str_command[g_command_len++] = read_env->content[e++];
	g_str_command[g_command_len] = '\0';
}

int		check_var(char *name, char *content, char *name_content)
{
	t_list_env	*read_env;

	read_env = g_list_env;
	while (read_env)
	{
		if (ft_strcmpr(read_env->name, name))
		{
			if (!ft_strcmpr(read_env->name_content, name_content))
			{
				ft_strcpy(read_env->content, content);
				ft_strcpy(read_env->name_content, name_content);
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

	read_env = g_list_env;
	while (read_env)
	{
		if (ft_strcmpr(read_env->name, var))
		{
			g_str_command = ft_realloc(g_str_command, ft_strlen(g_str_command)
			+ ft_strlen(command) + ft_strlen(read_env->content) + 1 + g_two);
			ft_cpy_env_command(read_env);
			break ;
		}
		read_env = read_env->next;
	}
}
