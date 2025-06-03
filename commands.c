#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"

char *parse_args(char *str, char *arg) {
    char *str_copy = strdup(str);
    char *result = NULL;

    char *token = strtok(str_copy, " ");

    while (token != NULL) {
        if (strcmp(token, arg) == 0) {
            token = strtok(NULL, " ");
            result = strdup(token);
            break;
        }
        token = strtok(NULL, " ");
    }

    free(str_copy);
    return result;
}

void parse_showuser_commands(char *str) {
    show_user();
}

void parse_adduser_commands(char *str) {
    char *name = NULL;
    int age = -1;

    name = parse_args(str, "--name");
    char *age_str = parse_args(str, "--age");
    if (age_str) {
        age = atoi(age_str);
    }

    if (name && age > 0) {
        user_t *user = add_user(name, age);
        printf("\tName: %s, Age: %d\n", user->name, user->age);
    } else {
        printf("Ошибка: команда некорректна. Пример: adduser --name Alex --age 20\n");
    }
}

void parse_delluser_commands(char *str) {
    char *name = parse_args(str, "--name");
    if (name != NULL) {
        del_user(name);
    } else {
        printf("Ошибка: команда некорректна. Пример: deluser --name Alex\n");
    }
}

void parse_command(char *str) {
    if (strstr(str, "listusers")) {
        parse_showuser_commands(str);
    } else if (strstr(str, "adduser")) {
        parse_adduser_commands(str);
    } else if (strstr(str, "deluser")) {
        parse_delluser_commands(str);
    }
}
