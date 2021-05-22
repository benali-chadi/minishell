/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:29:12 by cbenali-          #+#    #+#             */
/*   Updated: 2019/10/19 13:50:13 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	negative_case(char *res, int n, int k)
{
	unsigned int	ui;

	ui = -n;
	while (ui)
	{
		res[k] = ui % 10 + '0';
		ui /= 10;
		k--;
	}
	res[k] = '-';
}

char	*ft_itoa(int n)
{
	char	*res;
	int		l;
	int		k;

	l = num(n);
	k = l - 1;
	res = (char *)malloc((l + 1) * sizeof(char));
	if (!res)
		return (0);
	if (n < 0)
		negative_case(res, n, k);
	else
	{
		while (n || l == 1)
		{
			res[k] = n % 10 + '0';
			n /= 10;
			k--;
			if (n == 0)
				break ;
		}
	}
	res[l] = '\0';
	return (res);
}
