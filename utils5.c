/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 13:39:51 by smhah             #+#    #+#             */
/*   Updated: 2021/06/11 13:40:02 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	check_error_type(int i, char *s, char a)
{
	if (i > 0 && s[i - 1] == a)
		printf("minishell: syntax error near unexpected token `%c%c'\n",
			a, a);
	else
		printf("minishell: syntax error near unexpected token `%c'\n", a);
}
