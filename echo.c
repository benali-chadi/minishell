/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:00:31 by cbenali-          #+#    #+#             */
/*   Updated: 2021/02/01 15:47:13 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int		quote(char c)
{
	if (c == '"' || c == '\'')
		return (c);
	return (0);
}

int		to_print(char *str, int *j, char c)
{
	if (c)
		(*j)++;
	while (str[(*j)] && str[(*j)] != c)
	{
		if (!c && (str[(*j)] == '"' || str[(*j)] == '\''))
			return (1);
		if (str[(*j)] == '\\' &&
		(g_utils.cnt[(int)str[(*j) + 1]] || str[(*j) + 1] == '0'))
		{
			ft_putchar_fd(g_utils.cnt[(int)str[(*j) + 1]], 1);
			(*j) += 2;
			continue;
		}
		ft_putchar_fd(str[(*j)], 1);
		(*j)++;
	}
	return (0);
}

void	to_loop(t_command_info *cmd)
{
	int i;
	int j;
	int g;

	i = 0;
	g = 0;
	while (cmd->string[i])
	{
		j = 0;
		while (cmd->string[i][j])
		{
			g = to_print(cmd->string[i], &j, quote(cmd->string[i][j]));
			if (cmd->string[i][j] && !g)
				j++;
			else
				g = 0;
		}
		i++;
		if (cmd->string[i])
			ft_putchar_fd(' ', 1);
	}
}

void	echo(t_command_info *cmd)
{
	int n;

	n = 0;
	if (cmd->options && ft_strcmpr(cmd->options, "-n"))
		n = 1;
	else if (cmd->options)
	{
		while (*cmd->options)
			ft_putchar_fd(*cmd->options++, 1);
		ft_putchar_fd(' ', 1);
	}
	to_loop(cmd);
	if (!n)
		ft_putchar_fd('\n', 1);
}

// void	echo(t_command_info *cmd)
// {
// 	int i;
// 	int one;
// 	int two;
// 	int indice;
// 	int j;

// 	one = 0;
// 	two = 0;
// 	i = 0;
// 	while(cmd->string[i])
// 	{
// 		//ft_printf("arg is:|%s|\n", cmd->string[i]);
// 		j = 0;
// 		while(cmd->string[i][j])
// 		{
// 			indice = 0;
// 			if(cmd->string[i][j] == '\'')
// 			{
// 				if(one == 0 && two == 0)
// 				{
// 					one = 1;
// 					indice = 1;
// 				}
// 				else if(one == 1 && two == 0)
// 				{
// 					one = 0;
// 					indice = 1;
// 				}
// 				else if(two == 1)
// 				{
// 					indice = 0;
// 				}
// 			}
// 			if(cmd->string[i][j] == '"')
// 			{
// 				if(two == 0 && one == 0)
// 				{
// 					two = 1;
// 					indice = 1;
// 				}
// 				else if(two == 1 && one == 0)
// 				{
// 					two = 0;
// 					indice = 1;
// 				}
// 				else if(one == 1)
// 					indice = 0;
// 			}
// 			if(!indice)
// 				ft_printf("%c" ,cmd->string[i][j]);
// 			indice = 0;
// 			j++;
// 		}
// 		i++;
// 	}
// 	ft_printf("\n");
// 	if(one == 1 || two == 1)
// 		ft_printf("CHNO KATKHWER\n");
// }