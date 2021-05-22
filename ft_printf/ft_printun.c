/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:33:46 by cbenali-          #+#    #+#             */
/*   Updated: 2019/11/11 18:27:04 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern int	g_count;

static int	num(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

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
		k2--;
		g_count++;
	}
}

static void	case0_putnbr_lastspaces(int case0, int con, unsigned int ui, int n2)
{
	if (case0)
	{
		if (con != 1 && con != 3)
		{
			ft_putchar_fd(' ', 1);
			g_count++;
		}
	}
	else
	{
		ft_putunnbr_fd(ui, 1);
		g_count += num(ui);
	}
	while (n2 > 0 && con > 3)
	{
		ft_putchar_fd(' ', 1);
		n2--;
		g_count++;
	}
}

int	n2_for_norme(int n, int k, int k2)
{
	if (k2 > n)
		return (k - k2);
	else
		return (k - n);
}

void	ft_printun(va_list ap, int k, int k2, int con)
{
	unsigned int	ui;
	int				n;
	int				n2;
	int				case0;

	ui = va_arg(ap, unsigned int);
	n = num(ui);
	if (k < 0 && con != 1 && con != 3)
	{
		k = -k;
		if (!con)
			con = 4;
		else
			con = 5;
	}
	n2 = n2_for_norme(n, k, k2);
	if (ui == 0 && (k == 0 || (k2 == 0 && (con == 2 || con == 5)))
		&& con > 0)
		case0 = 1;
	else
		case0 = 0;
	if (k || k2)
		put_spaces_zeroes(n2, n, con, k2);
	case0_putnbr_lastspaces(case0, con, ui, n2);
}
