/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 12:07:38 by cbenali-          #+#    #+#             */
/*   Updated: 2019/10/19 13:37:40 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_match(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*to_find;
	char	*src;
	size_t	i;

	i = 0;
	to_find = (char *)needle;
	src = (char *)haystack;
	if (ft_strlen(to_find) == 0)
		return (src);
	while (*src && i < len)
	{
		if (is_match(src, to_find) && i + ft_strlen(to_find) <= len)
			return (src);
		i++;
		src++;
	}
	return (0);
}
