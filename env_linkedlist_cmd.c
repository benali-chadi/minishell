/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_linkedlist_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:43:22 by smhah             #+#    #+#             */
/*   Updated: 2021/04/10 18:23:16 by smhah            ###   ########.fr       */
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
