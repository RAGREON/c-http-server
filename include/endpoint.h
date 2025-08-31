#pragma once

#include "./shared.h"
#include "./request.h"
#include "./response.h"

typedef struct {
  char      url[256];
  Response*  (*controller)(Request*);
} EndPoint;


EndPoint* create_endpoint(const char* url, Response* (*controller)(Request*));