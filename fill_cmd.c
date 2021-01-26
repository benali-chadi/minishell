/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <cbenali-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 17:11:55 by cbenali-          #+#    #+#             */
/*   Updated: 2021/01/19 18:09:37 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	fill_command_string(t_command_info *cmd, char a, int i)
{
	cmd->string[i][cmd->string_len++] = a;
	if (a == '\'')
		g_one = g_one == 1 ? 0 : 1;
	if (a == '"')
		g_two = g_two == 1 ? 0 : 1;
}

void	init_one_two(void)
{
	g_one = 0;
	g_two = 0;
}

void	red_file_names(t_command_info *cmd, char *args, int red, int j)
{
	int k;

	if (red == 1)
	{
		cmd->reds.out[cmd->reds.out_num].file_name =
		m_malloc(ft_strlen(args) + 1);
		k = 0;
		while (args[j])
			cmd->reds.out[cmd->reds.out_num].file_name[k++] = args[j++];
		cmd->reds.out[cmd->reds.out_num].file_name[k] = '\0';
		cmd->reds.out_num++;
	}
	else
	{
		cmd->reds.in_file_name[cmd->reds.in_num] =
		m_malloc(ft_strlen(args) + 1);
		k = 0;
		while (args[j])
			cmd->reds.in_file_name[cmd->reds.in_num][k++] = args[j++];
		cmd->reds.in_file_name[cmd->reds.in_num][k] = '\0';
		cmd->reds.in_num++;
	}
}

void	red_helper(t_command_info *cmd, char *arg, int *j, int *red)
{
	if (arg[*j] == '>')
	{
		while (arg[*j] && arg[*j] == '>')
		{
			cmd->reds.out[cmd->reds.out_num].sym[*j] = arg[*j];
			(*j)++;
		}
		*red = 1;
	}
	else
	{
		(*j)++;
		*red = 0;
	}
}

int		redirection(t_command_info *cmd, char **args, int *i)
{
	int j;
	int red;

	j = 0;
	red_helper(cmd, args[*i], &j, &red);
	if ((size_t)j >= ft_strlen(args[*i]))
	{
		(*i)++;
		j = 0;
	}
	if (!args[*i])
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 1);
		return (-1);
	}
	red_file_names(cmd, args[*i], red, j);
	(*i)++;
	if (!args[*i])
		return (1);
	j = 0;
	if (args[*i] && (args[*i][j] == '<' || args[*i][j] == '>'))
		if (!redirection(cmd, args, i))
			return (-1);
	return (1);
}

int		cat_command_string(t_command_info *cmd, char **args, int i)
{
	char	*var;
	int		j;
	int		k;
	int		s;

	s = 0;
	while (args[i])
	{
		j = 0;
		if (args[i] && (args[i][j] == '<' || args[i][j] == '>'))
			if (redirection(cmd, args, &i) < 0)
				return (-1);
		if (!args[i])
			break ;
		init_one_two();
		cmd->string[s] = m_malloc(ft_strlen(args[i]) + 1);
		cmd->string[s] = ft_strcpy(cmd->string[s], args[i]);
		cmd->string_len = 0;
		// j = 0;
		while (args[i][j])
		{
			if ((args[i][j] == '$' && args[i][j + 1] && g_one != 1 ) || (args[i][j] == '$' && args[i][j + 1] && g_one == 1 && g_two == 1))
			{
				j++;
				var = m_malloc(ft_strlen(args[i]));
				k = 0;
				while (is_alpha_digit(args[i][j]) && args[i][j] != '$' && args[i][j])
					var[k++] = args[i][j++];
				var[k] = '\0';
				if (ft_strcmpr(var, "?"))
				{
					g_str_return = ft_itoa(g_return);
					cmd->string[s] = ft_realloc(cmd->string[s] ,ft_strlen(cmd->string[s]) + ft_strlen(args[i]) + ft_strlen(g_str_return) + 1 + g_two);
					k = 0;
					while (g_str_return[k])
					{
						cmd->string[s][cmd->string_len++] = g_str_return[k];
						k++;
					}
					cmd->string[s][cmd->string_len++] = '\0';
				}
				else
					compare_var(cmd, var, args[i], s);
				if (args[i][j] == '"' || args[i][j] == '\'')
					fill_command_string(cmd, args[i][j], s);
			}
			else
				fill_command_string(cmd, args[i][j], s);
			if (args[i][j] && (args[i][j] != '$' || (g_one == 1 && args[i][j] == '$')))
				j++;
		}
		cmd->string[s][cmd->string_len] = '\0';
		s++;
		i++;
	}
	cmd->string[s] = NULL;
	return (1);
}

int		fill_cmd(char **split, int p)
{
	t_command_info *cmd;
	int i;

	i = 0;
	if (!*split)
		return (0);
	cmd = malloc(sizeof(t_command_info));
	
	// initializing reds
	
	cmd->reds.in_num = 0;
	cmd->reds.out_num = 0;
	
	if (split[i][0] == '<' || split[i][0] == '>')
		if (redirection(cmd, split, &i) < 0)
			return (-1);
	
	cmd->command = m_malloc(ft_strlen(split[i]) + 1);

	ft_strcpy(cmd->command, split[i]);
	i++;

	if (split[i] && split[i][0] == '-')
	{
		cmd->options = m_malloc(ft_strlen(split[i]) + 1);
		ft_strcpy(cmd->options, split[i]);
		i++;
	}
	else
		cmd->options = NULL;
	if (split[i])
        if (cat_command_string(cmd, split, i) < 0)
			return (-1);
	test(cmd);
	cmd->pipe = p;
	cmd_lstadd_back(&g_commands, cmd);
	return (1);
}
