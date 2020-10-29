#include "mini_shell.h"

void	fill_command_string(t_command_info *cmd, char a, int i)
{
	cmd->string[i][cmd->string_len++] = a;
	if(a == '\'')
		g_one = g_one == 1 ? 0 : 1;
	if(a == '"')
		g_two = g_two == 1 ? 0 : 1;
	// cmd->string[i][cmd->string_len] = '\0';
}

void	init_one_two()
{
	g_one = 0;
	g_two = 0;
}

void	change_one_two(char a)
{
	if (a == '"')	
		g_two = g_two == 1 ? 0 : 1;
	if (a == '\'')	
		g_one = g_one == 1 ? 0 : 1;
}

void	redirection(t_command_info *cmd, char **args, int *i)
{
	int j;
	int k;
	int red;

	j = 0;
	if (args[*i][j] == '>' || ft_strcmpr(args[*i], ">>"))
	{
		cmd->out_red = ft_strcmpr(args[*i], ">>") ? 2 : 1;
		j += cmd->out_red;
		red = 1;
	}
	else
	{
		cmd->in_red = 1;
		j++;
		red = 0;
	}
	if ((size_t)j >= ft_strlen(args[*i]))
	{
		(*i)++;
		j = 0;
	}
	if (red == 1)
	{
		cmd->out_file_name = malloc(ft_strlen(args[*i]) + 1);
		k = 0;
		while (args[*i][j])
			cmd->out_file_name[k++] = args[*i][j++];
		cmd->out_file_name[k] = '\0';
	}
	else
	{
		cmd->in_file_name = malloc(ft_strlen(args[*i]) + 1);
		k = 0;
		while (args[*i][j])
			cmd->in_file_name[k++] = args[*i][j++];
		cmd->in_file_name[k] = '\0';
	}
	(*i)++;
	if (!args[*i])
		return;
	j = 0;
	if (args[*i] && (args[*i][j] == '<' || args[*i][j] == '>' || ft_strcmpr(args[*i], ">>")))
		redirection(cmd, args, i);
}

void	cat_command_string(t_command_info *cmd, char **args, int i)
{
	int j;
	char *var;
	int k;
	int s;

	s = 0;
	while(args[i])
	{	
		j = 0;
		if (args[i] && (args[i][j] == '<' || args[i][j] == '>' || ft_strcmpr(args[i], ">>")))
			redirection(cmd, args, &i);
		if (!args[i])
			break;
		init_one_two();
		cmd->string[s] = m_malloc(ft_strlen(args[i]) + 1);
		cmd->string_len = 0;
		// j = 0;
		
		while(args[i][j])
		{
			if((args[i][j] == '$' && args[i][j + 1] && g_one != 1 )|| (args[i][j] == '$' && args[i][j + 1] && g_one == 1 && g_two == 1))
			{
				j++;
				var = m_malloc(ft_strlen(args[i]));
				k = 0;
				while(is_alpha_digit(args[i][j]) && args[i][j] != '$' && args[i][j])
					var[k++] = args[i][j++];
				var[k] = '\0';

				compare_var(&cmd->string[s], var, args[i], &cmd->string_len);
				if(args[i][j] == '"' || args[i][j] == '\'')
					fill_command_string(cmd, args[i][j], s);
			}
			else
				fill_command_string(cmd, args[i][j], s);
			if(args[i][j] && (args[i][j] != '$' || (g_one == 1 && args[i][j] == '$')))
				j++;
		}
		cmd->string[s][cmd->string_len] = '\0';
		s++;
		i++;
	}
	cmd->string[s] = NULL;
}

void	fill_cmd(char **split, int p)
{
	t_command_info *cmd;
	int i;

	i = 0;
	if (!*split)
		return;
	cmd = malloc(sizeof(t_command_info));
	cmd->in_red = 0;
	cmd->out_red = 0;
	cmd->in_file_name = NULL;
	cmd->out_file_name = NULL;
	
	if (split[i][0] == '<' || split[i][0] == '>' || ft_strcmpr(split[i], ">>"))
		redirection(cmd, split, &i);
	
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
        cat_command_string(cmd, split, i);

	test(cmd);
	cmd->pipe = p;
	cmd_lstadd_back(&commands, cmd);
}
