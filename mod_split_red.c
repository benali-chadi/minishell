/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_split_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:03:11 by smhah             #+#    #+#             */
/*   Updated: 2021/06/05 20:23:44 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

// int			ft_stock_red(char **tab1, int a, char o)
// {

// 	if (g_var_one == 0 && g_var_two == 0)
// 	{
// 		tab1[a][g_join_red++] = o;
// 		//tab1[a][g_join_red] = '\0';
// 	}
// 	printf("tab:|%s|\n", tab1[a]);
// 	return (g_join_red);
//
char		**result_red(char **tab1, const char *str, char *c)
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
		while (g_var_one == 0 && g_var_two == 0 && str[i] && ft_strchr(c, str[i]))
		{
				tab1[a][b++] = str[i++];
				tab1[a][b] = '\0';
				printf("[%s]\n", tab1[a]);
				if(!str[i])
					a++;
				//printf("pa9chta9\n");
		}// &&
			//((b = ft_stock_red(tab1, a, str[i])) >= 0))
			//i++;
		if (str[i] == '\0')
			break ;
		while ((g_var_one == 1 || g_var_two == 1 ||
		(i && str[i - 1] == '\\') || !ft_strchr(c, str[i]))
			&& str[i] != '\0' && re_check_quots(str, i))
			tab1[a][b++] = str[i++];
		tab1[a][b] = '\0';
		a++;
	}
	tab1[a] = 0;
	return (tab1);
}

char		**mod_split_red(char const *s, char *c)
{
	int		i;
	int		casee;
	char	**tab1;
	int		*p;
	int		len;

	//printf("String:%s\n", s);
	i = 0;
	g_join_red = 0;
	if (s)
		casee = ft_countwords_red(s, c);
	else
		return (0);
	if (!(tab1 = (char **)m_malloc(sizeof(char*) * (casee + 1) + 100)))
		return (0);
	casee = 0;
	p = &casee;
	while (i < ft_countwords_red(s, c))
	{
		len = ft_countlen_red(s, c, p);
		if (!(tab1[i] = (char *)m_malloc(sizeof(char) * (len + 100))))
			return (freetab(tab1, i));
		i++;
	}
	tab1 = result_red(tab1, s, c);
	int pipi = 0;
	while(tab1[pipi])
	{
		printf("--->[%s]\n", tab1[pipi++]);
	}
	return (tab1);
}
