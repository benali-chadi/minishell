#include "mini_shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include "ft_printf/libft/libft.h"

# define UP			183
# define DOWN		184
# define LEFT 		186
# define RIGHT		185
# define ENTER		10
# define REMOVE		127
# define TAB		9
# define CTRL_D		4

struct termios	term;
struct termios	init;

typedef struct	s_stack {
	char c;
	struct s_stack *next;
}				t_stack;

typedef struct	s_read {
	t_stack *left;
	t_stack *right;
	int l_len;
	int r_len;
	int count;
}				t_read;

char	*ft_join_stacks(t_read reads)
{
	char *str;
	t_stack *tmp;
	int i;

	str = malloc(reads.l_len + reads.r_len + 1);
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
	return (str);
}

void	ft_push_front(char c, t_stack **ri)
{
	t_stack *new = malloc(sizeof(t_stack));

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

	new = malloc(sizeof(t_stack));
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
	char *ce = tgetstr("ce", NULL);
	tputs(ce, 1, putchar);
	while (st)
	{
		write(1, &st->c, 1);
		st = st->next;
	}
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

char ft_getch()
{
	char c;
	int total;
	int ret;

	tcgetattr(0, &term);
	tcgetattr(0, &init);
	term.c_lflag &= ~ (ICANON | ECHO | ECHOE);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	total = 0;
	ret = read(0, &c, 1);
	total += c;
	tcsetattr(0, TCSANOW, &init);
	return (total);
}

int ft_read_line(int fd, t_read *reads)
{
	int				c;
	int				total;
	int				ret;

	c = ft_getch();
	if (c >= 32 && c < 127)
	{
		save_and_print(c, reads);
		reads->l_len++;
		// reads->col++;
		reads->count++;
	}
	else if (c == 27)
	{
		c = ft_getch();
		c = ft_getch();
		if (c == 'A') // up
		{

		}
		else if (c == 'D') // left
		{
			if (reads->l_len > 0)
			{
				write(1, "\033[D", 4);
				cursor_backward(reads);
				// reads->col--;
				reads->l_len--;
				reads->r_len++;
			}

		}
		else if (c == 'B') // down
		{

		}
		else if (c == 'C') // right
		{
			if (reads->l_len < reads->count)
			{
				cursor_forward(reads);
				write(1, "\033[C", 4);
				// reads->col++;
				reads->l_len++;
				reads->r_len--;
			}

		}
	}
	if (c == REMOVE && reads->l_len)
	{
		delete_char(reads);
		// reads->col--;
		reads->count--;
		reads->l_len--;
	}
	if (c == ENTER)
	{
		return (0);
	}
	return (1);
}

int read_char(int fd, char **line)
{
	const char *term_type = getenv("TERM");
	tgetent(NULL, term_type);
	t_read reads;
	// char *cm_c = tgetstr("cm", NULL);
	// int				col = 1;
	// int				count = 0;
	// char *line;
	// int fd  = 0;
	reads.l_len = 0;
	reads.r_len = 0;
	reads.left = NULL;
	reads.right = NULL;
	while (ft_read_line(fd, &reads))
	{
		// print_stack(left);
		// printf("\n");
		// print_stack(right);
	}
	*line = ft_join_stacks(reads);
	return (0);
}
