#include "mini_shell.h"

int		test_cmds(t_command_info *cmd)
{
	char pwd[100];

	if (cmd->tests.cd)
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
	else if (cmd->tests.pwd)
	{
		ft_putstr_fd(getcwd(pwd, 100), 1);
		ft_putchar_fd('\n', 1);
	}
	else if (cmd->tests.echo)
		echo(cmd);
	else if (cmd->tests.env)
		loop_env();
	else if (cmd->tests.unset)
		ft_remove_node(cmd->string);
	else if (cmd->tests.export_t)
		ft_export(cmd->string);
	else
		return (0);
	return (1);
}

void	ft_pipe(t_command_info *cmd, int n)
{
	int fd[2];
	int f;
	int i = 0;
	int in = 0;
	int f2;

	if ((f2 = fork()) == 0)
	{
		int out = dup(STDOUT_FILENO);
		while (i < n - 1)
		{
			pipe(fd);
			dup2(fd[1], STDOUT_FILENO);

			if (test_cmds(cmd));
			else if ((f = fork()) == 0)
			{
				if (in != 0)
					dup2(in, 0);
				exec_cmd(cmd, 1);
			}
			close(fd[1]);

			in = fd[0];
			cmd = cmd->next;
			i++;
		}
		if (in != 0)
			dup2(in, 0);
		dup2(out, STDOUT_FILENO);
		close(out);
		exec_cmd(cmd, 1);
	}
	while (wait(NULL) != -1);
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

void	exec_cmd(t_command_info *cmd, int pipe)
{
	char			*var;
	int				f;
	int				p;

	p = 0;
	if (cmd->tests.exit)
	{
		to_free();
		exit(0);
	}
	if (test_cmds(cmd))
		return;
	else if (pipe)
	{
		var = check_cmd(cmd->command, &p);
		find_path(cmd, var, p);
	}
	else
	{
		f = fork();
		if (f > 0)
			wait(NULL);
		else if(!f)
		{
			var = check_cmd(cmd->command, &p);
			find_path(cmd, var, p);
		}
	}
}