#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/ioctl.h>

#define eq(s) (!strcmp(optarg, s))
#define die(s) {perror(s); exit(1);}

unsigned short getwsize();
unsigned short ansicolor(char *);
char *repeat(char, unsigned short);
void usage();

int main(int argc, char **argv) {
    char chr = '-';
    unsigned short maxw = getwsize(), width = maxw, fg = 0, bg = 0;
    int c;
    while((c = getopt(argc, argv, "hc:s:f:b:")) != -1) {
        switch(c) {
            case 'h':
                usage();
                return 0;
            case 'c':
                chr = *optarg;
                break;
            case 's':
                width = atoi(optarg);
                break;
            case 'f':
                fg = 30 + ansicolor(optarg);
                break;
            case 'b':
                bg = 40 + ansicolor(optarg);
                break;
        }
    }
    char *line = repeat(chr, width);
    int pad = (width >= maxw) ? 0 : (maxw - width)/2;
    if(!fg && !bg)
        printf("%*.*s%s\n", pad, pad, " ", line);
    else if(!bg)
        printf("%*.*s\033[%dm%s\033[0m\n", pad, pad, " ", fg, line);
    else
        printf("%*.*s\033[%d;%dm%s\033[0m\n", pad, pad, " ", fg,
               bg, line);
    free(line);
    return 0;
}

unsigned short getwsize() {
    struct winsize ws;
    if(ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
        die("ioctl");
    return ws.ws_col;
}

unsigned short ansicolor(char *optarg) {
    if(eq("black"))
        return 0;
    else if(eq("red"))
        return 1;
    else if(eq("green"))
        return 2;
    else if(eq("yellow"))
        return 3;
    else if(eq("blue"))
        return 4;
    else if(eq("magenta"))
        return 5;
    else if(eq("cyan"))
        return 6;
    else if(eq("white"))
        return 7;
    else {
        fprintf(stderr, "Unknown color %s\n", optarg);
        exit(1);
    }
}

char *repeat(char c, unsigned short n) {
    char *line = malloc(n + 1);
    if(!line)
        die("malloc");
    for(unsigned short i = 0; i != n; i++)
        line[i] = c;
    line[n] = 0;
    return line;
}

void usage() {
    printf("Usage: hr [-h] [-c char] [-s n] [-f color] [-b color]\n\n"
           "A horizontal rule for terminal\n\n"
           "Options:\n"
           "  -h          display this message and exit\n"
           "  -c <char>   set character\n"
           "  -s <n>      set size\n"
           "  -f <color>  set foreground color\n"
           "  -b <color>  set background color\n\n"
           "Colors:\n"
           "  black, red, green, yellow, blue, magenta, cyan, white\n");
}
