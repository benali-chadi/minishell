#include "mini_shell.h"

t_command_info		*cmd_lstlast(t_command_info *lst)
{
	t_command_info *tmp;

	tmp = lst;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	return(tmp);
}

void				cmd_lstadd_back(t_command_info **commands, t_command_info *new)
{
	t_command_info *tmp;

	if (commands && *commands && new)
	{
		tmp = cmd_lstlast(*commands);
		tmp->next = new;
		new->next = NULL;
	}
	else if (!*commands)
	{
		*commands = new;
		new->next = NULL;
	}
}