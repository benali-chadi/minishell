#include "mini_shell.h"

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

void	exec_cmd(void)
{
	t_command_info	*cmd;
	char			*var;
	char			pwd[100];
	int				f;
	int				p;

	cmd = commands;
	while (cmd)
	{
		p = 0;
		if (cmd->tests.cd)
		{
			if (!cmd->string)
				cmd->string = search_lgnam();
			else if (cmd->string[0] == '~')
			{
				cmd->string = ft_strjoin(search_lgnam(), cmd->string + 1);
				printf("%s\n", cmd->string);
			}
			if (chdir(cmd->string) < 0)
			{
				ft_putstr_fd("cd: can't cd to ", 1);
				ft_putstr_fd(cmd->string, 1);
				ft_putchar_fd('\n', 1);
			}
		}
		else if (cmd->tests.exit)
		{
			to_free();
			exit(0);
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

		cmd = cmd->next;
	}
}