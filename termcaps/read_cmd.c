#include "../mini_shell.h"

int g_flag = 0;
int g_flag2 = 0;

void reenitialize(t_read **reads, char *cmd)
{
	(*reads)->left = NULL;
	(*reads)->right = NULL;
	(*reads)->l_len = ft_strlen(cmd);
	(*reads)->r_len = 0;
	(*reads)->count = (*reads)->l_len;
	ft_add_line(&(*reads)->left, cmd);
	print_prompt();
	print_stack((*reads)->left);
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
				(*read)->command_line = ft_join_stacks(*reads);
			if (*read != g_histo)
				*read = (*read)->previous;
			reenitialize(&reads, (*read)->command_line);
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
			reenitialize(&reads, (*read)->command_line);
		}
		else if (c == 'C') // right
			if (reads->l_len < reads->count)
			{
				cursor_forward(reads);
				write(1, "\033[C", 4);
				reads->l_len++;
				reads->r_len--;
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
