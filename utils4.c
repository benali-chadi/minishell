#include "mini_shell.h"

void	print_prompt(void)
{
	ft_putstr_fd("\033[0;32mCS\033[0;31m@minishell \033[0m",
		g_all.utils.out);
}

void	exec_cd(t_command_info *cmd)
{
	add_last_cmd(g_all.utils.pwd, "OLDPWD");
	if (!cmd->string[0])
		cmd->string[0] = search_lgnam();
	else if (cmd->string[0][0] == '~')
		cmd->string[0] = ft_strjoin(search_lgnam(), (*cmd->string) + 1);
	if (chdir(cmd->string[0]) < 0)
	{
		printf("minishell: cd: %s: %s\n", cmd->string[0], strerror(errno));
		g_all.returnn = 256;
	}
	getcwd(g_all.utils.pwd, 100);
	add_last_cmd(g_all.utils.pwd, "PWD");
	add_last_cmd("cd", "_");
	if (ft_strcmpr(cmd->string[0], ".") || ft_strcmpr(cmd->string[0], ".."))
		add_last_cmd(cmd->string[0], "_");
}

int	in_value(int n, int *p)
{
	*p = 0;
	if (!n)
		return (0);
	return (g_all.fd[n - 1][0]);
}

int	check_solo_at_the_first(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}

void	print_error_and_exit(void)
{
	printf("minishell: %s\n", strerror(errno));
	exit(1);
}
