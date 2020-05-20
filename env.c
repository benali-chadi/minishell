#include "mini_shell.h"

void	stock_env(char **env)
{
	list_env  = NULL;
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
		add_back(&list_env, name, content, name_content);
		i++;
		// list_env = ft_lstnew(str);
	}
	// t_list_env *read;
	// read = list_env;
    // while(read)
    // {
        // printf("name_content = %s\n%s\n%s\n", read->name_content,  read->name,  read->content);
        // read = read->next;
    // }
}

void	ft_cpy_env(t_command_info *cmd, t_list_env *read_env)
{
	int e ;

	e = 0;
	while(read_env->content[e])
		cmd->string[cmd->string_len++] = read_env->content[e++];
	cmd->string[cmd->string_len] = '\0';
}

void	loop_env(void)
{
	t_list_env *tmp;

	tmp = list_env;
	while(tmp)
	{
		ft_putstr_fd(tmp->name_content, 1);
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
}

void	ft_export(char *variable)
{
	int i;
	char *name;
	char *content;

	i = -1;
	name = m_malloc(ft_strlen(variable));
	while(variable[++i] != '=')
		name[i] = variable[i];
	name[i] = '\0';
	content = &variable[++i];
	add_back(&list_env, name, content, variable);
}

void	ft_remove_node(char *name)
{
	t_list_env *read_list;
	t_list_env *prev;
	read_list = list_env;

	if(read_list != NULL && ft_strcmpr(read_list->name, name))
	{
		list_env = read_list->next;
		free(read_list);
		return;
	}
	while(read_list && !ft_strcmpr(name, read_list->name))
	{
		prev = read_list;
		read_list = read_list->next;
	}
	if(read_list != NULL)
	{
		prev->next = read_list->next;
		free(read_list);
	}
}

void	compare_var(t_command_info *cmd, char *var, char *arg)
{
	// int			i;
	// int			j;
	t_list_env	*read_env;

	read_env = list_env;
	// i = 0;
	while(read_env)
	{
		if(ft_strcmpr(read_env->name, var))
		{
			cmd->string  = ft_realloc(cmd->string ,ft_strlen(cmd->string) + ft_strlen(arg) + ft_strlen(read_env->content) + 1 + g_two); // + g_two prsq si kant two mfto7a ("") khas n2aloki liha blastha;
			ft_cpy_env(cmd, read_env);
			break;
		}
		read_env = read_env->next;
	}
}