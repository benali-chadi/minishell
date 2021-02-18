#include "mini_shell.h"

int			skip_repeat(char *str, int *i, char c)
{
	int repeat;

	repeat = 0;
	while (str[*i] == c)
	{
		if (c == ';')
		{
			repeat++;
			if (repeat > 1)
			{
				ft_printf("minishell: syntax error near unexpected token `;;'\n"
);
				return (0);
			}
		}
		*i += 1;
	}
	return (1);
}

int			stock_index(int a)
{
	g_case_index[a] = '1';
	g_case_index[a + 1] = '\0';
	return (1);
}
