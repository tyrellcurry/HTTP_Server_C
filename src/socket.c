#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

struct AddrResult {
  struct addrinfo *servinfo;
  int error_code;
};

struct AddrResult generateAddrInfo() {
  struct AddrResult result = {0};
  struct addrinfo hints;
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  result.error_code = getaddrinfo(NULL, "3490", &hints, &result.servinfo);
  return result;
}

// temp name to main for development/testing
int main() {
  struct AddrResult result = generateAddrInfo();
  if (result.error_code != 0) {
    fprintf(stderr, "Error: %s\n", gai_strerror(result.error_code));
  } else {
    freeaddrinfo(result.servinfo);
  }
}
