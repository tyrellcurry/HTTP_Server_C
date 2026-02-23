#include "http.h"
#include "server.h"
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  // Disable output buffering
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  int server_fd = generate_server_fd();

  // Reuse port
  int reuse = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) <
      0) {
    printf("setsockopt failed: %s\n", strerror(errno));
    return 1;
  }

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

  printf("Waiting for a client to connect...\n");

  int client_fd = generate_client_fd(server_fd);

  char buffer[4096];

  ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
  if (bytes_read < 0) {
    printf("Read failed: %s\n", strerror(errno));
    close(client_fd);
    close(server_fd);
    return 1;
  }

  // Null-terminate the buffer so we can use string functions
  buffer[bytes_read] = '\0';

  // Now parse the HTTP request
  printf("Received request:\n%s\n", buffer);

  // Extract the request line (first line)
  char method[16], path[256], version[16];
  if (sscanf(buffer, "%15s %255s %15s", method, path, version) == 3) {
    printf("Method: %s, Path: %s, Version: %s\n", method, path, version);
  } else {
    printf("Failed to parse request line\n");
  }

  const char *http_response = get_http_response(path);

  send(client_fd, http_response, strlen(http_response), 0);

  close(server_fd);
  close(client_fd);

  return 0;
}
