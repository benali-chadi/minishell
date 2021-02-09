/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:59:54 by cbenali-          #+#    #+#             */
/*   Updated: 2021/01/29 15:20:54 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	stock_env(char **env)
{
	char	*name;
	char	*content;
	char	*name_content;
	int		i;
	int		j;

	g_list_env = NULL;
	i = 0;
	while (env[i])
	{
		j = 0;
		name_content = env[i];
		name = m_malloc(ft_strlen(env[i]));
		while (env[i][j] != '=')
		{
			name[j] = env[i][j];
			j++;
		}
		name[j] = '\0';
		content = &env[i][j] + 1;
		add_back(&g_list_env, name, content, name_content);
		i++;
	}
}

void	loop_env(void)
{
	t_list_env *tmp;

	tmp = g_list_env;
	while (tmp)
	{
		ft_putstr_fd(tmp->name_content, 1);
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
}


void	ft_export(t_command_info *cmd)
{
	char	*name;
	char	*content;
	int		i;
	int		j;

	i = -1;
	if (!cmd->string[0])
	{
		loop_env();
		return ;
	}
	while (cmd->string[++i])
	{
		j = -1;
		if (cmd->string[i][0] == '=' || (cmd->string[i][0] >= '0' && cmd->string[i][0] <= '9'))
		{
			ft_printf("export: `%s': not a valid identifier\n", cmd->string[i]);
			continue ;
		}

		name = m_malloc(ft_strlen(cmd->string[i]));
		while (cmd->string[i][++j] != '=' && cmd->string[i][j])
			name[j] = cmd->string[i][j];
		if (cmd->string[i][j] != '=')
			continue ;
		name[j] = '\0';
		content = &cmd->string[i][++j];
		if(check_var(name))
			add_back(&g_list_env, name, content, cmd->string[i]);
	}
}

void	ft_remove_node(t_command_info *cmd)
{
	t_list_env	*read_list;
	t_list_env	*prev;
	int			i;

	i = -1;
	if (!cmd->string[0])
		return ;
	while (cmd->string[++i])
	{
		read_list = g_list_env;
		if (cmd->string[i][0] == '=' || (cmd->string[i][0] >= '0' && cmd->string[i][0] <= '9'))
		{
			ft_printf("export: `%s': not a valid identifier\n", cmd->string[i]);
			continue ;
		}
		if (read_list != NULL && ft_strcmpr(read_list->name, cmd->string[i]))
		{
			g_list_env = read_list->next;
			continue ;
		}
		while (read_list && !ft_strcmpr(cmd->string[i], read_list->name))
		{
			prev = read_list;
			read_list = read_list->next;
		}
		if (read_list != NULL)
			prev->next = read_list->next;
	}
}

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
	printf("var:%s\n", var);
	while (read_env)
	{
		//printf("search\n");
		if (ft_strcmpr(read_env->name, var))
		{
			printf("found:%s\n", read_env->name);
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
		str_command[command_len++] = read_env->content[e++];
	str_command[command_len] = '\0';
	//printf("COPYY\n");
}

int		check_var(char *var)
{
	t_list_env	*read_env;

	read_env = g_list_env;
	while (read_env)
	{
		if (ft_strcmpr(read_env->name, var))
			return (0);
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
			str_command = ft_realloc(str_command, ft_strlen(str_command)
			+ ft_strlen(command) + ft_strlen(read_env->content) + 1 + g_two);
			ft_cpy_env_command(read_env);
			break ;
		}
		read_env = read_env->next;
	}
}


