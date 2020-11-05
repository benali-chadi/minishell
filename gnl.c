#include "mini_shell.h"
#define BUFFER_SIZE 10000

char	*ft_stock(char **line, char *buff, int i)
{
	char	*newline;
	int		len;
	int		j;

	j = 0;
	len = (*line ? ft_strlen(*line) : 0);
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
		line = NULL;
	}
	while (j < len + i)
	{
		newline[j] = buff[j - len];
		j++;
	}
	newline[j] = '\0';
	return (newline);
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
