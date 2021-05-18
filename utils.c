/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:12:31 by cbenali-          #+#    #+#             */
/*   Updated: 2021/05/15 18:05:03 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_strcmpr(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	while (s2[++i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

int	is_alpha_digit(char a)
{
	if ((a <= 'Z' && a >= 'A') || (a <= 'z' && a >= 'a'
		) || (a <= '9' && a >= '0') || a == '?')
		return (1);
	return (0);
}

int	is_digit(char a)
{
	if (a <= '9' && a >= '0')
		return (1);
	return (0);
}

void	*ft_realloc(void *ptr, int size)
{
	void	*tmp;

	tmp = ptr;
	ptr = m_malloc(size);
	ptr = ft_strcpy(ptr, tmp);
	return (ptr);
}
