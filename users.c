#include <stdio.h>
#include "users.h"
#include "commands.h"

#include <stdlib.h>
#include <string.h>


user_t *users[1024];

void init_users(void) {
    for (int i = 0; i < 1024; i++) {
        users[i] = NULL;
    }
}

void show_user() {
    for (int i = 0; i < 1024; i++) {
        if (users[i] != NULL) {
            printf("\t%d) Name: %s, Age: %d\n", i + 1, users[i]->name, users[i]->age);
        }
    }
}

user_t *add_user(char *name, int age) {
    user_t *user = malloc(sizeof(user_t));
    user->name = strdup(name);
    user->age = age;

    user_t *res = add_user_to_list(user);

    if (res == NULL) {
        return NULL;
    }
    return user;
}

void del_user(char *name) {
    for (int i = 0; i < 1024; i++) {
        if (users[i] != NULL && users[i]->name != NULL) {
            if (strcmp(users[i]->name, name) == 0) {
                free(users[i]);
                users[i] = NULL;
                return;
            }
        }
    }
}

user_t *add_user_to_list(user_t *user) {
    for (int i = 0; i < 1024; i++) {
        if (users[i] == NULL) {
            users[i] = user;
            return user;
        }
    }
    return NULL;
}
