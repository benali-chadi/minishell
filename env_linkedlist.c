/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_linkedlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:59:51 by cbenali-          #+#    #+#             */
/*   Updated: 2021/01/29 15:15:13 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_list_env		*ft_lstlast(t_list_env *lst)
{
	t_list_env	*loop;

	loop = lst;
	if (loop)
		while (loop->next)
			loop = loop->next;
	return (loop);
}

void			ft_lstadd_front(t_list_env **alst, t_list_env *new)
{
	if (new)
	{
		new->next = *alst;
		*alst = new;
	}
}

void			ft_lstadd_back(t_list_env **alst, t_list_env *new)
{
	t_list_env	*temp;

	if (alst && *alst && new)
	{
		temp = ft_lstlast(*alst);
		temp->next = new;
		new->next = NULL;
	}
	else if (!*alst)
	{
		*alst = new;
		new->next = NULL;
	}
}

t_list_env		*ft_lstnew(char *name, char *content, char *name_content)
{
	t_list_env	*list;

	list = m_malloc(sizeof(t_list_env));
	if (list)
	{
		list->content = content;
		list->name = name;
		list->name_content = name_content;
		list->next = NULL;
		return (list);
	}
	return (NULL);
}

void			add_back(t_list_env **head, char *name,
				char *content, char *name_content)
{
	ft_lstadd_back(head, ft_lstnew(name, content, name_content));
}
