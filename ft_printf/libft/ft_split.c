/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:37:31 by cbenali-          #+#    #+#             */
/*   Updated: 2019/10/21 16:02:46 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strl(char const *str, char c)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	if (str[0] != c && str[0] != '\0')
		words++;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			if (str[i + 1] != c && str[i + 1] != '\0')
				words++;
		i++;
	}
	return (words);
}

static int	wordlen(char const *str, int *p, char c)
{
	int	i;
	int	w;

	w = 0;
	i = *p;
	while (str[i] == c)
	{
		i++;
		*p += 1;
	}
	while (str[i] != '\0')
	{
		if (str[i] == c)
			break ;
		w++;
		i++;
	}
	return (w);
}

static void	give_value(char *a_str, char const *str, int *p, int c)
{
	int	j;

	j = -1;
	while (str[*p] != '\0')
	{
		if (str[*p] == c)
			break ;
		a_str[++j] = str[*p];
		*p += 1;
	}
	a_str[++j] = '\0';
}

static char	**free_tab(char **a_str, int i)
{
	while (i--)
		free(a_str[i]);
	free(a_str);
	a_str = NULL;
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	char	**a_str;
	int		i;
	int		k;
	int		*p;
	int		words;

	if (!str)
		return (0);
	words = strl(str, c);
	i = -1;
	k = 0;
	p = &k;
	a_str = (char **)malloc((words + 1) * (sizeof(char *)));
	if (!a_str)
		return (0);
	while (++i < words)
	{
		a_str[i] = (char *)malloc(wordlen(str, p, c) + 1);
		if (!a_str[i])
			return (free_tab(a_str, i));
		give_value(a_str[i], str, p, c);
	}
	a_str[i] = 0;
	return (a_str);
}
