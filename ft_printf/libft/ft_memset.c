/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:05:43 by cbenali-          #+#    #+#             */
/*   Updated: 2019/10/12 17:20:02 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*dup;
	unsigned long	i;

	i = 0;
	dup = str;
	while (i < n)
	{
		dup[i] = c;
		i++;
	}
	return (dup);
}
