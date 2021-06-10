/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:59:54 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/10 10:58:12 by smhah            ###   ########.fr       */
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
		if (!ft_strcmpr(name, "OLDPWD"))
			add_back(&g_list_env, name, content, name_content);
		i++;
	}
}
void swap(int j, int i)
{
    char *temp;

	temp = env_tab[j];
    env_tab[j] = env_tab[i];
    env_tab[i] = temp;
}

void bubbleSort(void)
{
   int i;
   int j;

   i = 0;
   while (env_tab[i])
   {
	   j = 0;
       while(env_tab[j])
	   {
           if (ft_strncmp(env_tab[i], env_tab[j], 5000) < 0)
              swap(j, i);
			j++;
	   }
	   i++;
   }
   i = -1;
   
   while(env_tab[++i])
		printf("declare -x %s\n", env_tab[i]);
}

int	check_equal_at_the_last(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return(0);
}

int	loop_env(int e)
{
	t_list_env	*tmp;
	int i;

	i = 0;
	tmp = g_list_env;
	while (tmp)
	{
		if (e)
		{
			//ft_strcpy(env_tab[i++], tmp->name_content);
			env_tab[i++] = tmp->name_content;
		}
		else if (tmp->content)
		{
			if (ft_strcmpr(tmp->name_content, "_=env"))
				printf("_=/usr/bin/env\n");
			else
			{
				if(!ft_strcmpr("", tmp->content) ||  check_equal_at_the_last(tmp->name_content))
					printf("%s\n", tmp->name_content);
			}
		}
		tmp = tmp->next;
	}
   env_tab[i] = NULL;
	if(e)
		bubbleSort();
	return (1);
}

void	loop_env_cmd(void)
{
	t_histo	*tmp;

	tmp = g_histo;
	while (tmp)
	{
		printf("%s\n", tmp->command_line);
		tmp = tmp->next;
	}
}

char	*join_name_content(char *name, char *content)
{
	char *buffer;

	buffer = ft_strjoin(name, "=");
	buffer = ft_strjoin(buffer, content);
	return(buffer);
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
		while (cmd->string[i][++j] != '=' && cmd->string[i][j])
			name[j] = cmd->string[i][j];
		name[j] = '\0';
		if(cmd->string[i][j] != '=')
		{
			if(check_var(name, ft_strdup(""), name))
				add_back(&g_list_env, name, ft_strdup(""), name);
			//printf("name=|%s|\n", name);
			continue ;
		}
		bypass_ternarie_1(cmd, &content, i, j);
		// printf("%s\n", name);
		// printf("%s\n", content);
		name_content = join_name_content(name, content);
		if(name_content)
		{
			if (check_var(name, content, name_content))
			{
				add_back(&g_list_env, name,
					content, name_content);
			}
		}
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
		if (ft_print_error(cmd->string[i][0], cmd, i))
			continue ;
		if (read_list != NULL && ft_strcmpr(cmd->string[i],
				read_list->name))
		{
			g_list_env = read_list->next;
			continue ;
		}
		while (read_list && !ft_strcmpr(cmd->string[i],
				read_list->name))
			ft_next_node(&read_list, &prev);
		if (read_list != NULL)
			prev->next = read_list->next;
	}
}
