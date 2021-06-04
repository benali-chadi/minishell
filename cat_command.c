/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:21:41 by cbenali-          #+#    #+#             */
/*   Updated: 2021/06/04 10:59:52 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	first_condition(int j, char **args, int i, int *s)
{
	g_print_next = 0;
	j++;
	g_str_var = m_malloc(ft_strlen(args[i]));
	g_var_k = 0;
	while (args[i][j] && (is_alpha_digit(args[i][j]) || args[i][j] == '_'))
		g_str_var[g_var_k++] = args[i][j++];
	g_str_var[g_var_k] = '\0';
	if (ft_strcmpr(g_str_var, "?"))
	{
		g_str_return = ft_itoa(g_return);
		g_cmd->string[*s] = ft_realloc(g_cmd->string[*s],
				ft_strlen(g_cmd->string[*s]) + ft_strlen(args[i])
				+ ft_strlen(g_str_return) + 1 + g_two);
		g_var_k = 0;
		while (g_str_return[g_var_k])
		{
			g_cmd->string[*s][g_cmd->string_len++] = g_str_return[g_var_k];
			g_var_k++;
		}
		g_cmd->string[*s][g_cmd->string_len++] = '\0';
	}
	else
		replace_var(args, i, j, s);
	return (j);
}

int	check_backslash(char *str, int e)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (str[i] && i < e)
	{
		if(str[i] == '\\')
			c++;
		i++;				
	}
	if (i > 0 && str[i - 1] == '\\')
	{
		if (c % 2 == 0)
		{	
			return (0);
		}
		else
			return (1);
	}
	return (0);
}

int	condition1(char a1, char a2, char *str, int e)
{
	if (a1 == '$' && a2 && g_one != 1 && !is_digit(a2) && a2 != '.' && !check_backslash(str, e))
		return (1);
	return (0);
}

int	check_first_char(char **args, int *i, int *j)
{
	char	a1;
	char	a2;

	a1 = args[*i][*j];
	a2 = '\0';
	// !!!!!!!!!!!!!!!!!!!!!!!!!!! ATTENTION SEGFAULT !!!!!!!!!!!!!!!!!!!!!!!!
	// ^^^^^^^^^^^^^^^^^^^
	if (args[*i][*j + 1])
		a2 = args[*i][*j + 1];
	//printf("a2 is [%c]\n", a2);
	if (condition1(a1, a2, args[*i], *j))
	{
		if (a1 == '$' && a2 == '"' && !args[*i][*j + 2])
			return (0);
		return (1);
	}
	else if ((a1 == '$' && a2 && g_one != 1 && is_digit(a2) && a2 != '.')
		|| (a1 == '$' && a2 && g_one == 1
			&& g_two == 1 && is_digit(a2) && a2 != '.'))
	{
		printf("ENTER@@@\n");
		*j = *j + 2;
		return (2);
	}
	else if ((a1 == '$' && a2 && g_one != 1 && !is_digit(a2) && a2 == '.')
		|| (a1 == '$' && a2 && g_one == 1
			&& g_two == 1 && !is_digit(a2) && a2 == '.'))
	{
		*j = *j + 1;
	}
	return (0);
}

int	check_if_print(char *str, int j)
{
	int i;
	int c;

	c = 0;
	i = 0;
	printf("backslash_number:%d\n", j);
	while (str[i])
	{
		if (str[i] != '\\')
		{
			printf("{%c}\n", str[i]);
			c = 0;
		}
		if (i == j)
		{
			if(c == 0)
			{
				printf("c[%d] =%d\n", i, c);
				return (0);
			}
			if (c % 2 == 0)
			{
				printf("c[%d] =%d\n", i, c);
				return (0);
			}		
			return (1);	
		}
		if (str[i] == '\\')
			c++;
		i++;
	}
	return (0);
}

int	check_char_first(char **args, int i, int j)
{
	int e;
	
	e = 0;
	if(args[i][j] == '\\' && g_one != 1 && g_two != 1)
	{
		if(j == 0)
			return (0);
		if(!check_if_print(args[i], j))	
				return (0);
	}
	else if (args[i][j] == '\\' && g_one != 1)
	{
		if(args[i][j + 1] && !is_special(args[i][j + 1]))
			return (1);
		if(j > 0 && args[i][j - 1] == '\\' && check_if_print(args[i], j) && args[i][j + 1])
			return (1);
		else if (j > 0 && args[i][j - 1] == '\\')
			return (0);
		if(args[i][j + 1] && is_special(args[i][j + 1]))
			return (0);
	}
	if(args[i][j] == '"')
	{
		if (g_one == 1)
			return (1);
		return (0);
	}
	if(args[i][j] == '\'')
	{
		if (g_two == 1)
			return (1);
		return (0);
	}
	return (1);
}

void	switch_one_two(char a)
{
	if (a == '\'' && g_two != 1)
	{
		if (g_one)
			g_one = 0;
		else
			g_one = 1;
	}
	if (a == '"' && g_one != 1)
	{
		if (g_two)
			g_two = 0;
		else
			g_two = 1;
	}
}

void	to_while(char **args, int i, int *s)
{
	int	j;

	j = 0;
	while (args[i][j])
	{
		if (check_first_char(args, &i, &j) == 1)
		{
			if(args[i][j] == '$' && j > 0 && (args[i][j - 1] == '"' || args[i][j - 1] == '\'') && !g_two)
				g_cmd->indice[*s] = 0;
			else if (!g_two)
			{
				g_cmd->indice[*s] = 1;
			}
			j = first_condition(j, args, i, s) - 1;
			// if (args[i][j] == '"' || args[i][j] == '\'')
			// 	check_quots_after_dollar(args, i, j, s);
		}
		else if (check_first_char(args, &i, &j) == 2)
		{
			fill_command_string(args[i][j], *s);
		}
		else
		{
			if(check_char_first(args, i, j))
			{
				
				//printf("--%c--\n", a1);
				//fix_quotes_next_to_var(args, i, j, s);
				fill_command_string(args[i][j], *s);
			}
			switch_one_two(args[i][j]);
		}
		if (args[i][j] && (args[i][j] != '$'
				|| ((g_one == 1 && args[i][j] == '$') || (args[i][j] == '$' && ((args[i][j + 1] && args[i][j + 2] && args[i][j + 1] == '"' && args[i][j + 2] == '\0' ) || (j > 0 && args[i][j - 1] == '\\') || args[i][j + 1] == '\0')))))
		{
			j++;
		}
	}
	g_cmd->string[*s][g_cmd->string_len] = '\0';
}

int	cat_command_string(char **args, int *s)
{
	int	j;
	int	i;

	i = 0;
	while (args[i])
	{
		g_cmd->indice[*s] = 0;
		j = 0;
		if (args[i] && (args[i][j] == '<' || args[i][j] == '>'))
			if (redirection(args, i) < 0)
				return (-1);
		while (args[i] && (args[i][j] == '<' || args[i][j] == '>'))
			i++;
		if (!args[i])
			break ;
		init_one_two();
		g_cmd->string[*s] = m_malloc(ft_strlen(args[i]) + 1);
		g_cmd->string[*s] = ft_strcpy(g_cmd->string[*s], args[i]);
		g_cmd->string_len = 0;
		to_while(args, i, s);
		(*s)++;
		i++;
	}
	g_cmd->string[*s] = NULL;
	return (1);
}
