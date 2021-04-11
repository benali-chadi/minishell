/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_clean_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:29:26 by cbenali-          #+#    #+#             */
/*   Updated: 2021/04/10 19:13:09 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	fill_command(char a)
{
	g_str_command[g_command_len++] = a;
	if (a == '\'')
		g_one = g_one == 1 ? 0 : 1;
	if (a == '"')
		g_two = g_two == 1 ? 0 : 1;
}

int	check_quotes_one1(void)
{
	if (g_var_one == 0 && g_var_two == 0)
	{
		g_var_one = 1;
		return (1);
	}
	else if (g_var_one == 1 && g_var_two == 0)
	{
		g_var_one = 0;
		return (1);
	}
	return (0);
}

int	check_quotes_two1(void)
{
	if (g_var_two == 0 && g_var_one == 0)
	{
		g_var_two = 1;
		return (1);
	}
	else if (g_var_two == 1 && g_var_one == 0)
	{
		g_var_two = 0;
		return (1);
	}
	return (0);
}

int	ft_continue1(int *force, int i, char *str)
{
	if ((str[i] == '\\' && *force != 1
			&& g_var_one != 1 && g_var_two != 1)
		|| (str[i] == '\\' && *force != 1 && is_special(str[i + 1])))
	{
		*force = 1;
		return (1);
	}
	if (str[i] == '\'' && *force != 1)
		if (check_quotes_one1())
			return (1);
	if (str[i] == '"' && *force != 1)
		if (check_quotes_two1())
			return (1);
	return (0);
}

char	*clean_cmd(char *str)
{
	int		i;
	int		j;
	int		force;
	char	*str2;

	if (!str)
		return (NULL);
	str2 = m_malloc(ft_strlen(str) + 1);
	i = -1;
	g_var_one = 0;
	g_var_two = 0;
	force = 0;
	j = 0;
	while (str[++i])
	{
		if (ft_continue1(&force, i, str))
			continue ;
		str2[j++] = str[i];
		force = 0;
	}
	str2[j] = '\0';
	if (g_var_one == 1 || g_var_two == 1)
		ft_printf("CHNO KATKHWER\n");
	return (str2);
}
