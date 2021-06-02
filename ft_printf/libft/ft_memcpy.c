/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:04:13 by cbenali-          #+#    #+#             */
/*   Updated: 2019/10/17 20:01:37 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long	i;
	char			*tmp;

	if (dst == 0 && src == 0)
		return ("");
	tmp = (char *)src;
	i = 0;
	while (i < n)
	{
		*((char *)dst + i) = tmp[i];
		i++;
	}
	return (dst);
}
