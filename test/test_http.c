#include "unity_internals.h"
#define UNITY_VERBOSE_OUTPUT
#include "http.h"
#include "unity.h"
#include <string.h>

void setUp(void) {}

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

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_root_path_returns_200);
  RUN_TEST(test_other_path_returns_404);
  return UNITY_END();
}
