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


// int execute_command(char *command) {
// char *argv[BUFSIZ];
// int argc = 0;

// char *token = strtok(command, " ");
// while (token) {
// argv[argc] = token;
// argc++;
// token = strtok(NULL, " ");
// }

// for (int i = 0; i < sizeof(command_list); i++) {
// if (strcmp(argv[0], command_list[i].cmd) == 0) {
// command_list[i].routine(argc, argv);
// }
// }

// return -1;
// }


int cmd_add_user(int argc, char *argv[]) {
    char *name = NULL;
    int age = -1;
    char *age_from_str = NULL;
    int c;

    opterr = 0;
    optind = 1;
    
    while ((c = getopt(argc, argv, "ln:a:")) != -1)
        switch (c) {
            case 'l':
                show_user();
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
        printf("\tName: %s, Age: %d\n", user->name, user->age);
    }

    return 0;
}

void parse_command(char *str) {
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
        if (strcmp(argv[0], command_list[i].cmd) == 0) {
            int ans = command_list[i].routine(argc, argv);
            if (ans != 0) {
                fprintf(stderr, "ERROR");
            }
            break;
        }
    }
}


// char *parse_args(char *str, char *arg) {
//     char *str_copy = strdup(str);
//     char *result = NULL;
//
//     char *token = strtok(str_copy, " ");
//
//     while (token != NULL) {
//         if (strcmp(token, arg) == 0) {
//             token = strtok(NULL, " ");
//             result = strdup(token);
//             break;
//         }
//         token = strtok(NULL, " ");
//     }
//
//     free(str_copy);
//     return result;
// }

// void parse_showuser_commands(char *str) {
// show_user();
// }

// void parse_adduser_commands(char *str) {
//     char *name = NULL;
//     int age = -1;
//
//     name = parse_args(str, "--name");
//     char *age_str = parse_args(str, "--age");
//     if (age_str) {
//         age = atoi(age_str);
//     }
//
//     if (name && age > 0) {
//         user_t *user = add_user(name, age);
//         printf("\tName: %s, Age: %d\n", user->name, user->age);
//     } else {
//         printf("Ошибка: команда некорректна. Пример: adduser --name Alex --age 20\n");
//     }
// }

// void parse_delluser_commands(char *str) {
//     char *name = parse_args(str, "--name");
//     if (name != NULL) {
//         del_user(name);
//     } else {
//         printf("Ошибка: команда некорректна. Пример: deluser --name Alex\n");
//     }
// }

// void parse_command(char *str) {
// if (strstr(str, "listusers")) {
// parse_showuser_commands(str);
// } else if (strstr(str, "adduser")) {
// parse_adduser_commands(str);
// } else if (strstr(str, "deluser")) {
// parse_delluser_commands(str);
// }
// }
