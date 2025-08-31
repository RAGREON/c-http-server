#include "./include/server.h"

Response* get_webpage(Request* request) {
  char html[] = "<h1>Hello World</h1>";

  Response* response = (Response*)malloc(sizeof(Response));
  response->status_code = OK;
  strcpy(response->data, html);

  // printf("data: %s\n", response->data);

  return response;
}

int main() {
  printf("creating server:\n");
  Server* server = create_server(8080);

  if (server) {
    printf("server created successfully\n");
  }
  else {
    printf("server creation failed\n");
    return 1;
  }

  printf("\n");
  
  add_endpoint(server, "/api/page", get_webpage);

  server_listen(server, 100);

  return 0;
}