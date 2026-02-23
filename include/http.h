#ifndef HTTP_H
#define HTTP_H
const char *get_http_response(const char *path);
int parse_request_line(char *buffer, char *method, char *path, char *version);
#endif
