/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:17:45 by cbenali-          #+#    #+#             */
/*   Updated: 2019/10/21 16:03:08 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*tmp;
	size_t	i;

	i = 0;
	tmp = malloc(n * size);
	if (!tmp)
		return (0);
	while (i < n)
	{
		if (size == sizeof(int))
			*((int *)tmp + i) = 0;
		else
			*((char *)tmp + i) = 0;
		i++;
	}
	return (tmp);
}
