#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "commands.h"
#include "server.h"


int main(int argc, char **argv) {
    start_server("", 23);
    // printf("$ ");
    // char buffer[BUFSIZ];
    // while (fgets(buffer, sizeof buffer, stdin)) {
        // buffer[strcspn(buffer, "\r\n")] = '\0';
        // parse_command(buffer);
        // printf("$ ");
    // }

    return 0;
}
