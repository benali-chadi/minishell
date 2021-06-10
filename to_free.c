/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:59:10 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/10 19:29:00 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	*m_malloc(size_t n)
{
	void	*tmp;

	tmp = malloc(n);
	if (!tmp)
		return (NULL);
	g_all.alloc[g_all.all] = tmp;
	g_all.all++;
	return (tmp);
}

void	m_free(void *elm)
{
	free(elm);
	g_all.all--;
}

void	to_free(void)
{
	int	i;

	i = -1;
	while (++i < g_all.all)
		free(g_all.alloc[i]);
}
