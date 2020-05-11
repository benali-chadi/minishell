#include "mini_shell.h"

t_list_env		*ft_lstlast(t_list_env *lst)
{
	t_list_env	*loop;

	loop = lst;
	if (loop)
		while (loop->next)
			loop = loop->next;
	return (loop);
}


void		ft_lstadd_front(t_list_env **alst, t_list_env *new)
{
	if (new)
	{
		new->next = *alst;
		*alst = new;
	}
}

void		ft_lstadd_back(t_list_env **alst, t_list_env *new)
{
	t_list_env	*temp;

	if (alst && *alst && new)
	{
		temp = ft_lstlast(*alst);
		temp->next = new;
		new->next = NULL;
	}
	else if (!*alst)
	{
		*alst = new;
		new->next = NULL;
	}
}

// void		ft_lstadd_back(t_list_env **alst, t_list_env *new)
// {
//     t_list_env *tmp;

//     tmp = *alst;
//     while(tmp->next)
//         tmp = tmp->next;
//     tmp->next = new;
//     new->next = NULL;
// }

t_list_env		*ft_lstnew(char *name, char *content, char *name_content)
{
	t_list_env	*list;

	list = malloc(sizeof(t_list_env));
	if (list)
	{
		list->content = content;
		list->name = name;
		list->name_content = name_content;
		list->next = NULL;
		return (list);
	}
	return (NULL);
}

void	add_back(t_list_env **head, char *name, char *content, char *name_content)
{
	ft_lstadd_back(head, ft_lstnew(name, content, name_content));
}