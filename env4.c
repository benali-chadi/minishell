/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 11:12:51 by smhah             #+#    #+#             */
/*   Updated: 2021/06/11 10:44:48 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	swap(int j, int i)
{
	char	*temp;

	temp = g_all.env_tab[j];
	g_all.env_tab[j] = g_all.env_tab[i];
	g_all.env_tab[i] = temp;
}

void	bubbleSort(void)
{
	int		i;
	int		j;

	i = 0;
	while (g_all.env_tab[i])
	{
		j = 0;
		while (g_all.env_tab[j])
		{
			if (ft_strncmp(g_all.env_tab[i], g_all.env_tab[j], 5000) < 0)
				swap(j, i);
			j++;
		}
		i++;
	}
	i = -1;
	while (g_all.env_tab[++i])
		printf("declare -x %s\n", g_all.env_tab[i]);
}

int	check_equal_at_the_last(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	loop_env(int e)
{
	t_list_env	*tmp;
	int			i;

	i = 0;
	tmp = g_all.list_env;
	while (tmp)
	{
		if (e)
			add_quotes_and_fill(tmp, &i);
		else if (tmp->content)
		{
			if (ft_strcmpr(tmp->name_content, "_=env"))
				printf("_=/usr/bin/env\n");
			else if (!ft_strcmpr("", tmp->content)
				|| check_equal_at_the_last(tmp->name_content))
				printf("%s\n", tmp->name_content);
		}
		tmp = tmp->next;
	}
	g_all.env_tab[i] = NULL;
	if (e)
		bubbleSort();
	return (1);
}

void	loop_env_cmd(void)
{
	t_histo	*tmp;

	tmp = g_all.histo;
	while (tmp)
	{
		printf("%s\n", tmp->command_line);
		tmp = tmp->next;
	}
}
