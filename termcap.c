#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <string.h>
#include <termios.h>

int ret;
char *term_type;
char *af_cmd;
char *blink_cmd;
char *underline_cmd;
char *cm_cap;
int		cmpr_maj(char *s1, char *s2)
{
	int i;
	int diff;

	i = 0;
	while (s1[i] || s2[i])
	{ 
		if (s1[i] != s2[i])
		{
			diff = s1[i] - s2[i];
			if (diff != 32 && diff != -32)
            {
				return (0);
            }
		}
		i++;
	}
	return (1);
}

int		check_term()
{
	// int column_count;
	// int line_count;
	term_type = getenv("TERM");
	ret = tgetent(NULL, term_type);
	// char *blink_cmd = tgetstr("mb", NULL);
	af_cmd = tgetstr("AF", NULL);
    underline_cmd = tgetstr("us", NULL);
	// tputs(blink_cmd, 1, putchar);
	// column_count = tgetnum("co");
	// line_count = tgetnum("li");
	//printf("column:%d\n", column_count);
    return ret;
}
void    text_color(char *str)
{
    if(cmpr_maj(str, "green"))
        tputs(tparm(af_cmd, COLOR_MAGENTA), 1, putchar);
    if(cmpr_maj(str, "red"))
        tputs(tparm(af_cmd, COLOR_RED), 1, putchar);
    if(cmpr_maj(str, "pink"))
        tputs(tparm(af_cmd, COLOR_MAGENTA), 1, putchar);
    if(cmpr_maj(str, "black"))
        tputs(tparm(af_cmd, COLOR_BLACK), 1, putchar);
    if(cmpr_maj(str, "blue"))
        tputs(tparm(af_cmd, COLOR_BLUE), 1, putchar);
    if(cmpr_maj(str, "yellow"))
        tputs(tparm(af_cmd, COLOR_YELLOW), 1, putchar);
    if(cmpr_maj(str, "cyan"))
        tputs(tparm(af_cmd, COLOR_CYAN), 1, putchar);
    if(cmpr_maj(str, "white"))
        tputs(tparm(af_cmd, COLOR_WHITE), 1, putchar);
}

int main(int argc, char **argv)
{
    struct termios *p;

    check_term();
    text_color("CYAN");
    printf("TRUE\n");
    blink_cmd = tgetstr("mb", NULL);
    tputs(blink_cmd, 1, putchar);
    tputs(underline_cmd, 1, putchar);
    text_color("YELLOW");
    printf("FALSE\n");
    int a = tcgetattr(0, p);
    text_color("WHITE");
    printf("[%d]\n", a);
    while(1)
    {
        char *buf;
        cm_cap = tgetstr("cm", NULL);
        tputs(tgoto(cm_cap, 5, 5), 1, putchar);
        read(0, buf, 10);
    }
    (void)argc;
    (void)argv;
}
