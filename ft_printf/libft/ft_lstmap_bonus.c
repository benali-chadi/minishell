/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 20:44:30 by cbenali-          #+#    #+#             */
/*   Updated: 2019/10/23 01:00:11 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	int		i;
	t_list	*new;
	t_list	*tmp;

	i = ft_lstsize(lst);
	new = NULL;
	tmp = new;
	while (i && f && del)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&tmp, del);
			break ;
		}
		new->next = new;
		lst = lst->next;
		new = new->next;
		i--;
	}
	return (new);
}
