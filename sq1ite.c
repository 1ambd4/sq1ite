#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <readline/history.h>
#include <readline/readline.h>

#define ANSI_FG_BLACK   "\33[1;30m"
#define ANSI_FG_RED     "\33[1;31m"
#define ANSI_FG_GREEN   "\33[1;32m"
#define ANSI_FG_YELLOW  "\33[1;33m"
#define ANSI_FG_BLUE    "\33[1;34m"
#define ANSI_FG_MAGENTA "\33[1;35m"
#define ANSI_FG_CYAN    "\33[1;36m"
#define ANSI_FG_WHITE   "\33[1;37m"

#define ANSI_BG_BLACK   "\33[1;40m"
#define ANSI_BG_RED     "\33[1;41m"
#define ANSI_BG_GREEN   "\33[1;42m"
#define ANSI_BG_YELLOW  "\33[1;43m"
#define ANSI_BG_BLUE    "\33[1;44m"
#define ANSI_BG_MAGENTA "\33[1;45m"
#define ANSI_BG_CYAN    "\33[1;46m"
#define ANSI_BG_WHITE   "\33[1;37m"

#define ANSI_NONE       "\33[0m"

static inline void print_prompt()
{
    printf("%ssq1ite%s, a sqlite clone from scratch in c.\n", ANSI_FG_BLUE, ANSI_NONE); 
}

static char* read_input()
{
    static char* line_read = NULL;

    if (line_read) {
        free(line_read);
        line_read = NULL;
    }

    line_read = readline("sq1ite> ");

    if (line_read && *line_read) {
        add_history(line_read);
    }

    return line_read;
}

int main()
{
    print_prompt();
    for (char *input; (input = read_input()) != NULL; ) {
        if (strcmp(input, ".exit") == 0) {
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command '%s'\n", input);
        }
    }
    return 0;
}
