/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_linkedlist_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:43:22 by smhah             #+#    #+#             */
/*   Updated: 2021/06/06 07:29:17 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_histo	*ft_lstlast_cmd(t_histo *lst)
{
	t_histo	*loop;

	loop = lst;
	if (loop)
		while (loop->next)
			loop = loop->next;
	return (loop);
}

t_histo	*ft_lstnew_cmd(char *command_line)
{
	t_histo	*list;

	list = m_malloc(sizeof(t_histo));
	if (list)
	{
		list->command_line = command_line;
		list->next = NULL;
		return (list);
	}
	return (NULL);
}

void	ft_lstadd_back_cmd(t_histo **alst, t_histo *new)
{
	t_histo	*temp;

	if (alst && *alst && new)
	{
		temp = ft_lstlast_cmd(*alst);
		temp->next = new;
		new->previous = temp;
		new->next = NULL;
	}
	else if (!*alst)
	{
		*alst = new;
		g_histo = new;
		new->next = NULL;
		new->previous = NULL;
	}
}

void	add_back_cmd(t_histo **head, char *command_line)
{
	ft_lstadd_back_cmd(head, ft_lstnew_cmd(command_line));
}

void	ft_remove_node_cmd_1(void)
{
	t_histo	*read_list;
	int		i;
	//t_histo	*prev;


	read_list = g_histo;
	i = -1;
	if (!read_list->command_line)
		return ;
	while (read_list)
	{
		read_list = read_list->next;
		if (read_list->next == NULL && (read_list->previous))
		{
			read_list->previous->next = NULL;
			return ;
		}
		// read_list = g_list_env;
		// if (ft_print_error(cmd->string[i][0], cmd, i))
		// 	continue ;
		// if (read_list != NULL && ft_strcmpr(clean_cmd(cmd->string[i]),
		// 		read_list->name))
		// {
		// 	g_list_env = read_list->next;
		// 	continue ;
		// }
		// while (read_list && !ft_strcmpr(clean_cmd(cmd->string[i]),
		// 		read_list->name))
		// 	ft_next_node(&read_list, &prev);
		// if (read_list != NULL)
		// 	prev->next = read_list->next;
	}
}