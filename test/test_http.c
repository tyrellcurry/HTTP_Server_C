#include "unity_internals.h"
#define UNITY_VERBOSE_OUTPUT
#include "http.h"
#include "unity.h"
#include <string.h>

char buffer[4096];

void setUp(void) { strcpy(buffer, "GET /hello HTTP/1.1"); }

void tearDown(void) {}

/**
 * Test: Parse HTTP path
 */
void test_root_path_returns_200(void) {
  const char *response = get_http_response("/");
  TEST_ASSERT_TRUE(strstr(response, "200") != NULL);
}

void test_other_path_returns_404(void) {
  const char *response = get_http_response("/other");
  TEST_ASSERT_TRUE(strstr(response, "404") != NULL);
}

void test_parse_line_request() {
  char method[16], path[256], version[16];
  int result = parse_request_line(buffer, method, path, version);
  TEST_ASSERT_EQUAL(0, result);
  TEST_ASSERT_EQUAL_STRING("GET", method);
  TEST_ASSERT_EQUAL_STRING("/hello", path);
  TEST_ASSERT_EQUAL_STRING("HTTP/1.1", version);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_root_path_returns_200);
  RUN_TEST(test_other_path_returns_404);
  RUN_TEST(test_parse_line_request);
  return UNITY_END();
}
