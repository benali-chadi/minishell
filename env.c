/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:59:54 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/11 13:06:23 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	join_name_content(char *name, char *content, char **name_content)
{
	*name_content = ft_strjoin(name, "=");
	*name_content = ft_strjoin(*name_content, content);
	if (!(*name_content))
		return (0);
	return (1);
}

int	add_solo_var_name(char *name)
{
	if (check_var_solo(name))
		add_back(&g_all.list_env, name, ft_strdup(""), name);
	return (1);
}

int	fill_var(char **name, int i, int *j)
{
	while (g_all.cmd->string[i][++(*j)] != '=' && g_all.cmd->string[i][*j])
	{
		(*name)[*j] = g_all.cmd->string[i][*j];
		if ((*name)[*j] == '+' || (*name)[*j] == '-')
		{
			printf("minishell: export: `%s': ", g_all.cmd->string[i]);
			printf("not a valid identifier\n");
			return (0);
		}
	}
	(*name)[*j] = '\0';
	return (1);
}

void	ft_export(t_command_info *cmd)
{
	char	*name;
	char	*content;
	int		i;
	int		j;
	char	*name_content;

	i = -1;
	if (!cmd->string[0] && loop_env(1))
		return ;
	while (cmd->string[++i])
	{
		j = -1;
		if (ft_print_error(cmd->string[i][0], cmd, i))
			continue ;
		name = m_malloc(ft_strlen(cmd->string[i]) + 1);
		if (!fill_var(&name, i, &j))
			continue ;
		if (cmd->string[i][j] != '=' && add_solo_var_name(name))
			continue ;
		bypass_ternarie_1(cmd, &content, i, j);
		if (!join_name_content(name, content, &name_content))
			continue ;
		if (check_var(name, content, name_content))
			add_back(&g_all.list_env, name, content, name_content);
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
		read_list = g_all.list_env;
		if (ft_print_error(cmd->string[i][0], cmd, i))
			continue ;
		if (read_list != NULL && ft_strcmpr(cmd->string[i],
				read_list->name))
		{
			g_all.list_env = read_list->next;
			continue ;
		}
		while (read_list && !ft_strcmpr(cmd->string[i],
				read_list->name))
			ft_next_node(&read_list, &prev);
		if (read_list != NULL)
			prev->next = read_list->next;
	}
}
