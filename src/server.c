#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int generate_server_fd() {
  int server_fd;

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == -1) {
    printf("Socket creation failed: %s...\n", strerror(errno));
    return 1;
  }
  return server_fd;
}

int generate_client_fd(int server_fd) {
  socklen_t client_addr_len;
  struct sockaddr_in client_addr;
  client_addr_len = sizeof(client_addr);

  int client_fd =
      accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
  if (client_fd == -1) {
    printf("Socket creation failed: %s...\n", strerror(errno));
    return 1;
  }
  printf("Client connected\n");
  return client_fd;
}

char *generate_buffer(int client_fd, int server_fd) {
  char *buffer = malloc(4096);

  if (buffer == NULL) {
    printf("malloc failed\n");
    return NULL;
  }

  ssize_t bytes_read = read(client_fd, buffer, 4095);

  if (bytes_read < 0) {
    printf("Read failed: %s\n", strerror(errno));
    close(client_fd);
    close(server_fd);
    free(buffer);
    return NULL;
  }

  buffer[bytes_read] = '\0';

  return buffer;
}

int reuse_socket_for_development(int server_fd) {
  int reuse = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) <
      0) {
    printf("setsockopt failed: %s\n", strerror(errno));
    return 1;
  }
  return 0;
}

int setup_server_socket(int server_fd) {
  reuse_socket_for_development(server_fd);

  struct sockaddr_in serv_addr = {
      .sin_family = AF_INET,
      .sin_port = htons(4221),
      .sin_addr = {htonl(INADDR_ANY)},
  };

  if (bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0) {
    printf("Bind failed: %s \n", strerror(errno));
    return 1;
  }

  int connection_backlog = 5;
  if (listen(server_fd, connection_backlog) != 0) {
    printf("Listen failed: %s \n", strerror(errno));
    return 1;
  }
  return 0;
}
