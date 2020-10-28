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
}

void	echo(t_command_info *cmd)
{
	int c;
	int i;
	int g;
	int n;


	i = 0;
	g = 0;
	n = 0;
	if (cmd->options && ft_strcmpr(cmd->options, "-n"))
		n = 1;
	else if (cmd->options)
	{
		while (*cmd->options)
			ft_putchar_fd(*cmd->options++, 1);
		ft_putchar_fd(' ', 1);
	}
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
				if (cmd->string[i] == '\\' && (utils.cnt[(int)cmd->string[i + 1]] || cmd->string[i + 1] == '0'))
				{
					ft_putchar_fd(utils.cnt[(int)cmd->string[i + 1]], 1);
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
	if (!n)
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

int		**allocate_fd(int j)
{
	int i;
	int **fd;

	i = 0;
	fd = malloc(j * sizeof(int *));
	while (i < j)
	{
		fd[i] = malloc(2 * sizeof(int));
		i++;
	}
	i = 0;
	while (i < j)
	{
		pipe(fd[i]);
		i++;
	}
	return (fd);
}

int 	main(int ac, char **av, char **env)
{
	char	*line;
	char	**m_split;
	char	**p_split;
	char	**c_split;
	t_command_info	*cmd;
	int		i;
	int		j;

	(void)ac;
	(void)av;
	init_cnt();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	stock_env(env);
	j = 0;
	while (1)
	{
		ft_putstr_fd("\033[0;32mCS\033[0;31m@minishell \033[0m", 1);
		if (!(get_next_line(0, &line)))
		{
			to_free();
			exit(0);
		}
		
		m_split = mod_split(line, ';');
		i = 0;
		while (m_split[i])
		{
			commands = NULL;
			p_split = mod_split(m_split[i], '|');
			j = 0;
			if (mod_strlen(p_split) > 1)
			{
				while (p_split[j])
				{
					c_split = mod_split(p_split[j], ' ');
					fill_cmd(c_split, 1);
					j++;
				}
			}
			else
			{
				c_split = mod_split(m_split[i], ' ');
				fill_cmd(c_split, 0);
			}
			cmd = commands;

			int k = 0;
			while(cmd != NULL)
			{
				exec_cmd(cmd, k, j);
				cmd = cmd->next;
				k++;
			}
			close_all(j);
			while (wait(NULL) != -1);
			i++;
		}

		free(line);
	}
	return (0);
}
