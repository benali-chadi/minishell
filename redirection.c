#include "mini_shell.h"

void	red_file_names(char *args, int red, int j)
{
	int k;

	if (red == 1)
	{
		g_cmd->reds.out[g_cmd->reds.out_num].file_name =
		m_malloc(ft_strlen(args) + 1);
		k = 0;
		while (args[j])
			g_cmd->reds.out[g_cmd->reds.out_num].file_name[k++] = args[j++];
		g_cmd->reds.out[g_cmd->reds.out_num].file_name[k] = '\0';
		g_cmd->reds.out_num++;
	}
	else
	{
		g_cmd->reds.in_file_name[g_cmd->reds.in_num] =
		m_malloc(ft_strlen(args) + 1);
		k = 0;
		while (args[j])
			g_cmd->reds.in_file_name[g_cmd->reds.in_num][k++] = args[j++];
		g_cmd->reds.in_file_name[g_cmd->reds.in_num][k] = '\0';
		g_cmd->reds.in_num++;
	}
}

void	red_helper(char *arg, int *j, int *red)
{
	if (arg[*j] == '>')
	{
		while (arg[*j] && arg[*j] == '>')
		{
			g_cmd->reds.out[g_cmd->reds.out_num].sym[*j] = arg[*j];
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

int		redirection(char **args, int i)
{
	int j;
	int red;

	j = 0;
	red_helper(args[i], &j, &red);
	if ((size_t)j >= ft_strlen(args[i]))
	{
		(i)++;
		j = 0;
	}
	if (!args[i])
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 1);
		return (-1);
	}
	red_file_names(args[i], red, j);
	(i)++;
	if (!args[i])
		return (1);
	j = 0;
	if (args[i] && (args[i][j] == '<' || args[i][j] == '>'))
		if (!redirection(args, i))
			return (-1);
	return (1);
}
