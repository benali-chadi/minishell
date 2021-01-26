#include "mini_shell.h"

int g_var_one;
int g_var_two;

static int	ft_countwords(const char *str, char *c)
{
	int i;
	int compteur;

	g_var_one = 0;
	g_var_two = 0;
	compteur = 0;
	i = 0;
	while (str[i] != '\0')
	{
			if(str[i] == '"')
				g_var_two = 1;
			if(str[i] == '\'')
				g_var_one = 1;
		while (ft_strchr(c, str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		compteur++;
		while ((g_var_one == 1 || g_var_two == 1 || !ft_strchr(c, str[i])) && str[i] != '\0')
		{
			if(str[i] == '"')
				g_var_two = (g_var_two == 1 ? 0 : 1);
			if(str[i] == '\'')
				g_var_one = (g_var_one == 1 ? 0 : 1);
			i++;
		}
		if (str[i] == '\0')
			break ;
	}
	return (compteur);
}

static int	ft_countlen(const char *str, char *c, int *i)
{
	int len;

	g_var_one = 0;
	g_var_two = 0;
	len = 0;
	while (str[*i] != '\0')
	{
		if(str[*i] == '"')
			g_var_two = 1;
		if(str[*i] == '\'')
			g_var_one = 1;
		while (ft_strchr(c, str[*i]))
			*i = *i + 1;
		if (str[*i] == '\0')
			return (len);
		while ((g_var_one == 1 || g_var_two == 1 || !ft_strchr(c, str[*i])) && str[*i] != '\0')
		{
			if(str[*i] == '"')
				g_var_two = (g_var_two == 1 ? 0 : 1);
			if(str[*i] == '\'')
				g_var_one = (g_var_one == 1 ? 0 : 1);
			*i = *i + 1;
			len++;
		}
		return (len);
		if (str[*i] == '\0')
			return (len);
	}
	return (len + 10);
}

int			ft_stock_red(char **tab, int a, char o)
{
	if(g_var_one == 0 && g_var_two == 0)
		tab[a][g_join_red++] = o;
	return(g_join_red);
}

static char	**result(char **tab, const char *str, char *c)
{
	int a;
	int b;
	int i;

	i = 0;
	a = 0;
	g_var_one = 0;
	g_var_two = 0;
	while (str[i] != '\0' && ((g_join_red = 0) >= 0))
	{
		if(str[i] == '"')
			g_var_two = 1;
		if(str[i] == '\'')
			g_var_one = 1;
		b = 0;
		while (ft_strchr(c, str[i]) && ((b = ft_stock_red(tab, a, str[i])) >= 0))
			i++;
		printf("b=[%d]\n",  b);
		if (str[i] == '\0')
			break ;
		while ((g_var_one == 1 || g_var_two == 1 || !ft_strchr(c, str[i]) ) && str[i] != '\0')
		{
			if(str[i] == '"')
				g_var_two = (g_var_two == 1 ? 0 : 1);
			if(str[i] == '\'')
				g_var_one = (g_var_one == 1 ? 0 : 1);
			tab[a][b] = str[i];
			i++;
			b++;
		}
		//printf("---a=[%d]|b=[%d]---\n", a, b);
		tab[a][b] = '\0';
		a++;
	}
	tab[a] = 0;
	return (tab);
}

static char	**freetab(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (0);
}

char		**mod_split_red(char const *s, char *c)
{
	int		i;
	int		casee;
	char	**tab;
	int		*p;
	int		len;

	i = 0;
	g_join_red = 0;
	if (s)
		casee = ft_countwords(s, c);
	else
		return (0);
	if (!(tab = (char **)m_malloc(sizeof(char*) * (casee + 1))))
		return (0);
	casee = 0;
	p = &casee;
	while (i < ft_countwords(s, c))
	{
		len = ft_countlen(s, c, p);
		if (!(tab[i] = (char *)m_malloc(sizeof(char) * (len + 1))))
			return (freetab(tab, i));
		i++;
	}
	tab = result(tab, s, c);
	return (tab);
}

// int main()
// {
// 	char **tab;

// 	char *str = ">123<5<<67>>8'>'99";
// 	tab = mod_split_red(str, "><");
// 	int i;

// 	i = 0;
// 	while(tab[i])
// 	{
// 		printf("[%s]\n" ,tab[i++]);
// 	}
// }