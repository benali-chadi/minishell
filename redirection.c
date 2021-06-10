/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:59:14 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/10 17:59:31 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	red_file_names(char *args, int red, int j)
{
	int		k;
	char	*str;

	if (red == 1)
	{
		g_all.cmd->reds.out[g_all.cmd->reds.out_num].file_name = m_malloc
			(ft_strlen(&args[j]) + 1);
		str = clean_cmd(&args[j]);
		k = -1;
		while (str[++k])
			g_all.cmd->reds.out[g_all.cmd->reds.out_num].file_name[k] = str[k];
		g_all.cmd->reds.out[g_all.cmd->reds.out_num].file_name[k] = '\0';
		g_all.cmd->reds.out_num++;
	}
	else
	{
		g_all.cmd->reds.in_file_name[g_all.cmd->reds.in_num
		] = m_malloc(ft_strlen(args) + 1);
		str = clean_cmd(&args[j]);
		k = -1;
		while (str[++k])
			g_all.cmd->reds.in_file_name[g_all.cmd->reds.in_num][k] = str[k];
		g_all.cmd->reds.in_file_name[g_all.cmd->reds.in_num][k] = '\0';
		g_all.cmd->reds.in_num++;
	}
}

int	for_norme(int cnt, char c)
{
	if (cnt > 1)
	{
		if (c == '>')
			printf("minishell: syntax error near unexpected token `>>'\n");
		else
			printf("minishell: syntax error near unexpected token `>'\n");
		g_all.returnn = 258;
		return (0);
	}
	return (1);
}

int	red_helper(char *arg, int *j, int *red)
{
	int	cnt;

	cnt = 0;
	if (arg[*j] == '>')
	{
		while (arg[*j] && arg[*j] == '>')
		{
			if (!for_norme(cnt, arg[*j + 1]))
				return (0);
			g_all.cmd->reds.out[g_all.cmd->reds.out_num].sym[*j] = arg[*j];
			(*j)++;
			cnt++;
		}
		*red = 1;
	}
	else
	{
		(*j)++;
		*red = 0;
	}
	return (1);
}

int	redirection(char **args, int i)
{
	int	j;
	int	red;

	j = 0;
	if (!red_helper(args[i], &j, &red))
		return (-1);
	if ((size_t)j >= ft_strlen(args[i]))
	{
		i++;
		j = 0;
	}
	if (!args[i])
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 1);
		return (-1);
	}
	red_file_names(args[i], red, j);
	i++;
	if (!args[i])
		return (1);
	j = 0;
	if (args[i] && (args[i][j] == '<' || args[i][j] == '>'))
		if (!redirection(args, i))
			return (-1);
	return (1);
}
