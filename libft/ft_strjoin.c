/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:35:00 by cbenali-          #+#    #+#             */
/*   Updated: 2019/10/19 01:48:40 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	len;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(s = (char *)malloc(len + 1 * sizeof(char))))
		return (0);
	while (*s1 != '\0')
	{
		s[i] = (char)*s1;
		i++;
		s1++;
	}
	while (*s2 != '\0')
	{
		s[i] = (char)*s2;
		i++;
		s2++;
	}
	s[i] = '\0';
	return (s);
}
