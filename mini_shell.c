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
	command_info.command = NULL;
	command_info.options = NULL;
	command_info.string = NULL;
	command_info.string_len = 0;
	tests.echo = 0;
	tests.cd = 0;
	tests.env = 0;
	tests.exit = 0;
	tests.export_t = 0;
	tests.pwd = 0;
	tests.unset = 0;
	tests.ls = 0;
	ctrl_c = 0;
}

void	echo()
{
	int c;
	int i;
	int g;


	i = 0;
	g = 0;
	if (command_info.string != NULL)
		while (command_info.string[i])
		{
			if (command_info.string[i] == '"' || command_info.string[i] == '\'')
				c = command_info.string[i++];
			else
				c = 0;
			while (command_info.string[i] && command_info.string[i] != c)
			{
				if (!c && (command_info.string[i] == '"' || command_info.string[i] == '\'' ))
				{
					g = 1;
					break;
				}
				if (command_info.string[i] == '\\' && cnt[(int)command_info.string[i + 1]])
				{
					if (c)
					{
						ft_putchar_fd(cnt[(int)command_info.string[i + 1]], 1);
						i +=2;
						continue;
					}
					else
						i++;
				}
				ft_putchar_fd(command_info.string[i], 1);
				i++;
			}
			if (command_info.string[i] && !g)
				i++;
			else
				g = 0;
		}
	if (command_info.options == NULL)
	 	ft_putchar_fd('\n', 1);
}

int		test()
{
	tests.echo = ft_strcmpr(command_info.command, "echo");
	tests.cd = ft_strcmpr(command_info.command, "cd");
	tests.env = ft_strcmpr(command_info.command, "env");
	tests.exit = ft_strcmpr(command_info.command, "exit");
	tests.export_t = ft_strcmpr(command_info.command, "export");
	tests.pwd = ft_strcmpr(command_info.command, "pwd");
	tests.unset = ft_strcmpr(command_info.command, "unset");
	tests.ls = ft_strcmpr(command_info.command, "ls");

	if (tests.echo || tests.cd || tests.env || tests.exit 
	|| tests.export_t || tests.pwd || tests.unset || tests.ls)
		return (1);
	return (0);
}

int 	main(int ac, char **av, char **env)
{
	char	*line;
	char	**split;
	char	*args[200];
	char	pwd[100];
	int		f;
	int		ret;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	stock_env(env);
	init_cnt();
	variables.num = 0;
	while (1)
	{
		ret = 0;
		init_struct();
		if (ctrl_c)
			continue;
		ft_putstr_fd("CSN@minishell ", 1);
		if (!(get_next_line(0, &line)))
			exit(0);
		split = mod_split(line, ' ');
		fill_cmd(split);
		printf("command : |%s|\noptions : |%s|\nstring : |%s|\n", command_info.command, command_info.options, command_info.string);
		
		if (*split)
			ret = test();
		
		if (tests.cd)
		{
			int a = chdir(command_info.string);
			if (a < 0)
			{
				ft_putstr_fd("cd: no such file or directory: ", 1);
				ft_putstr_fd(command_info.string, 1);
				ft_putchar_fd('\n', 1);
			}
		}
		else if (tests.pwd)
		{
			ft_putstr_fd(getcwd(pwd, 100), 1);
			ft_putchar_fd('\n', 1);
		}
		else if (tests.echo)
			echo();
		else if (tests.env)
			loop_env();
		else if (tests.unset)
			ft_remove_node(command_info.string);
		else if (tests.export_t)
			ft_export(command_info.string);
		else if (tests.exit)
			exit(0);
		else if (ret)
		{
			f = fork();
			if (f > 0)
				wait(NULL);
			else if(f == 0)
			{
				char *bin = "/bin/";
				char *my_command = ft_strjoin(bin, command_info.command);
				printf("%s\n", my_command);
				if (command_info.options)
				{
					args[0] = command_info.command;
					args[1] = command_info.options;
					args[2] = command_info.string;
					args[3] = NULL;
				}
				else
				{
					args[0] = command_info.command;
					args[1] = command_info.string;
					args[2] = NULL;
				}
				execve(my_command, args, NULL);
			}
		}
		free(line);
	}
	free(line);
	return (0);
}