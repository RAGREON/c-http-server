#pragma once

#include "./shared.h"
#include "./socket.h"
#include "./request.h"
#include "./response.h"

Socket* create_server_socket(const char* address, int port);
int client_connect(Socket* server_socket);
int send_message(Socket* server_socket, const void* data, size_t length);
int send_credentials(Socket* server_socket, Credentials* credentials);
int send_request(Socket* server_socket, Request* request);