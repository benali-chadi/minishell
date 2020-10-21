#include "mini_shell.h"

void	ft_pipe(t_command_info *cmd, int n)
{
    // pid_t   pid;
    // pid = fork();

	// if (!pid)
	// {
	// 	while (n)
	// 	{
	// 		int		in;
	// 		int     fd_tab[2];
    // 		pipe(fd_tab);
	// 		in = 0;

    // 		if (pid == 0)
    // 		{
    // 		    if (n == 3)
    // 		        dup2(fd_tab[1], 1);
    // 		    else if (n == 2)
    // 		    {
    // 		        dup2(in, 0);
    // 		        dup2(fd_tab[1], 1);
    // 		    }
    // 		    else
    // 		        dup2(in, 0);
	// 			exec_cmd(cmd, 1);
    // 		}
    // 		if (in != 0)
    // 		    close(in);
    // 		close(fd_tab[1]);
    // 		if (n == 1)
    // 		    close(fd_tab[0]);
    // 			in = fd_tab[0];
	// 		n--;
	// 	}
	// }
	// else
	// 	for (size_t i = 0; i < 3; i++)
	// 	{
	// 		wait(NULL);
	// 	}
	

	int fd[2];
	int f;
	int i = 0;
	int in = 0;
	int out;

	pid_t f2 = fork();
	if (!f2)
	{
		while (i < n - 1)
		{
			pipe(fd);
			out = fd[1];
			if ((f = fork()) == 0)
			{
				if (in != 0)
				{
					dup2(in, 0);
					// close(in);
				}
				if (out != 1)
				{
					dup2(out, 1);
					// close(out);
				}
				exec_cmd(cmd, 1);
				exit(1);
			}
			// close(in);
			// close(out);

			// else
			// 	wait(NULL);

			close(out);
			in = fd[0];
			cmd = cmd->next;
			i++;
	// 		// if (!f)
	// 		// {
	// 		// 	// pipe(fd);
	// 		// 	f_p = fork();
	// 		// 	if (!f_p)
	// 		// 	{
	// 		// 		cmd = cmd->next;
	// 		// 		dup2(fd[0], 0);
	// 		// 		// close(fd[1]);
	// 		// 		exec_cmd(cmd, 1);
	// 		// 		exit(1);
	// 		// 	}
	// 		// 	else
	// 		// 	{
	// 		// 		dup2(fd[1], 1);
	// 		// 		// close(fd[0]);
	// 		// 		exec_cmd(cmd, 1);
	// 		// 		exit(1);
	// 		// 	}
	// 		// 	exit(1);
	// 		// }
	// 		// else
	// 		// 	wait(NULL);
			if (i == n-1)
			{
				dup2(1, out);
			}
		}
		if (in != 0)
			dup2(in, 0);
		exec_cmd(cmd, 1);

		printf("out : %d, in : %d\n", out, in);
		// close(fd[1]);
		exit(1);
	}
	// else
	// {
		while (wait(NULL) != -1 || errno != ECHILD)
		// while (waitpid(f2, NULL, 0) == -1)
			printf("Waiting for children||pipe||\n");

	// }
	
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
	char			pwd[100];
	int				f;
	int				p;

	p = 0;
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
	else if (pipe)
	{
		var = check_cmd(cmd->command, &p);
		find_path(cmd, var, p);
	}
	else
	{
		if(!(f = fork()))
		{
			var = check_cmd(cmd->command, &p);
			find_path(cmd, var, p);
			exit(0);
		}
		else
			wait(NULL);
	}
}
