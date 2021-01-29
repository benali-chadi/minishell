/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_linkd_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:59:43 by cbenali-          #+#    #+#             */
/*   Updated: 2021/01/29 15:13:48 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_command_info		*cmd_lstlast(t_command_info *lst)
{
	t_command_info *tmp;

	tmp = lst;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	return (tmp);
}

void				cmd_lstadd_back(t_command_info **commands,
					t_command_info *new)
{
	t_command_info *tmp;

	if (commands && *commands && new)
	{
		tmp = cmd_lstlast(*commands);
		tmp->next = new;
		new->next = NULL;
	}
	else if (!*commands)
	{
		*commands = new;
		new->next = NULL;
	}
}
