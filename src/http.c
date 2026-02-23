#include "http.h"
#include <stdio.h>
#include <string.h>

const char *get_http_response(const char *path) {
  if (strcmp(path, "/") == 0) {
    return "HTTP/1.1 200 OK\r\n\r\n";
  }
  return "HTTP/1.1 404 OK\r\n\r\n";
}

int parse_request_line(char *buffer, char *method, char *path, char *version) {
  if (sscanf(buffer, "%15s %255s %15s", method, path, version) == 3) {
    return 0;
  } else {
    return -1;
  }
}
