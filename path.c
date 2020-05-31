#include "mini_shell.h"

void	execute_cmd(t_command_info *cmd, char *command)
{
	if (cmd->options)
	{
		utils.args[0] = cmd->command;
		utils.args[1] = cmd->options;
		utils.args[2] = cmd->string;
		utils.args[3] = NULL;
	}
	else
	{
		utils.args[0] = cmd->command;
		utils.args[1] = cmd->string;
		utils.args[2] = NULL;
	}
	if (execve(command, utils.args, NULL) < 0)
	{
		ft_putstr_fd(cmd->command, 1);
		ft_putstr_fd(": command not found\n", 1);
		exit(-1);
	}
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

void	find_path(t_command_info *cmd, char *var, int p)
{
	char	**split;
	char	*command;
	struct stat buf;
	int		i;

	split = mod_split(search_path(), ':');
	i = 0;
	if (p)
		execute_cmd(cmd, var);
	while (split[i])
	{
		command = ft_strjoin(split[i], var);
		if (!stat(command, &buf))
			execute_cmd(cmd, command);
		i++;
	}
	ft_putstr_fd(cmd->command, 1);
	ft_putstr_fd(": command not found\n", 1);
	exit(-1);
}