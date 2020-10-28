#include "mini_shell.h"

int		test_cmds(t_command_info *cmd)
{
	char pwd[100];

	if (cmd->tests.exit)
	{
		to_free();
		exit(0);
	}
	else if (cmd->tests.cd)
	{
		if (!cmd->string)
			cmd->string = search_lgnam();
		else if (cmd->string[0] == '~')
			cmd->string = ft_strjoin(search_lgnam(), cmd->string + 1);
		if (chdir(cmd->string) < 0)
		{
			ft_putstr_fd("cd: can't cd to ", 1);
			ft_putstr_fd(cmd->string, 1);
			ft_putchar_fd('\n', 1);
		}
	}
	if (cmd->tests.pwd)
	{
		ft_putstr_fd(getcwd(pwd, 100), 1);
		ft_putchar_fd('\n', 1);
		exit(1);
	}
	else if (cmd->tests.echo)
		echo(cmd);
	else if (cmd->tests.env)
		loop_env();
	else
		return (0);
	return (1);
	// exit(1);
}

void	close_all(int last)
{
	int i;

	i = 0;
	while (i < last)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	ft_fork(t_command_info *cmd, int n, int last)
{
	int f;
	int in;
	char *var;
	int p = 0;
	
	in = n == 0 ? 0 : fd[n-1][0];

	pipe(fd[n]);
	if ((f = fork()) == 0)
	{
		if (in != 0)
			dup2(in, STDIN_FILENO);
			
		if (n != last - 1 && n != last)
		{
			dup2(fd[n][1], STDOUT_FILENO);
		}
		
		if (test_cmds(cmd));
		else
		{
			var = check_cmd(cmd->command, &p);
			find_path(cmd, var, p);
		}
		exit(1);
	}

	if (n == last - 1 || n == last)
		close_all(last);
	else
		close(fd[n][1]);
}

char	*check_cmd(char *command, int *p)
{
	int		i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
		{
			*p = 1;
			return (command);
		}
		i++;
	}
	return (ft_strjoin("/", command));
}

void	exec_cmd(t_command_info *cmd, int i, int last)
{
	if (cmd->tests.exit)
	{
		to_free();
		exit(0);
	}
	else if (cmd->tests.cd)
	{
		if (!cmd->string)
			cmd->string = search_lgnam();
		else if (cmd->string[0] == '~')
			cmd->string = ft_strjoin(search_lgnam(), cmd->string + 1);
		if (chdir(cmd->string) < 0)
		{
			ft_putstr_fd("cd: can't cd to ", 1);
			ft_putstr_fd(cmd->string, 1);
			ft_putchar_fd('\n', 1);
		}
	}
	else if (cmd->tests.export_t)
		ft_export(cmd->string);
	else if (cmd->tests.unset)
		ft_remove_node(cmd->string);
	else
		ft_fork(cmd, i, last);
}
