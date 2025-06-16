#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"
#include "commands.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


command_t command_list[] = {
    {"user", cmd_add_user},
    {NULL, NULL}
};

int cmd_add_user(int argc, char *argv[], int stream) {
    char *name = NULL;
    int age = -1;
    char *age_from_str = NULL;
    int c;

    opterr = 0;
    optind = 1;

    while ((c = getopt(argc, argv, "ln:a:")) != -1)
        switch (c) {
            case 'l':
                show_user(stream);
                break;
            case 'n':
                name = strdup(optarg);
                break;
            case 'a':
                age_from_str = optarg;
                age = atoi(age_from_str);
                break;
        }

    if (name && age > 0) {
        user_t *user = add_user(name, age);

        char buffer[256];
        int len = snprintf(buffer, sizeof(buffer), "\tName: %s, Age: %d\n", user->name, user->age);

        write(stream, buffer, len);
    }

    return 0;
}

void parse_command(char *str, int stream) {
    char *str_copy = strdup(str);
    char *argv[BUFSIZ];
    int argc = 0;

    char *token = strtok(str_copy, " ");
    while (token) {
        argv[argc] = strdup(token);
        argc++;
        token = strtok(NULL, " ");
    }

    for (int i = 0; i < sizeof(command_list); i++) {
        if (command_list[i].cmd != NULL && strcmp(argv[0], command_list[i].cmd) == 0) {
            int ans = command_list[i].routine(argc, argv, stream);
            if (ans != 0) {
                char *error_msg = "ERROR\n";
                write(stream, error_msg, strlen(error_msg));
            }
            return;
        }
    }
    char *msg = "Command not Found\n";
    write(stream, msg, strlen(msg));
}
