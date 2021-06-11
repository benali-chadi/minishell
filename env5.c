/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 05:55:40 by macbook           #+#    #+#             */
/*   Updated: 2021/06/11 10:49:42 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	check_var_solo(char *name)
{
	t_list_env	*read_env;

	read_env = g_all.list_env;
	while (read_env)
	{
		if (ft_strcmpr(read_env->name, name))
			return (0);
		read_env = read_env->next;
	}
	return (1);
}

void	add_quotes_and_fill(t_list_env *tmp, int *i)
{
	if (check_equal_at_the_last(tmp->name_content))
	{
		tmp->name_content = ft_strjoin(tmp->name, "=\"");
		tmp->name_content = ft_strjoin(tmp->name_content, tmp->content);
		tmp->name_content = ft_strjoin(tmp->name_content, "\"");
	}
	g_all.env_tab[(*i)++] = tmp->name_content;
}

int	check_if_void(char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i])
		return (0);
	return (1);
}
