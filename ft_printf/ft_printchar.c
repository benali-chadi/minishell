/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:23:06 by cbenali-          #+#    #+#             */
/*   Updated: 2019/11/08 14:28:53 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern int	g_count;

void	ft_printchar(va_list ap, int k, int con)
{
	char	c;

	if (k < 0)
	{
		k = -k;
		con = 1;
	}
	c = va_arg(ap, int);
	while (k - 1 > 0 && !con)
	{
		ft_putchar_fd(' ', 1);
		k--;
		g_count++;
	}
	ft_putchar_fd(c, 1);
	g_count++;
	while (k - 1 > 0 && con)
	{
		ft_putchar_fd(' ', 1);
		k--;
		g_count++;
	}
}
