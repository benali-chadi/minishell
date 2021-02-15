/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:57:58 by smhah             #+#    #+#             */
/*   Updated: 2021/02/14 15:58:32 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int		ft_print_error(char a, t_command_info *cmd, int i)
{
	if (a == '=' || (a >= '0' && a <= '9'))
	{
		ft_printf("minishell: export: `%s': ", cmd->string[i]);
		ft_printf("not a valid identifier\n");
		g_return = 1;
		return (1);
	}
	return (0);
}
