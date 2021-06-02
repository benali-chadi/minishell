/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:07:14 by cbenali-          #+#    #+#             */
/*   Updated: 2019/10/16 11:52:01 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		res;

	res = 0;
	while (n && (*s1 || *s2))
	{
		res = (unsigned char)*s1++ - (unsigned char)*s2++;
		if (res != 0)
			return (res);
		n--;
	}
	return (0);
}
