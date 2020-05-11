#include "mini_shell.h"

void	stock_env(char **env)
{
	list_env  = NULL;
	int i;
	char *tmp1;
	char *tmp2;
	int j;

	i = 0;
	while(env[i])
	{
		j = 0;
		tmp1 = malloc(ft_strlen(env[i]));
		// tmp2 = malloc(ft_strlen(env[i]));
		while(env[i][j] != '=')
		{
			tmp1[j] = env[i][j];
			j++;
		}
		tmp1[j] = '\0';
		tmp2 = &env[i][j] + 1;
		add_back(&list_env, tmp1,tmp2);
		i++;
		// list_env = ft_lstnew(str);
	}
	// t_list_env *read;
	// read = list_env;
    // while(read)
    // {
    //     printf("name = %s|content = %s|\n", read->name, read->content);
    //     read = read->next;
    // }
}

void	ft_cpy_env(t_list_env *read_env)
{
	int e ;

	e = 0;
	while(read_env->content[e])
		command_info.string[command_info.string_len++] = read_env->content[e++];
	command_info.string[command_info.string_len] = '\0';
}

void	compare_var(char *var, char *arg)
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
			command_info.string  = ft_realloc(command_info.string ,ft_strlen(command_info.string) + ft_strlen(arg) + ft_strlen(read_env->content) + 1 + g_two); // + g_two prsq si kant two mfto7a ("") khas n2aloki liha blastha;
			ft_cpy_env(read_env);
			break;
		}
		read_env = read_env->next;
	}
}