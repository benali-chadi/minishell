#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int main(int ac, char **av)
{
	ac--;
	char *line;
	int fd;

	fd = open("main.c", O_RDONLY);
	if (fd > 0)
		while(get_next_line(fd, &line))
		{
			printf("%s\n", line);
			free(line);
		}
//	printf("%s\n", line);
	free(line);
}
