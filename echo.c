/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:02:50 by smhah             #+#    #+#             */
/*   Updated: 2021/06/11 18:47:09 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	check_quotes_one(void)
{
	if (g_all.var_one == 0 && g_all.var_two == 0)
	{
		g_all.var_one = 1;
		return (1);
	}
	else if (g_all.var_one == 1 && g_all.var_two == 0)
	{
		g_all.var_one = 0;
		return (1);
	}
	return (0);
}

int	check_quotes_two(void)
{
	if (g_all.var_two == 0 && g_all.var_one == 0)
	{
		g_all.var_two = 1;
		return (1);
	}
	else if (g_all.var_two == 1 && g_all.var_one == 0)
	{
		g_all.var_two = 0;
		return (1);
	}
	return (0);
}

int	ft_continue(int *force, int i, int j, t_command_info *cmd)
{
	if (cmd->string[i][j] == '\\' && *force != 1
	&& g_all.var_one != 1 && g_all.var_two != 1)
	{
		*force = 1;
		return (1);
	}
	if (cmd->string[i][j] == '\'' && *force != 1)
		if (check_quotes_one())
			return (1);
	if (cmd->string[i][j] == '"' && *force != 1)
		if (check_quotes_two())
			return (1);
	return (0);
}

void	ft_echo(t_command_info *cmd)
{
	int	i;
	int	force;
	int	s;

	s = 0;
	i = -1;
	g_all.var_one = 0;
	g_all.var_two = 0;
	force = 0;
	(void)cmd;
	while (cmd->string[++i])
	{
		write(1, cmd->string[i], ft_strlen(cmd->string[i]));
		if (cmd->string[i + 1])
			write(1, " ", 1);
	}
	if (!cmd->options || !ft_strcmpr(cmd->options, "-n"))
		printf("\n");
}
