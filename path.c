#include "mini_shell.h"

void	execute_cmd(t_command_info *cmd, char *command)
{
	char	*args[200];

	if (cmd->options)
	{
		args[0] = cmd->command;
		args[1] = cmd->options;
		args[2] = cmd->string;
		args[3] = NULL;
	}
	else
	{
		args[0] = cmd->command;
		args[1] = cmd->string;
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

void	find_path(t_command_info *cmd, char *var)
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
			execute_cmd(cmd, command);
		i++;
	}
	if (cmd->command)
	{
		ft_putstr_fd(cmd->command, 1);
		ft_putstr_fd(": command not found\n", 1);
		exit(-1);
	}
	exit(0);
}