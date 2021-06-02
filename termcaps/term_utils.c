#include "../mini_shell.h"

char	*ft_join_stacks(t_read reads)
{
	char *str;
	t_stack *tmp;
	int i;

	str = m_malloc(reads.l_len + reads.r_len + 1);
	tmp = reads.left;
	i = 0;
	while (tmp)
	{
		str[i++] = tmp->c;
		tmp = tmp->next;
	}
	tmp = reads.right;
	while (tmp)
	{
		str[i++] = tmp->c;
		tmp = tmp->next;
	}
	str[i] = '\0';
	// ft_stcclear(reads.left);
	// ft_stcclear(reads.right);
	return (str);
}

void	ft_stcclear(t_stack *st)
{
	t_stack *pt;
	t_stack *tmp;

	if (st)
	{
		pt = st;
		while (pt)
		{
			tmp = pt->next;
			free(pt);
			pt = tmp;
		}
	}
}

void	ft_push_front(char c, t_stack **ri)
{
	t_stack *new;

	new = m_malloc(sizeof(t_stack));
	new->c = c;
	if (!*ri)
		new->next = NULL;
	else
		new->next = *ri;
	*ri = new;
}

int ft_pop_front(t_stack **ri)
{
	if (!*ri)
		return (0);
	
	char c = (*ri)->c;

	*ri = (*ri)->next;
	return (c);
}

void print_stack(t_stack *st)
{
	if (!st)
		return;
	char *ce = tgetstr("ce", NULL);
	tputs(ce, 1, putchar);
	while (st)
	{
		write(1, &st->c, 1);
		st = st->next;
	}
}