#include "mini_shell.h"

void	stock_env(char **env)
{
	g_list_env  = NULL;
	int i;
	char *name;
	char *content;
	char *name_content;
	int j;

	i = 0;
	while(env[i])
	{
		j = 0;
		name_content = env[i];
		name = m_malloc(ft_strlen(env[i]));
		// tmp2 = malloc(ft_strlen(env[i]));
		while(env[i][j] != '=')
		{
			name[j] = env[i][j];
			j++;
		}
		name[j] = '\0';
		content = &env[i][j] + 1;
		add_back(&g_list_env, name, content, name_content);
		i++;
	}
}

void	loop_env(void)
{
	t_list_env *tmp;

	tmp = g_list_env;
	while(tmp)
	{
		ft_putstr_fd(tmp->name_content, 1);
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
}

void	ft_export(t_command_info *cmd)
{
	char *name;
	char *content;
	int i;
	int j;

	i = -1;
	if (!cmd->string[0])
	{
		loop_env();
		return;
	}
	while (cmd->string[++i])
	{
		j = -1;
		name = m_malloc(ft_strlen(cmd->string[i]));
		while(cmd->string[i][++j] != '=' && cmd->string[i][j])
			name[j] = cmd->string[i][j];
		if (cmd->string[i][j] != '=')
			return;
		name[j] = '\0';
		content = &cmd->string[i][++j];
		add_back(&g_list_env, name, content, cmd->string[i]);
	}
}

void	ft_remove_node(t_command_info *cmd)
{
	t_list_env *read_list;
	t_list_env *prev;
	int i;

	read_list = g_list_env;
	i = 0;
	if (!cmd->string[i])
		return;
	while (cmd->string[i])
	{
		if (read_list != NULL && ft_strcmpr(read_list->name, cmd->string[i]))
		{
			g_list_env = read_list->next;
			free(read_list);
			return;
		}
		while (read_list && !ft_strcmpr(cmd->string[i], read_list->name))
		{
			prev = read_list;
			read_list = read_list->next;
		}
		if (read_list != NULL)
		{
			prev->next = read_list->next;
			free(read_list);
		}
		i++;
	}
}

void	ft_cpy_env(t_list_env *read_env, int s)
{
	int e ;

	e = 0;
	while(read_env->content[e])
		g_cmd->string[s][g_cmd->string_len++] = read_env->content[e++];
	g_cmd->string[s][g_cmd->string_len] = '\0';
}

void	compare_var(char *var, char *arg, int s)
{
	// int			i;
	// int			j;
	t_list_env	*read_env;

	read_env = g_list_env;
	// i = 0;
	while(read_env)
	{
		if(ft_strcmpr(read_env->name, var))
		{
			g_cmd->string[s]  = ft_realloc(g_cmd->string[s] ,ft_strlen(g_cmd->string[s]) + ft_strlen(arg) + ft_strlen(read_env->content) + 1 + g_two); // + g_two prsq si kant two mfto7a ("") khas n2aloki liha blastha;
			ft_cpy_env(read_env, s);
			break;
		}
		read_env = read_env->next;
	}
}