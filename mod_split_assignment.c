/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_split_assignment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 19:24:19 by smhah             #+#    #+#             */
/*   Updated: 2021/04/20 16:21:23 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	**alloc_1(char **tab1, int casee)
{
	tab1 = (char **)m_malloc(sizeof(char *) * (casee + 1));
	return (tab1);
}

char	*alloc_2(char **tab1, int i, int len)
{
	tab1[i] = (char *)m_malloc(sizeof(char) * (len + 1));
	return (tab1[i]);
}

int 	calcule_len(int *len, char *s, char c, int *p)
{
	*len = ft_countlen(s, c, p);
	return (*len);
}
