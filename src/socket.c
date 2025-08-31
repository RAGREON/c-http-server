#include "../include/socket.h"

WinSock* initialize_winsock() {
  WinSock* winsock = (WinSock*)malloc(sizeof(WinSock));

  int rc = WSAStartup(MAKEWORD(2, 2), &winsock->winsock_data);

  if (rc != 0) {
    WSA_ERROR("winsock intialization");
    return NULL;
  }

  return winsock;
}

Socket* create_socket(int port) {
  Socket* _socket = (Socket*)malloc(sizeof(Socket));

  _socket->descriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (_socket->descriptor == INVALID_SOCKET) {
    WSA_ERROR("socket creation");
    return NULL;
  }

  _socket->address.sin_family = AF_INET;
  _socket->address.sin_addr.s_addr = INADDR_ANY;  
  _socket->address.sin_port = htons(port);

  return _socket;
}

Socket* set_address(Socket* _socket, const char* address) {
  _socket->address.sin_addr.s_addr = inet_addr(address);

  return _socket;
}

Socket* bind_socket(Socket* _socket) {
  int rc = bind(_socket->descriptor, (struct sockaddr*)&_socket->address, sizeof(_socket->address));

  if (rc == SOCKET_ERROR) {
    WSA_ERROR("binding failed");
    return NULL;
  }

  return _socket;
}

void listen_socket(Socket* _socket, int max_connection) {
  listen(_socket->descriptor, max_connection);
}

int socket_send_message(Socket* _socket, const void* data, size_t length) {
  uint32_t net_length = htonl((uint32_t)length);

  int bytes_sent = send(_socket->descriptor, (char*)&net_length, sizeof(net_length), 0);
  if (bytes_sent != sizeof(net_length))
    return -1;

  size_t total_sent = 0;
  const char* buffer = (const char*)data;

  while (total_sent < length) {
    int sent = send(_socket->descriptor, buffer + total_sent, length - total_sent, 0);
    if (sent < 0) return -1;
    total_sent += sent;
  }

  return (int)total_sent;
}

void* socket_recv_message(Socket* _socket, size_t* out_size) {
  uint32_t net_length;
  int bytes = recv(_socket->descriptor, (char*)&net_length, sizeof(net_length), 0);

  if (bytes <= 0) return NULL;

  size_t length = ntohl(net_length);

  char* buffer = malloc(length);
  size_t total_recv = 0;

  while (total_recv < length) {
    int bytes_recv = recv(_socket->descriptor, buffer + total_recv, length - total_recv, 0);
    if (bytes_recv <= 0) {
      free(buffer);
      return NULL;
    }
    total_recv += bytes_recv;
  }

  if (out_size) 
    *out_size = total_recv; 

  return buffer;
}