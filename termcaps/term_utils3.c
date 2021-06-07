#include "../mini_shell.h"

void	cursor_backward(t_read *reads)
{
	char	c;

	c = ft_pop(&reads->left);
	if (c)
		ft_push_front(c, &reads->right);
}

void	cursor_forward(t_read *reads)
{
	char	c;

	c = ft_pop_front(&reads->right);
	if (c)
		ft_push(c, &reads->left);
}

void	delete_char(t_read *reads)
{
	char	*le;
	char	*dc;

	le = tgetstr("le", NULL);
	dc = tgetstr("dc", NULL);
	ft_pop(&reads->left);
	tputs(le, 1, ft_puts);
	tputs(dc, 1, ft_puts);
}

int	ft_getch(int fd, t_read *reads)
{
	char	c;
	int		total;
	int		ret;

	tcgetattr(0, &reads->term);
	tcgetattr(0, &reads->init);
	reads->term.c_lflag &= ~ (ICANON | ECHO | ECHOE);
	reads->term.c_cc[VMIN] = 1;
	reads->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &reads->term);
	total = 0;
	ret = read(fd, &c, 1);
	total += c;
	if (c == 27)
	{
		read(fd, &c, 1);
		total += c;
		read(fd, &c, 1);
		total += c;
	}
	tcsetattr(0, TCSANOW, &reads->init);
	return (total);
}

void	ft_add_line(t_stack **st, char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		ft_push(str[i++], st);
}
