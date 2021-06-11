/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:14:40 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/11 05:51:41 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	check_white_spaces(void)
{
	int	i;
	int	j;

	i = 0;
	int e = 0;
	int f = 0;
	while(g_all.utils.m_split[e])
		e++;
	while(f < e)
		printf("[%c]", g_all.case_index[(f++) + 1]);
	printf("\n");
	while (g_all.utils.m_split[i] != NULL)// && (!check_if_void(g_all.utils.m_split[i])))
	{
		j = 0;
		while (g_all.utils.m_split[i][j] == ' '
			|| g_all.utils.m_split[i][j] == '\t')
			j++;
		printf("index:[%c]\n", g_all.case_index[i + 1]);
		if ((g_all.utils.m_split[i][j] == '\0' && g_all.utils.m_split
			[i + 1])) //|| (g_all.utils.m_split[i][j] == '\0' && g_all.case_index
		//	[i + 1] == '1' && i > 0))
		{
			printf("minishell: syntax error near unexpected token `;;'\n");
			// g_all.case_index[i + 1] = 0;
			// g_all.case_index[i] = 0;
			g_all.returnn = 258;
			return (0);
		}
		i++;
	}
	f = 0;
	while(f < i)
		g_all.case_index[f++] = 0;
	return (1);
}

int	check_white_spc(char *s)
{
	int i;
	int c;

	c = 0;
	i = 0;
	while(s[i])
	{
		while(s[i] && s[i] == ' ')
			i++;
		if(!s[i])
			break ;
		if(s[i] == ';' && c == 0)
			c = 1;
		else if(s[i] == ';')
		{
			printf("minishell: syntax error near unexpected token `;'\n");
			return (0);
		}
		else
			c = 0;
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

void	leave(char **strings)
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
	close(g_all.utils.out);
	exit(uc);
}
