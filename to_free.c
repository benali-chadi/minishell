/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:59:10 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/06 11:28:30 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	*g_alloc[400];
int		g_all = 0;

void	*m_malloc(size_t n)
{
	void	*tmp;

	tmp = malloc(n);
	if (!tmp)
		return (NULL);
	g_alloc[g_all] = tmp;
	g_all++;
	return (tmp);
}

void	m_free(void *elm)
{
	free(elm);
	g_all--;
}

void	to_free(void)
{
	int	i;

	i = -1;
	while (++i < g_all)
		free(g_alloc[i]);
}
