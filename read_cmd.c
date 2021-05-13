#include "mini_shell.h"

int g_flag = 0;
int g_flag2 = 0;

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

void ft_push(char c, t_stack **st)
{
	t_stack *tmp;
	t_stack *new;

	new = m_malloc(sizeof(t_stack));
	new->c = c;
	new->next = NULL;

	if (!*st)
	{
		*st = new;
		return;
	}
	tmp = *st;

	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

char ft_pop(t_stack **st)
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

int		ft_puts(int c)
{
	return (write(1, &c, 1));
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

void add_line(char *str, t_stack **st)
{
	int i;

	i = 0;
	while (str[i])
		ft_push(str[i++], st);
}

void save_and_print(char c, t_read *reads)
{
	char *cur_pos;

	write(1, &c, 1);
	ft_push(c, &reads->left);
	cur_pos = tgetstr("sc", NULL);
	tputs(cur_pos, 1, ft_puts);
	print_stack(reads->right);
	cur_pos = tgetstr("rc", NULL);
	tputs(cur_pos, 1, ft_puts);
}

void cursor_backward(t_read *reads)
{
	char c = ft_pop(&reads->left);
	
	if (c)
		ft_push_front(c, &reads->right);
}

void cursor_forward(t_read *reads)
{
	char c = ft_pop_front(&reads->right);
	
	if (c)
		ft_push(c, &reads->left);
}

void delete_char(t_read *reads)
{
	char *le = tgetstr("le", NULL);
	char *dc = tgetstr("dc", NULL);

	ft_pop(&reads->left);
	tputs(le, 1, ft_puts);
	tputs(dc, 1, ft_puts);
}

char ft_getch(int fd, t_read *reads)
{
	char c;
	int total;
	int ret;

	tcgetattr(0, &reads->term);
	tcgetattr(0, &reads->init);
	reads->term.c_lflag &= ~ (ICANON | ECHO | ECHOE);
	reads->term.c_cc[VMIN] = 1;
	reads->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &reads->term);
	total = 0;
	ret = read(fd, &c, 1);
	total += c;
	tcsetattr(0, TCSANOW, &reads->init);
	return (total);
}

// void	read_prev(t_histo *histo)
// {
// 	t_histo *read;

// 	read = g_histo;
// 	read = ft_lstlast_cmd(read);
// 	read = read->previous;
// 	ft_printf("[%s]\n", read->command_line);
// }

void ft_add_line(t_stack **st, char *str)
{
	int i;

	i = 0;
	while (str[i])
		ft_push(str[i++], st);
}

int ft_read_line(int fd, t_read *reads, t_histo **read)
{
	int		c;
	// char	*line = NULL;
	//t_histo *tmp;
	// t_histo *redox;

	c = ft_getch(fd, reads);
	if (c == 4 && !reads->left && !reads->right)
	{
		ft_printf("exit\n");
		exit(0);
	}
	if (c >= 32 && c < 127)
	{
		save_and_print(c, reads);
		reads->l_len++;
		reads->count++;
	}
	else if (c == 27)
	{
		c = ft_getch(fd, reads);
		c = ft_getch(fd, reads);
		if (c == 'A' && (*read)) // up
		{
				tputs(tgetstr("ch", NULL), 1, ft_puts);
				tputs(tgetstr("dl", NULL), 1, ft_puts);
				// save line f historique
				
				if((*read)->next == NULL && g_flag == 0)
				{
					g_flag = 1;
					add_back_cmd(&g_histo, ft_join_stacks(*reads));
					(*read) = (*read)->next;
				}
				else
				{
					(*read)->command_line = ft_join_stacks(*reads);
				}
				if (*read != g_histo)
					*read = (*read)->previous;
				reads->left = NULL;
				reads->right = NULL;
				// Renitialize
				reads->l_len = ft_strlen((*read)->command_line);
				reads->r_len = 0;
				reads->count = reads->l_len;
				ft_add_line(&reads->left, (*read)->command_line);
				print_prompt();
				print_stack(reads->left);
		}
		else if (c == 'D') // left
		{
			if (reads->l_len > 0)
			{
				write(1, "\033[D", 4);
				cursor_backward(reads);
				reads->l_len--;
				reads->r_len++;
			}

		}
		else if (c == 'B' && (*read)) // down
		{
			tputs(tgetstr("ch", NULL), 1, ft_puts);
			tputs(tgetstr("dl", NULL), 1, ft_puts);
			// save line f historique
			if ((*read)->next != NULL)
			{
				(*read)->command_line = ft_join_stacks(*reads);
				*read = (*read)->next;
			}
			reads->left = NULL;
			reads->right = NULL;
			ft_add_line(&reads->left, (*read)->command_line);
			print_prompt();
			print_stack(reads->left);
		}
		else if (c == 'C') // right
		{
			if (reads->l_len < reads->count)
			{
				cursor_forward(reads);
				write(1, "\033[C", 4);
				reads->l_len++;
				reads->r_len--;
			}

		}
	}
	if (c == REMOVE && reads->l_len)
	{
		delete_char(reads);
		reads->count--;
		reads->l_len--;
	}
	if (c == ENTER)
	{
		if ((*read) && (*read)->next != NULL)
			ft_remove_node_cmd_1();
		return (0);
	}
	return (1);
}

int read_char(int fd, char **line)
{
	t_read reads;
	t_histo *read;
	const char *term_type = getenv("TERM");
	
	tgetent(NULL, term_type);
	reads.l_len = 0;
	reads.r_len = 0;
	reads.count = 0;
	reads.left = NULL;
	reads.right = NULL;
	reads.first = 0;
	read = g_histo;
	read = ft_lstlast_cmd(read);
	g_flag = 0;
	while (ft_read_line(fd, &reads, &read));
	*line = ft_join_stacks(reads);
	add_back_cmd(&g_histo, ft_strdup(*line));
	return (1);
}
