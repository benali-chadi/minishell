/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:02:50 by smhah             #+#    #+#             */
/*   Updated: 2021/06/02 21:44:08 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	check_quotes_one(void)
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

int	check_quotes_two(void)
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

int	ft_continue(int *force, int i, int j, t_command_info *cmd)
{
	if (cmd->string[i][j] == '\\' && *force != 1
	&& g_var_one != 1 && g_var_two != 1)
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

	i = -1;
	g_var_one = 0;
	g_var_two = 0;
	force = 0;
	printf("%s\n", *cmd->string);
	while (cmd->string[++i])
	{
		printf("HH\n");
		if (!cmd->indice[i])
			ft_printf("%s", clean_cmd(cmd->string[i]));
		else
			ft_printf("%s", cmd->string[i]);
		if (cmd->string[i + 1])
			ft_printf(" ");
	}
	if (!cmd->options || !ft_strcmpr(cmd->options, "-n"))
		ft_printf("\n");
}
