#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define VERSION "0.1.0"

#define print_error(...) fprintf(stderr, "hr: " __VA_ARGS__);

// get terminal width size
int get_term_cols() {
    char *columns_env;
    struct winsize ws;

    columns_env = getenv("COLUMNS");
    if(columns_env)
        return atoi(columns_env);

    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
        return -1;

    return ws.ws_col;
}

// return a string with the repeated character
char *repeat_char(char c, int count) {
    char *line = NULL;

    line = malloc(count + 1);
    if(!line)
        return NULL;

    for(int i = 0; i != count; i++)
        line[i] = c;

    line[count] = '\0';

    return line;
}

void display_help() {
    printf(
        "Usage: hr [-h] [-v] [-n COUNT] [CHAR]\n\n"
        "Options:\n"
        "  -h        display this help and exit\n"
        "  -v        output version information and exit\n"
        "  -n COUNT  repeat CHAR COUNT times\n"
        "  -l        left alignment\n"
        "  -r        right alignment\n\n"
        "Report bugs to <https://github.com/xfgusta/hr/issues>\n"
    );
    exit(EXIT_SUCCESS);
}

void display_version() {
    printf("hr version %s\n", VERSION);
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    int opt;
    char chr = '-';
    int count = 0;
    int alignment = 0;
    int term_cols;
    char *line;

    while((opt = getopt(argc, argv, "hvn:lr")) != -1) {
        switch(opt) {
            case 'h':
                display_help();
                break;
            case 'v':
                display_version();
                break;
            case 'n':
                count = atoi(optarg);
                if(count <= 0) {
                    print_error("COUNT must be greater than 0\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'l':
                alignment = -1;
                break;
            case 'r':
                alignment = 1;
                break;
        }
    }

    // skip to the non-option arguments
    argc -= optind;
    argv += optind;

    if(argc >= 1)
        chr = **argv;

    term_cols = get_term_cols();
    if(term_cols <= 0)
        term_cols = 80;

    // if none of the options were given
    if(alignment == 0 && count == 0)
        count = term_cols;

    // default value if left/right alignment options was given
    if(count == 0)
        count = 80;

    line = repeat_char(chr, count);
    if(!line) {
        print_error("could not repeat \"%c\" %d times\n", chr, count);
        exit(EXIT_FAILURE);
    }

    switch(alignment) {
        // left
        case -1:
            puts(line);
            break;
        // center
        case 0:
            printf("%*s%s\n", (term_cols - count) / 2, "", line);
            break;
        // right
        case 1:
            printf("%*s%s\n", term_cols - count, "", line);
            break;
    }

    free(line);
    exit(EXIT_SUCCESS);
}
