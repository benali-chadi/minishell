#include "mini_shell.h"

void	execute_cmd(char *command)
{
	char	*args[200];

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
	if (execve(command, args, NULL) < 0)
		exit(-1);
	exit(0);
}

char	*search_path(void)
{
	t_list_env	*read_env;

	read_env = list_env;
	while(read_env)
	{
		if(ft_strcmpr(read_env->name, "PATH"))
			return(read_env->content);	
		read_env = read_env->next;
	}
	return (NULL);
}

void	find_path(char *var)
{
	char	**split;
	char	*command;
	struct stat buf;
	int		i;

	split = mod_split(search_path(), ':');
	i = 0;
	while (split[i])
	{
		command = ft_strjoin(split[i], var);
		if (!stat(command, &buf))
			execute_cmd(command);
		i++;
	}
	if (command_info.command)
	{
		ft_putstr_fd(command_info.command, 1);
		ft_putstr_fd(": command not found\n", 1);
		exit(-1);
	}
	exit(0);
}