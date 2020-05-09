#ifndef MINI_SHELL_H
#define MINI_SHELL_H

#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

typedef struct	s_command_info {
	char		*command;
	char		*options;
	char		*string;
}				t_command_info;

typedef struct	s_tests {
	int			echo;
	int			cd;
	int			pwd;
	int			export_t;
	int			unset;
	int			env;
	int			exit;
	int			ls;
}				t_tests;

t_command_info	command_info;
t_tests			tests;

char			**mod_split(char *str, char c);

#endif