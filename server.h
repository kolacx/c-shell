#ifndef SERVER_H
#define SERVER_H

void start_server(char *ip, int port);
int create_socket(void);
struct sockaddr_in *create_address(char *ip, int port);
void bind_socket(int socket_fd, struct sockaddr_in *address);
void create_listener(int socket_fd, struct sockaddr_in *address, int connection_count);
void accept_client(int socket_fd, struct sockaddr_in *address);
void receive_client(int client_fd);
void answer_client(int client_fd, char * str);


#endif //SERVER_H
