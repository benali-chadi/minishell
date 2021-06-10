/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_split_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:03:11 by smhah             #+#    #+#             */
/*   Updated: 2021/06/10 18:00:53 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	fill_red(char **tab1, int *a, int *b, char *str)
{
	int	i;

	i = 0;
	tab1[*a][(*b)++] = str[i++];
	tab1[*a][*b] = '\0';
	if (!str[i])
		(*a)++;
	return (i);
}

int	init_join_red(void)
{
	g_all.join_red = 0;
	return (1);
}

char	**result_red(char **tab1, const char *str, char *c)
{
	int	a;
	int	b;
	int	i;

	i = 0;
	a = 0;
	g_all.var_one = 0;
	g_all.var_two = 0;
	while (str[i] != '\0' && init_join_red() >= 0)
	{
		b = 0;
		while (g_all.var_one == 0 && g_all.var_two == 0
			&& str[i] && ft_strchr(c, str[i]))
			i += fill_red(tab1, &a, &b, (char *) &(str[i]));
		if (str[i] == '\0')
			break ;
		while ((g_all.var_one == 1 || g_all.var_two == 1
				|| (i && str[i - 1] == '\\') || !ft_strchr(c, str[i]))
			&& str[i] != '\0' && re_check_quots(str, i))
			tab1[a][b++] = str[i++];
		tab1[a][b] = '\0';
		a++;
	}
	tab1[a] = 0;
	return (tab1);
}

char	**mod_split_red(char const *s, char *c)
{
	int		i;
	int		casee;
	char	**tab1;
	int		len;

	i = 0;
	g_all.join_red = 0;
	tab1 = NULL;
	if (s)
		casee = ft_countwords_red(s, c);
	else
		return (0);
	if (!alloc_1(&tab1, casee))
		return (0);
	casee = 0;
	while (i < ft_countwords_red(s, c))
	{
		len = ft_countlen_red(s, c, &casee);
		if (!alloc_2(tab1, i, len))
			return (freetab(tab1, i));
		i++;
	}
	tab1 = result_red(tab1, s, c);
	return (tab1);
}
