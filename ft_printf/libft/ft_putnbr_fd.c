/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:30:19 by cbenali-          #+#    #+#             */
/*   Updated: 2019/10/15 23:11:53 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	ui;

	ui = n * (-1);
	if (n >= 0 && n < 10)
		ft_putchar_fd(n + '0', fd);
	else if (n < 0 && n > -10)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd(ui + '0', fd);
	}
	else if (n > 9 || n < -9)
	{
		ft_putnbr_fd(n / 10, fd);
		if (n < -9)
			ft_putnbr_fd(ui % 10, fd);
		else
			ft_putnbr_fd(n % 10, fd);
	}
}
