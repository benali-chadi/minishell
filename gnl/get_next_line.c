/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbenali- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 22:48:02 by cbenali-          #+#    #+#             */
/*   Updated: 2019/11/07 16:02:47 by cbenali-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_stock(char **line, char *buff, int i)
{
	char	*newline;
	int		len;
	int		j;

	j = 0;
	len = (line ? ft_strlen(*line) : 0);
	if (!(newline = (char *)malloc(len + i + 1)))
		return (0);
	while (j < len)
	{
		newline[j] = *(*line + j);
		j++;
	}
	if (line)
	{
		free(*line);
		*line = NULL;
	}
	while (j < len + i)
	{
		newline[j] = buff[j - len];
		j++;
	}
	newline[j] = '\0';
	return (newline);
}

int		ret_line(char **line, char **str, char *buff, int ret)
{
	int		i;

	i = 0;
	buff[ret] = '\0';
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
	{
		*line = ft_stock(line, buff, i);
		*str = ft_stock(str, buff + i + 1, ret - i - 1);
		free(buff);
		buff = NULL;
		return (1);
	}
	if (buff[i] == '\0')
		*line = ft_stock(line, buff, i);
	return (0);
}

int		str_new_line(char **line, char **str, char *buff, int i)
{
	char	*tmp;

	tmp = *str;
	free(buff);
	if (!(*line = ft_stock(line, *str, i)))
		return (-1);
	if (!(*str = ft_stock(0, *str + i + 1, ft_strlen(*str) - i - 1)))
		return (-1);
	free(tmp);
	tmp = NULL;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int			i;
	static char	*str;
	char		*buff;

	if (!(buff = (char *)malloc(BUFFER_SIZE + 1))
	|| fd < 0 || !(*line = ft_strdup("")))
		return (-1);
	i = 0;
	if (str)
		while (str[i] && str[i] != '\n')
			i++;
	if (str && str[i] == '\n')
		return (str_new_line(line, &str, buff, i));
	else if (str && str[i] == '\0')
	{
		*line = ft_stock(line, str, i);
		free(str);
		str = NULL;
	}
	while ((i = read(fd, buff, BUFFER_SIZE)))
		if (ret_line(line, &str, buff, i))
			return (1);
	free(buff);
	buff = NULL;
	return (0);
}
