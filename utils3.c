/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:14:40 by cbenali-          #+#    #+#             */
/*   Updated: 2021/03/04 12:05:12 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int		check_white_spaces(void)
{
	int i;
	int j;

	i = 0;
	while (g_utils.m_split[i] != NULL)
	{
		j = 0;
		while (g_utils.m_split[i][j] == ' ' || g_utils.m_split[i][j] == '\t')
		{
			j++;
		}
		if ((g_utils.m_split[i][j] == '\0' && g_utils.m_split[i + 1]) ||
		(g_utils.m_split[i][j] == '\0' && g_case_index[i + 1] == '1' && i > 0))
		{
			ft_printf("minishell: syntax error near unexpected token `;;'\n");
			g_case_index[i + 1] = 0;
			return (0);
		}
		i++;
	}
	return (1);
}

int		mod_strlen(char **s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		add_last_cmd(char *s, char *name)
{
	char	*content;
	char	*name_content;
	int		i;

	i = ft_strlen(name);
	content = m_malloc(ft_strlen(s) + 1);
	ft_strcpy(content, s);
	name_content = m_malloc(i + ft_strlen(content) + 1);
	name_content = ft_strcpy(name_content, name);
	name_content[i++] = '=';
	ft_strcpy(&name_content[i], s);
	if (check_var(name, content, name_content))
		add_back(&g_list_env, name, content, name_content);
	return (1);
}

void	leave(void)
{
	to_free();
	close(g_utils.out);
	exit(0);
}
