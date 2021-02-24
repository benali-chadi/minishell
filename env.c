/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:59:54 by cbenali-          #+#    #+#             */
/*   Updated: 2021/02/22 18:40:29 by cbenali-         ###   ########.fr       */
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

int		loop_env(int e)
{
	t_list_env *tmp;

	tmp = g_list_env;
	while (tmp)
	{
		if (e)
			ft_printf("declare -x %s\n", tmp->name_content);
		else if (tmp->content)
			ft_printf("%s\n", tmp->name_content);
		tmp = tmp->next;
	}
	return (1);
}

void	ft_export(t_command_info *cmd)
{
	char	*name;
	char	*content;
	int		i;
	int		j;

	i = -1;
	if (!cmd->string[0] && loop_env(1))
		return ;
	while (cmd->string[++i])
	{
		j = -1;
		// printf("cmd = %s\n", cmd->string[i]);
		if (ft_print_error(cmd->string[i][0], cmd, i))
			continue ;
		name = m_malloc(ft_strlen(cmd->string[i]) + 1);
		while (cmd->string[i][++j] != '=' && cmd->string[i][j])
			name[j] = cmd->string[i][j];
		name[j] = '\0';
		content = cmd->string[i][j] == '=' ? &cmd->string[i][++j] : NULL;
		// printf("%s\n", cmd->string[i]);
		if (check_var(name, content, cmd->string[i]))
			add_back(&g_list_env, clean_cmd(name),
				clean_cmd(content), clean_cmd(cmd->string[i]));
	}
}

void	ft_next_node(t_list_env **read_list, t_list_env **prev)
{
	*prev = *read_list;
	*read_list = (*read_list)->next;
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
		if (ft_print_error(cmd->string[i][0], cmd, i))
			continue ;
		if (read_list != NULL &&
			ft_strcmpr(clean_cmd(cmd->string[i]), read_list->name))
		{
			g_list_env = read_list->next;
			continue ;
		}
		while (read_list &&
			!ft_strcmpr(clean_cmd(cmd->string[i]), read_list->name))
			ft_next_node(&read_list, &prev);
		if (read_list != NULL)
			prev->next = read_list->next;
	}
}
