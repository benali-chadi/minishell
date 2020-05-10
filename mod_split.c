#include "mini_shell.h"

int		g_con = 0;
int		g_quotation = 0;

int		num_words(char *str, char c)
{
	int words;

	words = 0;
	if (*str != c && *str != '\0')
		words++;
	while (*str)
	{
		if (*str == c)
			if (*(str + 1) != c && *(str + 1) != '\0')
				words++;
		if (c == ' ' && (*str == '"' || *str == '\''))
		{
			g_quotation = 1;
			if (*(str - 1) != c)
				words++;
			break;
		}
		str++;
	}
	return (words);
}

int		num_chars(char *str, int c, int *p)
{
	int i;
	int w;

	i = *p;
	while (str[i] == c)
	{
		i++;
		(*p)++;
	}
	while (str[i])
	{
		if (str[i] == c && !g_con)
			break;
		w++;
		i++;
	}
	return (w);
}

void		give_value(char *split, char *str, int *p, int c)
{
	int j;

	j = -1;
	while (str[*p] != '\0')
	{
		if (str[*p] == c && !g_con)
			break ;
		split[++j] = str[*p];
		(*p)++;
	}
	split[++j] = '\0';
}

char		**free_tab(char **split, int i)
{
	while (i--)
		free(split[i]);
	free(split);
	split = NULL;
	return (split);
}

char	**mod_split(char *str, char c)
{
	char	**split;
	int		words;
	int		i;
	int		k;

	words = num_words(str, c);
	g_con = 0;
	i = -1;
	k = 0;
	if (!(split = malloc(sizeof(char *) * (words + 1))))
		return (0);
	while (++i < words)
	{
		if (i == words - 1 && g_quotation)
			g_con = 1;
		if (!(split[i] = malloc(num_chars(str, c, &k) + 1)))
			return (free_tab(split, i));
		give_value(split[i], str, &k, c);
	}
	split[i] = 0;
	return(split);
}