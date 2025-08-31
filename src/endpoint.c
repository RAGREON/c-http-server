#include "./endpoint.h"

EndPoint* create_endpoint(const char* url, Response* (*controller)(Request*)) {
  EndPoint* endpoint = (EndPoint*)malloc(sizeof(EndPoint));

  strcpy(endpoint->url, url);
  endpoint->controller = controller;

  return endpoint;
}