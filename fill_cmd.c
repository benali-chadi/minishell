#include "mini_shell.h"

void	fill_command_string(t_command_info *cmd, char a)
{
	cmd->string[cmd->string_len++] = a;
	if(a == '\'')
		g_one = g_one == 1 ? 0 : 1;
	if(a == '"')
		g_two = g_two == 1 ? 0 : 1;
	cmd->string[cmd->string_len] = '\0';
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

void	cat_command_string(t_command_info *cmd, char **args, int i)
{
	int j;
	char *var;
	int k;

	j = 0;
	cmd->string = m_malloc(ft_strlen(args[i]) + 1);
	cmd->string = ft_strcpy(cmd->string, args[i]);
	while(args[i])
	{
		init_one_two();
		if(j != 0)    // to not realloc for the first time !
			cmd->string = ft_realloc(cmd->string, ft_strlen(cmd->string) + ft_strlen(args[i]) + 1);
		j = 0;
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
				// printf("var:%s\n", var);
				compare_var(cmd, var, args[i]);
				if(args[i][j] == '"' || args[i][j] == '\'')
					fill_command_string(cmd, args[i][j]);
				// free(var);
				// printf("|%s|\n", cmd->string);
			}
			else
				fill_command_string(cmd, args[i][j]);
			if(args[i][j] && (args[i][j] != '$' || (g_one == 1 && args[i][j] == '$')))
				j++;
		}
		if(args[i] && args[i + 1])
		{
			cmd->string = ft_realloc(cmd->string, ft_strlen(cmd->string) + 2);
			fill_command_string(cmd, ' ');
		}
		i++;
	}
	cmd->string[cmd->string_len++] = '\0';
}

void	fill_cmd(char **split, int p)
{
	t_command_info *cmd;
	int i;

	i = 0;
	if (!*split)
		return;
	cmd = malloc(sizeof(t_command_info));
	cmd->command = m_malloc(ft_strlen(split[0]) + 1);

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
