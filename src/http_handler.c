#include "http_handler.h"
#include <string.h>

const char *get_http_response(const char *path) {
  if (strcmp(path, "/") == 0) {
    return "HTTP/1.1 200 OK\r\n\r\n";
  }
  return "HTTP/1.1 404 OK\r\n\r\n";
}
