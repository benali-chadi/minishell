/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:14:40 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/11 13:39:47 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	chck_spc(char *s, char a)
{
	int	i;
	int	c;

	c = 0;
	i = -1;
	while (s[++i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		if (s[i] == a && c == 0)
			c = 1;
		else if (s[i] == a)
		{
			check_error_type(i, s, a);
			return (0);
		}
		else
			c = 0;
	}
	return (1);
}

int	mod_strlen(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	add_last_cmd(char *s, char *name)
{
	char	*content;
	char	*name_content;

	content = ft_strjoin("", s);
	name_content = ft_strjoin(name, "=");
	name_content = ft_strjoin(name_content, content);
	if (check_var(name, content, name_content))
		add_back(&g_all.list_env, name, content, name_content);
	return (1);
}

int	check_args(char **strings)
{
	int	i;

	if (!*strings)
		return (-1);
	i = 0;
	while (strings[0][i])
		if (ft_isalpha(strings[0][i++]))
			return (1);
	if (strings[1])
		return (2);
	return (0);
}

void	leave (char **strings)
{
	unsigned char	uc;
	int				ret;

	uc = 0;
	ret = check_args(strings);
	if (ret >= 0)
	{
		if (ret == 0)
			uc = ft_atoi(strings[0]);
		else if (ret == 1)
		{
			uc = 255;
			printf("minishell: exit: %s: numeric argument required\n",
				strings[0]);
		}
		else
		{
			printf("minishell: exit: too many arguments\n");
			return ;
		}
	}
	close (g_all.utils.out);
	exit(uc);
}
