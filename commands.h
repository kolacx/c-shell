#ifndef COMMANDS_H
#define COMMANDS_H

struct command_s {
    char *cmd;
    int (*routine)(int argc, char *argv[], int stream);
};

typedef struct command_s command_t;


void parse_command(char *str, int stream);
void parse_showuser_commands(char *str);
void parse_delluser_commands(char *str);
int cmd_add_user(int argc, char *argv[], int stream);

#endif //COMMANDS_H
