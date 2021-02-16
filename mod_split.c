/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:01:03 by cbenali-          #+#    #+#             */
/*   Updated: 2021/02/16 16:52:58 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int			ft_countwords(const char *str, char c)
{
	int i;
	int compteur;

	g_var_one = 0;
	g_var_two = 0;
	compteur = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] == '\0')
			break ;
		compteur++;
		while ((g_var_one == 1 || g_var_two  == 1 || str[i] != c)
			&& str[i] != '\0' && re_check_quots(str, i))
			i++;
		if (str[i] == '\0')
			break ;
	}
	return (compteur);
}

int			ft_countlen(const char *str, char c, int *i)
{
	int len;

	g_var_one = 0;
	g_var_two = 0;
	len = 0;
	while (str[*i] != '\0')
	{
		while (str[*i] == c)
			*i = *i + 1;
		if (str[*i] == '\0')
			return (len);
		while ((g_var_one == 1 || g_var_two == 1 || str[*i] != c)
			&& str[*i] != '\0' && re_check_quots(str, *i))
		{
			*i = *i + 1;
			len++;
		}
		return (len);
		if (str[*i] == '\0')
			return (len);
	}
	return (len);
}

char		**result(char **tab, const char *str, char c)
{
	int a;
	int b;
	int i;

	i = 0;
	a = 0;
	g_var_one = 0;
	g_var_two = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] == '\0')
			break ;
		b = 0;
		while ((g_var_one == 1 || g_var_two == 1 || str[i] != c)
			&& str[i] != '\0' && re_check_quots(str, i))
			tab[a][b++] = str[i++];
		tab[a][b] = '\0';
		a++;
	}
	tab[a] = 0;
	return (tab);
}

char		**freetab(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (0);
}

char		**mod_split(char const *s, char c, int end)
{
	int		i;
	int		casee;
	char	**tab;
	int		*p;
	int		len;

	i = 0;
	(void)end;
	if (s)
		casee = ft_countwords(s, c);
	else
		return (0);
	if (!(tab = (char **)m_malloc(sizeof(char*) * (casee + 1))))
		return (0);
	casee = 0;
	p = &casee;
	while (i < ft_countwords(s, c))
	{
		len = ft_countlen(s, c, p);
		if (!(tab[i] = (char *)m_malloc(sizeof(char) * (len + 1))))
			return (freetab(tab, i));
		i++;
	}
	tab = result(tab, s, c);
	return (tab);
}
