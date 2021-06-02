#include "../mini_shell.h"

void	left_right(t_read **reads, int c)
{
	if (c == RIGHT)
	{
		if ((*reads)->l_len < (*reads)->count)
		{
			cursor_forward(*reads);
			write(1, "\033[C", 4);
			(*reads)->l_len++;
			(*reads)->r_len--;
		}
	}
	else if (c == LEFT)
	{
		if ((*reads)->l_len > 0)
		{
			write(1, "\033[D", 4);
			cursor_backward((*reads));
			(*reads)->l_len--;
			(*reads)->r_len++;
		}
	}
}
