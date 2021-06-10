/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_split_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:31:56 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/10 18:06:29 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	p_e(char *msg)
{
	printf("minishell: syntax error near unexpected token `%s'\n", msg);
	return (0);
}

int	skip_repeat(char *str, int *i, char c)
{
	int	repeat;

	repeat = 0;
	while (str[*i] == c)
	{
		if (*i && str[*i - 1] == '|' && str[*i + 1] == '|'
			&& str[*i + 2] == '|')
			if (c == '|')
				return (p_e("||"));
		if (*i && str[*i - 1] == '|')
			if (c == '|')
				return (p_e("|"));
		if (c == ';')
		{
			repeat++;
			if (repeat > 1)
				return (p_e(";;"));
		}
		*i += 1;
	}
	return (1);
}

int	stock_index(int a)
{
	g_all.case_index[a] = '1';
	g_all.case_index[a + 1] = '\0';
	return (1);
}
