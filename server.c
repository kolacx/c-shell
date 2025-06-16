#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "server.h"

#include "commands.h"


void start_server(char *ip, int port) {
    int socket_fd = create_socket();
    struct sockaddr_in *address = create_address(ip, port);
    bind_socket(socket_fd, address);
    create_listener(socket_fd, address, 10);
    accept_client(socket_fd, address);

    free(address);
    shutdown(socket_fd, SHUT_RDWR);
}

int create_socket(void) {
    int result_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (result_socket < 0) {
        perror("Fail create socket");
    }
    printf("Socket successfully created\n");
    return result_socket;
}

struct sockaddr_in *create_address(char *ip, int port) {
    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));

    address->sin_family = AF_INET;
    address->sin_port = htons(port);

    if (strlen(ip) == 0) {
        address->sin_addr.s_addr = INADDR_ANY;
    } else {
        inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    }

    printf("Address successfully created\n");
    return address;
}

void bind_socket(int socket_fd, struct sockaddr_in *address) {
    int result = bind(socket_fd, (struct sockaddr *)address, sizeof(struct sockaddr_in));
    if (result < 0) {
        perror("Bind failed");
        close(socket_fd);
        exit(1);
    }
    printf("Bind successful\n");
}

void create_listener(int socket_fd, struct sockaddr_in *address, int connection_count) {
    int listen_result = listen(socket_fd, connection_count);
    if (listen_result < 0) {
        perror("Fail create listener");
        exit(1);
    }
    printf("Listening on http://%s:%d\n\n",
           inet_ntoa(address->sin_addr),
           ntohs(address->sin_port));
}

void accept_client(int socket_fd, struct sockaddr_in *address) {
    while (1) {
        int client_fd;
        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);

        client_fd = accept(socket_fd, (struct sockaddr *) &client_address, &client_len);
        if (client_fd < 0) {
            printf("Fail accept client");
            close(client_fd);
        }

        printf("Client connected: %s:%d\n",
               inet_ntoa(client_address.sin_addr),
               ntohs(client_address.sin_port));

        char *disconnect_text = "For close send: exit\n";
        write(client_fd, disconnect_text, strlen(disconnect_text));

        char *enter = "$ ";
        write(client_fd, enter, strlen(enter));
        receive_client(client_fd);
    }
}


void receive_client(int client_fd) {
    char buffer[BUFSIZ];

    while (1) {
        ssize_t read_client = read(client_fd, buffer, BUFSIZ);
        if (read_client < 0) break;

        buffer[strcspn(buffer, "\r\n")] = '\0';
        if (strcmp(buffer, "exit") == 0) break;

        printf("Receive from client: %s\n", buffer);

        parse_command(buffer, client_fd);
        char *enter = "$ ";
        write(client_fd, enter, strlen(enter));

        // answer_client(client_fd, buffer);
    }
    close(client_fd);
}

void answer_client(int client_fd, char * str) {
    char buffer[BUFSIZ];
    char answer[BUFSIZ] = "server: ";

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        strcat(answer, buffer);
        write(client_fd, answer, strlen(answer));
    }
}