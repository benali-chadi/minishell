/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:22:11 by cbenali-          #+#    #+#             */
/*   Updated: 2019/11/11 18:29:00 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	g_k;
int	g_k2;
int	g_count;
int	g_forzero;

int	ft_check_flags_num(va_list ap, const char *s, int *i, int con)
{
	if (ft_isdigit(s[*i]))
	{
		g_k = ft_atoi(s + *i);
		while (s[*i] == '0')
			(*i)++;
		if (g_k)
			*i += num_int(g_k);
	}
	if (s[*i] == '*' || s[*i] == '.')
	{
		con = 2;
		if (s[*i] == '.')
			(*i)++;
		if (s[*i] == '*')
		{
			g_k2 = va_arg(ap, int);
			(*i)++;
		}
	}
	return (con);
}

int	ft_check_flags(va_list ap, const char *s, int *i, int con)
{
	if (s[*i] == '0' || s[*i] == '.' || s[*i] == '*')
	{
		if ((s[*i] == '0' || s[*i] == '.') && s[*i + 1] == '*')
			(*i)++;
		if (s[*i] == '*')
			g_k = va_arg(ap, int);
		if ((s[*i] == '0' || s[*i] == '.' || s[*i - 1] == '.')
			&& s[*i - 1] != '-')
			con = 1;
		if (s[*i] == '0')
			g_forzero = 1;
		else
			g_forzero = 0;
		(*i)++;
	}
	con = ft_check_flags_num(ap, s, i, con);
	if (ft_isdigit(s[*i]))
	{
		g_k2 = ft_atoi(s + *i);
		while (s[*i] == '0')
			(*i)++;
		if (g_k2)
			*i += num_int(g_k2);
	}
	return (con);
}

int	ft_flag(va_list ap, const char *s, int *i)
{
	int	con;
	int	pos;

	pos = 0;
	con = 0;
	while (s[*i] == '-')
	{
		pos = *i;
		(*i)++;
	}
	con = ft_check_flags(ap, s, i, con);
	if (s[pos] == '-')
	{
		if (con == 1)
			con = 3;
		else if (!con)
			con = 4;
		else
			con = 5;
	}
	return (con);
}

void	ft_check(const char *s, va_list ap, int *i)
{
	int	con;

	con = 0;
	if (ft_isdigit(s[*i]) || s[*i] == '.' || s[*i] == '*' || s[*i] == '-')
		con = ft_flag(ap, s, i);
	if (s[*i] == '%')
		ft_printper(g_k, con);
	else if (s[*i] == 'c')
		ft_printchar(ap, g_k, con);
	else if (s[*i] == 's')
		if (con > 2)
			ft_printstr_mns(ap, g_k, g_k2, con);
	else
		ft_printstr(ap, g_k, g_k2, con);
	else if (s[*i] == 'd' || s[*i] == 'i')
		ft_printint(ap, g_k, g_k2, con);
	else if (s[*i] == 'u')
		ft_printun(ap, g_k, g_k2, con);
	else if (s[*i] == 'x')
		ft_printhex_x(ap, g_k, g_k2, con);
	else if (s[*i] == 'X')
		ft_printhex_bigx(ap, g_k, g_k2, con);
	else if (s[*i] == 'p')
		ft_printaddr(ap, g_k, con);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		i;
	int		*pi;

	pi = &i;
	i = 0;
	va_start(ap, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			ft_check(s, ap, pi);
		}
		else
		{
			ft_putchar_fd(s[i], 1);
			g_count++;
		}
		i++;
		g_k = 0;
		g_k2 = 0;
	}
	va_end(ap);
	return (g_count);
}
