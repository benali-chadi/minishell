/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:54:50 by cbenali-          #+#    #+#             */
/*   Updated: 2019/10/21 21:32:12 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *t_list_1;

	if (!(t_list_1 = (t_list *)malloc(sizeof(t_list))))
		return (0);
	t_list_1->content = content;
	t_list_1->next = NULL;
	return (t_list_1);
}
