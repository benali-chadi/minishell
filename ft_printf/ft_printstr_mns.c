/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr_mns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:23:38 by cbenali-          #+#    #+#             */
/*   Updated: 2019/11/08 15:00:10 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern int	g_count;

static void	put_space(int n, int con)
{
	if (n > 0 && con != 3)
	{
		while (n > 0)
		{
			ft_putchar_fd(' ', 1);
			g_count++;
			n--;
		}
	}
}

static void	cut(char *str, int k, int k2, int con)
{
	int	i;

	i = 0;
	if (!k2 && con != 5)
	{
		while (i < k && i < (int)ft_strlen(str))
		{
			ft_putchar_fd(str[i], 1);
			g_count++;
			i++;
		}
	}
	else
	{
		while (i < k2 && i < (int)ft_strlen(str))
		{
			ft_putchar_fd(str[i], 1);
			g_count++;
			i++;
		}
	}
}

int	n_for_norme(char *str, int k, int k2, int con)
{
	if ((!k2 && con == 4) || k2 < 0)
		return (k - ft_strlen(str));
	else
	{
		if (k2 < (int)ft_strlen(str))
			return (k - k2);
		else
			return (k - (int)ft_strlen(str));
	}
}

void	ft_printstr_mns(va_list ap, int k, int k2, int con)
{
	char	*str;
	int		n;

	if (k < 0)
		k = -k;
	str = va_arg(ap, char *);
	if (!str)
		str = "(null)";
	n = n_for_norme(str, k, k2, con);
	if (con != 4)
		cut(str, k, k2, con);
	if (con == 4 || k2 < 0)
	{
		ft_putstr_fd(str, 1);
		g_count += ft_strlen(str);
	}
	if (n > 0 && con != 3)
		put_space(n, con);
}
