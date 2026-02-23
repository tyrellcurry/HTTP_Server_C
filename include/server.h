#ifndef SERVER_H
#define SERVER_H

int generate_server_fd();
int generate_client_fd(int server_fd);
char *generate_buffer(int client_fd, int server_fd);
int setup_server_socket(int server_fd);

#endif
