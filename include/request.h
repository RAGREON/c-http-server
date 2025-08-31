#pragma once

typedef enum {
  GET, POST, PUT, DEL
} RequestType;

typedef struct {
  RequestType   type;
  char          endpoint_url[256];
} Request;