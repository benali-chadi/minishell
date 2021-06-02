/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_split_red_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:04:04 by smhah             #+#    #+#             */
/*   Updated: 2021/06/02 07:53:46 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	check_quots(const char *str, int i)
{
	if (str[i] == '"')
		g_var_two = 1;
	if (str[i] == '\'')
		g_var_one = 1;
	return (1);
}

int	re_check_quots(const char *str, int i)
{
	if (str[i] == '"')
	{
		if (g_var_two == 1)
			g_var_two = 0;
		else
			g_var_two = 1;
	}
	if (str[i] == '\'')
	{
		if (g_var_one == 1)
			g_var_one = 0;
		else
			g_var_one = 1;
	}
	return (1);
}

int	ft_countwords_red(const char *str, char *c)
{
	int i;
	int compteur;

	g_var_one = 0;
	g_var_two = 0;
	compteur = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (g_var_one == 0 && g_var_two == 0 && str[i] && ft_strchr(c, str[i]))
		{
			//printf("str[i]:|%c|\n", str[i]);
			i++;
		}
		if (str[i] == '\0')
			break ;
		compteur++;
		while ((g_var_one == 1 || g_var_two == 1 || (i && str[i - 1] == '\\') ||
		!ft_strchr(c, str[i])) && str[i] != '\0' && re_check_quots(str, i))
		{
			i++;
		}
		if (str[i] == '\0')
			break ;
	}
	if(compteur == 0)
		compteur = 1;
	else
		compteur += compteur - 1;
	return (compteur + 10);
}

int			ft_countlen_red(const char *str, char *c, int *i)
{
	int len;

	g_var_one = 0;
	g_var_two = 0;
	len = 0;
	while (str[*i] != '\0')
	{
		while (g_var_one == 0 && g_var_two == 0 && str[*i] && ft_strchr(c, str[*i]))
			*i = *i + 1;
		if (str[*i] == '\0')
			return (len);
		while ((g_var_one == 1 || g_var_two == 1 ||
		(*i && str[*i - 1] == '\\') || !ft_strchr(c, str[*i]))
			&& str[*i] != '\0' && re_check_quots(str, *i))
		{
			(*i)++;
			len++;
		}
		return (len);
		if (str[*i] == '\0')
			return (len);
	}
	return (len + 10);
}
