#define UNITY_VERBOSE_OUTPUT
#include "unity.h"
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

static int test_socket_fd = -1;

void setUp(void) {
  // reusable socket run on each test
  test_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
}

void tearDown(void) {
  // close open socket, run on each test
  if (test_socket_fd >= 0) {
    close(test_socket_fd);
    test_socket_fd = -1;
  }
}

/**
 * Test: socket creation
 */
void test_socket_creation(void) {
  TEST_ASSERT_TRUE(test_socket_fd >= 0);
  close(test_socket_fd);
}

/**
 * Test: bind to port
 */
void test_socket_bind(void) {
  int reuse = 1;
  setsockopt(test_socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
  struct sockaddr_in serv_addr = {
      .sin_family = AF_INET,
      .sin_port = htons(4222), // 4222 - port for testing
      .sin_addr = {htonl(INADDR_ANY)},
  };
  int result =
      bind(test_socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  TEST_ASSERT_EQUAL(0, result);
  close(test_socket_fd);
}

/**
 * Test: HTTP request parsing
 */
void test_parse_http_request(void) {
  const char *request =
      "GET /echo/helloworld HTTP/1.1\r\nHost: localhost\r\n\r\n";
  char method[16], path[256], version[16];
  int parsed = sscanf(request, "%15s %255s %15s", method, path, version);
  TEST_ASSERT_EQUAL(3, parsed);
  TEST_ASSERT_EQUAL_STRING("GET", method);
  TEST_ASSERT_EQUAL_STRING("/echo/helloworld", path);
  TEST_ASSERT_EQUAL_STRING("HTTP/1.1", version);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_socket_creation);
  RUN_TEST(test_socket_bind);
  RUN_TEST(test_parse_http_request);
  return UNITY_END();
}
