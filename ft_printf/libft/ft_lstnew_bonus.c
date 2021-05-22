/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:54:50 by cbenali-          #+#    #+#             */
/*   Updated: 2021/02/25 17:56:10 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*t_list_1;

	t_list_1 = (t_list *)m_malloc(sizeof(t_list));
	if (!t_list_1)
		return (0);
	t_list_1->content = content;
	t_list_1->next = NULL;
	return (t_list_1);
}
