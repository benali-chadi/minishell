/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:23:45 by cbenali-          #+#    #+#             */
/*   Updated: 2019/11/08 15:00:39 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putunnbr_fd(unsigned int ui, int fd)
{
	if (ui < 10)
		ft_putchar_fd(ui + '0', fd);
	else if (ui > 9)
	{
		ft_putnbr_fd(ui / 10, fd);
		ft_putnbr_fd(ui % 10, fd);
	}
}
