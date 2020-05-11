#include "mini_shell.h"

void	fill_command_string(char a)
{
	command_info.string[command_info.string_len++] = a;
	if(a == '\'')
		g_one = g_one == 1 ? 0 : 1;
	if(a == '"')
		g_two = g_two == 1 ? 0 : 1;
	command_info.string[command_info.string_len] = '\0';
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

void	cat_command_string(char	**args, int i)
{
	int j;
	char *var;
	int k;

	j = 0;
	command_info.string  = ft_strdup(args[i]);
	while(args[i])
	{
		init_one_two();
		if(j != 0)    // to not realloc for the first time !
			command_info.string = ft_realloc(command_info.string, ft_strlen(command_info.string) + ft_strlen(args[i]) + 1);
		j = 0;
		while(args[i][j])
		{
			if((args[i][j] == '$' && args[i][j + 1] && g_one != 1 )|| (args[i][j] == '$' && args[i][j + 1] && g_one == 1 && g_two == 1))
			{
				j++;
				var = malloc(ft_strlen(args[i]));
				k = 0;
				while(is_alpha_digit(args[i][j]) && args[i][j] != '$' && args[i][j])
					var[k++] = args[i][j++];
				var[k] = '\0';
				printf("var:%s\n", var);
				compare_var(var, args[i]);
				if(args[i][j] == '"' || args[i][j] == '\'')
					fill_command_string(args[i][j]);
				free(var);
				printf("|%s|\n", command_info.string);
			}
			else
				fill_command_string(args[i][j]);
			if(args[i][j] && (args[i][j] != '$' || (g_one == 1 && args[i][j] == '$')))
				j++;
		}
		if(args[i] && args[i + 1])
		{
			command_info.string = ft_realloc(command_info.string, ft_strlen(command_info.string) + 2);
			fill_command_string(' ');
		}
		i++;
	}
	command_info.string[command_info.string_len++] = '\0';
}

void	fill_cmd(char **split)
{
	int i;

	i = 0;
	if (!*split)
		return;
	command_info.command = malloc(ft_strlen(split[0]) + 1);

	ft_strcpy(command_info.command, split[i]);
	i++;

	if (split[i] && split[i][0] == '-')
	{
		command_info.options = malloc(ft_strlen(split[i]) + 1);
		ft_strcpy(command_info.options, split[i]);
		i++;
	}
	if (split[i])
        cat_command_string(split, i);
}
