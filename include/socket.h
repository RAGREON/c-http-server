#pragma once

#include "./shared.h"

#define BUFFER_CHUNK 1024

typedef struct {
  WSADATA             winsock_data;
} WinSock;

typedef struct {
  SOCKET              descriptor;
  struct sockaddr_in  address; 
} Socket;

WinSock* initialize_winsock();

Socket* create_socket(int port);
Socket* set_address(Socket* _socket, const char* address);
Socket* bind_socket(Socket* _socket);
void listen_socket(Socket* _socket, int max_connection);
int socket_send_message(Socket* _socket, const void* data, size_t length, int send_http);
void* socket_recv_message(Socket* _socket, size_t* out_size);
int socket_send_http(Socket* _socket, Response* http_response);