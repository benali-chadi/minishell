/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:01:03 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/02 21:25:03 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_countwords(char *str, char c)
{
	int	i;
	int	compteur;

	g_var_one = 0;
	g_var_two = 0;
	compteur = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (!skip_repeat(str, &i, c))
			return (-1);
		if (str[i] == '\0')
			break ;
		compteur++;
		while ((g_var_one == 1 || g_var_two == 1
				|| str[i] != c || (i && str[i - 1] == '\\'))
			&& str[i] != '\0' && re_check_quots(str, i))
			i++;
		if (str[i] == '\0')
			break ;
	}
	return (compteur);
}

int	ft_countlen(const char *str, char c, int *i)
{
	int	len;

	g_var_one = 0;
	g_var_two = 0;
	len = 0;
	while (str[*i] != '\0')
	{
		while (str[*i] == c)
			*i = *i + 1;
		if (str[*i] == '\0')
			return (len);
		while ((g_var_one == 1 || g_var_two == 1
				|| (*i && str[*i - 1] == '\\') || str[*i] != c)
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

char	**result(char **tab1, const char *str, char c)
{
	int	a;
	int	b;
	int	i;

	i = 0;
	a = 0;
	g_var_one = 0;
	g_var_two = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] == '\0' && stock_index(a))
			break ;
		g_case_index[a] = '0';
		b = 0;
		while ((g_var_one == 1 || g_var_two == 1
				|| (i && str[i - 1] == '\\') || str[i] != c)
			&& str[i] != '\0' && re_check_quots(str, i))
			tab1[a][b++] = str[i++];
		tab1[a][b] = '\0';
		a++;
	}
	tab1[a] = 0;
	return (tab1);
}

char	**freetab(char **tab1, int i)
{
	// while (i >= 0)
	// {
	// 	free(tab1[i]);
	// 	i--;
	// }
	// free(tab1);
	tab1 = NULL;
	(void)i;
	return (0);
}

char	**mod_split(char *s, char c)
{
	int		i;
	int		casee;
	char	**tab1;
	int		*p;
	int		len;

	len = 0;
	tab1 = NULL;
	i = 0;
	casee = 0;
	if (s)
		casee = ft_countwords(s, c);
	if (!s || casee < 0)
		return (0);
	if (!(tab1 = alloc_1(tab1, casee))) // zedt hadi
		return (0);
	casee = 0;
	p = &casee;
	while (i < ft_countwords(s, c) && calcule_len(&len, s, c, p))
    {
        if (!(tab1[i] = (char *)m_malloc(sizeof(char) * (len + 1))))
            return (freetab(tab1, i));
        i++;
    }
	tab1 = result(tab1, s, c);
	return (tab1);
}
