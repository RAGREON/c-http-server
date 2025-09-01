#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
  OK = 200, 
  NOT_FOUND = 404
} StatusCode;

typedef struct {
  StatusCode    status_code; 
  char          data[50];
} Response;

char* create_http_response(Response* response);