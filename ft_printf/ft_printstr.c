/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:22:37 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/02 21:10:35 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

extern int	g_count;

static void	put_space(int n, int con)
{
	if (n > 0 && con != 1)
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
	if (!k2 && con != 2)
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

static int	negative_k(va_list ap, int k, int k2, int con)
{
	char	*str;

	if (k < 0)
	{
		if (con == 1)
		{
			str = va_arg(ap, char *);
			if (!str)
				str = "(null)";
			ft_putstr_fd(str, 1);
			g_count += ft_strlen(str);
			return (1);
		}
		k = -k;
		if (!con)
			con = 4;
		else
			con = 5;
		ft_printstr_mns(ap, k, k2, con);
		return (1);
	}
	return (0);
}

static int	n_for_norme(char *str, int k, int k2, int con)
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

void	ft_printstr(va_list ap, int k, int k2, int con)
{
	char	*str;
	int		n;

	if (negative_k(ap, k, k2, con))
		return ;
	str = va_arg(ap, char *);
	if (!str)
		str = "(null)";
	n = n_for_norme(str, k, k2, con);
	if (n > 0 && con != 1)
		put_space(n, con);
	if (con)
		cut(str, k, k2, con);
	if (!con || k2 < 0)
	{
		ft_putstr_fd(str, 1);
		g_count += ft_strlen(str);
	}
}
