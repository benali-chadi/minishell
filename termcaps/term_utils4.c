#include "../mini_shell.h"

int	save_or_remove(t_read *reads, int c)
{
	if (c >= 32 && c < 127)
	{
		save_and_print(c, reads);
		reads->l_len++;
		reads->count++;
		return (1);
	}
	if (c == REMOVE && reads->l_len)
	{
		delete_char(reads);
		reads->count--;
		reads->l_len--;
		return (1);
	}
	return (0);
}

char	*last_char(t_stack *st)
{
	t_stack	*tmp;
	char	*c;

	tmp = st;
	c = m_malloc(2);
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	c[0] = tmp->c;
	c[1] = '\0';
	return (c);
}
