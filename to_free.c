#include "mini_shell.h"

void	*g_alloc[400];
int		g_all = 0;

void	*m_malloc(size_t n)
{
		void            *tmp;

		if (!(tmp = malloc(n)))
				return (NULL);
		g_alloc[g_all] = tmp;
		g_all++;
		return (tmp);
}

void	to_free(void)
{
		int i;

		i = -1;
		while (++i < g_all)
				free(g_alloc[i]);
}