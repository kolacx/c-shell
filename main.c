#include <stdio.h>
#include <string.h>

#include "users.h"
#include "commands.h"

// lshell# adduser ivan
// lshell# listusers
// 1. ivan
// lshell#


int main(int argc, char **argv) {
    printf("$ ");
    char buffer[BUFSIZ];
    while (fgets(buffer, sizeof buffer, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        parse_command(buffer);
        printf("$ ");
    }
    return 0;
}
