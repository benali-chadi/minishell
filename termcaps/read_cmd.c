#include "../mini_shell.h"

int	g_flag = 0;

void	reenitialize(t_read **reads, char *cmd)
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

void	clear_and_reen(t_read *reads, char *command_line)
{
	tputs(tgetstr("ch", NULL), 1, ft_puts);
	tputs(tgetstr("dl", NULL), 1, ft_puts);
	reenitialize(&reads, command_line);
}

void	up_down(t_read *reads, t_histo ***read, int c)
{
	if (c == UP && (**read))
	{
		if ((**read)->next == NULL && g_flag == 0)
		{
			g_flag = 1;
			add_back_cmd(&g_histo, ft_join_stacks(*reads));
			(**read) = (**read)->next;
		}
		else
			(**read)->command_line = ft_join_stacks(*reads);
		if (**read != g_histo)
			**read = (**read)->previous;
		clear_and_reen(reads, (**read)->command_line);
	}
	else if (c == DOWN && (**read))
	{
		if ((**read)->next != NULL)
		{
			(**read)->command_line = ft_join_stacks(*reads);
			**read = (**read)->next;
			clear_and_reen(reads, (**read)->command_line);
		}
	}
}

int	ft_read_line(int fd, t_read *reads, t_histo **read)
{
	int	c;

	c = ft_getch(fd, reads);
	if (c == 4 && !reads->left && !reads->right)
	{
		printf("exit\n");
		exit(0);
	}
	if (save_or_remove(reads, c))
		;
	else if (c == UP || c == DOWN)
		up_down(reads, &read, c);
	else if ((c == LEFT || c == RIGHT) && BONUS)
		left_right(&reads, c);
	if (c == ENTER)
	{
		if ((*read) && (*read)->next != NULL)
			ft_remove_node_cmd_1();
		ft_putchar_fd('\n', 1);
		return (0);
	}
	return (1);
}

int	read_char(int fd, char **line)
{
	t_read		reads;
	t_histo		*read;
	const char	*term_type;

	term_type = getenv("TERM");
	tgetent(NULL, term_type);
	reads.l_len = 0;
	reads.r_len = 0;
	reads.count = 0;
	reads.left = NULL;
	reads.right = NULL;
	reads.first = 0;
	read = g_histo;
	read = ft_lstlast_cmd(read);
	g_utils.for_ctrl_c = 0;
	g_flag = 0;
	while (ft_read_line(fd, &reads, &read))
		;
	if (!g_utils.for_ctrl_c)
		*line = ft_join_stacks(reads);
	add_back_cmd(&g_histo, ft_strdup(*line));
	return (1);
}