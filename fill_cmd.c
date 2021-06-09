/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:08:59 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/09 16:55:36 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	check_end_1(char **args, char **split, int *i)
{
	char	a1;
	char	a2;

	a1 = split[*i][0];
	a2 = '\0';
	if (split[*i + 1])
		a2 = split[*i + 1][0];
	if (split[*i + 1] && (ft_strcmpr(split[*i] , ">") || ft_strcmpr(split[*i], "<") || ft_strcmpr(split[*i] , ">>")) && a2 != '>' && a2 != '<' )
		join_lonely_red(args, split, i);
	else if ((split[*i + 1] && a2 != '>' && a2 != '<'
			&& check_last_char(split[*i])))
		join_friendly_red(args, split, i);
	else if (split[*i + 1] && check_if_at_the_last(split[*i])
		&& (a2 == '>' || a2 == '<'))
	{
		printf("minishell: syntax error near unexpected token `%c'\n", a2);
		return (0);
	}
	if (redirection(args, 0) < 0)
		return (0);
	return (1);
}

char	**join_2_tab(char **tab1, char **tab2)
{
	char **tabtab;
	int i;
	int j;

	j = 0;	
	i = 0;
	tabtab = (char **)malloc(mod_strlen(tab1) * sizeof(char *) + mod_strlen(tab2) * sizeof(char *) + sizeof(char *));
	while(tab1[i] != NULL)
	{
		tabtab[i] = ft_strdup(tab1[i]);
		i++;
	}
	while(tab2[j] != NULL)
	{
		tabtab[i++] = ft_strdup(tab2[j++]);
	}
	tabtab[i] = NULL;
	return (tabtab);
}

int	fill_cmd_helper(char ***split)
{
	char	**args;
	int		i;
	char	**cmd_args;
	int 	j;

	j = 0;
	i = 0;
	g_cmd = m_malloc(sizeof (t_command_info));
	g_cmd->reds.in_num = 0;
	g_cmd->reds.out_num = 0;
	
	cmd_args = mod_split(clean_command_1((*split)[i]), ' ');
	(*split) = join_2_tab(cmd_args, &(*split)[i + 1]);
	// if (!(*split)[i + 1])
	// {
	// 	g_cmd->command = ft_strdup("");
	// 	g_cmd->options = NULL;
	// 	//printf("ENTER2\n");
	// 	return (i);
	// }
	while ((*split)[i] && ((*split)[i][0] == '<' || (*split)[i][0] == '>'))
	{
		args = mod_split_red((*split)[i], "><");
		if (!check_end_1(args, (*split), &i))
			return (-1);
		i++;
	}
	if (!(*split)[i])
	{
		printf("ENTER\n");
		g_cmd->command = ft_strdup("");
		g_cmd->options = NULL;
		return (i);
	}
	//cmd_args = mod_split(clean_command_1((*split)[i]), ' ');
	// if (mod_strlen(cmd_args) > 1)
	// {
	// 	g_cmd->command = m_malloc(ft_strlen(cmd_args[j]) + 1);
	// 	ft_strcpy(g_cmd->command, clean_command_1(cmd_args[j]));
	// 	j++;
	// 	if (cmd_args[j] && cmd_args[j][0] == '-')
	// 	{
	// 		g_cmd->options = m_malloc(ft_strlen(cmd_args[j]) + 1);
	// 		ft_strcpy(g_cmd->options, cmd_args[j]);
	// 		i++;
	// 	}
	// 	//i++;	
	// }
	// else
	// {
		// if (mod_strlen(cmd_args) > 1)
		// {
			// (*split) = join_2_tab(cmd_args, &(*split)[i + 1]);
			// if (!(*split)[i + 1])
			// {
			// 	g_cmd->command = ft_strdup("");
			// 	g_cmd->options = NULL;
			// 	//printf("ENTER2\n");
			// 	return (i);
			// }
			// else
			// 	printf("why:[%s]\n", (*split)[i + 1]);
		// }
		g_cmd->command = m_malloc(ft_strlen((*split)[i]) + 1);
		//printf("str is |%s|\n", (*split)[i]);
		ft_strcpy(g_cmd->command, (*split)[i]);
		//printf("--->(*split)[%d]=|%s|\n", i, (*split)[i]);
		i++;
		g_cmd->options = NULL;
		if ((*split)[i] && (*split)[i][0] == '-')
		{
			g_cmd->options = m_malloc(ft_strlen((*split)[i]) + 1);
			ft_strcpy(g_cmd->options, (*split)[i]);
			i++;
		}
		
	// }
	return (i);
}

int	check_end_2(char **args, char **split, int *i, int *s)
{
	char	a1;
	char	a2;

	a1 = split[*i][0];
	a2 = '\0';
	if (split[*i + 1])
		a2 = split[*i + 1][0];
	if (split[*i + 1] && (ft_strcmpr(split[*i] , ">") || ft_strcmpr(split[*i], "<") || ft_strcmpr(split[*i] , ">>")) && a2 != '>' && a2 != '<' )
		join_lonely_red(args, split, i);
	else if ((split[*i + 1] && a2 != '>' && a2 != '<'
			&& check_last_char(split[*i])))
		join_friendly_red(args, split, i);
	else if (split[*i + 1] && check_if_at_the_last(split[*i])
		&& (a2 == '>' || a2 == '<'))
	{
		printf("minishell: syntax error near unexpected token `%c'\n", a2);
		return (0);
	}
	if (cat_command_string(args, s) < 0)
		return (0);
	return (1);
}

void	continue_our_road(int s, int p)
{
	if (s)
		add_last_cmd(g_cmd->string[s - 1], "_");
	else if (g_cmd->options)
		add_last_cmd(g_cmd->options, "_");
	else
		add_last_cmd(g_cmd->command, "_");
	test(g_cmd);
	g_cmd->pipe = p;
	cmd_lstadd_back(&g_commands, g_cmd);
}

int		is_red(char a)
{
	if (a == '>' || a == '<')
		return (1);
	return (0);
}


// void	remove_before_red(char **str)
// {
// 	int i;

// 	i = 0;
// 	while((*str)[i])
// 	{
// 		if(is_red((*str)[i] && (*str)[i + 1]))
// 		{
// 			ft_strcpy((*str), &(*str)[i]);
// 			return;
// 		}
// 		i++;
// 	}
// 	str[0] = ft_strdup(str[1]);
// 	return;
// }

int	fill_cmd(char **split, int p)
{
	char	**args;
	int		i;
	int		s;

	i = fill_cmd_helper(&split) - 1;
	if (!*split || i < 0)
		return (-1);
	s = 0;
	g_cmd->string[0] = NULL;
	g_move_and_pass = 0;
	while (split[++i])
	{
		//printf("second_check:split[i]=%s\n", split[i]);
		args = mod_split_red(split[i], "><");
		if (g_move_and_pass == 1 || g_move_and_pass == 2)
		{
			g_move_and_pass = 0;
			if (!check_end_2(&args[1], split, &i, &s))
				return (-1);
		}
		else
		{
			if (!check_end_2(args, split, &i, &s))
				return (-1);
		}
	}
	continue_our_road(s, p);
	return (1);
}
