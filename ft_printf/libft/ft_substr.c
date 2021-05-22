/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:34:20 by cbenali-          #+#    #+#             */
/*   Updated: 2019/10/19 01:19:16 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*s_ptr;
	int				i;
	unsigned int	l;

	l = len + start;
	i = 0;
	if (!s)
		return (0);
	s_ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!s_ptr)
		return (0);
	while (start < l && start < ft_strlen(s))
	{
		s_ptr[i] = s[start];
		i++;
		start++;
	}
	s_ptr[i] = '\0';
	return (s_ptr);
}
