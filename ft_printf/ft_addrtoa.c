/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addrtoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:22:46 by cbenali-          #+#    #+#             */
/*   Updated: 2019/11/08 14:26:19 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	num_addr(size_t n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static void	give_value(char *res, int l, int x, size_t n)
{
	size_t	a;
	size_t	f;
	int		k;

	k = l - 1;
	a = 0xa;
	f = 0xf;
	if (n == 0)
		res[k] = '0';
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
	res[1] = 'x';
	res[0] = '0';
}

char	*ft_addrtoa(size_t n, int x)
{
	char	*res;
	int		l;

	l = num_addr(n) + 2;
	res = (char *)malloc((l + 1));
	if (!res)
		return (0);
	give_value(res, l, x, n);
	res[l] = '\0';
	return (res);
}
