/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 15:57:58 by smhah             #+#    #+#             */
/*   Updated: 2021/06/09 13:49:36 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_print_error(char a, t_command_info *cmd, int i)
{
	if (a == '=' || (a >= '0' && a <= '9'))
	{
		printf("minishell: export: `%s': ", cmd->string[i]);
		printf("not a valid identifier\n");
		return (1);
	}
	return (0);
}

void	split_content(char **str)
{
	char **buffer;
	int i;

	i = 0;
	buffer = mod_split(*str, ' ');
	*str = ft_strdup("");
	while(buffer[i])
	{
		*str = ft_strjoin(*str, buffer[i]);
		if(buffer[i + 1])
			*str = ft_strjoin(*str, " ");
		i++;
	}
}

void	bypass_ternarie_1(t_command_info *cmd, char **content, int i, int j)
{
	if (cmd->string[i][j] == '=')
	{
		*content = &cmd->string[i][++j];
		split_content(content);
	}
	else
		*content = NULL;
}

void	ft_next_node(t_list_env **read_list, t_list_env **prev)
{
	*prev = *read_list;
	*read_list = (*read_list)->next;
}
