#include "mini_shell.h"

int		ft_strcmpr(char *s1, char *s2)
{
	int i;

	i = 0;
	while(s1[i] || s2[i])
	{
		if(s1[i] != s2[i])
			return(0);
		i++;
	}
	return(1);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int i;

	i = -1;
	while(s2[++i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return(s1);
}

int		is_alpha_digit(char a)
{
	if ((a <= 'Z' && a >= 'A') || (a <= 'z' && a >= 'a' )|| (a <= '9' && a >= '0'))
		return (1);
	return(0);
}

void    *ft_realloc(void *ptr, int size)
{
    void *tmp;

    tmp = ptr;
    ptr = malloc(size);
    ptr = ft_strcpy(ptr, tmp);
    free(tmp);
    return(ptr);
}

void	init_cnt()
{
	int i;

	i = 0;
	while (i < 128)
		cnt[i++] = 0;
	cnt['0'] = '\0';
	cnt['a'] = '\a';
	cnt['b'] = '\b';
	cnt['t'] = '\t';
	cnt['n'] = '\n';
	cnt['v'] = '\v';
	cnt['f'] = '\f';
	cnt['r'] = '\r';
	cnt['e'] = '\e';
}