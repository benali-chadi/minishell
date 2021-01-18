#include "mini_shell.h"

int		ft_strcmpr(char *s1, char *s2)
{
	int i;

	i = 0;
	while(s1[i] || s2[i])
	{
		if(s1[i] != s2[i])
			return(0);
		i++;
	}
	return(1);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int i;

	i = -1;
	while(s2[++i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return(s1);
}

int		is_alpha_digit(char a)
{
	if ((a <= 'Z' && a >= 'A') || (a <= 'z' && a >= 'a' )|| (a <= '9' && a >= '0') || a == '?')
		return (1);
	return(0);
}

void	*ft_realloc(void *ptr, int size)
{
	void *tmp;

	tmp = ptr;
	ptr = m_malloc(size);
	ptr = ft_strcpy(ptr, tmp);
	// free(tmp);
	return(ptr);
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
