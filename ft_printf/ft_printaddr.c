/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printaddr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:21:59 by cbenali-          #+#    #+#             */
/*   Updated: 2019/11/11 18:21:34 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern int	g_count;

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

static void	zero_case(int con)
{
	char	*incase;
	char	*incase_min;

	incase = " 0x";
	incase_min = "0x ";
	if (con < 3)
		ft_putstr_fd(incase, 1);
	else
		ft_putstr_fd(incase_min, 1);
	g_count += 3;
}

static void	put_spcae(int n)
{
	while (n > 0)
	{
		ft_putchar_fd(' ', 1);
		n--;
		g_count++;
	}
}

void	ft_printaddr(va_list ap, int k, int con)
{
	size_t	p;
	char	*str;
	int		n;

	if (k < 0)
	{
		k = -k;
		con = 1;
	}
	p = (size_t)va_arg(ap, void *);
	n = k - num_addr(p) - 2;
	if (con < 3)
		put_spcae(n);
	if (p == 0 && ((con > 0 && con < 3) || con == 5))
		zero_case(con);
	else
	{
		str = ft_addrtoa(p, 'x');
		ft_putstr_fd(str, 1);
		g_count += ft_strlen(str);
	}
	if (con > 3)
		put_spcae(n);
}
