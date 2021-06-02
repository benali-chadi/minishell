/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:23:28 by cbenali-          #+#    #+#             */
/*   Updated: 2019/11/11 18:30:16 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern int	g_count;
extern int	g_forzero;

static int	negative_d(int d)
{
	ft_putchar_fd('-', 1);
	d = -d;
	g_count++;
	return (d);
}

static void	case0_putnbr_lastspaces(int con, int d, int n2, int n)
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
		ft_putnbr_fd(d, 1);
		g_count += num_int(d);
	}
	while (n2 > 0 && con > 3)
	{
		ft_putchar_fd(' ', 1);
		n2--;
		g_count++;
	}
}

static int	put_spaces_zeroes(int d, int n2, int con, int k2)
{
	if (d < 0 && (con == 1 || con == 3))
		d = negative_d(d);
	while (n2 > 0 && con < 4)
	{
		if (con == 1 || con == 3)
			ft_putchar_fd('0', 1);
		else if (con < 3)
			ft_putchar_fd(' ', 1);
		n2--;
		g_count++;
	}
	if (d < 0 && con != 1)
		d = negative_d(d);
	while (k2 - num_int(d) > 0)
	{
		ft_putchar_fd('0', 1);
		g_count++;
		k2--;
	}
	return (d);
}

static int	assign_for_norm(int *k, int *con, int n, int k2)
{
	int	n2;

	if (*k < 0 && *con != 1 && *con != 3)
	{
		*k = - *k;
		if (!*con)
			*con = 4;
		else
			*con = 5;
	}
	if (k2 > n)
		n2 = *k - k2;
	else
		n2 = *k - n;
	return (n2);
}

void	ft_printint(va_list ap, int k, int k2, int con)
{
	int	d;
	int	n;
	int	n2;

	d = va_arg(ap, int);
	n = num_int(d);
	n2 = assign_for_norm(&k, &con, n, k2);
	if (k || k2)
	{
		if (d < 0 && k2 >= n && (con == 2 || con == 5))
			n2--;
		if (d < 0 && con == 1 && !g_forzero)
			n2++;
		d = put_spaces_zeroes(d, n2, con, k2);
	}
	if (d == 0 && (k == 0 || (k2 == 0 && (con == 2 || con == 5)))
		&& con > 0)
		n = 1;
	else
		n = 0;
	case0_putnbr_lastspaces(con, d, n2, n);
}
