#include "mini_shell.h"

int		mod_strlen(char **s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return(i);
}

void	init_struct()
{
	commands = NULL;
	// command_info.command = NULL;
	// command_info.options = NULL;
	// command_info.string = NULL;
	// command_info.string_len = 0;
	// tests.echo = 0;
	// tests.cd = 0;
	// tests.env = 0;
	// tests.exit = 0;
	// tests.export_t = 0;
	// tests.pwd = 0;
	// tests.unset = 0;
	// ctrl_c = 0;
}

void	echo(t_command_info *cmd)
{
	int c;
	int i;
	int g;


	i = 0;
	g = 0;
	if (cmd->string != NULL)
		while (cmd->string[i])
		{
			if (cmd->string[i] == '"' || cmd->string[i] == '\'')
				c = cmd->string[i++];
			else
				c = 0;
			while (cmd->string[i] && cmd->string[i] != c)
			{
				if (!c && (cmd->string[i] == '"' || cmd->string[i] == '\'' ))
				{
					g = 1;
					break;
				}
				if (cmd->string[i] == '\\' && (cnt[(int)cmd->string[i + 1]] || cmd->string[i + 1] == '0'))
				{
					ft_putchar_fd(cnt[(int)cmd->string[i + 1]], 1);
					i +=2;
					continue;
				}
				ft_putchar_fd(cmd->string[i], 1);
				i++;
			}
			if (cmd->string[i] && !g)
				i++;
			else
				g = 0;
		}
	if (cmd->options == NULL)
	 	ft_putchar_fd('\n', 1);
}

void		test(t_command_info *cmd)
{
	cmd->tests.echo = ft_strcmpr(cmd->command, "echo") ||
	ft_strcmpr(cmd->command, "/bin/echo") ? 1 : 0;
	cmd->tests.cd = ft_strcmpr(cmd->command, "cd");
	cmd->tests.env = ft_strcmpr(cmd->command, "env") ||
	ft_strcmpr(cmd->command, "/usr/bin/env") ? 1 : 0;
	cmd->tests.exit = ft_strcmpr(cmd->command, "exit");
	cmd->tests.export_t = ft_strcmpr(cmd->command, "export");
	cmd->tests.pwd = ft_strcmpr(cmd->command, "pwd") ||
	ft_strcmpr(cmd->command, "/bin/pwd") ? 1 : 0;
	cmd->tests.unset = ft_strcmpr(cmd->command, "unset");

}

int 	main(int ac, char **av, char **env)
{
	char	*line;
	char	**split;
	char	**s;
	int		i;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	stock_env(env);
	init_cnt();
	variables.num = 0;
	while (1)
	{
		init_struct();
		ft_putstr_fd("\033[0;32mCS\033[0;31m@minishell \033[0m", 1);
		if (!(get_next_line(0, &line)))
		{
			to_free();
			exit(0);
		}
		split = mod_split(line, ';');
		i = 0;
		while (split[i])
		{
			s = mod_split(split[i], ' ');
			fill_cmd(s);
			i++;
		}
		
		exec_cmd();

		free(line);
	}
	return (0);
}
