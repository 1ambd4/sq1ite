#include <stdio.h>
#include <stdbool.h>
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

#define ARRLEN(arr) (int)(sizeof(arr) / sizeof(arr[0]))


static inline void print_prompt();
static char* read_input();
static int execute_insert(char *input);
static int execute_select(char *input);

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} meta_command_result;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} prepare_result;

static struct {
    const char *name;
    const char *desc;
    int (*handler) (char *);
} command_table[] = {
    { "insert", "The INSERT command is used to create new rows in an existing table.", execute_insert },
    { "select", "The SELECT command is used to query the database.", execute_select },
};

typedef struct {
} statement;

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

meta_command_result execute_meta_command(char *meta_command)
{
    if (strcmp(meta_command, ".exit") == 0) {
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

prepare_result prepare_statement(char *input)
{
    return PREPARE_SUCCESS;
}

bool execute_statement(char *input)
{
    char *input_end = input + strlen(input);

    char *command = strtok(input, " ");
    if (command == NULL)  { return false; }

    char *args = command + strlen(command) + 1;
    if (args >= input_end) { args = NULL; }

    for (int i = 0; i < ARRLEN(command_table); ++i) {
        if (strcmp(command, command_table[i].name) == 0) {
            if (command_table[i].handler(args) == 0) {
                return true;
            }
        }
        if (i + 1 == ARRLEN(command_table)) {
            printf("Unrecognized command '%s'\n", command);
        }
    }
    return false;
}

static int execute_insert(char *input)
{
    printf("this is where we would do an insert.\n");
    return 0;
}

static int execute_select(char *input)
{
    printf("this is where we would do an select.\n");
    return 0;
}

int main()
{
    print_prompt();

    // meta-command
    for (char *input; (input = read_input()) != NULL; ) {

        if (input[0] == '.') {
            switch(execute_meta_command(input)) {
                case META_COMMAND_SUCCESS:
                    continue;
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    printf("Unrecognized meta command '%s'\n", input);
                    continue;
            }
        }

        // prepare statement
        switch(prepare_statement(input)) {
            case PREPARE_SUCCESS:
                break;
            case PREPARE_UNRECOGNIZED_STATEMENT:
                printf("Unrecognized statement '%s'.\n", input);
                continue;
        }

        // execute statement
        execute_statement(input);

    }
    return 0;
}
