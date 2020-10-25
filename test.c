#include <unistd.h>
#include <stdio.h>
#include "mini_shell.h"

int main()
{
	char *c;
	char *line;

	line = ft_strdup("\0");

	while (1)
	{
		if (!(read(0, &c, 1)) || *c != '\n')
			break;
		printf("%s\n", c);
		// if (*c != '\n')
		// 	break;
		line = ft_strjoin(line, c);
	}
	
	printf("%s\n", line);
	return(0);
}