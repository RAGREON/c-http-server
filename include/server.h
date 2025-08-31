#pragma once

#include "./shared.h"
#include "./request.h"
#include "./response.h"
#include "./socket.h"
#include "./endpoint.h"

#define BUFFER_SIZE 4028

typedef struct {
  WinSock*    winsock;
  Socket*     socket;
  int         port;
  EndPoint**  endpoints;
  int         endpoint_count;
} Server;

Server* create_server(int port);
int accept_connection(Socket* server_socket, Socket* client_socket);
void server_listen(Server* server, int max_connection);
void* handle_client(void* arg);
Response* auth_endpoint(Request* request);
void add_endpoint(Server* server, const char* url, Response* (*controller)(Request*));
void handle_endpoint(Server* server, Request* request, Response** response);

typedef struct {
  Socket*     client_socket;
  Server*     server;
} ThreadData;