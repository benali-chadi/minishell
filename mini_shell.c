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
	tests.echo = 1;
	tests.cd = 1;
	tests.env = 1;
	tests.exit = 1;
	tests.export_t = 1;
	tests.pwd = 1;
	tests.unset = 1;
	tests.ls = 1;
}

void	fill_my_command(char **split)
{
	int i;
	int j;
	int k;
	int len;

	i = 0;
	j = 0;
	k = 0;
	len = 0;
	if (!*split)
		return;
	command_info.command = malloc(ft_strlen(split[0]) + 1);

	while (split[i][j])
	{
		command_info.command[j] = split[i][j];
		j++;
	}
	command_info.command[j] = '\0';
	i++;
	if (split[i] && split[i][0] == '-')
	{
		command_info.options = malloc(ft_strlen(split[i]) + 1);
		j = 0;
		while (split[i][j])
		{
			command_info.options[j] = split[i][j];
			j++;
		}
		command_info.options[j] = '\0';
		i++;
	}
	if (split[i])
	{
		len = ft_strlen(split[i]);
		printf("len : %d\n", len);
		command_info.string = malloc(len + 1);
		j = 0;
		while(split[i][j])
		{
			command_info.string[k++] = split[i][j];
			j++;
		}
		command_info.string[k] = '\0';
	}
}

void	echo()
{
	int c;

	if (command_info.string != NULL)
	{
		while (*command_info.string)
		{
			if (*command_info.string == '"' || *command_info.string == '\'')
				c = *command_info.string;
			while (*command_info.string && *command_info.string != c)
			{
				if (!c && (*command_info.string == '"' || *command_info.string == '\'' ))
					break;
				ft_putchar_fd(*command_info.string, 1);
				command_info.string++;
			}
			c = 0;
			if (*command_info.string)
				command_info.string++;
		}
	}
	if (command_info.options == NULL)
	 	ft_putchar_fd('\n', 1);
}

int		test()
{
	tests.echo = ft_strncmp(command_info.command, "echo", ft_strlen("echo"));
	tests.cd = ft_strncmp(command_info.command, "cd", ft_strlen("cd"));
	tests.env = ft_strncmp(command_info.command, "env", ft_strlen("env"));
	tests.exit = ft_strncmp(command_info.command, "exit", ft_strlen("exit"));
	tests.export_t = ft_strncmp(command_info.command, "export", ft_strlen("export"));
	tests.pwd = ft_strncmp(command_info.command, "pwd", ft_strlen("pwd"));
	tests.unset = ft_strncmp(command_info.command, "unset", ft_strlen("unset"));
	tests.ls = ft_strncmp(command_info.command, "ls", ft_strlen("ls"));

	if (!tests.echo || !tests.cd || !tests.env || !tests.exit 
	|| !tests.export_t || !tests.pwd || !tests.unset || !tests.ls)
		return (0);
	return (1);
}

int 	main()
{
	char	*line;
	char	**split;
	char	*args[200];
	char	pwd[100];
	int		f;
	int		ret;

	while (1)
	{
		ret = 1;
		write(1, "chadi@minishell : ", 19);
		get_next_line(0, &line);
		split = mod_split(line, ' ');
		fill_my_command(split);

		printf("command : |%s|\noptions : |%s|\nstring : |%s|\n", command_info.command, command_info.options, command_info.string);
		
		if (*split)
			ret = test();
		
		if (!tests.cd)
		{
			int a = chdir(command_info.string);
			if (a < 0)
			{
				ft_putstr_fd("cd: no such file or directory: ", 1);
				ft_putstr_fd(command_info.string, 1);
				ft_putchar_fd('\n', 1);
			}
		}
		else if (!tests.pwd)
		{
			ft_putstr_fd(getcwd(pwd, 100), 1);
			ft_putchar_fd('\n', 1);
		}
		else if (!tests.echo)
			echo();
		else if (!ret)
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
		init_struct();
		free(line);
	}
	free(line);
	return (0);
}