/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_command_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:25:55 by smhah             #+#    #+#             */
/*   Updated: 2021/04/10 18:28:17 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	check_quots_after_dollar(char **args, int i, int j, int *s)
{
	if (g_two == 1)
		fill_command_string(args[i][j], *s);
	else
		change_one_two(args[i][j]);
}
