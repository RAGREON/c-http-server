#include "./client.h"

Socket* create_server_socket(const char* address, int port) {
  Socket* _socket = create_socket(port);
  set_address(_socket, address);
  return _socket;
}

int client_connect(Socket* server_socket) {
  int rc = connect(server_socket->descriptor, (struct sockaddr*)&server_socket->address, sizeof(server_socket->address));

  if (rc == SOCKET_ERROR) {
    WSA_ERROR("connection to server failed");
    return 0;
  }

  printf("connected to server:\n");
  return 1; 
}

int send_message(Socket* server_socket, const void* data, size_t length) {
  int bytes_sent = send(server_socket->descriptor, (const char*)data, length, 0);

  if (bytes_sent == SOCKET_ERROR) {
    WSA_ERROR("send failed");
    return -1;
  }

  return bytes_sent;
}

Response recv_response(Socket* server_socket) {
  Response response;

  int bytes = recv(server_socket->descriptor, (char*)&response, sizeof(response), 0); 

  if (bytes == SOCKET_ERROR) {
    WSA_ERROR("no response");
  }

  return response;
}

int send_credentials(Socket* server_socket, Credentials* credentials) {
  int bytes = send_message(server_socket, credentials, sizeof(*credentials));
  return bytes;
}

int send_request(Socket* server_socket, Request* request) {
  int bytes_sent = socket_send_message(server_socket, request, sizeof(*request));

  if (bytes_sent < 0) {
    printf("failed to send reqeust\n");
  }

  size_t response_size;

  Response* response = (Response*)socket_recv_message(server_socket, &response_size);
  // char* byte_string = (char*)raw;
  // if (raw && response_size == sizeof(Response)) {
  //   memcpy(&response, raw, sizeof(Response));
  //   free(raw);
  // }

  // for (int i = 0; i < response_size; i++) {
  //   printf("%d ", byte_string[i]);
  // }

  printf("\n");

  printf("size: %d\n", sizeof(*response));
  printf("response:\n");
  printf("status code: %d\n", response->status_code);
  printf("string length: %d\n", strlen(response->data));
  printf("data: %s\n", response->data);

  return 1;
}