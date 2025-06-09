#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct passwd {
    char *username;
    char *hashed_password;
    char *uid;
    char *gid;
    char *gecos;
    char *home_path;
    char *login_shell;
};

struct passwd_list {
    struct passwd *passwd;
    struct passwd *next;
};

struct passwd *parser_passwd(char *str) {
    struct passwd *pwd = malloc(sizeof(struct passwd));

    char *token = strtok(str, ":");
    pwd->username = strdup(token);

    token = strtok(NULL, ":");
    pwd->hashed_password = strdup(token);

    token = strtok(NULL, ":");
    pwd->uid = strdup(token);

    token = strtok(NULL, ":");
    pwd->gid = strdup(token);

    token = strtok(NULL, ":");
    pwd->gecos = strdup(token);

    token = strtok(NULL, ":");
    pwd->home_path = strdup(token);

    token = strtok(NULL, ":");
    pwd->login_shell = strdup(token);

    return pwd;
}


int main(int argc, char **argv) {
    struct passwd_list *passwd_list = malloc(sizeof(struct passwd_list));
    passwd_list->passwd = NULL;
    passwd_list->next = NULL;

    FILE *fptr = fopen("/etc/passwd", "r");
    char buff[BUFSIZ];

    while (fgets(buff, BUFSIZ, fptr)) {
        if (buff[0] == '#') continue;

        struct passwd_list *buf = passwd_list;

        struct passwd *pwd = parser_passwd(buff);

        while (buf->next != NULL) {
            buf = buf->next;
        }
        buf->next = NULL;
        buf->passwd = pwd;

        // for (buf = passwd_list; buf->next == NULL; buf = buf->next) {
            // buf->passwd = pwd;
            // buf->next = NULL;
        // }
        // break;
        // printf("%s", buff);
    }

    free(passwd_list);
    return 0;
}