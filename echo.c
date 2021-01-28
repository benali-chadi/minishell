/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:00:31 by cbenali-          #+#    #+#             */
/*   Updated: 2021/01/28 16:00:32 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_shell.h"

void	echo(t_command_info *cmd)
{
	int c;
	int i;
	int g;
	int n;
	int j;

	i = 0;
	g = 0;
	n = 0;
	if (cmd->options && ft_strcmpr(cmd->options, "-n"))
		n = 1;
	else if (cmd->options)
	{
		while (*cmd->options)
			ft_putchar_fd(*cmd->options++, 1);
		ft_putchar_fd(' ', 1);
	}
	while (cmd->string[i])
	{
		j = 0;
		while (cmd->string[i][j])
		{
			if (cmd->string[i][j] == '"' || cmd->string[i][j] == '\'')
				c = cmd->string[i][j++];
			else
				c = 0;
			while (cmd->string[i][j] && cmd->string[i][j] != c)
			{
				if (!c && (cmd->string[i][j] == '"' || cmd->string[i][j] == '\'' ))
				{
					g = 1;
					break ;
				}
				if (cmd->string[i][j] == '\\' && (g_utils.cnt[(int)cmd->string[i][j + 1]] || cmd->string[i][j + 1] == '0'))
				{
					ft_putchar_fd(g_utils.cnt[(int)cmd->string[i][j + 1]], 1);
					j += 2;
					continue;
				}
				ft_putchar_fd(cmd->string[i][j], 1);
				j++;
			}
			if (cmd->string[i][j] && !g)
				j++;
			else
				g = 0;
		}
		i++;
		if (cmd->string[i])
			ft_putchar_fd(' ', 1);
	}
	if (!n)
	 	ft_putchar_fd('\n', 1);
	
}