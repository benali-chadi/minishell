/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:17:53 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/10 16:51:28 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include "../../mini_shell.h"

char	*ft_strdup(const char *s)
{
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen((char *)s);
	tmp = (char *)m_malloc(len + 1 * sizeof(char));
	if (!tmp)
		return (0);
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
