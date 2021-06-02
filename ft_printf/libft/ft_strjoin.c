/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:35:00 by cbenali-          #+#    #+#             */
/*   Updated: 2021/01/18 17:00:39 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../mini_shell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	len;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	s = (char *)m_malloc(len + 1 * sizeof(char));
	if (!s)
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
