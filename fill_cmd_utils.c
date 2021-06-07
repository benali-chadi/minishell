/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 11:00:09 by smhah             #+#    #+#             */
/*   Updated: 2021/06/07 21:15:13 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	check_last_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 0 && (str[i - 1] == '>' || str[i - 1] == '<'))
		return (1);
	return (0);
}

int	check_if_last(char *srch, char **str)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(*str);
	printf("str:%s\n", *str);
	while ((*str)[i] && ft_strchr(srch, (*str)[i]))
		i++;
	while ((*str)[i])
	{
		if ((ft_strchr(srch, (*str)[i])))
		{
			if ((*str)[i + 1] && ft_strchr(srch, (*str)[i + 1]))
			{
				(*str)[i] = '\0';
				return (2);
			}
			(*str)[i] = '\0';
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_if_at_the_last(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i > 2)
		if ((str[i - 1] == '>' || str[i - 1] == '<')
			&& (str[i] == '>' || str[i] == '<'))
			return (1);
	if (str[i] == '>' || str[i] == '<')
		return (1);
	return (0);
}

void	join_lonely_red(char **args, char **split, int *i)
{
	int	ret_slash;

	args[0] = ft_strjoin(args[0], split[*i + 1]);
	ret_slash = check_if_last("><", &args[0]);
	printf("ret_slash:%d\n", ret_slash);
	if (!ret_slash)
		*i = *i + 1;
	else
		g_move_and_pass = ret_slash;
}

void	join_friendly_red(char **args, char **split, int *i)
{
	int	ret_slash;

	args[1] = ft_strjoin(args[1], split[*i + 1]);
	ret_slash = check_if_last("><", &args[1]);
	if (!ret_slash)
		*i = *i + 1;
	else
		g_move_and_pass = ret_slash;
}
