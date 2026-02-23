#include "http.h"
#include "server.h"
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  // Log output immediately for real-time debugging
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  int server_fd = generate_server_fd();

  setup_server_socket(server_fd);

  printf("Waiting for a client to connect...\n");

  // Keep connection open
  while (1) {
    // Generate client file descriptor
    int client_fd = generate_client_fd(server_fd);

    // Generate buffer that holds the request string
    char *buffer = generate_buffer(client_fd, server_fd);
    printf("Received request:\n%s\n", buffer);

    // Parse method, path, and version from the buffer
    char method[16], path[256], version[16];
    if (parse_request_line(buffer, method, path, version) == 0) {
      printf("Method: %s, Path: %s, Version: %s\n", method, path, version);
    } else {
      printf("Failed to parse request line\n");
    }

    // Get the HTTP response based on path requested
    const char *http_response = get_http_response(path);

    // Send the response
    send(client_fd, http_response, strlen(http_response), 0);

    // Close the file descriptor for next connection
    close(client_fd);
  }

  close(server_fd);

  return 0;
}
