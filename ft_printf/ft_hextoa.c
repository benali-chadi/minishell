/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:21:48 by cbenali-          #+#    #+#             */
/*   Updated: 2019/11/08 14:29:39 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	give_value(char *res, int l, int x, unsigned int n)
{
	unsigned int	a;
	unsigned int	f;
	int				k;

	k = l - 1;
	a = 0xa;
	f = 0xf;
	while (n || l == 1)
	{
		if (n % 16 >= a && n % 16 <= f && x == 'x')
			res[k] = n % 16 + 87;
		else if (n % 16 >= a && n % 16 <= f && x == 'X')
			res[k] = n % 16 + 55;
		else
			res[k] = n % 16 + '0';
		n /= 16;
		k--;
		if (n == 0)
			break ;
	}
}

char	*ft_hextoa(unsigned int n, int x)
{
	char	*res;
	int		l;

	l = num_hex(n);
	res = (char *)malloc((l + 1));
	if (!res)
		return (0);
	give_value(res, l, x, n);
	res[l] = '\0';
	return (res);
}
