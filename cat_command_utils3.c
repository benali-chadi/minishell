/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_command_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:08:56 by smhah             #+#    #+#             */
/*   Updated: 2021/06/10 17:56:52 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	check_if_can_increment(char **args, int i, int j)
{
	if (args[i][j] && (args[i][j] != '$'
		|| ((g_all.one == 1 && args[i][j] == '$')
		|| args[i][j] == '$' || (j > 0
		&& args[i][j - 1] == '\\') || args[i][j + 1] == '\0')))
		return (1);
	return (0);
}

int	check_backslash(char *str, int e)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i] && i < e)
	{
		if (str[i] == '\\')
			c++;
		i++;
	}
	if (i > 0 && str[i - 1] == '\\')
	{
		if (c % 2 == 0)
		{	
			return (0);
		}
		else
			return (1);
	}
	return (0);
}
