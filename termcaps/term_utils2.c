#include "../mini_shell.h"

void	ft_push(char c, t_stack **st)
{
	t_stack	*tmp;
	t_stack	*new;

	new = m_malloc(sizeof(t_stack));
	new->c = c;
	new->next = NULL;
	if (!*st)
	{
		*st = new;
		return ;
	}
	tmp = *st;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

char	ft_pop(t_stack **st)
{
	t_stack	*tmp;
	char	c;

	tmp = *st;
	if (!tmp)
		return (0);
	if (tmp->next == NULL)
	{
		c = tmp->c;
		*st = NULL;
		return (c);
	}
	while (tmp->next->next != NULL)
		tmp = tmp->next;
	c = tmp->next->c;
	tmp->next = NULL;
	return (c);
}

int	ft_puts(int c)
{
	return (write(1, &c, 1));
}

void	add_line(char *str, t_stack **st)
{
	int	i;

	i = 0;
	while (str[i])
		ft_push(str[i++], st);
}

void	save_and_print(char c, t_read *reads)
{
	char	*cur_pos;

	write(1, &c, 1);
	ft_push(c, &reads->left);
	cur_pos = tgetstr("sc", NULL);
	tputs(cur_pos, 1, ft_puts);
	print_stack(reads->right);
	cur_pos = tgetstr("rc", NULL);
	tputs(cur_pos, 1, ft_puts);
}
