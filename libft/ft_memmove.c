/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:05:27 by cbenali-          #+#    #+#             */
/*   Updated: 2019/10/17 20:02:30 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst_tmp;
	const char	*src_tmp;
	char		*d;
	const char	*s;

	dst_tmp = dst;
	src_tmp = src;
	d = dst + (len - 1);
	s = src + (len - 1);
	if (!dst && !src)
		return (0);
	if (dst_tmp < src_tmp)
	{
		while (len--)
			*dst_tmp++ = *src_tmp++;
	}
	else
	{
		while (len--)
			*d-- = *s--;
	}
	return (dst);
}
