/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex_bigx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:23:17 by cbenali-          #+#    #+#             */
/*   Updated: 2019/11/11 18:22:33 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern int g_count;

static void	put_spaces_zeroes(int n2, int n, int con, int k2)
{
	while (n2 > 0 && con < 4)
	{
		if (con == 1 || con == 3)
			ft_putchar_fd('0', 1);
		else if (con < 3)
			ft_putchar_fd(' ', 1);
		g_count++;
		n2--;
	}
	while (k2 - n > 0)
	{
		ft_putchar_fd('0', 1);
		g_count++;
		k2--;
	}
}

static void	case0_putstr_lastspaces(int n, int con, char *str, int n2)
{
	if (n)
	{
		if (con != 1 && con != 3)
		{
			ft_putchar_fd(' ', 1);
			g_count++;
		}
	}
	else
	{
		ft_putstr_fd(str, 1);
		g_count += ft_strlen(str);
	}
	while (n2 > 0 && con > 3)
	{
		ft_putchar_fd(' ', 1);
		g_count++;
		n2--;
	}
}

void		ft_printhex_bigx(va_list ap, int k, int k2, int con)
{
	unsigned int	d;
	int				n;
	int				n2;
	char			*str;

	d = va_arg(ap, unsigned int);
	str = ft_hextoa(d, 'X');
	n = num_hex(d);
	if (k < 0 && con != 1 && con != 3)
	{
		k = -k;
		con = (!con ? 4 : 5);
	}
	n2 = (k2 > n ? k - k2 : k - n);
	if (k || k2)
		put_spaces_zeroes(n2, n, con, k2);
	n = (d == 0 && (k == 0 || (k2 == 0 && (con == 2 || con == 5)))
	&& con > 0 ? 1 : 0);
	case0_putstr_lastspaces(n, con, str, n2);
}
