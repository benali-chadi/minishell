/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 21:29:04 by cbenali-          #+#    #+#             */
/*   Updated: 2019/10/23 00:59:25 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*pt;

	if (!alst)
		return ;
	else if (*alst)
	{
		pt = ft_lstlast(*alst);
		pt->next = new;
	}
	else if (!*alst)
		*alst = new;
}
