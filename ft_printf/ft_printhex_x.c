/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex_x.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:22:24 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/02 21:09:59 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern int	g_count;

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

static int	n2_for_norme(int n, int k, int k2)
{
	if (k2 > n)
		return (k - k2);
	else
		return (k - n);
}

void	ft_printhex_x(va_list ap, int k, int k2, int con)
{
	unsigned int	d;
	int				n;
	int				n2;
	char			*str;

	d = va_arg(ap, unsigned int);
	str = ft_hextoa(d, 'x');
	n = num_hex(d);
	if (k < 0 && con != 1 && con != 3)
	{
		k = -k;
		if (!con)
			con = 4;
		else
			con = 5;
	}
	n2 = n2_for_norme(n, k, k2);
	if (k || k2)
		put_spaces_zeroes(n2, n, con, k2);
	if (d == 0 && (k == 0 || (k2 == 0 && (con == 2 || con == 5)))
		&& con > 0)
		con = 1;
	else
		con = 0;
	case0_putstr_lastspaces(n, con, str, n2);
}
