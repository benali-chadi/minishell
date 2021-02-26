/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_split_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:03:11 by smhah             #+#    #+#             */
/*   Updated: 2021/02/26 21:38:15 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int			ft_stock_red(char **tab, int a, char o)
{
	if (g_var_one == 0 && g_var_two == 0)
		tab[a][g_join_red++] = o;
	return (g_join_red);
}

char		**result_red(char **tab, const char *str, char *c)
{
	int a;
	int b;
	int i;

	i = 0;
	a = 0;
	g_var_one = 0;
	g_var_two = 0;
	while (str[i] != '\0' && ((g_join_red = 0) >= 0))
	{
		b = 0;
		while (ft_strchr(c, str[i]) &&
			((b = ft_stock_red(tab, a, str[i])) >= 0))
			i++;
		if (str[i] == '\0')
			break ;
		while ((g_var_one == 1 || g_var_two == 1 || str[i - 1] == '\\' || !ft_strchr(c, str[i]))
			&& str[i] != '\0' && re_check_quots(str, i))
			tab[a][b++] = str[i++];
		tab[a][b] = '\0';
		a++;
	}
	tab[a] = 0;
	return (tab);
}

char		**mod_split_red(char const *s, char *c)
{
	int		i;
	int		casee;
	char	**tab;
	int		*p;
	int		len;

	i = 0;
	g_join_red = 0;
	if (s)
		casee = ft_countwords_red(s, c);
	else
		return (0);
	if (!(tab = (char **)m_malloc(sizeof(char*) * (casee + 1) + 100)))
		return (0);
	casee = 0;
	p = &casee;
	while (i < ft_countwords_red(s, c))
	{
		len = ft_countlen_red(s, c, p);
		if (!(tab[i] = (char *)m_malloc(sizeof(char) * (len + 100))))
			return (freetab(tab, i));
		i++;
	}
	tab = result_red(tab, s, c);
	return (tab);
}
