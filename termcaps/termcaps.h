#ifndef TERMCAPS_H
# define TERMCAPS_H

# include <curses.h>
# include <term.h>
# include <termios.h>
# define UP			183
# define DOWN		184
# define LEFT 		186
# define RIGHT		185
# define ENTER		10
# define REMOVE		127
# define TAB		9
# define CTRL_D		4

typedef struct s_stack {
	char			c;
	struct s_stack	*next;
}				t_stack;

typedef struct s_read {
	struct termios	term;
	struct termios	init;
	t_stack			*left;
	t_stack			*right;
	char			*current_line;
	int				l_len;
	int				r_len;
	int				count;
}				t_read;

int		read_char(int fd, char **line);
int		ft_getch(int fd, t_read *reads);
void	delete_char(t_read *reads);
void	cursor_forward(t_read *reads);
void	cursor_backward(t_read *reads);
void	save_and_print(char c, t_read *reads);
void	print_stack(t_stack *st);
int		ft_puts(int c);
char	ft_pop(t_stack **st);
void	ft_push(char c, t_stack **st);
int		ft_pop_front(t_stack **ri);
void	ft_push_front(char c, t_stack **ri);
char	*ft_join_stacks(t_read reads);
void	ft_add_line(t_stack **st, char *str);
int		save_or_remove(t_read *reads, int c);
char	*last_char(t_stack *st);

/*
	** BONUS
*/

void	left_right(t_read **reads, int c);

#endif