/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:14:40 by cbenali-          #+#    #+#             */
/*   Updated: 2021/05/13 15:39:06 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	check_white_spaces(void)
{
	int	i;
	int	j;

	i = 0;
	while (g_utils.m_split[i] != NULL)
	{
		j = 0;
		while (g_utils.m_split[i][j] == ' ' || g_utils.m_split[i][j] == '\t')
		{
			j++;
		}
		if ((g_utils.m_split[i][j] == '\0' && g_utils.m_split
			[i + 1]) || (g_utils.m_split[i][j] == '\0' && g_case_index
			[i + 1] == '1' && i > 0))
		{
			ft_printf("minishell: syntax error near unexpected token `;;'\n");
			g_case_index[i + 1] = 0;
			g_return = 258;
			return (0);
		}
		i++;
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
		add_back(&g_list_env, name, content, name_content);
	return (1);
}

int		check_args(char **strings)
{
	int i;

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

void	leave(char **strings)
{
	unsigned char uc;
	int ret;

	uc = 0;
	ret = check_args(strings);
	if (ret >= 0)
	{
		if (ret == 0)
		{
			uc = ft_atoi(strings[0]);
		}
		else if (ret == 1)
		{
			uc = 255;
			ft_printf("exit: %s: numeric argument required\n", strings[0]);
		}
		else
		{
			ft_printf("exit: too many arguments\n");
			return;
		}
	}
	to_free();
	close(g_utils.out);
	exit(uc);
}

void	print_prompt()
{
	ft_putstr_fd("\033[0;32mCS\033[0;31m@minishell \033[0m",
				g_utils.out);
}
