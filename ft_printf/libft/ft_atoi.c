/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:02:16 by cbenali-          #+#    #+#             */
/*   Updated: 2019/10/19 00:57:53 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		signe;
	long	res;

	res = 0;
	i = 0;
	signe = 1;
	while (str[i] > 0 && str[i] <= 32 && str[i] != '\e')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		res = res * 10 + (str[i] - 48);
		i++;
		if (res > 2147483648 && signe == -1)
			return (0);
		else if (res > 2147483647 && signe == 1)
			return (-1);
	}
	return (res * signe);
}
