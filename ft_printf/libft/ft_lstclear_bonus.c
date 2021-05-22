/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 20:44:10 by cbenali-          #+#    #+#             */
/*   Updated: 2019/10/22 23:55:14 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*pt;
	t_list	*tmp;

	if (lst && del)
	{
		if (*lst)
		{
			pt = *lst;
			while (pt != NULL)
			{
				tmp = pt->next;
				del(pt->content);
				free(pt);
				pt = tmp;
			}
			*lst = NULL;
		}
	}
}
