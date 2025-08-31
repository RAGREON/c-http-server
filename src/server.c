#include "../include/server.h"

Server* create_server(int port) {
  Server* server = (Server*)malloc(sizeof(Server));

  server->port = port;

  server->winsock = initialize_winsock();
  if (server->winsock == NULL) {
    printf("winsock initialization failed\n");
    return NULL;
  }

  server->socket = create_socket(port);
  bind_socket(server->socket);

  server->endpoints = (EndPoint**)malloc(10 * sizeof(EndPoint*));
  for (int i = 0; i < 10; i++) {
    server->endpoints[i] = (EndPoint*)malloc(sizeof(EndPoint));
  }

  server->endpoint_count = 0;

  return server;
}

int accept_connection(Socket* server_socket, Socket* client_socket) {
  int client_sock_length = sizeof(client_socket->address);

  client_socket->descriptor = accept(
    server_socket->descriptor,
    (struct sockaddr*)&client_socket->address,
    &client_sock_length
  ); 
 
  if (client_socket->descriptor == INVALID_SOCKET) {
    WSA_ERROR("client socket accept failed");
    return 0;
  }

  printf("connection accepted\n");
  return 1;
}

void server_listen(Server* server, int max_connection) {
  listen_socket(server->socket, max_connection);
  
  printf("server is listening on port: %d\n", server->port);
  printf("max connections: %d\n\n", max_connection);
  
  printf("listening for incoming connections:\n");
  while (1) {
    Socket* client_socket = (Socket*)malloc(sizeof(Socket));

    if (!accept_connection(server->socket, client_socket)) {
      free(client_socket);
      continue;
    }

    ThreadData* thread_data = (ThreadData*)malloc(sizeof(ThreadData));
    thread_data->client_socket = client_socket;
    thread_data->server = server;

    pthread_t client_thread;
    pthread_create(&client_thread, NULL, handle_client, thread_data);
    pthread_detach(client_thread);
  }
}

void* handle_client(void* arg) {
  ThreadData* data = (ThreadData*)arg;

  Socket* client_socket = data->client_socket;
  Server* server = data->server;

  while (1) {
    Request* request = (Request*)socket_recv_message(client_socket, NULL);

    printf("request:\n");
    printf("request type: %d\n", request->type);
    printf("request endpoint: %s\n", request->endpoint_url);

    Response* response = NULL;
    printf("size: %d\n", sizeof(response));

    handle_endpoint(server, request, &response);

    printf("code: %d\n", response->status_code);
    printf("data: %s\n", response->data);

    printf("size: %d\n", sizeof(*response));

    int sent = socket_send_message(client_socket, response, sizeof(*response));
    printf("sent: %d\n", sent);

    closesocket(client_socket->descriptor);
    break;
  } 

  free(client_socket);

  printf("connection closed to client\n");
}

Response* auth_endpoint(Request* request) {
  printf("\n");
  
  printf("auth endpoint controller has been called\n");
  printf("request:\n");
  printf("request type: %d\n", request->type);
  printf("request endpoint: %s\n", request->endpoint_url);

  printf("\n");

  Response* response = (Response*)malloc(sizeof(Response));
  response->status_code = OK;

  return response;
}


void add_endpoint(Server* server, const char* url, Response* (*controller)(Request*)) {
  server->endpoints[server->endpoint_count++] = create_endpoint(url, controller);
}

void handle_endpoint(Server* server, Request* request, Response** response) {
  printf("\n");
  printf("handle endpoint called\n");
  *response = server->endpoints[0]->controller(request);
}
