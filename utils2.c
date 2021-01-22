# include "mini_shell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (!g_status)
			ft_putstr_fd("\n\033[0;32mCS\033[0;31m@minishell \033[0m", 0);
		else
		{
			ft_putstr_fd("\n", 0);
			g_status = 0;
		}
		return;
	}
	else if (signum == SIGQUIT)
	{
		if (g_status)
			ft_putstr_fd("Quit: 3\n", 1);
		else
			ft_putstr_fd("\b\b", 1);
	}
}

char	*search_lgnam()
{
	t_list_env	*read_env;

	read_env = g_list_env;
	while(read_env)
	{
		if(ft_strcmpr(read_env->name, "LOGNAME"))
			return(ft_strjoin("/home/", read_env->content));
		read_env = read_env->next;
	}
	return (NULL);
}

void	init_cnt()
{
	int i;

	i = 0;
	while (i < 128)
		g_utils.cnt[i++] = 0;
	g_utils.cnt['0'] = '\0';
	g_utils.cnt['a'] = '\a';
	g_utils.cnt['b'] = '\b';
	g_utils.cnt['t'] = '\t';
	g_utils.cnt['n'] = '\n';
	g_utils.cnt['v'] = '\v';
	g_utils.cnt['f'] = '\f';
	g_utils.cnt['r'] = '\r';
	g_utils.cnt['e'] = '\e';
}

void	test(t_command_info *cmd)
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
