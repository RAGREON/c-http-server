#include "./include/client.h"

int main(int argc, char** argv) {
  WinSock* winsock = initialize_winsock();

  Socket* server_socket = create_server_socket("127.0.0.1", 8080);

  client_connect(server_socket);

  printf("sending request...\n");

  Request request = { POST };
  strcpy(request.endpoint_url, "/api/users");

  send_request(server_socket, &request);
 
  return 0;
}