/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:05:10 by cbenali-          #+#    #+#             */
/*   Updated: 2019/10/12 17:01:59 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	res;

	res = 0;
	while (n)
	{
		res = *((unsigned char *)s1) - *((unsigned char *)s2);
		if (res != 0)
			return (res);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
