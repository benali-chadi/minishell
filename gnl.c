/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smhah <smhah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 15:59:19 by cbenali-          #+#    #+#             */
/*   Updated: 2021/04/07 17:51:10 by smhah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
#define BUFFER_SIZE 1

char	*ft_stock(char **line, char *buff, int i)
{
	char	*new_line;
	int		len;
	int		j;

	j = 0;
	len = (*line ? ft_strlen(*line) : 0);
	if (!(new_line = (char *)malloc(len + i + 1)))
		return (0);
	while (j < len)
	{
		new_line[j] = *(*line + j);
		j++;
	}
	if (line)
	{
		free(*line);
		line = NULL;
	}
	while (j < len + i)
	{
		new_line[j] = buff[j - len];
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

int		gnl(int fd, char **line)
{
	char	*buf;
	int		i;
	int		j;

	i = 0;
	if (!(buf = malloc(BUFFER_SIZE + 1)))
		return (-1);
	while ((i = read(fd, buf, BUFFER_SIZE)) || *line)
	{
		buf[i] = '\0';
		j = 0;
		while (buf[j] && buf[j] != '\n')
			j++;
		if (buf[j] == '\n')
		{
			*line = ft_stock(line, buf, j);
			free(buf);
			return (1);
		}
		*line = ft_stock(line, buf, ft_strlen(buf));
	}
	ft_putstr_fd("exit", 1);
	free(buf);
	return (0);
}
