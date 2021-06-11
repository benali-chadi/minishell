/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 05:55:40 by macbook           #+#    #+#             */
/*   Updated: 2021/06/11 05:58:02 by macbook          ###   ########.fr       */
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
