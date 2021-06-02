/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:22:49 by cbenali-          #+#    #+#             */
/*   Updated: 2019/11/11 18:24:21 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern int	g_count;
extern int	g_forzero;

static void	put_space(int k)
{
	while (k - 1)
	{
		ft_putchar_fd(' ', 1);
		k--;
		g_count++;
	}
}

static void	put_zeroes(int k)
{
	while (k - 1)
	{
		ft_putchar_fd('0', 1);
		k--;
		g_count++;
	}
}

void	ft_printper(int k, int con)
{
	if (k && (con == 0 || (con == 2 && !g_forzero)))
		put_space(k);
	if (k && (((con == 1 || con == 2) && g_forzero) || con == 3))
		put_zeroes(k);
	ft_putchar_fd('%', 1);
	g_count++;
	if (k && con > 3)
		put_space(k);
}
