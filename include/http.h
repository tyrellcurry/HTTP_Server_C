#ifndef HTTP_H
#define HTTP_H

#define MAX_HEADERS 32
#define MAX_HEADER_NAME 64
#define MAX_HEADER_VALUE 512
#define MAX_METHOD 16
#define MAX_PATH 2048
#define MAX_VERSION 16

const char *get_http_response(const char *path);
int parse_request_line(char *buffer, char *method, char *path, char *version);
#endif
