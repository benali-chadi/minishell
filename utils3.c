/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:14:40 by cbenali-          #+#    #+#             */
/*   Updated: 2021/04/10 19:03:10 by smhah            ###   ########.fr       */
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

void	leave(void)
{
	to_free();
	close(g_utils.out);
	exit(0);
}

void	print_prompt()
{
	ft_putstr_fd("\033[0;32mCS\033[0;31m@minishell \033[0m",
				g_utils.out);
}
